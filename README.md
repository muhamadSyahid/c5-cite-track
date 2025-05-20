# C5-Cite-Track
Tugas Besar SDA | Kelompok 5

CiteTrack merupakan pengembangan sebuah sistem yang mampu menampilkan daftar paper paling populer milik seorang penulis, berdasarkan jumlah sitasi yang diterima. Sistem ini dilengkapi fitur penyaringan (filter) berdasarkan nama penulis dan tahun publikasi, sehingga memudahkan pengguna dalam menemukan karya ilmiah yang paling berpengaruh dalam periode tertentu. Proses pengolahan data dilakukan menggunakan struktur data dinamis untuk memastikan efisiensi dalam pencarian dan penyusunan informasi.

## Field (Atribut Data)

| Field | Penjelasan |
| --- | --- |
| ID | ID unik untuk setiap paper |
| TITLE | Judul paper |
| PAPER ABSTRACK | Jumlah paper yang mengutip paper ini (indikator popularitas)|
| INCITATIONS | Jumlah kutipan yang dibuat oleh paper ini |
| OUTCITATIONS | Jumlah kutipan yang dibuat oleh paper ini |
| YEAR | Tahun publikasi |
| AUTHOR | Nama penulis |

## Input & Output
Sistem ini menerima nama penulis dan tahun publikasi, lalu menampilkan daftar paper paling populer karya penulis tersebut pada tahun itu, diurutkan berdasarkan jumlah sitasi masuk. Informasi yang ditampilkan meliputi judul, abstrak, jumlah sitasi masuk dan keluar, serta nama penulis lain (jika ada).

## Pembagian Tugas & Fitur

| Nama Fitur | Anggota yg Mengerjakan |
| --- | --- | 
|  insert balance (BST) author & paper | Syahid |
| parsing data | Ikhsan |
| sorting | Umem |
| show popular paper | Hanif |
| search paper by title | Helga |
| search paper by author | Umem |
| Input filter | Hanif | 
| Detail paper | Helga |
| Dashboard | Optional |

## Stackholder 

| Nama Stackholder | Peran |
| --- | --- |
| Mahasiswa dan Peneliti | Pengguna utama |
| Dosen dan Akademisi | Pengguna dan evaluator ilmiah |
| Perpustakaan dan Pusat Data Ilmiah Kampus | Penyedia dan pengelola data |
| Pengembang Sistem / Mahasiswa Teknik Informatika | Pengembang sistem |
|Institusi Pendidikan / Kampus | Pendukung implementasi dan pengembangan lebih lanjut |







