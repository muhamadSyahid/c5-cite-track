/// Nama File   : BSTree.c
///
/// Deskripsi   : File body untuk ADT Binary Search Tree Dinamis
///
/// Dibuat oleh : Hanifidin Ibrahim     (241511076)
///               Helga Athifa Hidayat  (241511077)
///               Hisyam Khaeru Umam    (241511078)
///               Ikhsan Satriadi       (241511080)
///               Muhamad Syahid        (241511081)
///
/// Tanggal     : 12-05-2025

#include "BSTree/BSTree.h"
#include "Paper/Paper.h"
#include <string.h>

// Fungsi Search by Author
Author* search_author_by_name(BSTree *tree, const char *name) {
    BSTreeNode *current = tree->root;

    while (current != NULL) {
        Author *author = (Author*)current->info;
        int cmp = strcmp(author->name, name);

        if (cmp == 0) {
            return author;  
        } else if (cmp < 0) {
            current = current->right;  
        } else {
            current = current->left;  
        }
    }

    return NULL;  
}
