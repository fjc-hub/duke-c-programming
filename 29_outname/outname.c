#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {
	size_t sz = strlen(inputName) + 8;
	char *out = malloc(sz * sizeof(*out));
	strncpy(out, inputName, sz);
	strcat(out, ".counts");
	return out;
}

