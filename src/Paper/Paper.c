/// Nama File   : Paper.c
///
/// Deskripsi   : File body untuk ADT Paper yang memanfaatkan ADT
///               Binary Search Tree untuk menyimpan data Author dan
///               Double Linked List untuk menyimpan data Paper
///
/// Dibuat oleh : Hanifidin Ibrahim     (241511076)
///               Helga Athifa Hidayat  (241511077)
///               Hisyam Khaeru Umam    (241511078)
///               Ikhsan Satriadi       (241511080)
///               Muhamad Syahid        (241511081)
///
/// Tanggal     : 12-05-2025

#include "Paper/Paper.h"
#include "DLList/DLList.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

Paper *paper_create()
{
  Paper *paper = (Paper *)malloc(sizeof(Paper));
  if (paper == NULL)
  {
    printf("Alokasi memori untuk Paper gagal.\n");
    return NULL;
  }

  paper->id = NULL;
  paper->title = NULL;
  paper->paper_abstract = NULL;
  paper->in_citations = NULL;
  paper->out_citations = NULL;

  paper->in_citation_count = 0;
  paper->out_citation_count = 0;

  paper->year = 0;
  paper->authors = NULL;

  paper->author_count = 0;

  return paper;
}

void print_paper(void *data)
{
  Paper *paper = (Paper *)data;
  if (paper == NULL)
  {
    printf("Paper is NULL\n");
    return;
  }

  printf("ID: %s\n", paper->id);
  printf("Title: %s\n", paper->title);
  printf("Abstract: %s\n", paper->paper_abstract);
  printf("Year: %d\n", paper->year);

  printf("Authors:\n");
  for (int i = 0; i < paper->author_count; i++)
  {
    printf("- %s\n", paper->authors[i]);
  }

  printf("In Citations:\n");
  for (int i = 0; i < paper->in_citation_count; i++)
  {
    printf("- %s\n", paper->in_citations[i]);
  }

  printf("Out Citations:\n");
  for (int i = 0; i < paper->out_citation_count; i++)
  {
    printf("- %s\n", paper->out_citations[i]);
  }
}

void build_bstree_paper(BSTree **tree, Paper **paper, int n_papers, int (*compare)(const void *, const void *))
{
  *tree = bstree_create();
  if (*tree == NULL)
  {
    *tree = bstree_create();
    if (*tree == NULL)
    {
      printf("Error alokasi memori untuk BSTree\n");
      return;
    }
  }
  if (paper == NULL || n_papers <= 0 || compare == NULL)
  {
    printf("Parameter untuk build_bstree_paper invalid!\n");
    return;
  }

  for (int i = 0; i < n_papers; i++)
  {
    if (paper[i] == NULL)
    {
      // printf("Paper di index %d NULL\n", i);
      continue;
    }
    bstree_insert(*tree, paper[i], (int (*)(const void *, const void *))compare);
  }
}

void build_balance_bstree_paper(BSTree **tree, Paper **paper, int n_papers, int (*compare)(const void *, const void *))
{
  *tree = bstree_create();
  if (*tree == NULL)
  {
    printf("Error alokasi memori untuk BSTree\n");
    return;
  }
  if (paper == NULL || n_papers <= 0 || compare == NULL)
  {
    printf("Parameter untuk build_bstree_paper invalid!\n");
    return;
  }

  for (int i = 0; i < n_papers; i++)
  {
    if (paper[i] == NULL)
    {
      printf("Paper di index %d NULL\n", i);
      continue;
    }
    bstree_insert_balance(*tree, paper[i], (int (*)(const void *, const void *))compare);
  }
}

int compare_paper_by_title(const void *paper1, const void *paper2)
{
  if (paper1 == NULL || paper2 == NULL)
  {
    printf("Satu atau kedua paper NULL di compare_paper_by_title\n");
    return 0;
  }

  // Cast void pointer ke Paper pointer
  Paper *p1 = (Paper *)paper1;
  Paper *p2 = (Paper *)paper2;

  if (p1->title == NULL || p2->title == NULL)
  {
    printf("Satu atau kedua judul NULL di compare_paper_by_title\n");
    return 0;
  }

  return strcmp(p1->title, p2->title);
}

