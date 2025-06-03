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

void fill_papers_list(BSTreeNode *node, DLList *list) {
    if (!node) return;
    fill_papers_list(node->left, list);

    // Tambahkan paper ke list
    Paper *p = (Paper *)node->info;
    
    DLListNode *new_node = (DLListNode *)malloc(sizeof(DLListNode));
    new_node->info = p;
    new_node->prev = list->tail;
    new_node->next = NULL;

    if (list->tail != NULL) {
        list->tail->next = new_node;
    } else {
        list->head = new_node;
    }
    list->tail = new_node;
    list->size++;

    fill_papers_list(node->right, list);
}

void sort_papers_by_popularity(DLList *list) {
    if (list == NULL || list->size <= 1){
        return;
    }

    for (DLListNode *i = list->head; i != NULL; i = i->next) {
        DLListNode *max = i;
        for (DLListNode *j = i->next; j != NULL; j = j->next) {
            Paper *p1 = (Paper *)max->info;
            Paper *p2 = (Paper *)j->info;
            if (p2->in_citation_count > p1->in_citation_count) {
                max = j;
            }
        }

        if (max != i) {
            void *temp = i->info;
            i->info = max->info;
            max->info = temp;
        }
    }
}

void show_all_papers_by_popularity() {
    // Bebaskan papers_list yang lama untuk mencegah memory leak
    if (papers_list != NULL) {
        DLListNode *current = papers_list->head;
        while (current) {
            DLListNode *temp = current;
            current = current->next;
            free(temp);
        }
        free(papers_list);
    }

    // Alokasi papers_list baru
    papers_list = (DLList *)malloc(sizeof(DLList));
    if (papers_list == NULL) {
        fprintf(stderr, "Error: Gagal alokasi memori untuk papers_list\n");
        return;
    }
    papers_list->head = papers_list->tail = NULL;
    papers_list->size = 0;

    // Cek apakah papers_tree valid
    if (papers_tree == NULL || papers_tree->root == NULL) {
        printf("\n=== Tidak ada paper untuk ditampilkan ===\n");
        free(papers_list);
        return;
    }

    // Isi dan urutkan papers_list
    fill_papers_list(papers_tree->root, papers_list);
    sort_papers_by_popularity(papers_list);

    // Cetak semua paper
    printf("\n=== All Papers Sorted by Popularity ===\n");
    int index = 1;
    for (DLListNode *node = papers_list->head; node != NULL; node = node->next) {
        Paper *p = (Paper *)node->info;
        if (p) {
            printf("%d. %s (Citations: %d, Year: %d)\n", index++, p->title, p->in_citation_count, p->year);
        }
    }
}

