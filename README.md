# Sisop-2-2024-MH-IT03


## ***KELOMPOK IT 03***
| Nama      | NRP         |
  |-----------|-------------|
  | Haidar Rafi Aqyla | 5027231029   |
  | Hasan | 5027231073  |  
  | Muhammad kenas Galeno Putra  | 5027231069  |

# Praktikum Sistem Operasi Modul 2


# Soal 1


**soal :**

Gavriel adalah seorang cyber security enthusiast. Suatu hari, ia dikontrak oleh sebuah perusahaan ternama untuk membuat sebuah program yang cukup rumit dengan bayaran jutaan rupiah. Karena tergoda dengan nominal bayaran tersebut, Gavriel langsung menerima tawaran tersebut. Setelah mencoba membuat dan mengembangkan program tersebut selama seminggu, laptop yang digunakan Gavriel mengalami overheat dan mati total sehingga harus dilarikan ke tukang servis terdekat. Karena keterbatasan waktu dalam pembuatan program dan tidak ingin mengecewakan perusahaan, Gavriel meminta bantuan kalian untuk membuat program tersebut dengan ketentuan sebagai berikut:

- Program dapat menerima input path berupa ‘argv’ untuk mengatur folder dimana file akan dieksekusi
  
- Program tersebut berfungsi untuk mereplace string dengan ketentuan sebagai berikut:
  
- String m4LwAr3 direplace dengan string [MALWARE]
  
- String 5pYw4R3 direplace dengan string [SPYWARE]
  
- String R4nS0mWaR3 direplace dengan string [RANSOMWARE]
  
- Program harus berjalan secara daemon, dan tidak diperbolehkan menggunakan command system() dalam pembuatan program
  
- Program akan secara terus menerus berjalan di background dengan jeda 15 detik
  
- Catat setiap penghapusan string yang dilakukan oleh program pada sebuah file bernama virus.log dengan format: [dd-mm-YYYY][HH:MM:SS] Suspicious string at <file_name> successfully replaced!

Contoh penggunaan: ./virus /home/user/virus

Contoh isi file sebelum program dijalankan:
```
pU=-JWQ$5$)D-[??%AVh]$cB6bm4LwAr3jEQC2p3R{HV]=-AUaxj:Qe+h
!aNX,i:!z3W=2;.tHc3&S+}6F)CFf%tfZLP1*w5m1PAzZJUux(
Pd&f8$F5=E?@#[6jd{TJKj]5pYw4R3{KK1?hz384$ge@iba5GAj$gqB41
#C&&a}M9C#f64Eb.?%c)dGbCvJXtU[?SE4h]BY4e1PR4nS0mWaR3{]S/{w?*
```

Contoh isi file setelah setelah program dijalankan:
```
pU=-JWQ$5$)D-[??%AVh]$cB6b[MALWARE]jEQC2p3R{HV]=-AUaxj:Qe+h
!aNX,i:!z3W=2;.tHc3&S+}6F)CFf%tfZLP1*w5m1PAzZJUux(
Pd&f8$F5=E?@#[6jd{TJKj][SPYWARE]{KK1?hz384$ge@iba5GAj$gqB41
#C&&a}M9C#f64Eb.?%c)dGbCvJXtU[?SE4h]BY4e1P[RANSOMWARE]{]S/{w?*
```

**STEP**
1. nano virus.c
2. gcc virus.c -o virus
3. ./virus [file directory]

# Soal 2


**soal :**

Paul adalah seorang mahasiswa semester 4 yang diterima magang di perusahaan XYZ. Pada hari pertama magang, ia diberi tugas oleh atasannya untuk membuat program manajemen file sederhana. Karena kurang terbiasa dengan bahasa C dan environment Linux, ia meminta bantuan kalian untuk mengembangkan program tersebut.

- Atasannya meminta agar program tersebut dapat berjalan secara daemon dan dapat mengunduh serta melakukan unzip terhadap file berikut. Atasannya juga meminta program ini dibuat tanpa menggunakan command system()

- Setelah ditelusuri, ternyata hanya 6 file teratas yang nama filenya tidak dienkripsi. Oleh karena itu, bantulah Paul untuk melakukan dekripsi terhadap nama file ke-7 hingga terakhir menggunakan algoritma ROT19