int compare_paper_by_year(const void *paper1, const void *paper2)
{
  if (paper1 == NULL || paper2 == NULL)
  {
    printf("Satu atau kedua paper NULL di compare_paper_by_year\n");
    return 0;
  }

  Paper *p1 = (Paper *)paper1;
  Paper *p2 = (Paper *)paper2;

  return p1->year - p2->year;
}

int compare_paper_by_author(const void *paper1, const void *paper2)
{
  if (paper1 == NULL || paper2 == NULL)
  {
    printf("Satu atau kedua paper NULL di compare_paper_by_author\n");
    return 0;
  }

  Paper *p1 = (Paper *)paper1;
  Paper *p2 = (Paper *)paper2;

  if (p1->authors[0] == NULL || p2->authors[0] == NULL)
  {
    printf("Satu atau kedua author NULL di compare_paper_by_author\n");
    return 0;
  }

  return strcmp(p1->authors[0], p2->authors[0]); // Asumsi kita membandingkan penulis pertama
}

int compare_papers_by_incitations_desc(const void *a, const void *b)
{
  Paper *paper_a = *(Paper **)a;
  Paper *paper_b = *(Paper **)b;

  // Penanganan jika ada paper NULL (seharusnya tidak terjadi jika data valid)
  if (paper_a == NULL && paper_b == NULL)
    return 0;
  if (paper_a == NULL)
    return 1; // Anggap NULL lebih kecil, jadi ditaruh di akhir (untuk descending)
  if (paper_b == NULL)
    return -1; // Anggap non-NULL lebih besar

  // Urutkan berdasarkan in_citation_count secara descending
  if (paper_a->in_citation_count < paper_b->in_citation_count)
  {
    return 1;
  }
  if (paper_a->in_citation_count > paper_b->in_citation_count)
  {
    return -1;
  }

  // Kriteria pengurutan sekunder jika jumlah sitasi sama (opsional)
  // Misalnya, berdasarkan tahun (terbaru dulu)
  if (paper_a->year < paper_b->year)
    return 1; // tahun lebih kecil berarti lebih tua, taruh di belakang
  if (paper_a->year > paper_b->year)
    return -1; // tahun lebih besar berarti lebih baru, taruh di depan

  return 0;
}

void search_paper_by_title(BSTreeNode *node, const char *title, DLList **paper_list)
{
  if (node == NULL || node->info == NULL)
  {
    return;
  }

  Paper *current_paper = (Paper *)node->info;
  if (current_paper->title == NULL)
  {
    return;
  }

  size_t key_len = strlen(title);

  int cmp = strncasecmp(title, current_paper->title, key_len);

  if (cmp < 0)
  {
    search_paper_by_title(node->left, title, paper_list);
  }
  else if (cmp > 0)
  {
    search_paper_by_title(node->right, title, paper_list);
  }
  else
  {
    dllist_insert_back(paper_list, current_paper);
    search_paper_by_title(node->left, title, paper_list);
    search_paper_by_title(node->right, title, paper_list);
  }
}

Paper *search_exact_paper_by_title(BSTreeNode *node, const char *title)
{
  if (node == NULL)
  {
    return NULL;
  }

  Paper *paper = (Paper *)node->info;

  int compare = compare_paper_by_title(title, paper->title);

  if (compare == 0)
  {
    return paper;
  }
  else if (compare < 0)
  {
    return search_exact_paper_by_title(node->left, title);
  }
  else
  {
    return search_exact_paper_by_title(node->right, title);
  }
}

