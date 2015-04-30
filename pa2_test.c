/*
 * sorted-list.c
 */

#include	<string.h>
#include	<stdio.h>
#include	"sorted-list.h"

static FILE *out;

int compareInts(void *p1, void *p2)
{
	int i1 = *(int *)p1;
	int i2 = *(int *)p2;

	return i1 - i2;
}

int compareDoubles(void *p1, void *p2)
{
	double d1 = *(double *)p1;
	double d2 = *(double *)p2;

	return (d1 < d2) ? -1 : ((d1 > d2) ? 1 : 0);
}

int compareStrings(void *p1, void *p2)
{
	char *s1 = p1;
	char *s2 = p2;

	return strcmp(s1, s2);
}

/*
 * Destructor functions
 * For pointers to basic data types (int*,char*,double*,...)
 * Use for allocated memory (malloc,calloc,etc.)
 */
void destroyBasicTypeAlloc(void *p)
{
	free(p);
}

/*
 * Destructor functions
 * For pointers to basic data types (int*,char*,double*,...)
 * Use for memory that has not been allocated (e.g., "int x = 5;SLInsert(mylist,&x);SLRemove(mylist,&x);")
 */
void destroyBasicTypeNoAlloc(void *p)
{
	return;
}

void destroyTestFunc(void *p)
{
	fprintf(out, "DESTROY FUNCTION CALLED\n");
}

