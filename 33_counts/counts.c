#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"

counts_t * createCounts(void) {
  counts_t *ans = malloc(sizeof(*ans));
  ans->Arr = NULL;
  ans->Length = 0;
  ans->unknown = 0;
  return ans;
}

void addCount(counts_t * c, const char * name) {
  if (name == NULL) {
    c->unknown++;
    return ;
  }
  one_count_t * tmp = c->Arr;
  for (int i=c->Length-1; i >= 0; i--) { // Observe: c->Length must be signed number such as ssized_t
    if (strcmp(name, tmp[i].Str) == 0) { // Observe: strcmp can't permit pass NULL into it. 
      tmp[i].Cnt++;
      return ;
    }
  }
  one_count_t * counter = malloc(sizeof(*counter));
  // counter->Str = name;  // error: type doesn't match, the front don't have const
  counter->Str = malloc(strlen(name) + 1);
  strcpy(counter->Str, name);
  counter->Cnt = 1;
  tmp = realloc(tmp, (c->Length+1)*sizeof(*tmp));
  tmp[c->Length] = *counter;
  free(counter);  // OBSERVE
  c->Arr = tmp;
  c->Length++;
  return ;
}

void printCounts(counts_t * c, FILE * outFile) {
  for (int i=0, l=c->Length; i < l; i++) {
    one_count_t counter = c->Arr[i];
    fprintf(outFile, "%s: %ld\n", counter.Str, counter.Cnt);
  }
  if (c->unknown > 0) {
    fprintf(outFile, "<unknown> : %ld\n", c->unknown);
  }
}

void freeCounts(counts_t * c) {
  one_count_t *counter = c->Arr;
  for (int i=c->Length-1; i >= 0; i--) {
    free(counter[i].Str);
  }
  free(c->Arr);
  free(c);
}

