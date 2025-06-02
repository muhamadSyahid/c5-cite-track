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
#include "Paper/Paper.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fungsi untuk menukar dua paper
void swap_papers(DLListNode *a, DLListNode *b) {
    Paper *temp = (Paper*)a->info;
    a->info = b->info;
    b->info = temp;
}

// Fungsi untuk mengurutkan paper berdasarkan kriteria yang diberikan
void sort_papers(DLList *list, int (*cmp)(Paper*, Paper*)) {
    if (list == NULL || list->size < 2) {
        return;  // Tidak perlu diurutkan jika list kosong atau hanya ada satu elemen
    }

    int swapped;
    DLListNode *current;
    DLListNode *last = NULL;

    do {
        swapped = 0;
        current = list->head;

        while (current->next != last) {
            Paper *current_paper = (Paper*)current->info;
            Paper *next_paper = (Paper*)current->next->info;

            // Gunakan fungsi pembanding yang diberikan untuk mengurutkan
            if (cmp(current_paper, next_paper) > 0) {
                swap_papers(current, current->next);
                swapped = 1;
            }
            current = current->next;
        }
        last = current; // Last is now the sorted paper at the end
    } while (swapped);
}

// Fungsi pembanding untuk sorting berdasarkan tahun
int compare_by_year(Paper *a, Paper *b) {
    return a->year - b->year;
}

// Fungsi pembanding untuk sorting berdasarkan judul
int compare_by_title(Paper *a, Paper *b) {
    return strcmp(a->title, b->title);
}

// Fungsi pembanding untuk sorting berdasarkan penulis
int compare_by_author(Paper *a, Paper *b) {
    // Asumsikan a->authors[0] adalah penulis utama
    return strcmp(a->authors[0], b->authors[0]);
}

