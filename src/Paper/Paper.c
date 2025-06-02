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

void print_paper(const Paper *paper)
{
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

void build_bstree_paper(BSTree *tree, Paper **paper, int n_papers, int (*compare)(const void *, const void *))
{
  tree = malloc(sizeof(BSTree));
  if (tree == NULL)
  {
    fprintf(stderr, "Error allocating memory for BSTree\n");
    return;
  }
  if (tree == NULL || paper == NULL || n_papers <= 0 || compare == NULL)
  {
    fprintf(stderr, "Invalid parameters for build_bstree_paper\n");
    return;
  }

  for (int i = 0; i < n_papers; i++)
  {
    if (paper[i] == NULL)
    {
      fprintf(stderr, "Paper at index %d is NULL\n", i);
      continue;
    }
    insert_bstree(tree, paper[i], (int (*)(const void *, const void *))compare);
  }
}

int compare_paper_by_title(const void *paper1, const void *paper2)
{
  return 0;
}
