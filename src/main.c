#include <stdio.h>
#include <stdlib.h>

#include "Parser/Parser.h"
#include "Paper/Paper.h"

// Binary Search Tree untuk Author diurutkan berdasarkan nama
// Setiap Author memiliki daftar Paper yang ditulisnya dalam sebuah Double Linked List
BSTree *authors_tree = NULL;

// Binary Search Tree untuk Paper diurutkan berdasarkan judul
BSTree *papers_tree = NULL;

// Double Linked List untuk menyimpan Paper yang akan ditampilkan
DLList *shown_paper_list = NULL;

// Array of Paper pointers untuk menyimpan data Paper sementara
// yang diambil dari file dataset
Paper **papers = NULL;

int n_papers = 0;

int main(int argc, char const *argv[])
{
  load_json_papers(&papers, &n_papers, "data/test.json");

  // Insert papers ke BSTree authors_tree & papers_tree
  build_bstree_paper(&papers_tree, papers, n_papers, compare_paper_by_title);

  in_order_traversal_bstree_nodes(papers_tree->root, print_paper);
  printf("\n");

  // Akhir program
  destroy_bstree(authors_tree);
  destroy_bstree(papers_tree);
  free(papers);

  return 0;
}