int main(int argc, char *argv[])
{
	SortedListPtr list;
	SortedListIteratorPtr iter;
	int *temp;
	int retVal;
	int testNum;
	char *testDesc;
	int totalTests = 11;

	if (argc < totalTests + 2) {
		printf("Usage: ./sl [0/non-0] [0/non-0] ... [outputfilename]\n\t");
		printf("(0/non-0 if you want to skip/run a test for each test.)\n");
		printf("\tThere are %d tests.\n", totalTests);
		return 1;
	}

    out = fopen(argv[argc - 1], "a");

    /**
     * test case 1 - create an empty list, then destroy the list.
     */

	testNum = 1;
    fflush(out);
	if (*argv[testNum] != '0') {
        fprintf(out, "\nNote: No expected output for test cases 1-5, if correct.\n");
		testDesc = "Create an empty List, create an iterator, and then destroy them";
		fprintf(out, "\nTest case %d: %s\n", testNum, testDesc);

		list = SLCreate(compareInts, destroyBasicTypeNoAlloc);

		if (list == NULL) {
			fprintf(out, "\tError: no list returned by SLCreate");
		}

		iter = SLCreateIterator(list);

		if (iter == NULL) {
			fprintf(out, "\tError: no iter returned by SLCreateIterator");
		}

		SLDestroyIterator(iter);
		SLDestroy(list);
	}
    /**
     * test case 2 - Insert and remove from a null list
     */
	testNum += 1;
    fflush(out);
	int ip1 = 1;
	if (*argv[testNum] != '0') {
        fprintf(out, "\nNote: No expected output for test cases 1-5, if correct.\n");
		testDesc = "Insert/remove an item from a null list";
		fprintf(out, "\nTest case %d: %s\n", testNum, testDesc);
		list = NULL;
		retVal = SLRemove(list, &ip1);
		if (retVal != 0) {
			fprintf(out, "\tIncorrect return value for SLRemove, %d instead of 0 on failure\n", retVal);
		}
		retVal = SLInsert(list, &ip1);
		if (retVal != 0) {
			fprintf(out, "\tIncorrect return value for SLInsert, %d instead of 0 on failure\n", retVal);
		}
	}

	/*
	 * test case 3 - Create a new iterator on an empty list and iterate
	 */
	testNum += 1;
    fflush(out);
	if (*argv[testNum] != '0') {
        fprintf(out, "\nNote: No expected output for test cases 1-5, if correct.\n");
		testDesc = "Create a new iterator on an empty list and iterate";
		fprintf(out, "\nTest case %d: %s \n", testNum, testDesc);

		list = SLCreate(compareInts, destroyBasicTypeNoAlloc);
		iter = SLCreateIterator(list);
		while ((temp = SLNextItem(iter)) != NULL) {
			fprintf(out, "Error: \tTest %d: Iter got %i\n", testNum, *temp);	//Prints nothing
		}

		SLDestroyIterator(iter);
		SLDestroy(list);
	}
	/*
	 * test case 4 - insert the same object into a list
	 */
	testNum += 1;
    fflush(out);
	if (*argv[testNum] != '0') {
        fprintf(out, "\nNote: No expected output for test cases 1-5, if correct.\n");
		testDesc = "SLInsert(list, item) into list twice and check return value";
		fprintf(out, "\nTest case %d: %s: \n", testNum, testDesc);
		list = SLCreate(compareInts, destroyBasicTypeNoAlloc);
		iter = SLCreateIterator(list);

		retVal = SLInsert(list, &ip1);
		if (retVal != 1) {
			fprintf(out, "\tIncorrect return value for SLInsert, %d instead of 1 on success\n", retVal);
		}
		retVal = SLInsert(list, &ip1);
		if (retVal != 0) {
			fprintf(out, "\tIncorrect return value for SLInsert, %d instead of 0 on failure\n", retVal);
		}
		SLDestroyIterator(iter);
		SLDestroy(list);
	}

	/*
	 * test case 5 - remove non-existant object from a list
	 */
	testNum += 1;
    fflush(out);
	if (*argv[testNum] != '0') {
        fprintf(out, "\nNote: No expected output for test cases 1-5, if correct.\n");
		testDesc = "SLRemove(list, item) twice and check return value";
		fprintf(out, "\nTest case %d: %s: \n", testNum, testDesc);
		list = SLCreate(compareInts, destroyBasicTypeNoAlloc);
		iter = SLCreateIterator(list);
		SLInsert(list, &ip1);
		retVal = SLRemove(list, &ip1);
		if (retVal != 1) {
			fprintf(out, "\tIncorrect return value for SLRemove, %d instead of 1 on success\n", retVal);
		}
		retVal = SLRemove(list, &ip1);
		if (retVal != 0) {
			fprintf(out, "\tIncorrect return value for SLRemove, %d instead of 0 on failure\n", retVal);
		}
		SLDestroyIterator(iter);
		SLDestroy(list);
	}

	/*
	 * test case 6a - populate a list with multiple integers
	 * 
	 * test case 6b - iterate through a poulated list
	 */

	testNum += 1;
    fflush(out);
	if (*argv[testNum] != '0') {
		testDesc = "Create and interate through a list with multiple ints";
		fprintf(out, "\nTest case %d: %s: \n", testNum, testDesc);
		int ip1 = 1;
		int ip2 = 2;
		int ip3 = 3;
		int ip4 = 4;
		int ip5 = 5;

		list = SLCreate(compareInts, destroyBasicTypeNoAlloc);
		SLInsert(list, &ip2);
		SLInsert(list, &ip5);
		SLInsert(list, &ip3);
		SLInsert(list, &ip4);
		SLInsert(list, &ip1);

		iter = SLCreateIterator(list);

		int solution_7[5] = { 5, 4, 3, 2, 1 };
		int i = 0;
        temp = SLGetItem(iter);
		do {

			if (i > 5) {
				break;
			}

			if (*(solution_7 + i) != *temp) {
				/*
				 * Prints 5, 4, 3, 2, 1
				 */
				fprintf(out, "Error: \tTest%d: Iter got %i instead of %i\n", testNum, *temp,
				       *(solution_7 + i));
			} else {
				fprintf(out, "\tTest%d: Iter got %d\n", testNum, *temp);
			}
			i++;
		} while ((temp = SLNextItem(iter)) != NULL); 

		if (i != 5) {
			fprintf(out, "Error: \tTest%d: Iter reached %d items instead of 5\n", testNum, i);
        } 

		SLDestroyIterator(iter);
		SLDestroy(list);
	}

	/*
	 * test case 7a - populate a list with multiple strings
	 * 
	 * test case 7b - iterate through a poulated list
	 */

	testNum += 1;
    fflush(out);
	char *str1 = "Alpha\0";
	char *str2 = "Bravo\0";
	char *str3 = "Charlie\0";
	char *str4 = "Delta\0";
	char *str5 = "Echo\0";

	if (*argv[testNum] != '0') {
		testDesc = "Create and interate through a list with multiple strs";
		fprintf(out, "\nTest case %d: %s: \n", testNum, testDesc);

		SortedListPtr listStr;

		listStr = SLCreate(compareStrings, destroyBasicTypeNoAlloc);

		SLInsert(listStr, str4);
		SLInsert(listStr, str1);
		SLInsert(listStr, str5);
		SLInsert(listStr, str2);
		SLInsert(listStr, str3);

		iter = SLCreateIterator(listStr);

		char *solution7[5] = { "Echo\0", "Delta\0", "Charlie\0", "Bravo\0", "Alpha\0" };
		char *strtemp = SLGetItem(iter);
		int i = 0;
        do {

			if (i > 5) {
				break;
			}

			if (strcmp(*(solution7 + i), strtemp) != 0) {
				fprintf(out, "Error: \tTest7: Iter got %s instead of %s\n", strtemp, *(solution7 + i));
			} else {
				fprintf(out, "\tTest7: Iter got %s\n", strtemp);
			}
			i++;
		} while ((strtemp = SLNextItem(iter)) != NULL);

		if (i != 5) {
			fprintf(out, "Error: \tTest%d: Iter reached %d items instead of 5\n", testNum, i);
		}

		SLDestroyIterator(iter);
		SLDestroy(listStr);
	}
	/*
	 * test 8 - test with doubles
	 */

	testNum += 1;
    fflush(out);
	double dp1 = -1.1;
	double dp2 = 2.2;
	double dp3 = 3.3;
	double dp4 = 4.4;
	double dp5 = -5.5;

	if (*argv[testNum] != '0') {
		testDesc = "Create and interate through a list with multiple doubles";
		fprintf(out, "\nTest case %d: %s: \n", testNum, testDesc);
		SortedListPtr doubles = SLCreate(compareDoubles, destroyBasicTypeNoAlloc);

		SLInsert(doubles, &dp2);
		SLInsert(doubles, &dp1);
		SLInsert(doubles, &dp5);
		SLInsert(doubles, &dp3);
		SLInsert(doubles, &dp4);

		iter = SLCreateIterator(doubles);

		double solution8[5] = { 4.4, 3.3, 2.2, -1.1, -5.5 };
		double *dbltemp = SLGetItem(iter);
		int i = 0;
		do {

			if (i > 5) {
				break;
			}

			if (*(solution8 + i) != *dbltemp) {
				fprintf(out, "Error: \tTest8: Iter got %f instead of %f\n", *dbltemp, *(solution8 + i));
			} else {
				fprintf(out, "\tTest8: Iter got %f\n", *dbltemp);
			}
			i++;
		} while ((dbltemp = SLNextItem(iter)) != NULL);


		if (i != 5) {
			fprintf(out, "Error: \tTest%d: Iter reached %d items instead of 5\n", testNum, i);
		} 

		SLDestroyIterator(iter);
		SLDestroy(doubles);
	}

	/*
	 * test9 - test with a lot of iterators
	 */
	testNum += 1;
    fflush(out);
	if (*argv[testNum] != '0') {
		testDesc = "Create a lot of iterators on a single list";
		fprintf(out, "\nTest case %d: %s: \n", testNum, testDesc);

		SortedListIteratorPtr iter9a;
		SortedListIteratorPtr iter9b;
		SortedListIteratorPtr iter9c;
		SortedListIteratorPtr iter9d;
		SortedListIteratorPtr iter9e;

		SortedListPtr listStr2 = SLCreate(compareStrings, destroyBasicTypeNoAlloc);

		SLInsert(listStr2, str1);
		iter9a = SLCreateIterator(listStr2);
		SLInsert(listStr2, str2);
		iter9b = SLCreateIterator(listStr2);
		SLInsert(listStr2, str3);
		iter9c = SLCreateIterator(listStr2);
		SLInsert(listStr2, str4);
		iter9d = SLCreateIterator(listStr2);
		SLInsert(listStr2, str5);
		iter9e = SLCreateIterator(listStr2);

		char *solution_9[5] = { "Echo\0", "Delta\0", "Charlie\0", "Bravo\0", "Alpha\0" };
		char *strtemp;

		/*
		 * Should be Alpha
		 */
		int i = 4;
        strtemp = SLGetItem(iter9a);
		do {

			if (i > 5) {
				break;
			}

			if (strcmp(*(solution_9 + i), strtemp) != 0) {
				fprintf(out, "Error: \tTest%da: Iter got %s instead of %s\n", testNum, strtemp,
				       *(solution_9 + i));
			} else {
				fprintf(out, "\tTest%da: Iter got %s\n", testNum, strtemp);
			}
			i++;
		} while ((strtemp = SLNextItem(iter9a)) != NULL);

		if (i != 5) {
			i -= 4;
			fprintf(out, "Error: \tTest%da: Iter reached %d items instead of 1\n", testNum, i);
		}

		fprintf(out, "\n");

		/*
		 * Should be Bravo, Alpha
		 */
		i = 3;
        strtemp = SLGetItem(iter9b);
		do {

			if (i > 5) {
				break;
			}

			if (strcmp(*(solution_9 + i), strtemp) != 0) {
				fprintf(out, "Error: \tTest%db: Iter got %s instead of %s\n", testNum, strtemp,
				       *(solution_9 + i));
			} else {
				fprintf(out, "\tTest%db: Iter got %s\n", testNum, strtemp);
			}
			i++;
		} while ((strtemp = SLNextItem(iter9b)) != NULL);

		if (i != 5) {
			i -= 3;
			fprintf(out, "Error: \tTest%db: Iter reached %d items instead of 2\n", testNum, i);
		}

		fprintf(out, "\n");

		/*
		 * Should be Charlie, Bravo, Alpha
		 */
		i = 2;
        strtemp = SLGetItem(iter9c);
		do {

			if (i > 5) {
				break;
			}

			if (strcmp(*(solution_9 + i), strtemp) != 0) {
				fprintf(out, "Error: \tTest%dc: Iter got %s instead of %s\n", testNum, strtemp,
				       *(solution_9 + i));
			} else {
				fprintf(out, "\tTest%dc: Iter got %s\n", testNum, strtemp);
			}
			i++;
		} while ((strtemp = SLNextItem(iter9c)) != NULL);

		if (i != 5) {
			i -= 2;
			fprintf(out, "Error: \tTest%dc: Iter reached %d items instead of 3\n", testNum, i);
		}

		fprintf(out, "\n");

		/*
		 * Should be Delta, Charlie, Bravo, Alpha
		 */
		i = 1;
        strtemp = SLGetItem(iter9d);
		do {

			if (i > 5) {
				break;
			}

			if (strcmp(*(solution_9 + i), strtemp) != 0) {
				fprintf(out, "Error: \tTest%dd: Iter got %s instead of %s\n", testNum, strtemp,
				       *(solution_9 + i));
			} else {
				fprintf(out, "\tTest%dd: Iter got %s\n", testNum, strtemp);
			}
			i++;
		} while ((strtemp = SLNextItem(iter9d)) != NULL);

		if (i != 5) {
			i -= 1;
			fprintf(out, "Error: \tTest%dd: Iter reached %d items instead of 4\n", testNum, i);
		}

		fprintf(out, "\n");

		SLRemove(listStr2, str5);
		SLRemove(listStr2, str4);

		i = 0;
        strtemp = SLGetItem(iter9e);
		do {

			if (i >= 5) {
				break;
			}
			if (strcmp(*(solution_9 + i), strtemp) != 0) {
				fprintf(out, "Error: \tTest%de: Iter got %s instead of %s\n", testNum, strtemp,
				       *(solution_9 + i));
			} else {
				fprintf(out, "\tTest%de: Iter got %s\n", testNum, strtemp);
			}
			i++;
		} while ((strtemp = SLNextItem(iter9e)) != NULL);

		if (i != 5) {
			i -= 2;
			fprintf(out, "Error: \tTest%de: Iter reached %d items instead of 3\n", testNum, i);
		}

		fprintf(out, "\n");

		SLDestroyIterator(iter9a);
		SLDestroyIterator(iter9b);
		SLDestroyIterator(iter9c);
		SLDestroyIterator(iter9d);
		SLDestroyIterator(iter9e);

		SLDestroy(listStr2);
	}

	/*
	 * Test Case 10
	 */
	testNum += 1;
    fflush(out);
	if (*argv[testNum] != '0') {
		int i1 = 1;
		int i2 = 2;
		int i3 = 3;
		//int *intTmp;
		testDesc = "Check if destructor function is called at the correct time";
		fprintf(out, "\nTest case %d: %s: \n", testNum, testDesc);
		SortedListPtr listTest = SLCreate(compareInts, destroyTestFunc);
		SortedListIteratorPtr iter10a;
		SortedListIteratorPtr iter10b;
		SLInsert(listTest, &i3);
		SLInsert(listTest, &i2);
		SLInsert(listTest, &i1);
		iter10a = SLCreateIterator(listTest);
		iter10b = SLCreateIterator(listTest);

		fprintf(out, "\tDestoy function should not be called here: ");
		SLRemove(listTest, &i3);

		fprintf(out, "\n");
		fprintf(out, "\tDestoy function should be called here: ");
		SLNextItem(iter10a);
		SLNextItem(iter10b);
		SLDestroyIterator(iter10a);
		SLDestroyIterator(iter10b);

		fprintf(out, "\n");
		fprintf(out, "\tDestoy function should not be called here: ");
		iter10a = SLCreateIterator(listTest);
		iter10b = SLCreateIterator(listTest);
		SLRemove(listTest, &i2);

		fprintf(out, "\n");
		fprintf(out, "\tDestoy function should be called here: ");
		SLDestroyIterator(iter10a);
		SLDestroyIterator(iter10b);
		fprintf(out, "\n");
		fprintf(out, "\tDestoy function should be called here: ");
		SLDestroy(listTest);

	}

	/*
	 * Test Case 11
	 */

	testNum += 1;
    fflush(out);
	if (*argv[testNum] != '0') {
		testDesc = "Check if iterator correctly handles removed elements";
		fprintf(out, "\nTest case %d: %s: \n", testNum, testDesc);
		int i1 = 1;
		int i2 = 2;
		int i3 = 3;
		int i4 = 4;
		int i5 = 5;
		int *intTmp;
		SortedListPtr listTest = SLCreate(compareInts, destroyBasicTypeNoAlloc);
		SortedListIteratorPtr iter11a;
		SortedListIteratorPtr iter11b;
		SLInsert(listTest, &i1);
		SLInsert(listTest, &i2);
		SLInsert(listTest, &i3);
		SLInsert(listTest, &i4);
		iter11b = SLCreateIterator(listTest);
		SLInsert(listTest, &i5);
		iter11a = SLCreateIterator(listTest);

		SLRemove(listTest, &i3);
		SLRemove(listTest, &i4);

		int solution_11a[3] = { 5, 2, 1 };
		int solution_11b[3] = { 4, 2, 1 };
		int i = 0;
        intTmp = SLGetItem(iter11a);
		do {

			if (i > 3) {
				break;
			}

			if (*(solution_11a + i) != *intTmp) {
				/*
				 * Prints 5, 2, 1
				 */
				fprintf(out, "Error: \tTest%da: Iter got %i instead of %i\n", testNum, *intTmp,
				       *(solution_11a + i));
			} else {
				fprintf(out, "\tTest%da: Iter got %d\n", testNum, *intTmp);
			}
			i++;
		} while ((intTmp = SLNextItem(iter11a)) != NULL);

		if (i != 3) {
			fprintf(out, "Error: \tTest%da: Iter reached %d items instead of 3\n", testNum, i);
		}
		fprintf(out, "\n");

		i = 0;
        intTmp = SLGetItem(iter11b);
		do {

			if (i > 3) {
				break;
			}

			if (*(solution_11b + i) != *intTmp) {
				/*
				 * Prints 4, 2, 1
				 */
				fprintf(out, "Error: \tTest%db: Iter got %i instead of %i\n", testNum, *intTmp,
				       *(solution_11b + i));
			} else {
				fprintf(out, "\tTest%db: Iter got %d\n", testNum, *intTmp);
			}
			i++;
		} while ((intTmp = SLNextItem(iter11b)) != NULL);

		if (i != 3) {
			fprintf(out, "Error: \tTest%db: Iter reached %d items instead of 3\n", testNum, i);
		}

		SLDestroyIterator(iter11a);
		SLDestroyIterator(iter11b);
		SLDestroy(listTest);

	}
  
    fclose(out);

	return 0;
}
