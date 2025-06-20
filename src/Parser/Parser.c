#include "Parser/Parser.h"

#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <limits.h>

static cJSON *json = NULL;

const char *get_filename_ext(const char *filename)
{
  const char *dot = strrchr(filename, '.');
  if (!dot || dot == filename)
    return "";
  return dot + 1;
}

int count_lines(const char *file_path)
{
  FILE *file;
  int lines = 0;
  int ch;

  file = fopen(file_path, "r");
  if (file == NULL)
  {
    perror("Error membuka file untuk menghitung baris");
    return -1; // Mengembalikan -1 untuk menunjukkan error
  }

  while ((ch = fgetc(file)) != EOF)
  {
    if (ch == '\n')
    {
      lines++;
    }
  }

  if (lines == 0 && ftell(file) > 0)
  {
    lines = 1;
  }
  else if (ftell(file) > 0 && ch != '\n')
  {
    fseek(file, -1, SEEK_END);
    if (fgetc(file) != '\n')
    {
      lines++;
    }
  }

  fclose(file);
  return lines;
}

char *get_json_string(const char *file)
{
  FILE *fp;
  long file_size;
  char *buffer;

  fp = fopen(file, "rb");
  if (fp == NULL)
    return NULL;

  fseek(fp, 0, SEEK_END);
  file_size = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  buffer = (char *)malloc(file_size + 1);
  if (buffer == NULL)
  {
    fclose(fp);
    return NULL;
  }

  size_t bytes_read = fread(buffer, 1, file_size, fp);
  if (bytes_read < (size_t)file_size)
  {
    free(buffer);
    fclose(fp);
    return NULL;
  }

  buffer[file_size] = '\0';

  fclose(fp);
  return buffer;
}

Paper *get_paper_from_json(const char *json_str)
{
  Paper *paper = paper_create();
  if (paper == NULL)
  {
    printf("Alokasi memori untuk Paper gagal.\n");
    return NULL;
  }

  json = cJSON_Parse(json_str);
  if (json == NULL)
  {
    printf("Error parsing JSON: %s\n", cJSON_GetErrorPtr());
    free(paper);
    return NULL;
  }

  cJSON *id_json = cJSON_GetObjectItemCaseSensitive(json, "id");
  cJSON *title_json = cJSON_GetObjectItemCaseSensitive(json, "title");
  cJSON *abstract_json = cJSON_GetObjectItemCaseSensitive(json, "paperAbstract");
  cJSON *year_json = cJSON_GetObjectItemCaseSensitive(json, "year");
  cJSON *authors_json = cJSON_GetObjectItemCaseSensitive(json, "authors");
  cJSON *in_citations_json = cJSON_GetObjectItemCaseSensitive(json, "inCitations");
  cJSON *out_citations_json = cJSON_GetObjectItemCaseSensitive(json, "outCitations");

  char *id = cJSON_GetStringValue(id_json);
  char *title = cJSON_GetStringValue(title_json);
  char *paper_abstract = cJSON_GetStringValue(abstract_json);

  paper->id = malloc((1 + strlen(id)) * sizeof(char));
  paper->title = malloc((1 + strlen(title)) * sizeof(char));
  paper->paper_abstract = malloc((1 + strlen(paper_abstract)) * sizeof(char));

  strncpy(paper->id, id, strlen(id));
  strncpy(paper->title, title, strlen(title));
  strncpy(paper->paper_abstract, paper_abstract, strlen(paper_abstract));
  paper->year = (int)cJSON_GetNumberValue(year_json);

  paper->author_count = cJSON_GetArraySize(authors_json);

  paper->authors = (char **)malloc(sizeof(char *) * paper->author_count);

  paper->in_citation_count = cJSON_GetArraySize(in_citations_json);
  paper->out_citation_count = cJSON_GetArraySize(out_citations_json);

  paper->in_citations = (char **)malloc(sizeof(char *) * paper->in_citation_count);
  paper->out_citations = (char **)malloc(sizeof(char *) * paper->out_citation_count);

  if (paper->in_citations == NULL || paper->out_citations == NULL || paper->authors == NULL)
  {
    printf("Alokasi memori untuk sitasi atau penulis gagal.\n");
    cJSON_Delete(json);
    free(paper);
    return NULL;
  }

  for (int i = 0; i < paper->author_count; i++)
  {
    cJSON *author_json = cJSON_GetArrayItem(authors_json, i);
    cJSON *author_name_json = cJSON_GetObjectItemCaseSensitive(author_json, "name");
    char *author_name = cJSON_GetStringValue(author_name_json);
    paper->authors[i] = malloc((1 + strlen(author_name)) * sizeof(char));

    strncpy(paper->authors[i], author_name, strlen(author_name));
  }

  for (int i = 0; i < paper->in_citation_count; i++)
  {
    cJSON *in_citation_json = cJSON_GetArrayItem(in_citations_json, i);
    char *in_citation = cJSON_GetStringValue(in_citation_json);
    paper->in_citations[i] = malloc((1 + strlen(in_citation)) * sizeof(char));

    strncpy(paper->in_citations[i], in_citation, strlen(in_citation));
  }

  for (int i = 0; i < paper->out_citation_count; i++)
  {
    cJSON *out_citation_json = cJSON_GetArrayItem(out_citations_json, i);
    char *out_citation = cJSON_GetStringValue(out_citation_json);
    paper->out_citations[i] = malloc((1 + strlen(out_citation)) * sizeof(char));

    strncpy(paper->out_citations[i], out_citation, strlen(out_citation));
  }

  // print_paper(paper);

  cJSON_Delete(json);
  json = NULL;

  return paper;
}

void load_json_papers(Paper ***papers, int *n_papers, const char *file_path)
{
  FILE *fp = NULL;
  int count = 0;
  int line_count = 0;

  char *buffer = (char *)malloc(INT_MAX * sizeof(char));

  fp = fopen(file_path, "r");

  if (fp == NULL)
  {
    printf("Error opening file: %s\n", file_path);
    exit(1);
  }

  line_count = count_lines(file_path);

  // Alokasi memory untuk n paper berdasarkan jumlah baris
  // asumsi setiap baris berisi satu paper
  *papers = (Paper **)malloc(sizeof(Paper *) * line_count);

  if (strcmp(get_filename_ext(file_path), "json") == 0)
  {
    while (fgets(buffer, INT_MAX, fp) != NULL)
    {
      Paper *paper = get_paper_from_json(buffer);

      if (paper == NULL)
      {
        continue;
      }

      (*papers)[count] = paper;

      count++;
    }

    *n_papers = count;

    printf("Found %u papers in JSON file.\n", *n_papers);
  }
  else
  {
    printf("Unsupported file format: %s\n", get_filename_ext(file_path));
    free(papers);
    exit(1);
  }
  fclose(fp);
  free(buffer);
}
