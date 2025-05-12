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

#endif