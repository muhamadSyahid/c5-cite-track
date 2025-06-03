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
#include "DLList/DLList.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_paper(void *data)
{
  Paper *paper = (Paper *)data;
  if (paper == NULL)
  {
    printf("Paper is NULL\n");
    return;
  }

  printf("ID: %s\n", paper->id);
  printf("Title: %s\n", paper->title);
  printf("Abstract: %s\n", paper->paper_abstract);
  printf("Year: %d\n", paper->year);

  printf("Authors:\n");
  for (int i = 0; i < paper->author_count; i++)
  {
    printf("- %s\n", paper->authors[i]);
  }

  printf("In Citations:\n");
  for (int i = 0; i < paper->in_citation_count; i++)
  {
    printf("- %s\n", paper->in_citations[i]);
  }

  printf("Out Citations:\n");
  for (int i = 0; i < paper->out_citation_count; i++)
  {
    printf("- %s\n", paper->out_citations[i]);
  }
}

void search_paper_by_title(BSTreeNode *node, const char *title, DLList **paper_list)
{
  if (node == NULL)
  {
    return;
  }

  search_paper_by_title(node->left, title, paper_list);

  Paper *paper = (Paper *)node->info;
  if (strstr(paper->title, title) != NULL) // Mencari substring
  {
    dllist_insert_back(paper_list, paper);
  }

  search_paper_by_title(node->right, title, paper_list);
}

void show_paper_detail(const Paper *paper)
{
  if (paper == NULL)
  {
    printf("Detail paper tidak tersedia (pointer NULL).\n");
    return;
  }

  printf("--- Detail Paper ---\n");
  printf("ID: %s\n", (paper->id != NULL) ? paper->id : "[Tidak Ada ID]");
  printf("Judul: %s\n", (paper->title != NULL) ? paper->title : "[Tidak Ada Judul]");
  printf("Tahun Publikasi: %d\n", paper->year);
  printf("Abstrak:\n%s\n", (paper->paper_abstract != NULL) ? paper->paper_abstract : "[Tidak Ada Abstrak]");

  // Menampilkan daftar penulis
  if (paper->authors != NULL && paper->author_count > 0)
  {
    printf("Penulis:\n");
    for (int i = 0; i < paper->author_count; i++)
    {
      printf("  %d. %s\n", i + 1, (paper->authors[i] != NULL) ? paper->authors[i] : "[Nama Penulis Tidak Tersedia]");
    }
  }
  else
  {
    printf("Penulis: Tidak tersedia atau tidak ada.\n");
  }

  // Menampilkan sitasi masuk
  if (paper->in_citations != NULL && paper->in_citation_count > 0)
  {
    printf("Sitasi Masuk (%d):\n", paper->in_citation_count);
    for (int i = 0; i < paper->in_citation_count; i++)
    {
      printf("  - %s\n", (paper->in_citations[i] != NULL) ? paper->in_citations[i] : "[ID Sitasi Tidak Tersedia]");
    }
  }
  else
  {
    printf("Sitasi Masuk: Tidak ada.\n");
  }

  // Menampilkan sitasi keluar
  if (paper->out_citations != NULL && paper->out_citation_count > 0)
  {
    printf("Sitasi Keluar (%d):\n", paper->out_citation_count);
    for (int i = 0; i < paper->out_citation_count; i++)
    {
      printf("  - %s\n", (paper->out_citations[i] != NULL) ? paper->out_citations[i] : "[ID Sitasi Tidak Tersedia]");
    }
  }
  else
  {
    printf("Sitasi Keluar: Tidak ada.\n");
  }
}

void build_bstree_paper(BSTree **tree, Paper **paper, int n_papers, int (*compare)(const void *, const void *))
{
  *tree = bstree_create();
  if (*tree == NULL)
  {
    printf("Error alokasi memori untuk BSTree\n");
    return;
  }
  if (paper == NULL || n_papers <= 0 || compare == NULL)
  {
    printf("Parameter untuk build_bstree_paper invalid!\n");
    return;
  }

  for (int i = 0; i < n_papers; i++)
  {
    if (paper[i] == NULL)
    {
      printf("Paper di index %d NULL\n", i);
      continue;
    }
    bstree_insert(*tree, paper[i], (int (*)(const void *, const void *))compare);
  }
}

void build_balance_bstree_paper(BSTree **tree, Paper **paper, int n_papers, int (*compare)(const void *, const void *))
{
  *tree = bstree_create();
  if (*tree == NULL)
  {
    printf("Error alokasi memori untuk BSTree\n");
    return;
  }
  if (paper == NULL || n_papers <= 0 || compare == NULL)
  {
    printf("Parameter untuk build_bstree_paper invalid!\n");
    return;
  }

  for (int i = 0; i < n_papers; i++)
  {
    if (paper[i] == NULL)
    {
      printf("Paper di index %d NULL\n", i);
      continue;
    }
    bstree_insert_balance(*tree, paper[i], (int (*)(const void *, const void *))compare);
  }
}

int compare_paper_by_title(const void *paper1, const void *paper2)
{
  if (paper1 == NULL || paper2 == NULL)
  {
    printf("Satu atau kedua paper NULL di compare_paper_by_title\n");
    return 0;
  }

  // Cast void pointer ke Paper pointer
  Paper *p1 = (Paper *)paper1;
  Paper *p2 = (Paper *)paper2;

  if (p1->title == NULL || p2->title == NULL)
  {
    printf("atu atau kedua judul NULL di compare_paper_by_title\n");
    return 0;
  }

  return strcmp(p1->title, p2->title);
}
