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

BSTree *bstree_create()
{
    BSTree *tree = (BSTree *)malloc(sizeof(BSTree));
    if (tree == NULL)
    {
        printf("Error allocating memory for BSTree\n");
        return NULL;
    }
    tree->root = NULL;
    tree->size = 0; // PERBAIKAN: Inisialisasi size
    return tree;
}

void bstree_destroy(BSTree *tree)
{
    if (tree == NULL)
    {
        return;
    }

    // bebaskan semua node di dalam BSTree rekursif
    bstree_destroy_nodes(tree->root);

    free(tree);
}

BSTreeNode *bstree_create_node(void *info)
{
    BSTreeNode *node = (BSTreeNode *)malloc(sizeof(BSTreeNode));
    if (node == NULL)
    {
        printf("Error allocating memory for BSTreeNode\n");
        return NULL;
    }
    node->info = info;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void bstree_destroy_nodes(BSTreeNode *node)
{
    if (node == NULL)
    {
        return;
    }

    // Bebaskan subtree kiri dan kanan secara rekursif
    bstree_destroy_nodes(node->left);
    bstree_destroy_nodes(node->right);

    // Bebaskan node itu sendiri
    free(node->info);
    free(node);
}

int bstree_get_height(BSTreeNode *node)
{
    if (node == NULL)
    {
        return 0;
    }

    int leftHeight = bstree_get_height(node->left);
    int rightHeight = bstree_get_height(node->right);

    if (leftHeight > rightHeight)
    {
        return leftHeight + 1;
    }
    else
    {
        return rightHeight + 1;
    }
}

int max(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

int bstree_get_balance(BSTreeNode *node)
{
    if (node == NULL)
    {
        return 0;
    }
    return bstree_get_height(node->left) - bstree_get_height(node->right);
}

BSTreeNode *bstree_right_rotate(BSTreeNode *y)
{
    BSTreeNode *x = y->left;
    BSTreeNode *T2 = x->right;

    // Lakukan rotasi
    x->right = y;
    y->left = T2;

    return x; // Kembalikan root baru
}

BSTreeNode *bstree_left_rotate(BSTreeNode *x)
{
    BSTreeNode *y = x->right;
    BSTreeNode *T2 = y->left;

    // Lakukan rotasi
    y->left = x;
    x->right = T2;

    return y; // Kembalikan root baru
}

// Implementasi insert untuk AVL Tree
BSTreeNode *bstree_insert_node_avl(BSTreeNode *node, void *info, int (*compare)(const void *, const void *))
{
    // Lakukan insertion BST biasa
    if (node == NULL)
    {
        return bstree_create_node(info);
    }

    if (compare(info, node->info) < 0)
    {
        node->left = bstree_insert_node_avl(node->left, info, compare);
    }
    else if (compare(info, node->info) > 0)
    {
        node->right = bstree_insert_node_avl(node->right, info, compare);
    }
    else
    {
        // Nilai sama, tidak insert (atau bisa diubah sesuai kebutuhan)
        // return node;
        node = bstree_insert_node_avl(node, info, compare);
    }

    // Dapatkan balance factor dari node ancestor
    int balance = bstree_get_balance(node);

    // Jika node tidak seimbang, ada 4 kasus:

    // Left Left Case
    if (balance > 1 && compare(info, node->left->info) < 0)
    {
        return bstree_right_rotate(node);
    }

    // Right Right Case
    if (balance < -1 && compare(info, node->right->info) > 0)
    {
        return bstree_left_rotate(node);
    }

    // Left Right Case
    if (balance > 1 && compare(info, node->left->info) > 0)
    {
        node->left = bstree_left_rotate(node->left);
        return bstree_right_rotate(node);
    }

    // Right Left Case
    if (balance < -1 && compare(info, node->right->info) < 0)
    {
        node->right = bstree_right_rotate(node->right);
        return bstree_left_rotate(node);
    }

    // Return node yang tidak berubah
    return node;
}

void bstree_insert(BSTree *tree, void *info, int (*compare)(const void *, const void *))
{
    if (tree == NULL || info == NULL || compare == NULL)
    {
        return;
    }

    BSTreeNode *new_node = bstree_create_node(info);
    if (new_node == NULL)
    {
        return;
    }

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
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }

    if (compare(info, parent->info) < 0)
    {
        parent->left = new_node;
    }
    else
    {
        parent->right = new_node;
    }

    tree->size++;
}

void bstree_insert_balance(BSTree *tree, void *info, int (*compare)(const void *, const void *))
{
    if (tree == NULL || info == NULL || compare == NULL)
    {
        return;
    }

    // Mrmasukkan node baru ke dalam AVL Tree
    tree->root = bstree_insert_node_avl(tree->root, info, compare);
    tree->size++;
}

void bstree_in_order_traversal(BSTreeNode *node, void (*visit)(void *))
{
    if (node == NULL)
    {
        return;
    }

    // Kunjungi subtree kiri
    bstree_in_order_traversal(node->left, visit);

    // Kunjungi node saat ini
    visit(node->info);

    // Kunjungi subtree kanan
    bstree_in_order_traversal(node->right, visit);
}
