#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_USERNAME_LENGTH 20
#define MAX_LOG_LENGTH 100

int monitoring_active = 0;

int file_exists(const char *path) {
    return access(path, F_OK) == 0;
}

void delete_line(char *file_name, char *string) {
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        printf("Error: Unable to open file %s.\n", file_name);
        return;
    }

    FILE *temp_file = fopen("temp.txt", "w");
    if (temp_file == NULL) {
        printf("Error: Unable to create temporary file.\n");
        fclose(file);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, string) == NULL) {
            fputs(line, temp_file);
        }
    }

    fclose(file);
    fclose(temp_file);

    if (remove(file_name) != 0) {
        printf("Error: Unable to delete file %s.\n", file_name);
        return;
    }

    if (rename("temp.txt", file_name) != 0) {
        printf("Error: Unable to rename temporary file.\n");
        return;
    }

    //printf("Line containing \"%s\" deleted successfully from %s.\n", string, file_name);
}

int check_line(char *file_name, char *string) {
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        printf("Error: Unable to open file %s.\n", file_name);
        exit(EXIT_FAILURE);
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, string) != NULL) {
	    return 1;
        }
    }
    return 0;
}

void print_options() {
    printf("Opsi:\n");
    printf("  -m : Memulai pemantauan proses pengguna\n");
    printf("  -s : Menghentikan pemantauan proses pengguna\n");
    printf("  -c : Mengendalikan proses pengguna\n");
    printf("  -a : Melepaskan kendali atas proses pengguna\n");
}

//YA ALLAH FORMAT DARI TADI GA BENER TERUS
//FUCK EMU OTORI
void log_action(char *username, pid_t pid, char *process_name, int status) {
    time_t now;
    struct tm *local_time;
    char timestamp[20];
    char log_message[MAX_LOG_LENGTH];

    now = time(NULL);
    local_time = localtime(&now);
    strftime(timestamp, sizeof(timestamp), "%d:%m:%Y-%H:%M:%S", local_time);

    if (status == 0) {
        snprintf(log_message, sizeof(log_message), "[%s]-%d-%s-GAGAL\n", timestamp, pid, process_name);
    } else {
        snprintf(log_message, sizeof(log_message), "[%s]-%d-%s-JALAN\n", timestamp, pid, process_name);
    }

    // Hapus waktu jika proses berjalan
    if (status == 1) {
        char *ptr = strchr(log_message, ']');
        memmove(ptr, ptr + 10, strlen(ptr + 10) + 1); // Hapus timestamp
    }

    char filename[MAX_USERNAME_LENGTH + 5];
    snprintf(filename, sizeof(filename), "%s.log", username);

    FILE *log_file = fopen(filename, "a");
    if (log_file == NULL) {
        perror("Error opening log file");
        exit(EXIT_FAILURE);
    }

    fputs(log_message, log_file);
    fclose(log_file);
}


void monitor_user_processes(char *username) {
    if (!file_exists("enable")) {
    	FILE *fdisable = fopen("enable", "w");
    	fclose(fdisable);
    }
    
    monitoring_active = 1;
    char command[MAX_COMMAND_LENGTH];
    pid_t pid;

    snprintf(command, sizeof(command), "ps -u %s", username);

    while (monitoring_active) {
        FILE *process_list = popen(command, "r");
        if (process_list == NULL) {
            perror("Error executing ps command");
            exit(EXIT_FAILURE);
        }

        char line[MAX_COMMAND_LENGTH];
        while (fgets(line, sizeof(line), process_list) != NULL) {
                // Skip header line
            if (strstr(line, "PID") != NULL)
                continue;
    
                // Extract PID and process name
            char *token = strtok(line, " ");
            pid_t pid = atoi(token);
            token = strtok(NULL, " ");
            char *process_name = strtok(NULL, "\n");
    
            if (pid != getpid()) {
                    // Log the process
                log_action(username, pid, process_name, 1);
            }
        }

        pclose(process_list);
        sleep(1);
    }
}


void stop_monitoring(char *username) {
    FILE *file = fopen("enable", "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int pid;
    char name[256];

    while (fscanf(file, "%s %d", name, &pid) != EOF) {
	if (check_line("enable", username)) {
	    kill(pid, SIGTERM);
	    delete_line("enable", username);
	}
    }

    fclose(file);
    
}

void control_user_process(char *username) {
    char command[MAX_COMMAND_LENGTH];
    pid_t pid;

    while (1) {
        snprintf(command, sizeof(command), "pgrep -u %s", username);

        FILE *process_list = popen(command, "r");
        if (process_list == NULL) {
            perror("Error executing pgrep command");
            exit(EXIT_FAILURE);
        }

        char line[MAX_COMMAND_LENGTH];
        while (fgets(line, sizeof(line), process_list) != NULL) {
            pid_t pid = atoi(line);
            kill(pid, SIGSTOP);
            log_action(username, pid, "unknown", 0); // Log as GAGAL since the process is being stopped forcibly
        }

        pclose(process_list);
        sleep(1);
    }
}

void release_control(char *username) {
    char command[MAX_COMMAND_LENGTH];
    pid_t pid;

    snprintf(command, sizeof(command), "pkill -SIGCONT -u %s", username);

    if (system(command) == -1) {
        perror("Error releasing control");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Penggunaan: %s <opsi> <username>\n", argv[0]);
        print_options();
        return EXIT_FAILURE;
    }

    char *option = argv[1];
    char *username = argv[2];
    FILE *enable = fopen("enable", "a");

    if (strcmp(option, "-m") == 0) {
        // Menjalankan fitur pemantauan
        printf("Memulai pemantauan proses pengguna untuk pengguna: %s\n", username);
        fflush(stdout); // Flush output buffer

        pid_t pid = fork();
        fprintf(enable, "%s %d\n", username, pid);
        if (pid < 0) {
            perror("Error forking process");
            return EXIT_FAILURE;
        } else if (pid == 0) {
            // Proses anak
            monitor_user_processes(username);
            exit(EXIT_SUCCESS);
        } else {
            // Proses induk
            printf("Pemantauan dimulai.\n");
            return EXIT_SUCCESS;
        }
    } else if (strcmp(option, "-s") == 0) {
        // Menghentikan fitur pemantauan
        printf("Menghentikan pemantauan proses pengguna untuk pengguna: %s\n", username);
        stop_monitoring(username);
    } else if (strcmp(option, "-c") == 0) {
        // Mengendalikan proses pengguna
        printf("Mengendalikan proses pengguna untuk pengguna: %s\n", username);
        control_user_process(username);
    } else if (strcmp(option, "-a") == 0) {
        // Melepaskan kendali atas proses pengguna
        printf("Melepaskan kendali atas proses pengguna untuk pengguna: %s\n", username);
        release_control(username);
    } else {
        printf("Opsi tidak valid: %s\n", option);
        print_options();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
