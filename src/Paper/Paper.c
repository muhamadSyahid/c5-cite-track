/// Nama File   : Paper.c
///
/// Deskripsi   : File body untuk ADT Paper yang memanfaatkan ADT
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

#include "Paper/Paper.h"

#include <stdio.h>
#include <stdlib.h>

BSTree *authors_tree = NULL;

BSTree *papers_tree = NULL;

DLList *papers_list = NULL;

void search_paper_by_title(BSTreeNode *node, const char *title, DLList *paper_list)
{
    if (node == NULL)
        return;

    search_paper_by_title(node->left, title, paper_list);

    Paper *paper = (Paper *)node->info;
    if (strstr(paper->title, title) != NULL)
    { // Mencari substring
        insertLastDLList(paper_list, paper);
    }

    search_paper_by_title(node->right, title, paper_list);
}