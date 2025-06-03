/// Nama File   : Author.h
///
/// Deskripsi   : File header untuk ADT Author yang memanfaatkan ADT
///               Binary Search Tree dan ADT Double Linked List
///
/// Dibuat oleh : Hanifidin Ibrahim     (241511076)
///               Helga Athifa Hidayat  (241511077)
///               Hisyam Khaeru Umam    (241511078)
///               Ikhsan Satriadi       (241511080)
///               Muhamad Syahid        (241511081)
///
/// Tanggal     : 12-05-2025

#ifndef AUTHOR_H
#define AUTHOR_H

#include "BSTree/BSTree.h"
#include "DLList/DLList.h"
#include "Paper/Paper.h"

/// Struct untuk menyimpan data Author
typedef struct
{
  char *name;     // nama author
  DLList *papers; // list Paper
} Author;

void print_author(void *data);

// fungsi membangun BSTree author dari array Paper tanpa balancing
void build_bstree_author(BSTree **tree, Paper **paper, int n_papers, int (*compare)(const void *, const void *));

// fungsi membangun BSTree author dari array Paper dengan balancing AVL
void build_balance_bstree_author(BSTree **tree, Paper **paper, int n_papers, int (*compare)(const void *, const void *));

// fungsi untuk membandingkan dua Author berdasarkan nama
int compare_author_name(const void *author1, const void *author2);

// fungsi untuk mencari daftar Paper berdasarkan Author dan memasukkannya ke dalam DLList
void search_paper_by_author(BSTreeNode *node, const char *author, DLList **paper_list);

#endif