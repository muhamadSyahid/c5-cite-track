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
/// Tanggal     : 03-06-2025

#include "Author/Author.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_author(void *data)
{
    Author *author = (Author *)data;
    if (author)
    {
        printf("Author: %s\n", author->name);
    }
}

void search_array_paper_by_author(Paper **paper, int n_papers, const char *author, DLList **paper_list)
{
    if (paper == NULL || author == NULL || paper_list == NULL)
    {
        return;
    }

    if (*paper_list == NULL)
    {
        *paper_list = dllist_create();
    }

    for (int i = 0; i < n_papers; i++)
    {
        for (int j = 0; j < paper[i]->author_count; j++)
        {
            if (strcmp(paper[i]->authors[j], author) == 0)
            {
                dllist_insert_back(paper_list, paper[i]);
            }
        }
    }
}

// Fungsi untuk membangun BSTree author dari array Paper tanpa balancing
void build_bstree_author(BSTree **tree, Paper **paper, int n_papers, int (*compare)(const void *, const void *))
{
    if (*tree == NULL)
    {
        *tree = bstree_create();
        if (*tree == NULL)
        {
            printf("Error alokasi memori untuk BSTree\n");
            return;
        }
    }
    if (paper == NULL || n_papers <= 0 || compare == NULL)
    {
        printf("Parameter untuk build_bstree_author invalid!\n");
        return;
    }

    for (int i = 0; i < n_papers; i++)
    {
        // printf("Author: %s", paper[i]->authors[0]);

        if (paper[i] == NULL)
        {
            // printf("Paper di index %d NULL\n", i);
            continue;
        }
        for (int j = 0; j < paper[i]->author_count; j++)
        {
            if (!is_author_exist((*tree)->root, paper[i]->authors[j]))
            {
                Author *new_author = malloc(sizeof(Author));
                DLList *new_author_papers = dllist_create();

                new_author->name = malloc(strlen(paper[i]->authors[j]) * sizeof(char) + 1);

                strcpy(new_author->name, paper[i]->authors[j]);

                search_array_paper_by_author(paper, n_papers, new_author->name, &new_author_papers);

                new_author->papers = new_author_papers;

                bstree_insert(*tree, new_author, (int (*)(const void *, const void *))compare);
            }
        }
    }
}

bool is_author_exist(BSTreeNode *node, const char *author)
{
    if (node == NULL)
    {
        return false;
    }

    Author *a = (Author *)node->info;

    if (a == NULL)
    {
        return false;
    }

    if (strcmp(a->name, author) == 0 ||
        is_author_exist(node->left, author) ||
        is_author_exist(node->right, author))
    {
        return true;
    }
    else
    {
        return false;
    }
}

int compare_author_name(const void *author1, const void *author2)
{
    if (author1 == NULL || author2 == NULL)
    {
        printf("Satu atau kedua author NULL di compare_author_name\n");
        return 0;
    }

    Author *a1 = (Author *)author1;
    Author *a2 = (Author *)author2;

    if (a1->name == NULL || a2->name == NULL)
    {
        printf("Satu atau kedua name Author NULL di compare_author_name\n");
        return 0;
    }

    return strcmp(a1->name, a2->name);
}

void search_author(BSTreeNode *node, const char *author, DLList **author_list)
{
    if (node == NULL)
    {
        return;
    }

    search_author(node->left, author, author_list);

    Author *a = (Author *)node->info;
    if (strstr(a->name, author) != NULL) // Mencari substring
    {
        dllist_insert_back(author_list, a);
    }

    search_author(node->right, author, author_list);
}

// Fungsi untuk mencari daftar paper berdasarkan author dan memasukkannya ke dalam DLList
void get_author_papers(BSTreeNode *node, const char *author, DLList **paper_list)
{
    if (node == NULL)
    {
        return;
    }

    Author *current_author = (Author *)node->info;
    if (strcmp(current_author->name, author) == 0)
    {
        // Jika penulis ditemukan, masukkan paper ke dalam DLList
        DLListNode *node_paper = current_author->papers->head;
        while (node_paper != NULL)
        {
            dllist_insert_back(paper_list, node_paper->info); // Menambahkan paper ke DLList
            node_paper = node_paper->next;
        }
    }

    get_author_papers(node->left, author, paper_list);
    get_author_papers(node->right, author, paper_list);
}