- Setelah dekripsi selesai, akan terlihat bahwa setiap file memuat salah satu dari kode berikut: r3N4mE, d3Let3, dan m0V3. Untuk setiap file dengan nama yang memuat kode d3Let3, hapus file tersebut. Sementara itu, untuk setiap file dengan nama yang memuat kode r3N4mE, lakukan hal berikut:

  - Jika ekstensi file adalah “.ts”, rename filenya menjadi “helper.ts”
  - Jika ekstensi file adalah “.py”, rename filenya menjadi “calculator.py”
  - Jika ekstensi file adalah “.go”, rename filenya menjadi “server.go”
  - Jika file tidak memuat salah satu dari ekstensi diatas, rename filenya menjadi “renamed.file”

- Atasan Paul juga meminta agar program ini dapat membackup dan merestore file. Oleh karena itu, bantulah Paul untuk membuat program ini menjadi 3 mode, yaitu:

  - default: program berjalan seperti biasa untuk me-rename dan menghapus file. Mode ini dieksekusi ketika program dijalankan tanpa argumen tambahan, yaitu dengan command ./management saja
  - backup: program memindahkan file dengan kode m0V3 ke sebuah folder bernama “backup”
  - restore: program mengembalikan file dengan kode m0V3 ke folder sebelum file tersebut dipindahkan
  - Contoh penggunaan: ./management -m backup

- Terkadang, Paul perlu mengganti mode dari program ini tanpa menghentikannya terlebih dahulu. Oleh karena itu, bantulan Paul untuk mengintegrasikan kemampuan untuk mengganti mode ini dengan mengirim sinyal ke daemon, dengan ketentuan:

  - SIGRTMIN untuk mode default
  - SIGUSR1 untuk mode backup
  - SIGUSR2 untuk mode restore
  - Contoh penggunaan: kill -SIGUSR2 [pid_program]

- Program yang telah dibuat ini tidak mungkin akan dijalankan secara terus-menerus karena akan membebani sistem. Maka dari itu, bantulah Paul untuk membuat program ini dapat dimatikan dengan aman dan efisien

- Terakhir, program ini harus berjalan setiap detik dan mampu mencatat setiap peristiwa yang terjadi ke dalam file .log yang bernama “history.log” dengan ketentuan:

  - Format: **[name_user][HH:MM:SS] - [name_file] - [action]**
  - nama_user adalah username yang melakukan action terhadap file
  - Format action untuk setiap kode:
    - kode r3N4mE: Successfully renamed.
    - kode d3Let3: Successfully deleted.
    - mode backup: Successfully moved to backup.
    - mode restore: Successfully restored from backup.
  - Contoh pesan log:
    - [paul][00:00:00] - r3N4mE.ts - Successfully renamed.
    - [paul][00:00:00] - m0V3.xk1 - Successfully restored from backup.

- soal_2/
  
    ├── history.log
  
    ├── management.c
  
    └── library/
  
        └── backup/

**STEP**
1. nano management.c
2. gcc management.c -o management
3. ./management (mode default)
4. ./management -backup (mode backup)
5. ./management -restore (mode restore)
6. kill -SIGRTMIN [pid] (mengirim signal ke program untuk berganti ke mode default)
7. kill -SIGUSR1 [pid] (mengirim signal ke program untuk berganti ke mode backup)
8. kill -SIGUSR2 [pid] (mengirim signal ke program untuk berganti ke mode restore)

# Soal 3


**soal :**

Pak Heze adalah seorang admin yang baik. Beliau ingin membuat sebuah program admin yang dapat memantau para pengguna sistemnya. Bantulah Pak Heze untuk membuat program  tersebut!

- Namai program tersebut dengan nama admin.c
  
- Program tersebut memiliki fitur menampilkan seluruh proses yang dilakukan oleh seorang user dengan menggunakan command:
  ./admin <user>

- Program dapat memantau proses apa saja yang dilakukan oleh user. Fitur ini membuat program berjalan secara daemon dan berjalan terus menerus. Untuk menjalankan fitur ini menggunakan command: 
  ./admin -m <user>
  Dan untuk mematikan fitur tersebut menggunakan: 
  ./admin -s <user>
  Program akan mencatat seluruh proses yang dijalankan oleh user di file <user>.log dengan format:
  [dd:mm:yyyy]-[hh:mm:ss]-pid_process-nama_process_GAGAL/JALAN

