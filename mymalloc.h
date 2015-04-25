#ifndef MALLOC_H
#define MALLOC_H
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct memEntry{
	struct memEntry *prev, *succ;
	int isFree;
	unsigned int size;
};


void* mymalloc(unsigned int size);

void myfree(void *p);

#endif