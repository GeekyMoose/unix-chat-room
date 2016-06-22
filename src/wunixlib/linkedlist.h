/**
 * \file		linkedlist.h
 * \author		Constantin MASSON
 * \date		June 22, 2016
 *
 * \details		Simple generic linkedlist.
 *
 * Header file
 *
 * \attention	List is meant to be used with the same type of data.
 * 				Although it will technically accept any, unexpected behaviors
 * 				might append. (Free function might not work anymore for example).
 * \attention	Each node has a pointer to the data for this node (Instead of copy).
 * 				If data was dynamically created (From malloc...), data must be free while
 * 				destroying the list.
 *
 * \bug			In case of non dynamic variable passed to the list (Like a simple
 * 				int), the list will keep a pointer to this int.
 * 				Do not use the same int variable to set several element!
 * 				Example (Of code you shouldn't use):
 * 				<br/><br/>
 * 				int i;
 * 				<br/>
 * 				for(int i=0; i<10; i++){ list_append(&list, &i); }
 * 				<br/><br/>
 * 				The result will be a list of 10 element pointing to the same 
 * 				integer (With value 11).
 */

#ifndef WUNIXLIB_LINKEDLIST_H
#define WUNIXLIB_LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>




// -----------------------------------------------------------------------------
// Structures / Data
// -----------------------------------------------------------------------------

/** \brief Function to define how to free an element in the list. */
typedef void(*freefct)(void*);

/**
 * \brief	Function that iterate a list.
 * \details	Iterate while iterator return 1
 */
typedef int(*iteratorfct)(void*);

/** \brief Define a linked list node. */
typedef struct _linkedlistNode{
	void *data;
	struct _linkedlistNode *next;
} LinkedlistNode;

/** \brief	Define a Linkedlist type (Must be initialized with init function). */
typedef struct _linkedlist{
	int				size; //Virtual size of the list.
	freefct			freefct; //Fct to free data in node.
	LinkedlistNode	*first;
	LinkedlistNode	*last;
} Linkedlist;


// -----------------------------------------------------------------------------
// Functions
// -----------------------------------------------------------------------------

/**
 * \brief		Initialize the list.
 * \details		Must be called on new declared linkedlist before using it.
 * \details		The freefct define the way a Node data must be free. If NULL given,
 * 				node data won't be free at all (Must be done manually or not needed.)
 * 				If not null, this function will be called for each node in the list
 * 				when list is destroyed.
 * \warning		If list is NULL, assert error thrown.
 *
 * \param list	Pointer to the list to initialize
 * \param f		Function used to free a Node data or NULL if not needed
 */
void list_init(Linkedlist *list, freefct f);

/**
 * \brief		Remove all elements from the list and free memory.
 * \details		All its elements will be destroyed and data free (If free defined)
 * \warning		If list is NULL, assert error thrown.
 *
 * \param list	List to destroys
 */
void list_clear(Linkedlist *list);

/**
 * \brief		Check whether the given is is empty.
 * \details		Empty means list has no element inside.
 * \warning		If list is NULL, assert error thrown.
 *
 * \param list	The list to test
 * \return		1 if empty, otherwise, return 0
 */
int list_is_empty(const Linkedlist *list);

/**
 * \brief		Get the list size.
 * \warning		If list is NULL, assert error thrown.
 *
 * \param list	The list to check
 * \return		Current list size
 */
int list_size(const Linkedlist *list);

/**
 * \brief		Iterate the given list according to iterator function.
 * \details		Call f on each Node (While iterator returns 1)
 * \warning		If list is NULL, assert error thrown.
 * \warning		If f is NULL, assert error thrown.
 *
 * \param list	List to iterate
 * \param f		Iterator function
 */
void list_iterate(const Linkedlist *list, iteratorfct f);

/**
 * \brief		Add data element at the end of the list.
 * \details		Element in list point to given data.
 * \warning		If list is NULL, assert error thrown.
 * \warning		If internal error occurred (Unable to allocate memory), -1 returned.
 *
 * \param list	List where to add element (Can be empty)
 * \param data	Data to place in list
 * \return		1 if successfully added, otherwise, -1
 */
int list_append(Linkedlist *list, void * const data);

/**
 * \brief		Add element at the beginning of the list.
 * \details		Element in list point to given data.
 * \warning		If list is NULL, assert error thrown.
 * \warning		If internal error occurred (Unable to allocate memory), -1 returned.
 *
 * \param list	List where to add element (Can be empty)
 * \param data	Data to place in list
 * \return		1 if successfully added, otherwise, -1
 */
int list_append_first(Linkedlist *list, void * const data);

/**
 * \brief		Return the first elements in the list.
 * \warning		If list is NULL, assert error thrown.
 *
 * \param list	List where to look for
 * \return		Pointer to the first element
 */
void* list_getfirst(const Linkedlist *list);

/**
 * \brief		Return the last elements in the list.
 * \warning		If list is NULL, assert error thrown.
 *
 * \param list	List where to look for
 * \return 		Pointer to the last element
 */
void* list_getlast(const Linkedlist *list);


#endif



