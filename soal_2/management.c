#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <sys/stat.h>
#include <minizip/unzip.h>
#include <string.h>
#include <zip.h>
#include <errno.h>
#include <zlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <ctype.h>
#include <time.h>
#include <fcntl.h>
#include <syslog.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>

int state = 0;
/*
1 = default
2 = backup
3 = restore
*/

int isexec = 0;
/*
0 = not executed yet
1 = executed
*/

int directory_exists(const char *path) {
    struct stat stats;

    stat(path, &stats);

    // Check for file existence
    if (S_ISDIR(stats.st_mode))
        return 1;

    return 0;
}

int download_file(const char* url, const char* filename) {
    CURL *curl;
    CURLcode res;
    FILE *fp;

    curl = curl_easy_init();
    if (curl) {
        fp = fopen(filename, "wb");
        if (fp) {
            curl_easy_setopt(curl, CURLOPT_URL, url);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, fwrite);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
            // Follow redirects
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
            res = curl_easy_perform(curl);
            /* Check for errors */
            if (res != CURLE_OK) {
                fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
                fclose(fp);
                curl_easy_cleanup(curl);
                return 1;
            }
            fclose(fp);
            curl_easy_cleanup(curl);
            return 0;
        } else {
            fprintf(stderr, "Error opening file %s\n", filename);
            curl_easy_cleanup(curl);
            return 1;
        }
    } else {
        fprintf(stderr, "curl_easy_init() failed\n");
        return 1;
    }
}

char cipher(char ch, int key) {
    if (!isalpha(ch)) {
	return ch;
    }
    char offset = isupper(ch) ? 'A' : 'a';
    return (char)((((ch + key) - offset) % 26) + offset);
}

char* decipher(char* input, int N) {
    int inputLen = strlen(input);
    char* output = (char*)malloc(inputLen + 1);
    int key = 26 - N;

    for (int i = 0; i < inputLen; ++i) {
	output[i] = cipher(input[i], key);
    }
    output[inputLen] = '\0';
    return output;
}

void defaultmode() {
    char date[25];
    int renamefile;
    
//    state = 1;
    
    const char* checkname = "library";
    char* user = getlogin();

    DIR *dir = opendir("library");
    if (dir == NULL) {
        fprintf(stderr, "Failed to open directory: %s", strerror(errno));
        exit(EXIT_FAILURE);
    }
    
    struct dirent *f1;
    while ((f1 = readdir(dir)) != NULL) {
        if (strcmp(f1->d_name, ".") == 0 || strcmp(f1->d_name, "..") == 0) {
            continue;
        }

        if (strstr(f1->d_name, "d3Let3")) {
            char delpath[256];
            sprintf(delpath, "%s/%s", checkname, f1->d_name);
            if (remove(delpath) != 0) {
                fprintf(stderr, "Failed to remove file: %s\n", delpath);
            }
            	
            FILE* flog = fopen("history.log", "a");
            if (flog != NULL) {
                time_t current_time = time(NULL);
                strftime(date, 25, "[%H:%M:%S]", localtime(&current_time));
                fprintf(flog, "[%s]%s - %s - Successfully deleted.\n", user, date, f1->d_name);
                fclose(flog);
            } 
            else {
                fprintf(stderr, "Failed to open log file");
            }
            fprintf(flog, "received signal SIGRTMIN\n");
        }
        else if (strstr(f1->d_name, "r3N4mE")) {
            char renamepath[256], destpath[256];
		
	    sprintf(renamepath, "%s/%s", checkname, f1->d_name);
	    if (strstr(f1->d_name, ".ts")) {
    	        sprintf(destpath, "%s/helper.ts", checkname); // Full destination path
    	        renamefile = rename(renamepath, destpath);
    		if(renamefile) {
                    fprintf(stderr, "Failed to rename file %s.\n", renamepath);
    	        }
	    }
	    else if (strstr(f1->d_name, ".py")) {
    		sprintf(destpath, "%s/calculator.py", checkname); // Full destination path
    		renamefile = rename(renamepath, destpath);
    		if(renamefile) {
           	    fprintf(stderr, "Failed to rename file %s.\n", renamepath);
    		}
	    }
	    else if (strstr(f1->d_name, ".go")) {
    	        sprintf(destpath, "%s/server.go", checkname); // Full destination path
    	        renamefile = rename(renamepath, destpath);
    	        if(renamefile) {
      	            fprintf(stderr, "Failed to rename file %s.\n", renamepath);
    	        }
	    }
	    else {
    		sprintf(destpath, "%s/renamed.file", checkname); // Full destination path
    		renamefile = rename(renamepath, destpath);
    	        if(renamefile) {
       	            fprintf(stderr, "Failed to rename file %s.\n", renamepath);
    	        }
	    }
		
	    FILE *flog = fopen("history.log", "a");
            if (flog != NULL) {
                time_t current_time = time(NULL);
                strftime(date, 25, "[%H:%M:%S]", localtime(&current_time));
                fprintf(flog, "[%s]%s - %s - Successfully renamed.\n", user, date, f1->d_name);
                fclose(flog);
            } 
            else {
                fprintf(stderr, "Failed to open log file");
            }
        }
    }
    closedir(dir);
}

