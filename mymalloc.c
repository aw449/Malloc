#include "mymalloc.h"
#define blocksize (1024*1024)
static struct memEntry *root;
static char bigblock[blocksize];
static int freespace = blocksize; //used to check saturation

void* mymalloc(unsigned int size,char* file, int line)
{
	static int initialized = 0;
	struct memEntry *p, *succ;

	if(size < 0){
		printf("Attempting to allocate negative space in %s, line %d\n",file,line);
		return 0;
	}
	
	if(size > freespace){
		printf("Attempting to allocate something larger than the block in %s, at line %d",file,line);
		return 0;
	}

	if(!initialized){
		root = (struct memEntry*)bigblock;
		root->prev = 0;
		root->succ = 0;
		root->size = blocksize - sizeof(struct memEntry);
		root->isFree = 1;
		initialized = 1;
		freespace -= sizeof(struct memEntry);


	}

	p = root;

	int range = (size * 1.5);
	struct memEntry *temp = root;
	struct memEntry *min = root;
	
	/*Locates proper block to store data
	 * Use best fit algorithm if block size is roughly between size and 1.5 size
	 * If we could only find much larger blocks we use the first fit algorithm ie:
	 * first come first serve
	 */
	while(p!=0){
		//If p points to NULL means that we found either unallocated space or the end of the list

		if(((p->size) < (min->size)) && p->isFree){
			min = p;
		}

		if(p->size <= range && p->size >= size && p->isFree){

			if((p->size)<(temp->size)){
				temp = p;
			}

		}
		p = p->succ;
	}

	p = temp;
	if(temp == root){
		p = min;
	}



//Does the actual malloc
	do{
		if (p->size < size || !p->isFree)
		{

			p = p->succ;
		}
		else if (p->size < (size + sizeof(struct memEntry)))
		{
			

			p->isFree = 0;
			freespace -= size;

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

			freespace -= (size+sizeof(struct memEntry));

			return (char *)p + sizeof(struct memEntry);

		}
	} while (p != 0);



	printf("Out of space in %s, line %d\n",file,line);
	return 0 ;
	/*
	if ((p = (struct memEntry *)sbrk(sizeof(struct memEntry) * size)) == (void *)-1)
	{
		printf("Memory has been saturated at %s at line %d \n",file,line);
		return 0;
	}
	else if (last == 0)
	{

		p->prev = p->prev->succ = 0;
		p->size = 0;
		p->isFree = 0;
		root = last = p;
		freespace -= (size+sizeof(struct memEntry));

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
		freespace -= (size+sizeof(struct memEntry));

		return (void*) (p + 1);
	}
*/

	
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
			return;
		}


		//Do the free BKR's code.  Do not touch. Do not Feed.
	ptr = (struct memEntry*)((char *)p - sizeof(struct memEntry));
	if ((pred = ptr->prev) != 0 && pred->isFree)
	{
		freespace += sizeof(struct memEntry) + ptr->size;

		pred->size += sizeof(struct memEntry) + ptr->size;
		pred->succ = ptr->succ;
		if(ptr->succ != 0)
		{
			ptr->succ->prev = pred;
		}
	}
	else
	{
		freespace += ptr->size;

		ptr->isFree = 1;
		pred = ptr;
	}
	if ((succ = ptr->succ) != 0 && (succ->isFree))
	{
		freespace += sizeof(struct memEntry);

		pred->size += sizeof(struct memEntry) + succ->size;
		pred->succ = succ->succ;
		if (succ->succ != 0)
		{
			succ->succ->prev = pred;
		}

	}
	return;
}

