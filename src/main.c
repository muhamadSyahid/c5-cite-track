#include <stdio.h>
#include <stdlib.h>
#include "Paper/Paper.h"

/// Search by author 
int main(int argc, char const *argv[])
{
  char author_name[100];

  printf("Enter the name of the author: ");
  scanf("%s", author_name); // Menerima input nama penulis

  // Cari penulis berdasarkan nama
  Author *found_author = search_author_by_name(authors_tree, author_name);

  // Jika penulis ditemukan, tampilkan hasilnya
  if (found_author != NULL)
  {
    printf("Author found: %s\n", found_author->name);
    // Tampilkan daftar paper yang dimiliki penulis
    DLListNode *node = found_author->papers->head;
    while (node != NULL)
    {
      Paper *paper = (Paper *)node->info;
      printf("Paper Title: %s\n", paper->title);
      node = node->next;
    }
  }
  else
  {
    printf("Author not found.\n");
  }

  return 0;
}
