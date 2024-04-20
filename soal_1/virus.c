#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <dirent.h>
#include <limits.h>
#include <time.h>

void replace(char *str, const char *oldWord, const char *newWord) {
    char *pos, temp[1000];
    int index = 0;
    int owlen = strlen(oldWord);

    while ((pos = strstr(str, oldWord)) != NULL) {
        strcpy(temp, str);
        index = pos - str;
        str[index] = '\0';
        strcat(str, newWord);
        strcat(str, temp + index + owlen);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <directory>\n", argv[0]);
        return 1;
    }

    pid_t pid, sid;

    pid = fork();

    if (pid < 0) {
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    umask(0);

    sid = setsid();
    if (sid < 0) {
        exit(EXIT_FAILURE);
    }

    if ((chdir(argv[1])) < 0) {
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    openlog("virus_daemon", LOG_PID, LOG_DAEMON);

    while (1) {
        DIR *dir = opendir(".");
        if (dir == NULL) {
            syslog(LOG_ERR, "Failed to open directory: %s", strerror(errno));
            exit(EXIT_FAILURE);
        }

        struct dirent *file;
        while ((file = readdir(dir)) != NULL) {
            if (strcmp(file->d_name, ".") == 0 || strcmp(file->d_name, "..") == 0) {
                continue;
            }

            FILE *fptr = fopen(file->d_name, "r");
            if (fptr == NULL) {
                syslog(LOG_ERR, "Failed to open file: %s", strerror(errno));
                continue;
            }

            FILE *ftemp = fopen("replace.tmp", "w");
            if (ftemp == NULL) {
                syslog(LOG_ERR, "Failed to create temporary file: %s", strerror(errno));
                fclose(fptr);
                continue;
            }

            char line[1000];
            int marked = 0;
            while (fgets(line, sizeof(line), fptr)) {
                if (strstr(line, "m4LwAr3") || strstr(line, "5pYw4R3") || strstr(line, "R4nS0mWaR3")) {
                    replace(line, "m4LwAr3", "[MALWARE]");
                    replace(line, "5pYw4R3", "[SPYWARE]");
                    replace(line, "R4nS0mWaR3", "[RANSOMWARE]");
                    marked = 1;
                }
                fputs(line, ftemp);
            }

            fclose(fptr);
            fclose(ftemp);
            if (marked) {
                FILE *flog = fopen("virus.log", "a");
                if (flog != NULL) {
                    char date[25];
                    time_t current_time = time(NULL);
                    strftime(date, 25, "[%d-%m-%Y][%H:%M:%S]", localtime(&current_time));
                    fprintf(flog, "%s Suspicious string in %s successfully replaced!\n", date, file->d_name);
                    fclose(flog);
                } else {
                    syslog(LOG_ERR, "Failed to open log file: %s", strerror(errno));
                }
            }

            remove(file->d_name);
            rename("replace.tmp", file->d_name);
        }

        closedir(dir);
        sleep(15);
    }

    closelog();
    return 0;
}
