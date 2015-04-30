/*
 * Node.h

 */

#ifndef NODE_H_
#define NODE_H_

#include <stdlib.h>

struct Node{
	int referencecount;
	struct Node *next;
	void *data;
	void (*Seppuku)(void*);
};
typedef struct Node* NodePtr;


NodePtr NodeCreate(void * myObj,void (*Seppuku)(void*));

void NodeSeppuku(NodePtr Node);

void incrementreference(NodePtr Node);

int decrementreference(NodePtr Node);

#endif /* NODE_H_ */
