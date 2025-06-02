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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

BSTree *create_bstree()
{
    BSTree *tree = (BSTree *)malloc(sizeof(BSTree));
    if (tree == NULL)
    {
        fprintf(stderr, "Error allocating memory for BSTree\n");
        return NULL;
    }
    tree->root = NULL;
    return tree;
}

void destroy_bstree(BSTree *tree)
{
    if (tree == NULL)
        return;

    // Free all nodes in the tree
    // This function should be implemented to free all nodes recursively
    // free_bstree_nodes(tree->root);

    free(tree);
}

BSTreeNode *create_bstree_node(void *info)
{
    BSTreeNode *node = (BSTreeNode *)malloc(sizeof(BSTreeNode));
    if (node == NULL)
    {
        fprintf(stderr, "Error allocating memory for BSTreeNode\n");
        return NULL;
    }
    node->info = info;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void insert_bstree(BSTree *tree, void *info, int (*compare)(const void *, const void *))
{
    if (tree == NULL || info == NULL || compare == NULL)
        return;

    BSTreeNode *new_node = create_bstree_node(info);
    if (new_node == NULL)
        return;

    if (tree->root == NULL)
    {
        tree->root = new_node;
        tree->size = 1;
        return;
    }

    BSTreeNode *current = tree->root;
    BSTreeNode *parent = NULL;

    while (current != NULL)
    {
        parent = current;
        if (compare(info, current->info) < 0)
            current = current->left;
        else
            current = current->right;
    }

    if (compare(info, parent->info) < 0)
        parent->left = new_node;
    else
        parent->right = new_node;

    tree->size++;
}

