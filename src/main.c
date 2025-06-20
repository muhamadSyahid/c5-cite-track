#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "Author/Author.h"
#include "Paper/Paper.h"
#include "Parser/Parser.h"

// Binary Search Tree untuk Author diurutkan berdasarkan nama
// Setiap Author memiliki daftar Paper yang ditulisnya dalam sebuah Double Linked List
BSTree *authors_tree = NULL;

// Binary Search Tree untuk Paper diurutkan berdasarkan judul
BSTree *papers_tree = NULL;

// Double Linked List untuk menyimpan Paper yang akan ditampilkan
DLList *shown_paper_list = NULL;

// Double Linked List untuk menyimpan Author yang akan ditampilkan
DLList *shown_author_list = NULL;

// Array of Paper pointers untuk menyimpan data Paper sementara
// yang diambil dari file dataset
Paper **papers = NULL;

// jumlah `papers`
int n_papers = 0;

void clear_input_buffer();
char *get_input();

// Fungsi untuk menampilkan daftar Paper dan aksi yang dapat dilakukan
void display_paper_actions(DLList *paper_list, Author *author);

// Fungsi untuk menampilkan daftar Author dan aksi yang dapat dilakukan
void display_author_actions(DLList *author_list);

// Fungsi untuk menampilkan statistik dan menu
void display_menu_and_stats();

clock_t start_time, end_time;

