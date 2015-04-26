#ifndef MALLOC_H
#define MALLOC_H
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define malloc( x ) mymalloc( x, __FILE__, __LINE__ )
#define free( x ) myfree( x, __FILE__, __LINE__ )

struct memEntry{
	struct memEntry *prev, *succ;
	int isFree;
	unsigned int size;
};


void* mymalloc(unsigned int size,char* file, int line);

void myfree(void *p,char* file, int line);

#endif
