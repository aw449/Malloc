/*
 * Node.c
 *
 */


#include "Node.h"
NodePtr NodeCreate(void * myObj, void (*Seppuku)(void*)){
	NodePtr newNode =(NodePtr) malloc(sizeof(struct Node));
	newNode->Seppuku = (Seppuku);
	newNode->data = myObj;
	newNode->next = NULL;
	newNode->referencecount = 0;
	return newNode;
}


void NodeSeppuku(NodePtr Node){
	Node->next = NULL;
	Node->Seppuku(Node->data);
	free(Node);

}

void incrementreference(NodePtr Node){
	Node->referencecount++;
}

int decrementreference(NodePtr Node){

	Node->referencecount--;
	return (Node->referencecount);
}
