/// Nama File   : DLList.h
///
/// Deskripsi   : File header untuk ADT Double Linked List Dinamis
///
/// Dibuat oleh : Hanifidin Ibrahim     (241511076)
///               Helga Athifa Hidayat  (241511077)
///               Hisyam Khaeru Umam    (241511078)
///               Ikhsan Satriadi       (241511080)
///               Muhamad Syahid        (241511081)
///
/// Tanggal     : 12-05-2025

#ifndef DLLIST_H
#define DLLIST_H

/// Node untuk Double Linked List
typedef struct DLListNode DLListNode;
struct DLListNode
{
  void *info; // pointer ke data generik
  DLListNode *next;
  DLListNode *prev;
};

/// Double Linked List
typedef struct
{
  DLListNode *head;
  DLListNode *tail;
  int size;
} DLList;

#endif