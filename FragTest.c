/*
 * FragTest.c
 *
 *  Created on: Apr 27, 2015
 *      Author: Anthony
 */


#include "mymalloc.h"
#include <string.h>

//Testing with size 220
int main(int argc, char** argv) {
	char *a,*b,*c,*d,*e,*f,*g;
	//memEntry has size
	g = (char*) malloc((1024*1024 - 244));
	a = (char*) malloc(25);
	b = (char*) malloc(25);
	c = (char*) malloc(25);
	d = (char*) malloc(20);

	free(c);


	e = (char*) malloc(5);


	f = (char*) malloc(20);

	free(a);
	free(b);
	free(d);
	free(e);
	free(f);
	free(g);

	return 0;
}
