#include <stdio.h>
#include <stdlib.h>

#include "Parser/Parser.h"
#include "Paper/Paper.h"

int main(int argc, char const *argv[])
{
  Paper **papers = NULL;
  int n_papers = 0;

  load_json_papers(&papers, &n_papers, "data/test.json");

  // Insert papers into the BSTree authors_tree & papers_tree

  free(papers);

  return 0;
}
