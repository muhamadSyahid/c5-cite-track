# CiteTrack

Tugas Besar Struktur Data dan Algoritma

CiteTrack merupakan pengembangan sebuah sistem yang mampu menampilkan daftar paper paling populer milik seorang penulis, berdasarkan jumlah sitasi yang diterima. Sistem ini dilengkapi fitur penyaringan (filter) berdasarkan nama penulis dan tahun publikasi, sehingga memudahkan pengguna dalam menemukan karya ilmiah yang paling berpengaruh dalam periode tertentu. Proses pengolahan data dilakukan menggunakan struktur data dinamis untuk memastikan efisiensi dalam pencarian dan penyusunan informasi.

---

**Kelompok** : C5

**Jurusan** : Teknik Komputer dan Informatika

**Prodi** : D3 Teknik Informatika

---

## Anggota Kelompok

| No  | Anggota                                                                 | NIM       |
| --- | ----------------------------------------------------------------------- | --------- |
| 1   | **Hanifidin Ibrahim** ([@Hanif13579](https://github.com/Hanif13579))    | 241511076 |
| 2.  | **Helga Athifa Hidayat** ([@helga1406](https://github.com/helga1406))   | 241511077 |
| 3.  | **Hisyam Khaeru Umam** ([@Umeem26](https://github.com/Umeem26))         | 241511078 |
| 4.  | **Ikhsan Satriadi** ([@ikhsan3adi](https://github.com/ikhsan3adi))      | 241511080 |
| 5.  | **Muhamad Syahid** ([@muhamadSyahid](https://github.com/muhamadSyahid)) | 241511081 |

---

## Field (Atribut Data)

| Field          | Penjelasan                                                   |
| -------------- | ------------------------------------------------------------ |
| ID             | ID unik untuk setiap paper                                   |
| TITLE          | Judul paper                                                  |
| PAPER ABSTRACK | Jumlah paper yang mengutip paper ini (indikator popularitas) |
| INCITATIONS    | Jumlah kutipan yang dibuat oleh paper ini                    |
| OUTCITATIONS   | Jumlah kutipan yang dibuat oleh paper ini                    |
| YEAR           | Tahun publikasi                                              |
| AUTHOR         | Nama penulis                                                 |

## Input & Output

Sistem ini menerima nama penulis dan tahun publikasi, lalu menampilkan daftar paper paling populer karya penulis tersebut pada tahun itu, diurutkan berdasarkan jumlah sitasi masuk. Informasi yang ditampilkan meliputi judul, abstrak, jumlah sitasi masuk dan keluar, serta nama penulis lain (jika ada).

## Pembagian Tugas & Fitur

| Nama Fitur                                      | Anggota yg Mengerjakan |
| ----------------------------------------------- | ---------------------- |
| initialize, insert balance (BST) author & paper | Syahid                 |
| parsing data paper                              | Ikhsan                 |
| sorting                                         | Umem                   |
| show popular paper                              | Hanif                  |
| search paper by title                           | Helga                  |
| search paper by author                          | Umem                   |
| Detail paper                                    | Helga                  |
| UI, Input & Dashboard                           | Ikhsan                 |

## Struktur Data

| Struktur Data            | Deskripsi                                                                                                                       |
| ------------------------ | ------------------------------------------------------------------------------------------------------------------------------- |
| BST (Binary Search Tree) | Digunakan untuk menyimpan data penulis dan paper, memungkinkan pencarian yang efisien berdasarkan judul paper dan nama penulis. |
| DLL (Doubly Linked List) | Digunakan untuk menyimpan daftar paper yang diurutkan berdasarkan judul, jumlah sitasi masuk, tahun dan nama penulis            |

## Stackholder

| Nama Stackholder                                 | Peran                                                |
| ------------------------------------------------ | ---------------------------------------------------- |
| Mahasiswa dan Peneliti                           | Pengguna utama                                       |
| Dosen dan Akademisi                              | Pengguna dan evaluator ilmiah                        |
| Perpustakaan dan Pusat Data Ilmiah Kampus        | Penyedia dan pengelola data                          |
| Pengembang Sistem / Mahasiswa Teknik Informatika | Pengembang sistem                                    |
| Institusi Pendidikan / Kampus                    | Pendukung implementasi dan pengembangan lebih lanjut |
