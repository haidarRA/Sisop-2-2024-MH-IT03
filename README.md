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