void backupmode() {
    char date[25];
    int renamefile;
    
//    state = 2;

    const char* checkname = "library";
    char* user = getlogin();
    
    DIR *dir = opendir("library");
    if (dir == NULL) {
        fprintf(stderr, "Failed to open directory: %s", strerror(errno));
        exit(EXIT_FAILURE);
    }

    struct dirent *f2;
    while ((f2 = readdir(dir)) != NULL) {
        if (strcmp(f2->d_name, ".") == 0 || strcmp(f2->d_name, "..") == 0) {
            continue;
        }

        if (strstr(f2->d_name, "m0V3")) {
            char backpath[256], path2[256];
	    sprintf(backpath, "%s/%s", checkname, f2->d_name);
            sprintf(path2, "%s/backup/%s", checkname, f2->d_name);
    	    renamefile = rename(backpath, path2);
   	    if(renamefile) {
    		fprintf(stderr, "Failed to move file: %s.\n", backpath);
    	    }
    		
    	    FILE *flog = fopen("history.log", "a");
            if (flog != NULL) {
                time_t current_time = time(NULL);
                strftime(date, 25, "[%H:%M:%S]", localtime(&current_time));
                fprintf(flog, "[%s]%s - %s - Successfully moved to backup.\n", user, date, f2->d_name);
                fclose(flog);
            } 
            else {
                fprintf(stderr, "Failed to open log file");
            }
        }
    }
    closedir(dir);
}

void restoremode() {
    char date[25];
    int renamefile;

//    state = 3;

    const char* checkname = "library";
    char* user = getlogin();

    DIR* dir = opendir("library/backup");
    if (dir == NULL) {
        fprintf(stderr, "Failed to open directory: %s", strerror(errno));
        exit(EXIT_FAILURE);
    }

    struct dirent *f3;
    while ((f3 = readdir(dir)) != NULL) {
        if (strcmp(f3->d_name, ".") == 0 || strcmp(f3->d_name, "..") == 0) {
            continue;
        }

        if (strstr(f3->d_name, "m0V3")) {
            char respath[256], path3[256];
	    sprintf(respath, "%s/backup/%s", checkname, f3->d_name);
            sprintf(path3, "%s/%s", checkname, f3->d_name);
    	    renamefile = rename(respath, path3);
   	    if(renamefile) {
    	        fprintf(stderr, "Failed to move file: %s.\n", respath);
    	    }
    		
    	    FILE *flog = fopen("history.log", "a");
            if (flog != NULL) {
                time_t current_time = time(NULL);
                strftime(date, 25, "[%H:%M:%S]", localtime(&current_time));
                fprintf(flog, "[%s]%s - %s - Successfully moved from backup.\n", user, date, f3->d_name);
                fclose(flog);
            } 
            else {
                fprintf(stderr, "Failed to open log file");
            }
        }
    }
    closedir(dir);
}

static void sig_usr(int signo) {
    if (signo == SIGRTMIN) {
        defaultmode();
    } else if (signo == SIGUSR1) {
        backupmode();
    } else if (signo == SIGUSR2) {
        restoremode();
    }
}

