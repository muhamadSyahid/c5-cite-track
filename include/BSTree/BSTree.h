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

BSTree *bstree_create();

void bstree_destroy(BSTree *tree);

BSTreeNode *bstree_create_node(void *info);

void bstree_destroy_nodes(BSTreeNode *node);

// insert tanpa balancing
void bstree_insert(BSTree *tree, void *info, int (*compare)(const void *, const void *));

int bstree_get_height(BSTreeNode *node);

int max(int a, int b);

int bstree_get_balance(BSTreeNode *node);

BSTreeNode *bstree_right_rotate(BSTreeNode *y);

BSTreeNode *bstree_left_rotate(BSTreeNode *x);

BSTreeNode *bstree_insert_node_avl(BSTreeNode *node, void *info, int (*compare)(const void *, const void *));

// insert dengan balancing AVL
void bstree_insert_balance(BSTree *tree, void *info, int (*compare)(const void *, const void *));

// Fungsi untuk melakukan traversal in-order pada BSTree secara rekursif
void bstree_in_order_traversal(BSTreeNode *node, void (*visit)(void *));

#endif