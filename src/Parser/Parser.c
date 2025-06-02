#include "Parser/Parser.h"

#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>

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
  Paper *paper = (Paper *)calloc(1, sizeof(Paper));
  if (paper == NULL)
  {
    fprintf(stderr, "Alokasi memori untuk Paper gagal.\n");
    return NULL;
  }

  cJSON *json = cJSON_Parse(json_str);
  if (json == NULL)
  {
    fprintf(stderr, "Error parsing JSON: %s\n", cJSON_GetErrorPtr());
    free(paper);
    return NULL;
  }

  cJSON *id_json = cJSON_GetObjectItemCaseSensitive(json, "title");
  cJSON *title_json = cJSON_GetObjectItemCaseSensitive(json, "title");
  cJSON *abstract_json = cJSON_GetObjectItemCaseSensitive(json, "paperAbstract");
  cJSON *year_json = cJSON_GetObjectItemCaseSensitive(json, "year");
  cJSON *authors_json = cJSON_GetObjectItemCaseSensitive(json, "authors");
  cJSON *in_citations_json = cJSON_GetObjectItemCaseSensitive(json, "inCitations");
  cJSON *out_citations_json = cJSON_GetObjectItemCaseSensitive(json, "outCitations");

  paper->id = cJSON_GetStringValue(id_json);
  paper->title = cJSON_GetStringValue(title_json);
  paper->paper_abstract = cJSON_GetStringValue(abstract_json);
  paper->year = (int)cJSON_GetNumberValue(year_json);

  paper->author_count = cJSON_GetArraySize(authors_json);

  paper->authors = (char **)malloc(sizeof(char *) * paper->author_count);

  paper->in_citation_count = cJSON_GetArraySize(in_citations_json);
  paper->out_citation_count = cJSON_GetArraySize(out_citations_json);

  paper->in_citations = (char **)malloc(sizeof(char *) * paper->in_citation_count);
  paper->out_citations = (char **)malloc(sizeof(char *) * paper->out_citation_count);

  if (paper->in_citations == NULL || paper->out_citations == NULL || paper->authors == NULL)
  {
    fprintf(stderr, "Alokasi memori untuk sitasi atau penulis gagal.\n");
    cJSON_Delete(json);
    free(paper);
    return NULL;
  }

  for (int i = 0; i < paper->author_count; i++)
  {
    cJSON *author_json = cJSON_GetArrayItem(authors_json, i);
    cJSON *author_name_json = cJSON_GetObjectItemCaseSensitive(author_json, "name");
    paper->authors[i] = cJSON_GetStringValue(author_name_json);
  }

  for (int i = 0; i < paper->in_citation_count; i++)
  {
    cJSON *citation_json = cJSON_GetArrayItem(in_citations_json, i);
    paper->in_citations[i] = cJSON_GetStringValue(citation_json);
  }

  for (int i = 0; i < paper->out_citation_count; i++)
  {
    cJSON *citation_json = cJSON_GetArrayItem(out_citations_json, i);
    paper->out_citations[i] = cJSON_GetStringValue(citation_json);
  }

  // print_paper(paper);

  return paper;
}

void load_json_papers(Paper ***papers, int *n_papers, const char *file_path)
{
  FILE *fp = NULL;
  int count = 0;
  int line_count = 0;

  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  fp = fopen(file_path, "r");

  if (fp == NULL)
  {
    fprintf(stderr, "Error opening file: %s\n", file_path);
    return;
  }

  line_count = count_lines(file_path);

  // Alokasi memory untuk n paper berdasarkan jumlah baris
  // asumsi setiap baris berisi satu paper
  *papers = (Paper **)malloc(sizeof(Paper *) * line_count);

  if (strcmp(get_filename_ext(file_path), "json") == 0)
  {
    while ((read = getline(&line, &len, fp)) != -1)
    {
      Paper *paper = get_paper_from_json(line);

      if (paper == NULL)
      {
        continue;
      }

      (*papers)[count] = paper;

      count++;
    }

    free(line);

    *n_papers = count;

    printf("Found %u papers in JSON file.\n", *n_papers);
  }
  else
  {
    fprintf(stderr, "Unsupported file format: %s\n", get_filename_ext(file_path));
    free(papers);
  }
  fclose(fp);
}
