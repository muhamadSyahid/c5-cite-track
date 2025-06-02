#include <stdio.h>
#include <stdlib.h>
#include "Paper/Paper.h"

/// Sorting paper berdasarkan tahun, judul, dan penulis
int main(int argc, char const *argv[])
{
  printf("Sorting papers by year...\n");
  sort_papers(papers_list, compare_by_year);
  // Menampilkan daftar paper setelah diurutkan
  DLListNode *node = papers_list->head;
  while (node != NULL)
  {
    Paper *paper = (Paper *)node->info;
    printf("Title: %s, Year: %d\n", paper->title, paper->year);
    node = node->next;
  }

  printf("\nSorting papers by title...\n");
  sort_papers(papers_list, compare_by_title);
  // Menampilkan daftar paper setelah diurutkan
  node = papers_list->head;
  while (node != NULL)
  {
    Paper *paper = (Paper *)node->info;
    printf("Title: %s, Year: %d\n", paper->title, paper->year);
    node = node->next;
  }

  printf("\nSorting papers by author...\n");
  sort_papers(papers_list, compare_by_author);
  // Menampilkan daftar paper setelah diurutkan
  node = papers_list->head;
  while (node != NULL)
  {
    Paper *paper = (Paper *)node->info;
    printf("Title: %s, Author: %s\n", paper->title, paper->authors[0]); // Menggunakan penulis pertama
    node = node->next;
  }

  return 0;
}
