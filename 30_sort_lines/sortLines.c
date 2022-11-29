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

int doWork(FILE *stream) {
  char **array = NULL;
  size_t arr_sz = 0;
  char *buffer = NULL;
  size_t buf_sz = 0;
  ssize_t len = 0;
  while ((len = getline(&buffer, &buf_sz, stream)) >= 0) {  // Observe &buffer
    array = realloc(array, (arr_sz + 1) * sizeof(*array));
    array[arr_sz] = malloc((len+1) * sizeof(char));
    strncpy(array[arr_sz], buffer, len + 1); //  len exclude null byte
    arr_sz++;
    // printf("%ld, %ld\n", buf_sz, len);
  }
  free(buffer);             // deallocate memory 1
  // sort and print
  sortData(array, arr_sz);
  for (int i=0; i < arr_sz; i++) {
    printf("%s", array[i]);
    free(array[i]);         // deallocate memory 2
  }
  free(array);              // deallocate memory 3
  return 0;
}

int main(int argc, char ** argv) {
  if (argc == 1) {
    if (doWork(stdin) != 0) {
      perror("error");
      return EXIT_FAILURE;
    }
  } else {
    for (int i=1; i < argc; i++) {
      FILE *file = fopen(argv[i], "r");
      if (file == NULL) {
        fprintf(stderr, "fopen %s error \n", argv[i]);
        return EXIT_FAILURE;
      }
      if (doWork(file) != 0) {
        perror("error");
        return EXIT_FAILURE;
      }
      // close input stream(except stdin)
      if (fclose(file) != 0) {
        perror("Failed to close the input file!");
        return EXIT_FAILURE;
      }
    }
  }
  return EXIT_SUCCESS;
}

