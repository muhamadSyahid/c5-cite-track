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
        printf("Error allocating memory for BSTree\n");
        return NULL;
    }
    tree->root = NULL;
    tree->size = 0; // PERBAIKAN: Inisialisasi size
    return tree;
}

void destroy_bstree(BSTree *tree)
{
    if (tree == NULL)
        return;

    // bebaskan semua node di dalam BSTree rekursif
    destroy_bstree_nodes(tree->root);

    free(tree);
}

BSTreeNode *create_bstree_node(void *info)
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

void destroy_bstree_nodes(BSTreeNode *node)
{
    if (node == NULL)
    {
        return;
    }

    // Bebaskan subtree kiri dan kanan secara rekursif
    destroy_bstree_nodes(node->left);
    destroy_bstree_nodes(node->right);

    // Bebaskan node itu sendiri
    free(node->info);
    free(node);
}

int getHeight(BSTreeNode *node)
{
    if (node == NULL)
        return 0;
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int getBalance(BSTreeNode *node)
{
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

BSTreeNode *rightRotate(BSTreeNode *y)
{
    BSTreeNode *x = y->left;
    BSTreeNode *T2 = x->right;

    // Lakukan rotasi
    x->right = y;
    y->left = T2;

    return x; // Kembalikan root baru
}

BSTreeNode *leftRotate(BSTreeNode *x)
{
    BSTreeNode *y = x->right;
    BSTreeNode *T2 = y->left;

    // Lakukan rotasi
    y->left = x;
    x->right = T2;

    return y; // Kembalikan root baru
}

// Implementasi insert untuk AVL Tree
BSTreeNode *insert_node_avl(BSTreeNode *node, void *info, int (*compare)(const void *, const void *))
{
    // Lakukan insertion BST biasa
    if (node == NULL)
    {
        return create_bstree_node(info);
    }

    if (compare(info, node->info) < 0)
    {
        node->left = insert_node_avl(node->left, info, compare);
    }
    else if (compare(info, node->info) > 0)
    {
        node->right = insert_node_avl(node->right, info, compare);
    }
    else
    {
        // Nilai sama, tidak insert (atau bisa diubah sesuai kebutuhan)
        return node;
    }

    // Dapatkan balance factor dari node ancestor
    int balance = getBalance(node);

    // Jika node tidak seimbang, ada 4 kasus:

    // Left Left Case
    if (balance > 1 && compare(info, node->left->info) < 0)
    {
        return rightRotate(node);
    }

    // Right Right Case
    if (balance < -1 && compare(info, node->right->info) > 0)
    {
        return leftRotate(node);
    }

    // Left Right Case
    if (balance > 1 && compare(info, node->left->info) > 0)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && compare(info, node->right->info) < 0)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Return node yang tidak berubah
    return node;
}

void insert_bstree(BSTree *tree, void *info, int (*compare)(const void *, const void *))
{
    if (tree == NULL || info == NULL || compare == NULL)
    {
        return;
    }

    // Mrmasukkan node baru ke dalam AVL Tree
    tree->root = insert_node_avl(tree->root, info, compare);
    tree->size++;
}

void in_order_traversal_bstree_nodes(BSTreeNode *node, void (*visit)(void *))
{
    if (node == NULL)
    {
        return;
    }

    // Kunjungi subtree kiri
    in_order_traversal_bstree_nodes(node->left, visit);

    // Kunjungi node saat ini
    visit(node->info);

    // Kunjungi subtree kanan
    in_order_traversal_bstree_nodes(node->right, visit);
}