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

// Fungsi untuk mencetak data Paper
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

// Fungsi untuk membandingkan dua Paper berdasarkan judul
int compare_paper_by_title(const void *paper1, const void *paper2)
{
  if (paper1 == NULL || paper2 == NULL)
  {
    printf("Satu atau kedua paper NULL di compare_paper_by_title\n");
    return 0;
  }

  Paper *p1 = (Paper *)paper1;
  Paper *p2 = (Paper *)paper2;

  if (p1->title == NULL || p2->title == NULL)
  {
    printf("Satu atau kedua judul NULL di compare_paper_by_title\n");
    return 0;
  }

  return strcmp(p1->title, p2->title);
}

// Fungsi untuk membandingkan dua Paper berdasarkan tahun
int compare_paper_by_year(const void *paper1, const void *paper2)
{
  if (paper1 == NULL || paper2 == NULL)
  {
    printf("Satu atau kedua paper NULL di compare_paper_by_year\n");
    return 0;
  }

  Paper *p1 = (Paper *)paper1;
  Paper *p2 = (Paper *)paper2;

  return p1->year - p2->year;
}

// Fungsi untuk membandingkan dua Paper berdasarkan author
int compare_paper_by_author(const void *paper1, const void *paper2)
{
  if (paper1 == NULL || paper2 == NULL)
  {
    printf("Satu atau kedua paper NULL di compare_paper_by_author\n");
    return 0;
  }

  Paper *p1 = (Paper *)paper1;
  Paper *p2 = (Paper *)paper2;

  if (p1->authors[0] == NULL || p2->authors[0] == NULL)
  {
    printf("Satu atau kedua author NULL di compare_paper_by_author\n");
    return 0;
  }

  return strcmp(p1->authors[0], p2->authors[0]); // Asumsi kita membandingkan penulis pertama
}

// Fungsi untuk membangun BSTree dari array Paper tanpa balancing
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

// Fungsi untuk mengambil data Paper yang populer berdasarkan jumlah sitasi dan memasukkannya ke dalam DLList sejumlah n
void get_popular_papers(BSTreeNode *node, DLList **paper_list, int n)
{
  if (node == NULL || n <= 0)
  {
    return;
  }

  get_popular_papers(node->left, paper_list, n);
  Paper *paper = (Paper *)node->info;
  if (paper->in_citation_count > 0)
  {
    if ((*paper_list)->size < n)
    {
      dllist_insert_back(paper_list, paper);
    }
    else
    {
      Paper *last_paper = (Paper *)(*paper_list)->tail->info;
      if (paper->in_citation_count > last_paper->in_citation_count)
      {
        dllist_remove_back(paper_list);
        dllist_insert_back(paper_list, paper);
      }
    }
  }
  get_popular_papers(node->right, paper_list, n);
}

// Fungsi untuk menampilkan detail Paper
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