int main(int argc, char const *argv[])
{
  printf("Loading dataset, please wait...\n");

  start_time = clock();

  load_json_papers(&papers, &n_papers, "data/test.json");
  // load_json_papers(&papers, &n_papers, "data/s2orc_small.json");

  end_time = clock();
  double time_taken_parse = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
  printf("Time taken to load and parse data: %f seconds\n", time_taken_parse);

  papers_tree = bstree_create();
  authors_tree = bstree_create();
  shown_paper_list = dllist_create();
  shown_author_list = dllist_create();

  start_time = clock();

  // Insert papers ke BSTree papers_tree
  build_bstree_paper(&papers_tree, papers, n_papers, compare_paper_by_title);

  end_time = clock();
  double time_taken_paper = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
  printf("Time taken to load and build BSTree Paper: %f seconds\n", time_taken_paper);

  start_time = clock();

  // Insert papers ke BSTree authors_tree
  build_bstree_author(&authors_tree, papers, n_papers, compare_author_name);

  end_time = clock();
  double time_taken_author = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
  printf("Time taken to load and build BSTree Author: %f seconds\n", time_taken_author);

  int choice = 0;
  char *keyword = NULL; // Untuk menyimpan keyword pencarian

  do
  {
    display_menu_and_stats();
    scanf(" %d", &choice);
    if (choice == 0)
    {
      printf("Input tidak valid. Masukkan angka antara 1-4.\n");
      clear_input_buffer();
      choice = 0;
      continue;
    }

    clear_input_buffer();

    switch (choice)
    {
    case 1:
      get_popular_papers(papers, n_papers, &shown_paper_list, 100);

      display_paper_actions(shown_paper_list, NULL);

      dllist_clear(shown_paper_list);
      break;
    case 2:
      printf("Masukkan judul paper yang ingin dicari: ");

      keyword = get_input();

      search_paper_by_title(papers_tree->root, keyword, &shown_paper_list);

      display_paper_actions(shown_paper_list, NULL);

      dllist_clear(shown_paper_list);
      break;
    case 3:
      printf("Masukkan penulis paper yang ingin dicari: ");

      keyword = get_input();

      search_author(authors_tree->root, keyword, &shown_author_list);

      display_author_actions(shown_author_list);

      dllist_clear(shown_author_list);
      break;
    case 4:
      printf("Keluar dari program. Terima kasih!\n");
      break;
    default:
      printf("Pilihan tidak valid. Silakan coba lagi.\n");
      clear_input_buffer();
    }

    if (choice != 4)
    {
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

void display_paper_actions(DLList *paper_list, Author *author)
{
  if (paper_list == NULL || paper_list->size == 0)
  {
    printf("Tidak ada paper yang ditampilkan.\n");
    printf("Tekan Enter untuk melanjutkan...");
    getchar();
    return;
  }

  int page_size = 10;
  int current_page = 1;
  char *action = NULL;

  while (true)
  {
    system("clear");

    int total_items = paper_list->size;
    int total_pages = (total_items + page_size - 1) / page_size;
    if (current_page > total_pages && total_pages > 0)
    {
      current_page = total_pages;
    }

    printf("==================================================\n");
    printf("                  DAFTAR PAPER\n");
    printf("==================================================\n");

    if (author != NULL)
    {
      print_author(author);
      printf("--------------------------------------------------\n");
    }

    printf("Halaman %d dari %d (%d total paper)\n", current_page, total_pages, total_items);
    printf("--------------------------------------------------\n");

    DLListNode *current_node = paper_list->head;
    int start_index = (current_page - 1) * page_size;
    for (int i = 0; i < start_index; i++)
    {
      if (current_node != NULL)
      {
        current_node = current_node->next;
      }
    }

    int items_on_page = 0;
    DLListNode *iter = current_node;
    for (int i = 0; i < page_size && iter != NULL; i++)
    {
      Paper *paper = (Paper *)iter->info;
      printf("%2d. %s (%d)\n", i + 1, paper->title, paper->year);
      iter = iter->next;
      items_on_page++;
    }

    printf("--------------------------------------------------\n");
    printf("[1-%d] Detail | [n] Next | [p] Prev | [q] Kembali\n", items_on_page);
    printf("[h] Urutkan Populer(desc) | [y] Urutkan Tahun(desc) | [t] Urutkan Judul(asc) | [a] Urutkan Penulis(asc)\n");
    printf("Aksi: ");

    action = get_input();

    if (action == NULL || strlen(action) == 0)
    {
      free(action);
      continue;
    }

    if (isdigit(action[0]))
    {
      int selection = atoi(action);
      if (selection >= 1 && selection <= items_on_page)
      {
        DLListNode *selected_node = current_node;
        for (int i = 0; i < selection - 1; i++)
        {
          selected_node = selected_node->next;
        }
        print_paper(selected_node->info);
        printf("\nTekan Enter untuk kembali...");
        getchar();
      }
    }
    else
    {
      switch (tolower(action[0]))
      {
      case 'n':
        if (current_page < total_pages)
          current_page++;
        break;
      case 'p':
        if (current_page > 1)
          current_page--;
        break;
      case 'h':
        dllist_sort_asc(&paper_list, compare_paper_by_incitations_desc);
        current_page = 1;
        break;
      case 'y':
        dllist_sort_dsc(&paper_list, compare_paper_by_year);
        current_page = 1;
        break;
      case 't':
        dllist_sort_asc(&paper_list, compare_paper_by_title);
        current_page = 1;
        break;
      case 'a':
        dllist_sort_asc(&paper_list, compare_paper_by_author);
        current_page = 1;
        break;
      case 'q':
        free(action);
        return;
      default:
        break;
      }
    }
    free(action);
  }
}

void display_author_actions(DLList *author_list)
{
  if (author_list == NULL || author_list->size == 0)
  {
    printf("Tidak ada penulis yang ditampilkan.\n");
    printf("Tekan Enter untuk melanjutkan...");
    getchar();
    return;
  }

  int page_size = 10;
  int current_page = 1;
  char *action = NULL;

  while (true)
  {
    system("clear");
    int total_items = author_list->size;
    int total_pages = (total_items + page_size - 1) / page_size;

    if (current_page > total_pages && total_pages > 0)
    {
      current_page = total_pages;
    }

    printf("==================================================\n");
    printf("                  DAFTAR PENULIS\n");
    printf("==================================================\n");
    printf("Halaman %d dari %d (%d total penulis)\n", current_page, total_pages, total_items);
    printf("--------------------------------------------------\n");

    DLListNode *current_node = author_list->head;
    int start_index = (current_page - 1) * page_size;
    for (int i = 0; i < start_index; i++)
    {
      if (current_node != NULL)
      {
        current_node = current_node->next;
      }
    }

    int items_on_page = 0;
    DLListNode *iter = current_node;
    for (int i = 0; i < page_size && iter != NULL; i++)
    {
      Author *author = (Author *)iter->info;
      printf("%2d. %s (%d paper)\n", i + 1, author->name, author->papers->size);
      iter = iter->next;
      items_on_page++;
    }

    printf("--------------------------------------------------\n");
    printf("[1-%d] Lihat Paper | [n] Next | [p] Prev | [q] Kembali ke Menu Utama\n", items_on_page);
    printf("Aksi: ");

    action = get_input();

    if (action == NULL || strlen(action) == 0)
    {
      free(action);
      continue;
    }

    if (isdigit(action[0]))
    {
      int selection = atoi(action);
      if (selection >= 1 && selection <= items_on_page)
      {
        DLListNode *selected_node = current_node;
        for (int i = 0; i < selection - 1; i++)
        {
          selected_node = selected_node->next;
        }
        Author *selected_author = (Author *)selected_node->info;
        // Panggil penampil paper untuk daftar paper milik penulis terpilih
        display_paper_actions(selected_author->papers, selected_author);
      }
    }
    else
    {
      switch (tolower(action[0]))
      {
      case 'n':
        if (current_page < total_pages)
          current_page++;
        break;
      case 'p':
        if (current_page > 1)
          current_page--;
        break;
      case 'q':
        free(action);
        return;
      default:
        break;
      }
    }
    free(action);
  }
}

void display_menu_and_stats()
{
  int paper_count = papers_tree->size;
  int author_count = authors_tree->size;
  int min_y = get_year_min(papers_tree->root);
  int max_y = get_year_max(papers_tree->root);

  printf("\n==================================================\n");
  printf("                     CITETRACK\n");
  printf("==================================================\n");
  printf("Jumlah paper: %d\n", paper_count);
  printf("Jumlah author: %d\n", author_count);
  printf("Rentang tahun paper: %d - %d\n", min_y, max_y);
  printf("--------------------------------------------------\n");
  printf("\nMenu Utama:\n");
  printf("1. Lihat Paper Populer\n");
  printf("2. Cari Paper Berdasarkan Judul\n");
  printf("3. Cari Paper Berdasarkan Penulis\n");
  printf("4. Keluar\n");
  printf("--------------------------------------------------\n");
  printf("Pilih menu (1-4): ");
}

char *get_input()
{
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

void clear_input_buffer()
{
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}