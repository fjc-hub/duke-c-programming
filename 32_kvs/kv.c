#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "kv.h"

// 1.cpoy string res[*start:x](exclude x) into a new string, where res[x] == delim.
// 2.fast fail if read a '\0' before delim
// 3.for security in avoiding 'read out of range of buffer', 
//   res must be a valid string, namely end up with '\0'
char * dynamicStrcpyUntil(const char * res, size_t *start, char delim) {
  int i = *start;
  size_t sz = 0;
  char * str = NULL;
  for (; res[i] && res[i] != delim; i++) {
    str = realloc(str, (sz+1)*sizeof(*str));
    str[sz] = res[i];
    sz++;
  }
  // add an null terminate
  str = realloc(str, (sz+1)*sizeof(*str));
  str[sz] = '\0';
  // update start
  *start = i;
  return str;
}

kvarray_t * readKVs(const char * fname) {
  if (fname == NULL) {
    perror("fname equals to NULL\n");
    return NULL;
  }
  FILE * file = fopen(fname, "r");
  if (file == NULL) {
    fprintf(stderr, "File(%s) not exist\n", fname);
    exit(-1);
  }
  // malloc and initialize
  kvarray_t * kvs = malloc(sizeof(*kvs));
  kvs->Arr = NULL;
  kvs->Length = 0;
  // read in and assign and dynamic expansion
  char * buf = NULL;
  size_t sz = 0;
  for (; getline(&buf, &sz, file) >= 0; ) {
    size_t i = 0;
    char *key = dynamicStrcpyUntil(buf, &i, '=');
    // fast fail
    assert(buf[i] == '=');
    i++;
    char *value = dynamicStrcpyUntil(buf, &i, '\n');
    assert(buf[i] == '\n');
    // assign key/value
    kvpair_t * pair = malloc(sizeof(*pair));
    pair->Key = key;
    pair->Value = value;
    int len = kvs->Length;
    kvs->Arr = realloc(kvs->Arr, (len + 1)*sizeof(*(kvs->Arr)));
    kvs->Arr[len] = pair;
    kvs->Length++;
  }
  free(buf);
  if (fclose(file) != 0) {
    fprintf(stderr, "Failed to close the input file(%s)!\n", fname);
    return NULL;
  }
  return kvs;
}

void freeKVs(kvarray_t * pairs) {
  kvpair_t ** arr = pairs->Arr;
  for (int i=pairs->Length-1; i >= 0; i--) {
    // free kvpair_t's key
    free(arr[i]->Key);
    // free kvpair_t's value
    free(arr[i]->Value);
    // free kvpair_t
    free(arr[i]);
  }
  free(pairs->Arr);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  kvpair_t ** arr = pairs->Arr;
  for (int i=0, l=pairs->Length; i < l; i++) {
    printf("key = '%s' value = '%s'\n", arr[i]->Key, arr[i]->Value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  kvpair_t ** arr = pairs->Arr;
  for (int i=0, l=pairs->Length; i < l; i++) {
    if(strcmp(key, arr[i]->Key) == 0) {
      return arr[i]->Value;
    }
  }
  return NULL;
}


