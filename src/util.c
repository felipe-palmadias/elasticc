#include "util.h"
#include <stdio.h>


void *xmalloc(size_t size) {
	void *pointer = malloc(size);
	if (pointer) {
		return pointer;
	}
	fprintf(stderr, "Out of memory\n");
	exit(1);
}
