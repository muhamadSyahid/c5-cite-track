/// Nama File   : DLList.c
///
/// Deskripsi   : File body untuk ADT Double Linked List Dinamis
///
/// Dibuat oleh : Hanifidin Ibrahim     (241511076)
///               Helga Athifa Hidayat  (241511077)
///               Hisyam Khaeru Umam    (241511078)
///               Ikhsan Satriadi       (241511080)
///               Muhamad Syahid        (241511081)
///
/// Tanggal     : 12-05-2025

#include "DLList/DLList.h"

#include <stdlib.h>
#include <stdio.h>

DLListNode *dllist_create_node(void *data)
{
  DLListNode *newNode = (DLListNode *)malloc(sizeof(DLListNode));
  if (newNode == NULL)
  {
    return NULL;
  }
  newNode->info = data;
  newNode->next = NULL;
  newNode->prev = NULL;
  return newNode;
}

DLList *dllist_create()
{
  DLList *list = (DLList *)malloc(sizeof(DLList));
  if (list == NULL)
  {
    printf("Error allocating memory for DLList\n");
    return NULL;
  }
  list->head = NULL;
  list->tail = NULL;
  list->size = 0;
  return list;
}

void dllist_clear(DLList *list)
{
  if (list == NULL)
  {
    return;
  }
  DLListNode *current = list->head;
  DLListNode *nextNode;
  while (current != NULL)
  {
    nextNode = current->next;
    free(current);
    current = nextNode;
  }
  list->head = NULL;
  list->tail = NULL;
  list->size = 0;
}

void dllist_destroy(DLList **list_ref)
{
  if (list_ref == NULL || *list_ref == NULL)
  {
    return;
  }
  dllist_clear(*list_ref); // Free all nodes
  free(*list_ref);         // Free the list structure
  *list_ref = NULL;        // Set the original pointer to NULL
}

void dllist_insert_front(DLList **list, void *data)
{
  if (list == NULL)
  {
    return;
  }
  DLListNode *newNode = dllist_create_node(data);
  if (newNode == NULL)
  {
    return;
  }

  if ((*list)->head == NULL)
  {
    (*list)->head = newNode;
    (*list)->tail = newNode;
  }
  else
  {
    newNode->next = (*list)->head;
    (*list)->head->prev = newNode;
    (*list)->head = newNode;
  }
  (*list)->size++; // Only one node
}

void dllist_insert_back(DLList **list, void *data)
{
  if (list == NULL)
  {
    return;
  }
  DLListNode *newNode = dllist_create_node(data);
  if (newNode == NULL)
  {
    return;
  }

  if ((*list)->tail == NULL)
  {
    (*list)->head = newNode;
    (*list)->tail = newNode;
  }
  else
  {
    newNode->prev = (*list)->tail;
    (*list)->tail->next = newNode;
    (*list)->tail = newNode;
  }
  (*list)->size++;
}

void dllist_remove_front(DLList **list)
{
  if (list == NULL || *list == NULL || (*list)->head == NULL)
  {
    return;
  }

  DLListNode *deleted_node = (*list)->head;
  if ((*list)->head == (*list)->tail)
  {
    (*list)->head = NULL;
    (*list)->tail = NULL;
  }
  else
  {
    (*list)->head = (*list)->head->next;
    (*list)->head->prev = NULL;
  }

  free(deleted_node);

  (*list)->size--;
}

void dllist_remove_back(DLList **list)
{
  if (list == NULL || *list == NULL || (*list)->tail == NULL)
  {
    return;
  }

  DLListNode *deleted_node = (*list)->tail;
  if ((*list)->head == (*list)->tail)
  {
    (*list)->head = NULL;
    (*list)->tail = NULL;
  }
  else
  {
    (*list)->tail = (*list)->tail->prev;
    (*list)->tail->next = NULL;
  }

  free(deleted_node);

  (*list)->size--;
}

void dllist_traverse_forward(DLList *list, void (*visit)(void *data))
{
  if (list == NULL || visit == NULL || list->head == NULL)
  {
    return;
  }
  DLListNode *current = list->head;
  while (current != NULL)
  {
    visit(current->info);
    current = current->next;
  }
}

void dllist_traverse_backward(DLList *list, void (*visit)(void *data))
{
  if (list == NULL || visit == NULL || list->tail == NULL)
  {
    return;
  }
  DLListNode *current = list->tail;
  while (current != NULL)
  {
    visit(current->info);
    current = current->prev;
  }
}

