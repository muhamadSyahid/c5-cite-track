/// Nama File   : Author.h
///
/// Deskripsi   : File header untuk ADT Author yang memanfaatkan ADT
///               Binary Search Tree dan ADT Double Linked List
///
/// Dibuat oleh : Hanifidin Ibrahim     (241511076)
///               Helga Athifa Hidayat  (241511077)
///               Hisyam Khaeru Umam    (241511078)
///               Ikhsan Satriadi       (241511080)
///               Muhamad Syahid        (241511081)
///
/// Tanggal     : 12-05-2025

#ifndef AUTHOR_H
#define AUTHOR_H

#include "BSTree/BSTree.h"
#include "DLList/DLList.h"

/// Struct untuk menyimpan data Author
typedef struct
{
  char *name;     // nama author
  DLList *papers; // list Paper
} Author;

#endif