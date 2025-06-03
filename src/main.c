#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Author/Author.h"
#include "Paper/Paper.h"
#include "Parser/Parser.h"

// Binary Search Tree untuk Author diurutkan berdasarkan nama
// Setiap Author memiliki daftar Paper yang ditulisnya dalam sebuah Double Linked List
BSTree *authors_tree = NULL;

// Binary Search Tree untuk Paper diurutkan berdasarkan judul
BSTree *papers_tree = NULL;

// Binary Search Tree untuk Paper yang sudah di-balance (untuk perbandingan)
BSTree *balance_papers_tree = NULL;

// Double Linked List untuk menyimpan Paper yang akan ditampilkan
DLList *shown_paper_list = NULL;

// Double Linked List untuk menyimpan Author yang akan ditampilkan
DLList *shown_author_list = NULL;

// Array of Paper pointers untuk menyimpan data Paper sementara
// yang diambil dari file dataset
Paper **papers = NULL;

int n_papers = 0;

int counter = 0;

void print_author_name(void *data)
{
    Author *paper = (Author *)data;
    if (paper == NULL)
    {
        return;
    }
    printf("%d: %s\n", ++counter, paper->name);
}

void print_title(void *data)
{
    Paper *paper = (Paper *)data;
    if (paper == NULL)
    {
        return;
    }
    printf("%d: %s\n", ++counter, paper->title);
}

void clear_input_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

char *get_input()
{
    clear_input_buffer();

    char *input = (char *)malloc(256 * sizeof(char));
    if (fgets(input, 256, stdin) != NULL)
    {
        // Hapus newline di akhir string jika ada
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n')
        {
            input[len - 1] = '\0';
        }
    }
    else
    {
        printf("Gagal membaca input.\n");
        free(input);
        return NULL;
    }
    return input;
}

// Fungsi untuk menampilkan statistik dan menu
void display_menu_and_stats()
{
    int paper_count = papers_tree->size;
    int author_count = authors_tree->size;
    int min_y = get_year_min(papers_tree->root);
    int max_y = get_year_max(papers_tree->root);

    if (paper_count > 0)
    {
        // get_paper_year_range(&min_y, &max_y);
    }

    printf("\n==================================================\n");
    printf("                  CiteTrack System\n");
    printf("==================================================\n");
    printf("Jumlah paper: %d\n", paper_count);
    printf("Jumlah author: %d\n", author_count);
    printf("Rentang tahun paper: %d - %d\n", min_y, max_y);
    // if (paper_count > 0 && min_y != 0)
    // {
    //     printf("Rentang tahun paper: %d - %d\n", min_y, max_y);
    // }
    // else
    // {
    //     printf("Rentang tahun paper: Data tidak tersedia\n");
    // }
    printf("--------------------------------------------------\n");
    printf("\nMenu Utama:\n");
    printf("1. Lihat Paper Populer\n");
    printf("2. Cari Paper Berdasarkan Judul\n");
    printf("3. Cari Paper Berdasarkan Penulis\n");
    printf("4. Keluar\n");
    printf("--------------------------------------------------\n");
    printf("Pilih menu (1-4): ");
}

void display_paper_actions()
{
    char *action = NULL;
    printf("\n[1-%d] Show paper detail | asc: Ascending | dsc: Descending\n",
           shown_paper_list->size);
    printf("Aksi: ");
    action = get_input();
}

void display_author_actions()
{
    char *action = NULL;
    printf("\n[1-%d] Show Author papers/detail | asc: Ascending | dsc: Descending\n",
           shown_author_list->size);
    printf("Aksi: ");
    action = get_input();
}

int main(int argc, char const *argv[])
{
    load_json_papers(&papers, &n_papers, "data/s2orc_small_part_2.json");

    papers_tree = bstree_create();
    authors_tree = bstree_create();
    shown_paper_list = dllist_create();
    shown_author_list = dllist_create();

    // Insert papers ke BSTree papers_tree
    build_bstree_paper(&papers_tree, papers, n_papers, compare_paper_by_title);

    // Insert papers ke BSTree authors_tree
    build_bstree_author(&authors_tree, papers, n_papers, compare_author_name);

    // Dashboard & Menu
    int choice;

    do
    {
        display_menu_and_stats();
        if (scanf("%d", &choice) != 1)
        {
            printf("Input tidak valid. Masukkan angka antara 1-4.\n");
            clear_input_buffer(); // Bersihkan buffer input yang salah
            choice = 0;           // Atur pilihan agar loop berlanjut
            printf("Tekan Enter untuk melanjutkan...");
            getchar(); // Tunggu user menekan enter
            continue;
        }

        char *keyword = NULL;

        switch (choice)
        {
        case 1:
            // Reset counter
            counter = 0;

            get_popular_papers(papers_tree->root, &shown_paper_list, 10);
            dllist_traverse_forward(shown_paper_list, print_title);

            display_paper_actions();

            dllist_clear(shown_paper_list);

            counter = 0; // Reset counter
            break;
        case 2:
            printf("Masukkan judul paper yang ingin dicari: ");

            keyword = get_input();

            // Reset counter
            counter = 0;

            search_paper_by_title(papers_tree->root, keyword, &shown_paper_list);
            dllist_traverse_forward(shown_paper_list, print_title);

            display_paper_actions();

            dllist_clear(shown_paper_list);

            counter = 0; // Reset counter
            break;
        case 3:
            printf("Masukkan penulis paper yang ingin dicari: ");

            keyword = get_input();

            // Reset counter
            counter = 0;

            search_author(authors_tree->root, keyword, &shown_author_list);
            dllist_traverse_forward(shown_author_list, print_author_name);

            display_author_actions();
            dllist_clear(shown_author_list);

            counter = 0; // Reset counter setelah pencetakan

            break;
        case 4:
            printf("Keluar dari program. Terima kasih!\n");
            break;
        default:
            printf("Pilihan tidak valid. Silakan coba lagi.\n");
            printf("Tekan Enter untuk kembali ke menu...");
            clear_input_buffer();
            getchar();
        }

        // tekan enter untuk melanjutkan
        if (choice != 4)
        {
            printf("Tekan Enter untuk melanjutkan...");
            getchar();
            system("clear");
        }
    } while (choice != 4);

    // Akhir program
    bstree_destroy(authors_tree);
    bstree_destroy(papers_tree);
    dllist_destroy(shown_paper_list);
    free(papers);

    return 0;
}
