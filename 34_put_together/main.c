#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  counts_t *ans = createCounts();
  FILE *f = fopen(filename, "r");
  if (f == NULL) {
    perror("open file error in countFile\n");
    exit(-1);
  }
  size_t sz = 0;
  char *buf = NULL;
  for (; getline(&buf, &sz, f) >= 0; ) {
    // Observe: remmove '\n' in buf
    char *t = strchr(buf, '\n');
    if (t != NULL) {
      *t = '\0';
    }
    char *v = lookupValue(kvPairs, buf);
    addCount(ans, v);
    // free(v);
  }
  free(buf);
  if (fclose(f) != 0) {
    perror("close file error in countFile\n");
    exit(-1);
  }
  return ans;
}

int main(int argc, char ** argv) {
  if (argc < 3) {
    perror("argc must >= 3");
    return EXIT_FAILURE;
  }
  //read the key/value pairs from the file named by argv[1]
  kvarray_t * kv = readKVs(argv[1]);
  for (int i=2; i < argc; i++) {
    //count the values that appear in the file named by argv[i]
    counts_t *c = countFile(argv[i], kv);
    //compute the output file name from argv[i] (call this outName)
    char *outName = computeOutputFileName(argv[i]);
    //open the file named by outName (call that f)
    FILE *f = fopen(outName, "w+");
    if (f == NULL) {
      perror("open out file error\n");
      return EXIT_FAILURE;
    }
    //print the counts from c into the FILE f
    printCounts(c, f);
    //close f
    if (fclose(f) != 0) {
      perror("close output file error\n");
      return EXIT_FAILURE;
    }
    //free the memory for outName and c
    free(outName);
    freeCounts(c);
  }
  free(kv);
  return EXIT_SUCCESS;
}