void get_popular_papers(Paper **paper_array, int n_papers, DLList **output_paper_list, int n_top_papers)
{
  // Validasi parameter
  if (paper_array == NULL || n_papers <= 0 || output_paper_list == NULL || n_top_papers <= 0)
  {
    fprintf(stderr, "Error: Parameter tidak valid (paper_array NULL, n_papers <= 0, output_paper_list NULL, atau n_top_papers <= 0).\n");
    // Inisialisasi list kosong jika output_paper_list valid tapi *output_paper_list NULL
    if (output_paper_list && *output_paper_list == NULL && n_top_papers > 0)
    {
      *output_paper_list = dllist_create();
      if (*output_paper_list == NULL)
      {
        fprintf(stderr, "Error: Gagal membuat DLList untuk output_paper_list.\n");
      }
    }
    return;
  }

  // Pastikan output_paper_list sudah diinisialisasi
  if (*output_paper_list == NULL)
  {
    *output_paper_list = dllist_create();
    if (*output_paper_list == NULL)
    {
      fprintf(stderr, "Error: Gagal membuat DLList untuk output_paper_list.\n");
      return;
    }
  }
  else
  {
    // Opsional: Bersihkan list jika sudah ada data lama
    // dllist_clear(*output_paper_list); // Uncomment jika fungsi ini ada dan sesuai kebutuhan
  }

  // Buat salinan array untuk menghindari modifikasi array asli
  Paper **temp_array = (Paper **)malloc(n_papers * sizeof(Paper *));
  if (temp_array == NULL)
  {
    fprintf(stderr, "Error: Gagal alokasi memori untuk temp_array.\n");
    return;
  }

  // Salin elemen dari paper_array ke temp_array
  for (int i = 0; i < n_papers; i++)
  {
    temp_array[i] = paper_array[i];
  }

  // Urutkan array berdasarkan in_citation_count secara descending
  qsort(temp_array, n_papers, sizeof(Paper *), compare_papers_by_incitations_desc);

  // Masukkan N paper teratas ke DLList output
  int num_to_add = (n_top_papers < n_papers) ? n_top_papers : n_papers;
  for (int i = 0; i < num_to_add; i++)
  {
    if (temp_array[i] != NULL)
    {
      dllist_insert_back(output_paper_list, temp_array[i]);
    }
  }

  // Bebaskan memori temp_array
  free(temp_array);
}

void show_paper_detail(const Paper *paper)
{
  if (paper == NULL)
  {
    printf("Detail paper tidak tersedia (pointer NULL).\n");
    return;
  }

  printf("--- Detail Paper ---\n");
  printf("ID: %s\n", (paper->id != NULL) ? paper->id : "[Tidak Ada ID]");
  printf("Judul: %s\n", (paper->title != NULL) ? paper->title : "[Tidak Ada Judul]");
  printf("Tahun Publikasi: %d\n", paper->year);
  printf("Abstrak:\n%s\n", (paper->paper_abstract != NULL) ? paper->paper_abstract : "[Tidak Ada Abstrak]");

  // Menampilkan daftar penulis
  if (paper->authors != NULL && paper->author_count > 0)
  {
    printf("Penulis:\n");
    for (int i = 0; i < paper->author_count; i++)
    {
      printf("  %d. %s\n", i + 1, (paper->authors[i] != NULL) ? paper->authors[i] : "[Nama Penulis Tidak Tersedia]");
    }
  }
  else
  {
    printf("Penulis: Tidak tersedia atau tidak ada.\n");
  }

  // Menampilkan sitasi masuk
  if (paper->in_citations != NULL && paper->in_citation_count > 0)
  {
    printf("Sitasi Masuk (%d):\n", paper->in_citation_count);
    for (int i = 0; i < paper->in_citation_count; i++)
    {
      printf("  - %s\n", (paper->in_citations[i] != NULL) ? paper->in_citations[i] : "[ID Sitasi Tidak Tersedia]");
    }
  }
  else
  {
    printf("Sitasi Masuk: Tidak ada.\n");
  }

  // Menampilkan sitasi keluar
  if (paper->out_citations != NULL && paper->out_citation_count > 0)
  {
    printf("Sitasi Keluar (%d):\n", paper->out_citation_count);
    for (int i = 0; i < paper->out_citation_count; i++)
    {
      printf("  - %s\n", (paper->out_citations[i] != NULL) ? paper->out_citations[i] : "[ID Sitasi Tidak Tersedia]");
    }
  }
  else
  {
    printf("Sitasi Keluar: Tidak ada.\n");
  }
}

int get_year_min(BSTreeNode *node)
{
  if (node == NULL)
  {
    return INT_MAX;
  }

  int min_year = node->info ? ((Paper *)node->info)->year : INT_MAX;

  int left_min = get_year_min(node->left);
  int right_min = get_year_min(node->right);

  if (left_min < min_year)
  {
    min_year = left_min;
  }
  if (right_min < min_year)
  {
    min_year = right_min;
  }

  return min_year;
}

int get_year_max(BSTreeNode *node)
{
  if (node == NULL)
  {
    return INT_MIN;
  }

  int max_year = node->info ? ((Paper *)node->info)->year : INT_MIN;

  int left_max = get_year_max(node->left);
  int right_max = get_year_max(node->right);

  if (left_max > max_year)
  {
    max_year = left_max;
  }
  if (right_max > max_year)
  {
    max_year = right_max;
  }

  return max_year;
}