- Program dapat menggagalkan proses yang dijalankan user setiap detik secara terus menerus dengan menjalankan: 
  ./admin -c user
  sehingga user tidak bisa menjalankan proses yang dia inginkan dengan baik. Fitur ini dapat dimatikan dengan command:
  ./admin -a user
  Ketika proses yang dijalankan user digagalkan, program juga akan melog dan menset log tersebut sebagai GAGAL. Dan jika di log menggunakan fitur poin c, log akan ditulis dengan JALAN

  **STEP**

  STEP SISOP NO 3

  1. touch admin.c (membuat admin.c)
  2. sudo chmod +x admin.c (memberi permission pada file admin.c)
  3. nano admin.c (membuka admin.c menggunakan nano)

     ISI SCRIPT admin.c
```
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
```


# Soal 4

**soal :**

Salomo memiliki passion yang sangat dalam di bidang sistem operasi. Saat ini, dia ingin mengotomasi kegiatan-kegiatan yang ia lakukan agar dapat bekerja secara efisien. Bantulah Salomo untuk membuat program yang dapat mengotomasi kegiatan dia!
(NB: Soal di uji coba dan berhasil di sistem yang menggunakan MacOS dan linux yang menggunakan dual boot dan VM. Untuk teman-teman yang menggunakan WSL bisa mengerjakan soal yang lain ya)
- Salomo ingin dapat membuka berbagai macam aplikasi dengan banyak jendela aplikasi dalam satu command. Namai file program tersebut setup.c

- Program dapat membuka berbagai macam aplikasi dan banyak jendela aplikasi sekaligus (bisa membuka 1 atau lebih aplikasi dengan 1 atau lebih window (kecuali        aplikasi yang tidak bisa dibuka dengan banyak window seperti discord)) dengan menjalankan: 
  ./setup -o <app1> <num1> <app2> <num2>.....<appN> <numN>
  Contoh penggunaannya adalah sebagai berikut: 
  ./setup -o firefox 2 wireshark 2
  Program akan membuka 2 jendela aplikasi firefox dan 2 jendela aplikasi wireshark.

- Program juga dapat membuka aplikasi dengan menggunakan file konfigurasi dengan menggunakan 
  ./setup -f file.conf 
  Format file konfigurasi dibebaskan, namun pastikan dapat menjalankan fitur dari poin 2.
  Contoh isi file.conf:
  Firefox 2
  Wireshark 3
  Ketika menjalankan command contoh, program akan membuka 2 jendela aplikasi firefox dan 3 jendela aplikasi wireshark.

- Program dapat mematikan semua aplikasi yg dijalankan oleh program tersebut dengan: 
  ./setup -k

- Program juga dapat mematikan aplikasi yang dijalankan sesuai dengan file konfigurasi. 
  Contohnya: 
  ./setup -k file.conf 
  Command ini hanya mematikan aplikasi yang dijalankan dengan 
  ./setup -f file.conf

**STEP**
1. nano setup.c (membuka setup.c)
2. gcc setup.c -o setup (proses kompilasi kode sumber C yang disimpan dalam file setup.c menjadi sebuah program)
3. ./setup -o firefox 2 wireshark 2 (membuka 2 jendela aplikasi firefox dan 2 jendela aplikasi wireshark)
4. nano file.conf (membuka file.conf)
   ![Screenshot 2024-04-20 140837](https://github.com/haidarRA/Sisop-2-2024-MH-IT03/assets/150374973/50c72c19-c693-4883-8a67-62df57c58694)

5. ./setup -f file.conf (menginstruksikan program setup untuk menggunakan file konfigurasi file.conf)
6. ./setup -k (mematikan semua aplikasi yg dijalankan oleh program)
7. ./setup -k file.conf (mematikan aplikasi yang dijalankan sesuai dengan file konfigurasi)

**DOKUMENTASI**
![Screenshot 2024-04-20 140837](https://github.com/haidarRA/Sisop-2-2024-MH-IT03/assets/150374973/d776c1e2-6bae-497a-9792-51fd2c1bebc8)








