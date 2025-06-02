/// Nama File   : DLList.h
///
/// Deskripsi   : File header untuk ADT Double Linked List Dinamis
///
/// Dibuat oleh : Hanifidin Ibrahim     (241511076)
///               Helga Athifa Hidayat  (241511077)
///               Hisyam Khaeru Umam    (241511078)
///               Ikhsan Satriadi       (241511080)
///               Muhamad Syahid        (241511081)
///
/// Tanggal     : 12-05-2025

#ifndef DLLIST_H
#define DLLIST_H

/// Node untuk Double Linked List
typedef struct DLListNode DLListNode;
struct DLListNode
{
  void *info; // pointer ke data generik
  DLListNode *next;
  DLListNode *prev;
};

/// Double Linked List
typedef struct
{
  DLListNode *head;
  DLListNode *tail;
  int size;
} DLList;

// Fungsi untuk menambah paper ke dalam list
void add_paper_to_list(DLList *list, Paper *paper);

// Fungsi untuk mengurutkan paper berdasarkan kriteria tertentu
void sort_papers(DLList *list, int (*cmp)(Paper*, Paper*));

// Fungsi pembanding untuk sorting berdasarkan tahun
int compare_by_year(Paper *a, Paper *b);

// Fungsi pembanding untuk sorting berdasarkan judul
int compare_by_title(Paper *a, Paper *b);

// Fungsi pembanding untuk sorting berdasarkan penulis
int compare_by_author(Paper *a, Paper *b);


#endif