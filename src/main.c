#include <stdio.h>
#include <stdlib.h>

#include "Parser/Parser.h"
#include "Paper/Paper.h"

// Binary Search Tree untuk Author diurutkan berdasarkan nama
// Setiap Author memiliki daftar Paper yang ditulisnya dalam sebuah Double Linked List
BSTree *authors_tree = NULL;

// Binary Search Tree untuk Paper diurutkan berdasarkan judul
BSTree *papers_tree = NULL;

// Binary Search Tree untuk Paper yang sudah di-balance (untuk perbandingan)
BSTree *balance_papers_tree = NULL;

// Double Linked List untuk menyimpan Paper yang akan ditampilkan
DLList *shown_paper_list = NULL;

// Array of Paper pointers untuk menyimpan data Paper sementara
// yang diambil dari file dataset
Paper **papers = NULL;

int n_papers = 0;

void print_title(void *data)
{
  Paper *paper = (Paper *)data;
  if (paper == NULL)
  {
    printf("Paper is NULL\n");
    return;
  }
  printf("title: %s\n", paper->title);
}

int main(int argc, char const *argv[])
{
  load_json_papers(&papers, &n_papers, "data/test.json");

  shown_paper_list = dllist_create();

  // Insert papers ke BSTree authors_tree tanpa balancing
  build_bstree_paper(&papers_tree, papers, n_papers, compare_paper_by_title);

  // Insert authors ke BSTree authors_tree dengan balancing AVL
  build_balance_bstree_paper(&balance_papers_tree, papers, n_papers, compare_paper_by_title);

  // bstree_in_order_traversal(balance_papers_tree->root, print_title);
  // printf("\n");

  search_paper_by_title(balance_papers_tree->root, "Prospective", &shown_paper_list);

  printf("\n");

  // Akhir program
  bstree_destroy(authors_tree);
  bstree_destroy(papers_tree);

  free(papers);
  return 0;
}
