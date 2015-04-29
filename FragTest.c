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
	char *a,*b,*c,*d,*e,*f;
	//memEntry has size
	a = (char*) malloc(25);
	b = (char*) malloc(25);
	c = (char*) malloc(25);
	d = (char*) malloc(20);

	free(c);


	e = (char*) malloc(5);


	f = (char*) malloc(20);




	return 0;
}
