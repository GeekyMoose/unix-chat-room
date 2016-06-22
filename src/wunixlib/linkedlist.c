// -----------------------------------------------------------------------------
/**
 * \file	linkedlist.c
 * \author	Constantin MASSON
 * \date	June 22, 2016
 *
 * \brief	Simple generic linkedlist.
 * \note	C Library for the Unix Programming Project
 */
// -----------------------------------------------------------------------------

#include "linkedlist.h"


void list_init(Linkedlist *list, freefct f){
	assert(list != NULL);
	list->size		= 0;
	list->first		= NULL;
	list->last		= NULL;
	list->freefct	= f;
}

void list_clear(Linkedlist *list){
	assert(list != NULL);
	LinkedlistNode *current;
	while(list->first != NULL){
		current		= list->first;
		list->first	= list->first->next;
		//If data of node need to be free
		if(list->freefct != NULL){
			list->freefct(current->data);
		}
	}
	//Reset the data (Not required, but one never knows)
	list->size		= 0;
	list->first		= NULL;
	list->last		= NULL;
}

int list_is_empty(const Linkedlist *list){
	assert(list != NULL);
	return (list->first == NULL) ? 1 : 0;
}

int list_size(const Linkedlist *list){
	assert(list != NULL);
	return list->size;
}

void list_iterate(const Linkedlist *list, iteratorfct f){
	assert(list != NULL);
	assert(f != NULL);
	int retval = 1;
	LinkedlistNode *current = list->first;
	while(current != NULL && retval == 1){
		retval = f(current->data);
		current = current->next;
	}
}

int list_append(Linkedlist *list, void * const data){
	assert(list != NULL);
	assert(data != NULL);
	
	//Create the new node and set data pointer
	LinkedlistNode* node = (LinkedlistNode*)malloc(sizeof(LinkedlistNode));
	if(node == NULL){
		return -1; //Means malloc failed
	}
	//Set the data in node and place node at the end
	node->data = data;
	node->next = NULL;
	if(list->first == NULL){
		list->first	= node;
		list->last	= node;
	}
	else{
		list->last->next = node;
		list->last = node;
	}
	list->size++;
	return 1;
}

int list_append_first(Linkedlist *list, void * const data){
	assert(list != NULL);
	assert(data != NULL);

	//Create the new node
	LinkedlistNode* node = (LinkedlistNode*)malloc(sizeof(LinkedlistNode));
	if(node == NULL){
		return -1; //Means malloc failed
	}
	//Set the data in node and place node at the beginning
	node->data = data;
	node->next = list->first;
	if(list->first == NULL){
		list->first	= node;
		list->last	= node;
	}
	else{
		list->first = node;
	}
	list->size++;
	return 1;
}

void* list_getfirst(const Linkedlist *list){
	assert(list != NULL);
	return list->first;
}

void* list_getlast(const Linkedlist *list){
	assert(list != NULL);
	return list->last;
}
