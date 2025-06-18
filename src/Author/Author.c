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
        printf("Nama Penulis: %s\n", author->name);
        printf("Jumlah Paper: %d\n", author->papers->size);
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
            const char *author_name = paper[i]->authors[j];

            Author *existing_author = find_author((*tree)->root, author_name);
            if (existing_author != NULL)
            {
                dllist_insert_back(&existing_author->papers, paper[i]);
            }
            else {

                Author *new_author = malloc(sizeof(Author));
                if (new_author == NULL)
                {
                    continue;
                }

                new_author->name = malloc(strlen(author_name) + 1);
                if (new_author->name == NULL)
                {
                    free(new_author);
                    continue;
                }

                strcpy(new_author->name, author_name);

                new_author->papers = dllist_create();

                // Urutkan daftar paper berdasarkan in_citation_count secara descending
                dllist_insert_back(&new_author->papers, paper[i]);
                
                bstree_insert(*tree, new_author, compare);
            }
        }
    }
}

Author* find_author(BSTreeNode *node, const char *author)
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

    int cmp = strcmp(author, a->name); // Membandingkan author yang dicari dengan nama author di node

    if (cmp == 0) // Jika cocok persis
    {
        return a;
    }
    else if (cmp < 0) // Jika author yang dicari lebih kecil, cek subtree kiri
    {
        return find_author(node->left, author);
    }
    else // Jika author yang dicari lebih besar, cek subtree kanan
    {
        return find_author(node->right, author);
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

void search_author(BSTreeNode *node, const char *prefix, DLList **author_list)
{
    if (node == NULL)
    {
        return;
    }

    Author *a = (Author *)node->info;
    size_t prefix_len = strlen(prefix);

    // Membandingkan prefix dengan nama author di node
    int cmp_left = strncasecmp(prefix, a->name, prefix_len);
    // Periksa apakah nama author node saat ini dimulai dengan prefix yang dicari
    bool starts_with_prefix = (cmp_left == 0 && strlen(a->name) >= prefix_len);

    if (cmp_left < 0 || starts_with_prefix)
    {
        search_author(node->left, prefix, author_list);
    }

    // Jika nama author saat ini dimulai dengan prefix yang dicari, tambahkan ke list
    if (starts_with_prefix)
    {
        dllist_insert_back(author_list, a);
    }

    if (cmp_left > 0 || starts_with_prefix)
    {
        search_author(node->right, prefix, author_list);
    }
}

void get_author_papers(BSTreeNode *node, const char *author, DLList **paper_list)
{
    if (node == NULL)
    {
        return;
    }

    Author *current_author = (Author *)node->info;
    int cmp = strcmp(author, current_author->name); // Gunakan strcmp untuk pencarian eksak

    if (cmp == 0)
    {
        // Jika penulis ditemukan, masukkan paper ke dalam DLList
        DLListNode *node_paper = current_author->papers->head;
        while (node_paper != NULL)
        {
            dllist_insert_back(paper_list, node_paper->info); // Menambahkan paper ke DLList
            node_paper = node_paper->next;
        }
    }
    else if (cmp < 0)
    {
        get_author_papers(node->left, author, paper_list);
    }
    else
    {
        get_author_papers(node->right, author, paper_list);
    }
}