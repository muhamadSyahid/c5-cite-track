/// Nama File   : BSTree.h
///
/// Deskripsi   : File header untuk ADT Binary Search Tree Dinamis
///
/// Dibuat oleh : Hanifidin Ibrahim     (241511076)
///               Helga Athifa Hidayat  (241511077)
///               Hisyam Khaeru Umam    (241511078)
///               Ikhsan Satriadi       (241511080)
///               Muhamad Syahid        (241511081)
///
/// Tanggal     : 12-05-2025

#ifndef BSTREE_H
#define BSTREE_H

/// Node untuk Binary Search Tree
typedef struct BSTreeNode BSTreeNode;
struct BSTreeNode
{
  void *info; // pointer ke data generik
  BSTreeNode *left;
  BSTreeNode *right;
};

/// Binary Search Tree
typedef struct
{
  BSTreeNode *root;
  int size;
} BSTree;

BSTree *create_bstree();

void destroy_bstree(BSTree *tree);

BSTreeNode *create_bstree_node(void *info);

void destroy_bstree_nodes(BSTreeNode *node);

// insert tanpa balancing
void insert_bstree(BSTree *tree, void *info, int (*compare)(const void *, const void *));

int get_height(BSTreeNode *node);

int max(int a, int b);

int get_balance(BSTreeNode *node);

BSTreeNode *right_rotate(BSTreeNode *y);

BSTreeNode *left_rotate(BSTreeNode *x);

BSTreeNode *insert_node_avl(BSTreeNode *node, void *info, int (*compare)(const void *, const void *));

// insert dengan balancing AVL
void insert_bstree_balance(BSTree *tree, void *info, int (*compare)(const void *, const void *));

// Fungsi untuk melakukan traversal in-order pada BSTree secara rekursif
void in_order_traversal_bstree_nodes(BSTreeNode *node, void (*visit)(void *));

#endif