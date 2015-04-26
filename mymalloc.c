#include "mymalloc.h"
#define blocksize (1024 * 1024)
static struct memEntry *root;
static char bigblock[blocksize];


void* mymalloc(unsigned int size,char* file, int line)
{
	static int initialized = 0;
	static struct memEntry *last;
	struct memEntry *p, *succ;

	if(!initialized){
		root = (struct memEntry*)bigblock;
		root->prev = 0;
		root->succ = 0;
		root->size = blocksize - sizeof(struct memEntry);
		root->isFree = 1;
		initialized = 1;
	}

	p = root;

	do{
		if (p->size < size || !p->isFree)
		{
			p = p->succ;
		}
		else if (p->size < (size + sizeof(struct memEntry)))
		{
			p->isFree = 0;
			return (char *)p + sizeof(struct memEntry);
		}
		else
		{
			succ = (struct memEntry *)((char *)p + sizeof(struct memEntry)+size);
			succ->prev = p;
			succ->succ = p->succ;
			if (p->succ != 0)
			{
				p->succ->prev = succ;
			}
			p->succ = succ;
			succ->size = p->size - sizeof(struct memEntry) - size;
			succ->isFree = 1;
			p->size = size;
			p->isFree = 0;
			return (char *)p + sizeof(struct memEntry);

		}
	} while (p != 0);

	if ((p = (struct memEntry *)sbrk(sizeof(struct memEntry) * size)) == (void *)-1)
	{
		return 0;
	}
	else if (last == 0)
	{
		p->prev = p->prev->succ = 0;
		p->size = 0;
		p->isFree = 0;
		root = last = p;
		return (char *)p + sizeof(struct memEntry);
	}
	else
	{
		p->prev = last;
		p->succ = last->prev;
		p->size = size;
		p->isFree = 0;
		last->succ = p;
		last = p;
		return (void*) (p + 1);
	}

	printf("Memory block saturated cannot allocate space");
	return 0;
}

void myfree(void *p, char* file, int line)
{
	struct memEntry *ptr, *pred, *succ;

	/*
	 * Error Checking
	 */
	//Check to see if ptr exists
	ptr = root;
	while((ptr != 0)){
		if((ptr+1) == p){
			break;
		}
		else{
			ptr = ptr ->succ;
		}
	}
		//If ptr does not exist in memory, error
		if(ptr == 0){
			printf("Attempting to free unallocated pointer in %s at line %d. \n ",file,line);
					return;
		}
		//If there is a redundant free somehow
		if(ptr->isFree){
			printf("Pointer has already been freed in %s at line %d \n",file,line);
		}


		//Do the free BKR's code.  Do not touch. Do not Feed.
	ptr = (struct memEntry*)((char *)p - sizeof(struct memEntry));
	if ((pred = ptr->prev) != 0 && pred->isFree)
	{
		pred->size += sizeof(struct memEntry) + ptr->size;
		pred->succ = ptr->succ;
		if(ptr->succ != 0)
		{
			ptr->succ->prev = pred;
		}
	}
	else
	{
		ptr->isFree = 1;
		pred = ptr;
	}
	if ((succ = ptr->succ) != 0 && (succ->isFree))
	{
		pred->size += sizeof(struct memEntry) + succ->size;
		pred->succ = succ->succ;
		if (succ->succ != 0)
		{
			succ->succ->prev = pred;
		}

	}
}

int main(int argc, char** argv)
{

	char *string;
	string = (char *) malloc(sizeof(char)*8);
	memcpy(string, "hello", 6);
	printf("%s\n", string);
	free(string);
	return 0;
}
