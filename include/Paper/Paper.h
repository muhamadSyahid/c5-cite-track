/// Nama File   : Paper.h
///
/// Deskripsi   : File header untuk ADT Paper yang memanfaatkan ADT
///               Binary Search Tree untuk menyimpan data Author dan
///               Double Linked List untuk menyimpan data Paper
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

/// Struct untuk menyimpan data Author di dalam BSTree
typedef struct
{
  char *name;     // nama author
  DLList *papers; // list Paper
} Author;

/**
 * BSTree untuk menyimpan data Author
 * @note Penyimpanan data utama
 */
extern BSTree *authors_tree;

/**
 * BSTree untuk menyimpan data Paper
 * @note Penyimpanan data utama
 */
extern BSTree *papers_tree;

/**
 * Double linked list untuk menyimpan data Paper untuk ditampilkan
 */
extern DLList *papers_list;

void print_paper(const Paper *paper);

// fungsi membangun BSTree dari array Paper
void build_bstree_paper(BSTree *tree, Paper **paper, int n_papers, int (*compare)(const void *, const void *));

// fungsi untuk membandingkan dua Paper berdasarkan judul
int compare_paper_by_title(const void *paper1, const void *paper2);

#endif