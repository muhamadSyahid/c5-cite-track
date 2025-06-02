#ifndef PARSER_H
#define PARSER_H

#include "Parser/cJSON.h"
#include "Paper/Paper.h"

// get file extension
// ambil ekstensi file
const char *get_filename_ext(const char *filename);

// get string content from file
// ambil isi string dari file
char *get_json_string(const char *file);

// count lines in file
// menghitung jumlah baris dalam file
int count_lines(const char *file_path);

// convert json to Paper
// konversi json ke Paper
Paper *get_paper_from_json(const char *json_str);

// load papers from json from file and store them in an array of Paper pointers
// muat data Paper dari file JSON dan simpan dalam array pointer Paper
void load_json_papers(Paper ***papers, int *n_papers, const char *file_path);

#endif // PARSER_H