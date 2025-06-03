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

int kunjungan = 0;

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

void search_paper_by_title(BSTreeNode *node, const char *title, DLList **paper_list)
{
  if (node == NULL)
  {
    return;
  }

  search_paper_by_title(node->left, title, paper_list);

  Paper *paper = (Paper *)node->info;
  if (strstr(paper->title, title) != NULL) // Mencari substring
  {
    dllist_insert_back(paper_list, paper);
  }

  search_paper_by_title(node->right, title, paper_list);
}

Paper *search_exact_paper_by_title(BSTreeNode *node, const char *title)
{
  kunjungan++;
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

// Fungsi rekursif untuk mengumpulkan semua paper dari BST ke dalam array.static
void collect_papers_recursive(BSTreeNode *current_node, Paper ***papers_array_ptr, int *count_ptr, int *capacity_ptr)
{
  if (current_node == NULL)
  {
    return;
  }

  // Traversal in-order (kiri, proses, kanan)
  collect_papers_recursive(current_node->left, papers_array_ptr, count_ptr, capacity_ptr);

  if (current_node->info != NULL)
  {
    if (*count_ptr >= *capacity_ptr)
    {
      int new_capacity = (*capacity_ptr == 0) ? 10 : *capacity_ptr * 2; // Kapasitas awal atau gandakan
      Paper **temp = (Paper **)realloc(*papers_array_ptr, new_capacity * sizeof(Paper *));
      if (temp == NULL)
      {
        fprintf(stderr, "Error: Gagal realokasi memori untuk array paper dalam collect_papers_recursive.\n");
        // Bisa dipertimbangkan untuk menghentikan pengumpulan atau keluar
        return;
      }
      *papers_array_ptr = temp;
      *capacity_ptr = new_capacity;
    }
    (*papers_array_ptr)[*count_ptr] = (Paper *)current_node->info;
    (*count_ptr)++;
  }

  collect_papers_recursive(current_node->right, papers_array_ptr, count_ptr, capacity_ptr);
}

// Fungsi pembanding untuk qsort, mengurutkan Paper berdasarkan in_citation_count secara descending.
static int compare_papers_by_incitations_desc(const void *a, const void *b)
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

void get_popular_papers(BSTreeNode *root_node_of_papers_tree, DLList **output_paper_list, int n_top_papers)
{
  if (output_paper_list == NULL || n_top_papers <= 0)
  {
    fprintf(stderr, "Error: Parameter output_paper_list tidak valid atau n_top_papers <= 0.\n");
    // Jika output_paper_list valid tapi *output_paper_list NULL, dan n_top_papers > 0,
    // kita mungkin tetap ingin membuat list kosong.
    if (output_paper_list && *output_paper_list == NULL && n_top_papers > 0)
    {
      *output_paper_list = dllist_create();
      if (*output_paper_list == NULL)
      {
        fprintf(stderr, "Error: Gagal membuat DLList untuk output_paper_list (kasus parameter invalid).\n");
      }
    }
    return;
  }

  // Pastikan output_paper_list sudah diinisialisasi atau buat baru
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
    // Opsi: Bersihkan list jika mungkin sudah ada data lama dan kita ingin menggantinya.
    // Ini tergantung pada apakah dllist_clear ada dan apa perilakunya (membebaskan node vs. data).
    // Jika Anda ingin fungsi ini mengisi list yang mungkin sudah ada,
    // pastikan untuk menghapus konten lama terlebih dahulu jika itu yang diinginkan.
    // Misalnya: dllist_clear(*output_paper_list); (jika ada dan sesuai)
  }

  if (root_node_of_papers_tree == NULL)
  {
    // Tree kosong, tidak ada paper untuk diproses. List output akan tetap kosong (atau seperti setelah clear).
    return;
  }

  Paper **all_papers_array = NULL;
  int paper_count = 0;
  int array_capacity = 0; // Kapasitas awal akan diatur di collect_papers_recursive

  collect_papers_recursive(root_node_of_papers_tree, &all_papers_array, &paper_count, &array_capacity);

  if (paper_count == 0 || all_papers_array == NULL)
  {
    // Tidak ada paper yang terkumpul atau terjadi error saat pengumpulan
    if (all_papers_array)
    {
      free(all_papers_array); // Bebaskan array jika sempat dialokasi
    }
    return; // List output akan kosong
  }

  // Urutkan paper yang terkumpul berdasarkan in_citation_count secara descending
  qsort(all_papers_array, paper_count, sizeof(Paper *), compare_papers_by_incitations_desc);

  // Masukkan N paper teratas ke DLList output
  // Prototipe: void dllist_insert_back(DLList **list, void *data);
  int num_to_add = (n_top_papers < paper_count) ? n_top_papers : paper_count;
  for (int i = 0; i < num_to_add; i++)
  {
    if (all_papers_array[i] != NULL)
    { // Pemeriksaan keamanan
      dllist_insert_back(output_paper_list, all_papers_array[i]);
      // Asumsi: dllist_insert_back akan mengupdate (*output_paper_list)->size secara internal.
      // Jika tidak, Anda perlu: (*output_paper_list)->size++;
    }
  }

  // Bebaskan memori yang digunakan oleh array sementara
  free(all_papers_array);
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
