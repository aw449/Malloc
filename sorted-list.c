/*
 * sorted-list.c

 */

#include "sorted-list.h"
#include <stdio.h>

SortedListPtr SLCreate(CompareFuncT cf, DestructFuncT df){
	SortedListPtr newList = malloc(sizeof(SortedListPtr));
	newList->Compare = cf;
	newList->Destruct = df;
	newList->Headptr = NULL;

	return newList;
}

void SLDestroy(SortedListPtr list){
	//Destroy the list
	if(list != NULL){
		while(list->Headptr != NULL){
			//NodePtr NodetoDelete = malloc(sizeof(NodePtr));
			NodePtr NodetoDelete;
			NodetoDelete = list->Headptr;
			list->Headptr = list->Headptr->next;
			NodeSeppuku(NodetoDelete);
		}
		free(list);
	}
}

SortedListIteratorPtr SLCreateIterator(SortedListPtr list){
	//Create a new iterator if list is empty iterator points to NULL
	if(list != NULL && list->Headptr != NULL)
	{
		SortedListIteratorPtr newIterator = malloc(sizeof(SortedListIteratorPtr));
		newIterator->Node = list->Headptr;
		newIterator->Node->Seppuku = list->Destruct;
		incrementreference(list->Headptr);
		return newIterator;
	}
	else
		return NULL;
}

void SLDestroyIterator(SortedListIteratorPtr iter){
	if(iter != NULL){
		//The node that the iterator is pointing to loses a referencecount when iterator is removed
		if((iter->Node != NULL)){
			if(decrementreference(iter->Node) == 0){
				NodeSeppuku(iter->Node);
			}
		}

		free(iter);
	}
}
void *SLGetItem( SortedListIteratorPtr iter ){
	if(iter == NULL){
		return NULL;
	}
	return iter->Node->data;
}
void *SLNextItem(SortedListIteratorPtr iter){
	if(iter == NULL){
		return NULL;
	}
	int ref = decrementreference(iter->Node);
	NodePtr temp;
	temp = iter->Node;
	iter->Node = iter->Node->next;
	if(iter->Node == NULL){
		return NULL;
	}
	if(ref == 0){
		NodeSeppuku(temp);
	}


	incrementreference(iter->Node);
	return iter->Node->data;

}
int SLInsert(SortedListPtr list, void *newObj){
	if(list == NULL || newObj == NULL){
		return 0;
	}
	SortedListIteratorPtr Iter = SLCreateIterator(list); 	//Create a temporary iterator
	NodePtr newNode;	//newNode object
	NodePtr prevNode;
	void *Comparator;//Comparator is data from the list to compare; starts from data in headptr
	newNode = NodeCreate(newObj, (list->Destruct)); //Create a Node containing given data
	prevNode = NULL;
	if(list->Headptr == NULL)  //if the list is empty just make headptr point to the newNode
		{

		list->Headptr = newNode;
		incrementreference(newNode);
		return 1;
		}
	else {

		Comparator = SLGetItem(Iter);
		

		while(Comparator != NULL && list->Compare(Comparator, newObj) > 0){ //If the compare function returns >0 means if newObj is less than or equal to compared object (List is ordered from largest to smallest
			prevNode = Iter->Node;
			Comparator = SLNextItem(Iter);

		}

		if (Comparator != NULL && list->Compare(Comparator, newObj) == 0){ //Throw out if duplicate is found

			SLDestroyIterator(Iter);
			return 0;
		}
		else {
			newNode->next = Iter->Node;
			incrementreference(newNode);
			if(prevNode != NULL){
				prevNode->next = newNode;
			}
			else{
				list->Headptr = newNode;
			}
		}

		SLDestroyIterator(Iter);
		return 1;

	}

}

int SLRemove(SortedListPtr list, void *newObj){
	if(list == NULL || newObj == NULL){
		return 0;
	}
	SortedListIteratorPtr Iter = SLCreateIterator(list); //Temp iterator
	NodePtr prevNode = NULL;
	void *Comparator; //Samething as in Slinsert
	if(list->Headptr != NULL){
		Comparator = SLGetItem(Iter);

		while(list->Compare(Comparator, newObj) != 0){
				prevNode = Iter->Node;
				Comparator = SLNextItem(Iter);
					if(Comparator == NULL){ //if object not found and comparator has reached the end of the list....end and return failure
					return 0;
				}
		}
		
		if(prevNode != NULL){
	
			prevNode->next = Iter->Node->next;
		}
		else{
				list->Headptr = Iter->Node->next;
		}
		if(decrementreference(Iter->Node) == 0){
			NodeSeppuku(Iter->Node);
		}
		else if(Iter->Node->next != NULL){
			incrementreference(Iter->Node->next);//desu
		}
		SLDestroyIterator(Iter); // Destroy temp iterator
		return 1;
	}
	SLDestroyIterator(Iter); // Destroy temp iterator
	return 0;
}

