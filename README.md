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






