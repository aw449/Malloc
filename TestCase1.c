


/*
#include "mymalloc.h"
#include <string.h>


int main(int argc, char** argv) {

    if (argc != 2) {
        printf("Incorrect number of arguments.\n");
        return 0;
    }

    //Basic Malloc
    int size = atoi(argv[1]);
    char* p = (char*)malloc(size);
    if (p == 0) {
        printf("Error with Malloc");
        return 1;
    }
    //Free never allocated
    int x;
    free(&x);

    free(p+1);
    //Repeated Free
    free(p);
    free(p);
    //This should not print an error
    p = (char *)malloc( 100 );
    free( p );
    p = (char *)malloc( 100 );
    free( p );


   //See if we can allocated exactly blocksize - sizeof(struct memEntry)
    p = (char*)malloc(1024*1024 - 24);
    free(p);
    //Really Make Sure. We should be 1 short in this case.  Prints error
    p = (char*)malloc(1024*1024 - 23);
    return 0;
}

*/
