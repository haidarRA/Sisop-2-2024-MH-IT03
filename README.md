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






# Soal 2


**soal :**






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
2. gcc setup.c -o setup 
3. ./setup -o firefox 2 wireshark 2
4. nano file.conf
5. ./setup -f file.conf
6. ./setup -k
7. ./setup -k file.conf 









