#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

int main(int argc, char ** argv) {
  // open input stream
  size_t stream_cnt = 0;
  FILE * streams[argc - 1];
  if (argc == 1) {
    stream_cnt = 1;
    streams[0] = stdin;
  } else {
    stream_cnt = argc - 1;
    for (int i=1; i < argc; i++) {
      FILE *file = fopen(argv[i], "r");
      if (file == NULL) {
        fprintf(stderr, "fopen %s error \n", argv[i]);
        return EXIT_FAILURE;
      }
      streams[i-1] = file;
    }
  }
  // read from stream into array
  char **array = NULL;
  size_t arr_sz = 0;
  char *buffer = NULL;
  size_t buf_sz = 0;
  for (int i=0; i < stream_cnt; i++) {
    while (getline(&buffer, &buf_sz, streams[i]) > 0) {  // Observe &buffer
      array = realloc(array, (arr_sz + 1) * sizeof(*array));
      array[arr_sz] = malloc(buf_sz * sizeof(*buffer));
      strncpy(array[arr_sz], buffer, buf_sz);
      arr_sz++;
    }
  }
  free(buffer);             // deallocate memory 1
  // sort and print
  sortData(array, arr_sz);
  for (int i=0; i < arr_sz; i++) {
    printf("%s", array[i]);
    free(array[i]);         // deallocate memory 2
  }
  free(array);              // deallocate memory 3

  // close input stream(except stdin)
  if (argc > 1) {
    for (int i=0; i < stream_cnt; i++) {
      if (fclose(streams[i]) != 0) {
        perror("Failed to close the input file!");
        return EXIT_FAILURE;
      }
    }
  }
  return EXIT_SUCCESS;
}

