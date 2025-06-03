#include "Author/Author.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fungsi untuk mencetak data Author
void print_author(void *data) {
    Author *author = (Author *)data;
    if (author) {
        printf("Author: %s\n", author->name);
    }
}

// Fungsi untuk membandingkan dua Author berdasarkan nama
int compare_author_name(const void *author1, const void *author2) {
    Author *a1 = (Author *)author1;
    Author *a2 = (Author *)author2;
    return strcmp(a1->name, a2->name);
}

// Fungsi untuk membangun BSTree author dari array Paper tanpa balancing
void build_bstree_author(BSTree **tree, Paper **paper, int n_papers, int (*compare)(const void *, const void *)) {
    for (int i = 0; i < n_papers; i++) {
        Author *author = (Author *)malloc(sizeof(Author));
        author->name = paper[i]->authors[0];  // Mengambil penulis pertama sebagai contoh
        author->papers = (DLList *)malloc(sizeof(DLList));  // Inisialisasi DLList

        // Insert author ke dalam BSTree
        insert_bstree(tree, author, compare);
    }
}

// Fungsi untuk membangun BSTree author dengan balancing AVL
void build_balance_bstree_author(BSTree **tree, Paper **paper, int n_papers, int (*compare)(const void *, const void *)) {
    // Sama dengan fungsi build_bstree_author, namun dengan teknik balancing AVL
    // Implementasi AVL balancing dapat ditambahkan jika diperlukan
    build_bstree_author(tree, paper, n_papers, compare);  // Implementasi sementara
}

// Fungsi untuk mencari daftar paper berdasarkan author dan memasukkannya ke dalam DLList
void search_paper_by_author(BSTreeNode *node, const char *author, DLList **paper_list) {
    if (node == NULL) return;

    Author *current_author = (Author *)node->info;
    if (strcmp(current_author->name, author) == 0) {
        // Jika penulis ditemukan, masukkan paper ke dalam DLList
        DLListNode *node_paper = current_author->papers->head;
        while (node_paper != NULL) {
            add_dllist(paper_list, node_paper->info);  // Menambahkan paper ke DLList
            node_paper = node_paper->next;
        }
    }

    search_paper_by_author(node->left, author, paper_list);
    search_paper_by_author(node->right, author, paper_list);
}
