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

DLList *dllist_create();
void dllist_destroy(DLList *list_ref);
void dllist_clear(DLList *list);

DLListNode *dllist_create_node(void *data);

// Insertion
void dllist_insert_front(DLList **list, void *data);
void dllist_insert_back(DLList **list, void *data);

// Deletion
void dllist_remove_front(DLList **list);
void dllist_remove_back(DLList **list);

// Traversal
void dllist_traverse_forward(DLList *list, void (*visit)(void *data));
void dllist_traverse_backward(DLList *list, void (*visit)(void *data));

#endif