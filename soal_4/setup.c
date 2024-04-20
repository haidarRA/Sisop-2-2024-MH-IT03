#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#define MAX_APPS 10
#define MAX_NAME_LENGTH 50

// Global array to store child process IDs
pid_t child_processes[MAX_APPS];
int num_child_processes = 0;

// Function to run an app
void run_app(char *app_name, int num_windows) {
    FILE *file = fopen("def.log", "a");
    printf("Opening %d windows of %s\n", num_windows, app_name);
    for (int i = 0; i < num_windows; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            execlp(app_name, app_name, NULL);
            perror("Execlp failed");
            exit(1);
        } else if (pid > 0) {
            // Store child process ID
            child_processes[num_child_processes] = pid;
            fprintf(file, "%d\n", child_processes[num_child_processes]);
            num_child_processes++;
        } else {
            perror("Fork failed");
            exit(1);
        }
    }
    fclose(file);
}

void run_apps_from_config(char *config_file) {
    FILE *file = fopen(config_file, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Create log file name
    char log_file[MAX_NAME_LENGTH + 5]; // 5 for ".log\0"
    strcpy(log_file, config_file);
    strcat(log_file, ".log");

    // Open log file
    FILE *log = fopen(log_file, "a");
    if (log == NULL) {
        perror("Error opening log file");
        exit(EXIT_FAILURE);
    }

    char app_name[MAX_NAME_LENGTH];
    int num_windows;

    while (fscanf(file, "%s %d", app_name, &num_windows) != EOF) {
        //fprintf(log, "Running %s with %d windows\n", app_name, num_windows);
        // Assuming run_app() is a function you've defined elsewhere
        // This is where you'd call run_app()
	printf("Opening %d windows of %s\n", num_windows, app_name);
	for (int i = 0; i < num_windows; i++) {
	    pid_t pid = fork();
	    if (pid == 0) {
		execlp(app_name, app_name, NULL);
		perror("Execlp failed");
		exit(1);
	    } 
	    else if (pid > 0) {
		// Store child process ID
		child_processes[num_child_processes] = pid;
		fprintf(log, "%d\n", child_processes[num_child_processes]);
		num_child_processes++;
	    } 
	    else {
		perror("Fork failed");
		exit(1);
	    }
	}
    }

    fclose(file);
    fclose(log);
}

void kill_default() {
    FILE *file = fopen("def.log", "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int pid;
    printf("Closing all applications\n");

    while (fscanf(file, "%d", &pid) != EOF) {
	kill(pid, SIGTERM);
    }

    fclose(file);
    remove("def.log");
}

void kill_conf(char *config_file) {
    char log_file[MAX_NAME_LENGTH + 5]; // 5 for ".log\0"
    strcpy(log_file, config_file);
    strcat(log_file, ".log");

    // Open log file
    FILE *file = fopen(log_file, "r");
    if (file == NULL) {
        perror("Error opening log file");
        exit(EXIT_FAILURE);
    }

    int pid;
    printf("Closing all applications\n");

    while (fscanf(file, "%d", &pid) != EOF) {
	kill(pid, SIGTERM);
    }

    fclose(file);
    remove(log_file);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s [-o <app1> <num1> <app2> <num2> ... | -f <config_file> | -k | -k <config_file>]\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "-o") == 0) {
        for (int i = 2; i < argc; i += 2) {
            char *app_name = argv[i];
            int num_windows = atoi(argv[i + 1]);
            run_app(app_name, num_windows);
        }
    } 
    else if (strcmp(argv[1], "-f") == 0) {
        if (argc != 3) {
            printf("Usage: %s -f <config_file>\n", argv[0]);
            return 1;
        }
        run_apps_from_config(argv[2]);
    } 
    else if (strcmp(argv[1], "-k") == 0) {
        if (argc == 2) {
            kill_default();
        }
        else if (argc == 3) {
            kill_conf(argv[2]);
        }
    } 
    else {
        printf("Invalid option\n");
        return 1;
    }

    return 0;
}
