#ifndef __KV_H__
#include <stdlib.h>
#define __KV_H__

struct _kvpair_t { 
  char * Key;
  char * Value;
};
typedef struct _kvpair_t kvpair_t;

struct _kvarray_t { 
  kvpair_t ** Arr;
  size_t Length;
};
typedef struct _kvarray_t kvarray_t;


kvarray_t * readKVs(const char * fname);

void freeKVs(kvarray_t * pairs);

void printKVs(kvarray_t * pairs);

char * lookupValue(kvarray_t * pairs, const char * key);

#endif