int main(int argc, char *argv[]) {

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
    
    const char* pidlog = "pid.log";
    struct stat sb;
     	
    FILE *fpid;
    int isNew = 0;
    
    if (stat(pidlog, &sb) != 0) {
    	fpid = fopen(pidlog, "w");
	isNew = 1;
    	fclose(fpid);
    }
    
    fpid = fopen("pid.log", "r");
    if (fpid == NULL) {
    	fprintf(stderr, "Can't open the PID log\n");
    	exit(EXIT_FAILURE);
    }
    	    
    int closepid;
    while (fscanf(fpid, "%d", &closepid) != EOF) {
	kill(closepid, SIGTERM);
    }
    fclose(fpid);
    
    fpid = fopen("pid.log", "w");
    fprintf(fpid, "%d", sid);
    fclose(fpid);

    if (isNew == 1) {
    	fpid = fopen("pid.log", "w");
    	fprintf(fpid, "%d", sid);
    	fclose(fpid);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    while (1) {
	if (signal(SIGUSR1, sig_usr) == SIG_ERR) {
            fprintf(stderr, "Can't catch SIGUSR1\n");
            exit(EXIT_FAILURE);
        }
        if (signal(SIGUSR2, sig_usr) == SIG_ERR) {
            fprintf(stderr, "Can't catch SIGUSR2\n");
            exit(EXIT_FAILURE);
        }
        if (signal(SIGRTMIN, sig_usr) == SIG_ERR) {
            fprintf(stderr, "Can't catch SIGRTMIN\n");
            exit(EXIT_FAILURE);
        }
	
	const char* url = "drive.google.com/uc?export=download&id=1rUIZmp10lXLtCIH3LAZJzRPeRks3Crup";
        const char* filename = "library.zip";
        const char* checkname = "library";

        char* user = getlogin();
    
        int renamefile;

   	pid_t child_id;
	DIR *dir;
    	FILE *flog;
    	char date[25];

    	if (directory_exists(checkname) == 0) {
    	    child_id = fork();
    	
	    if (child_id < 0) {
                fprintf(stderr, "Failed to create a new process.\n");
                exit(EXIT_FAILURE);
    	    }
    	
            if (download_file(url, filename) != 0) {
                fprintf(stderr, "Error downloading file\n");
                return 1;
            }

            if (child_id == 0) { // child
                fprintf(stderr, "File successfully downloaded and extracted.\n");
            } 
            else { // parent
                char *const argunzip[4] = {"unzip", "-q", "library.zip", NULL};
                execv("/usr/bin/unzip", argunzip);
            }
        
            sleep(2);
            remove("library.zip");
        
            dir = opendir("library");
            if (dir == NULL) {
                fprintf(stderr, "Failed to open directory: %s", strerror(errno));
                exit(EXIT_FAILURE);
            }

            struct dirent *file;
            while ((file = readdir(dir)) != NULL) {
                if (strcmp(file->d_name, ".") == 0 || strcmp(file->d_name, "..") == 0) {
                    continue;
                }
	
	        if (strstr(file->d_name, "r3N4mE") || strstr(file->d_name, "d3Let3") || strstr(file->d_name, "m0V3")) {
	    	    continue;
	        }
	        else { 
            	    char old_path[256];
            	    sprintf(old_path, "%s/%s", checkname, file->d_name);

            	    char* altname = decipher(file->d_name, 19);
        
           	    char new_path[256];
            	    sprintf(new_path, "%s/%s", checkname, altname);

            	    renamefile = rename(old_path, new_path);

            	    if(renamefile) {
                        fprintf(stderr, "Failed to rename file %s.\n", old_path);
            	    }
                }
            }
            if(mkdir("library/backup", 0777) == -1) {
	        fprintf(stderr, "Can't create backup folder.\n");
	        exit(EXIT_FAILURE);
	    }
            closedir(dir);
        }
        
        if (argc > 1 && strcmp(argv[1], "-m") == 0) {
            if (argc < 3) {
                fprintf(stderr, "Usage: %s\n%s -m backup\n%s -m restore", argv[0], argv[0], argv[0]);
                exit(EXIT_FAILURE);
            }

            if (strcmp(argv[2], "backup") == 0) {
                state = 2;
            }
            else if (strcmp(argv[2], "restore") == 0) {
                state = 3;
            }
            else {
                fprintf(stderr, "Usage: %s\n%s -m backup\n%s -m restore", argv[0], argv[0], argv[0]);
                exit(EXIT_FAILURE);
            }
        }
        else {
	    state = 1;
        } 
	
	if(isexec == 0) {
            if (state == 1) { //default
	    	defaultmode();
	    	isexec = 1;
            }
            else if (state == 2) { //backup
	    	backupmode();
	    	isexec = 1;
            }
            else if (state == 3) { //restore
	    	restoremode();
	    	isexec = 1;
            }
	}
	
        sleep(1);

//        fclose(fptr);
    }

    return 0;
}

