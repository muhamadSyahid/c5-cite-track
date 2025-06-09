/// Nama File   : Paper.h
///
/// Deskripsi   : File header untuk ADT Paper yang memanfaatkan ADT
///               Binary Search Tree dan ADT Double Linked List
///
/// Dibuat oleh : Hanifidin Ibrahim     (241511076)
///               Helga Athifa Hidayat  (241511077)
///               Hisyam Khaeru Umam    (241511078)
///               Ikhsan Satriadi       (241511080)
///               Muhamad Syahid        (241511081)
///
/// Tanggal     : 12-05-2025

#ifndef PAPER_H
#define PAPER_H

#include "BSTree/BSTree.h"
#include "DLList/DLList.h"

/// Struct untuk menyimpan data Paper
typedef struct
{
  char *id;             // id paper
  char *title;          // judul paper
  char *paper_abstract; // abstrak paper

  char **in_citations;  // array id sitasi
  char **out_citations; // array id sitasi

  int in_citation_count;  // jumlah sitasi masuk
  int out_citation_count; // jumlah sitasi keluar

  int year;       // tahun
  char **authors; // nama nama author

  int author_count; // jumlah author
} Paper;

extern int kunjungan;

Paper *paper_create();

void print_paper(void *data);

// fungsi membangun BSTree dari array Paper tanpa balancing
void build_bstree_paper(BSTree **tree, Paper **paper, int n_papers, int (*compare)(const void *, const void *));

// fungsi membangun BSTree dari array Paper dengan balancing AVL
void build_balance_bstree_paper(BSTree **tree, Paper **paper, int n_papers, int (*compare)(const void *, const void *));

// fungsi untuk membandingkan dua Paper berdasarkan judul
int compare_paper_by_title(const void *paper1, const void *paper2);

// fungsi untuk mencari Paper berdasarkan judul yang mirip dan memasukkannya ke dalam DLList
// menggunakan in order traversal
void search_paper_by_title(BSTreeNode *node, const char *title, DLList **paper_list);

// fungsi untuk mencari Paper berdasarkan nama author dengan prefix match
void search_paper_by_author(BSTreeNode *node, const char *author_name, DLList **paper_list);

// mencari 1 paper berdasarkan judul
Paper *search_exact_paper_by_title(BSTreeNode *node, const char *title);

// fungsi untuk mengambil data Paper yang populer berdasarkan jumlah sitasi
// dan memasukkannya ke dalam DLList sejumlah n
void get_popular_papers(BSTreeNode *node, DLList **paper_list, int n);

void show_paper_detail(const Paper *paper);

// fungsi untuk mengambil rentang tahun dari Paper
int get_year_min(BSTreeNode *node);
int get_year_max(BSTreeNode *node);

#endif