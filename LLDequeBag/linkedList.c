#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


/* Double Link*/
struct DLink {
	TYPE value;
	struct DLink * next;
	struct DLink * prev;
};

/* Double Linked List with Head and Tail Sentinels  */

struct linkedList{
	int size;
	struct DLink *firstLink;
	struct DLink *lastLink;
};

/*
	initList
	param lst the linkedList
	pre: lst is not null
	post: lst size is 0
*/

void _initList (struct linkedList *lst) {

    lst->firstLink = malloc(sizeof(struct DLink));
    assert(lst->firstLink != NULL);

    lst->lastLink = malloc(sizeof(struct DLink));
    assert(lst->lastLink != NULL);

    lst->firstLink->next = lst->lastLink;
    lst->lastLink->prev = lst->firstLink;

    lst->size = 0;
}

/*
 createList
 param: none
 pre: none
 post: firstLink and lastLink reference sentinels
 */

struct linkedList *createLinkedList()
{
	struct linkedList *newList = malloc(sizeof(struct linkedList));
	_initList(newList);
	return(newList);
}

/*
	_addLinkBeforeBefore
	param: lst the linkedList
	param: l the  link to add before
	param: v the value to add
	pre: lst is not null
	pre: l is not null
	post: lst is not empty. increased size by 1
*/

/* Adds Before the provided link, l */

void _addLinkBefore(struct linkedList *lst, struct DLink *l, TYPE v)
{
    //NULL checking
	assert(lst);
	assert(l);
	assert(l->prev);

	struct DLink *newLink = malloc(sizeof(struct DLink));
	assert(newLink);

	newLink->value = v;

	//set newlink links
	newLink->next   = l;
	newLink->prev   = l->prev;

	//point adjacent links to newlink
	l->prev->next   = newLink;
	l->prev         = newLink;

	lst->size++;

}


/*
	addFrontList
	param: lst the linkedList
	param: e the element to be added
	pre: lst is not null
	post: lst is not empty
*/

void addFrontList(struct linkedList *lst, TYPE e)
{
    //NULL checking
    assert(lst);
    assert(lst->firstLink);
    assert(lst->firstLink->next);

    _addLinkBefore(lst,lst->firstLink->next,e);

}

/*
	addBackList
	param: lst the linkedList
	param: e the element to be added
	pre: lst is not null
	post: lst is not empty
*/

void addBackList(struct linkedList *lst, TYPE e) {
  
    //NULL checking
    assert(lst);
    assert(lst->lastLink);

    _addLinkBefore(lst,lst->lastLink,e);

}

/*
	frontList
	param: lst the linkedList
	pre: lst is not null
	pre: lst is not empty
	post: none
*/

TYPE frontList (struct linkedList *lst) {

    //NULL checking
    assert(lst);
    assert(lst->firstLink);
    assert(lst->firstLink->next);
    assert(!isEmptyList(lst)); //check not empty

	return(lst->firstLink->next->value);
}

/*
	backList
	param: lst the linkedList
	pre: lst is not null
	pre: lst is not empty
	post: lst is not empty
*/

TYPE backList(struct linkedList *lst)
{
    //NULL checking
    assert(lst);
    assert(lst->lastLink);
    assert(lst->lastLink->prev);
    assert(!isEmptyList(lst)); //check not empty

    return(lst->lastLink->prev->value);
}

/*
	_removeLink
	param: lst the linkedList
	param: l the linke to be removed
	pre: lst is not null
	pre: l is not null
	post: lst size is reduced by 1
*/

void _removeLink(struct linkedList *lst, struct DLink *l)
{

    //NULL checking
    assert(lst);
    assert(l);
    assert(l->next);
    assert(l->prev);
    assert(!isEmptyList(lst)); //check not empty

    //reassign pointers
    l->next->prev = l->prev;
    l->prev->next = l->next;

    free(l);

    lst->size--;
	
}

/*
	removeFrontList
	param: lst the linkedList
	pre:lst is not null
	pre: lst is not empty
*/

void removeFrontList(struct linkedList *lst) {

    //NULL checking
    assert(lst);
    assert(lst->firstLink);
    assert(lst->firstLink->next);
    assert(!isEmptyList(lst)); //check not empty

    _removeLink(lst,lst->firstLink->next);

}

/*
	removeBackList
	param: lst the linkedList
	pre: lst is not null
	pre:lst is not empty
*/

void removeBackList(struct linkedList *lst)
{	
    //NULL checking
    assert(lst);
    assert(lst->lastLink);
    assert(lst->lastLink->prev);
    assert(!isEmptyList(lst)); //check not empty

    _removeLink(lst,lst->lastLink->prev);
	
}

/*
	isEmptyList
	param: lst the linkedList
	pre: lst is not null
	post: none
*/

int isEmptyList(struct linkedList *lst) {
    //NULL checking
    assert(lst);

	return(lst->size==0);
}


/* Function to print list
 Pre: lst is not null
 */
void _printList(struct linkedList* lst)
{
    assert(lst);
    assert(lst->lastLink);
    assert(lst->firstLink);

	for(struct DLink *l=lst->firstLink->next;
	        l!=lst->lastLink;
	        l=l->next){

	    //null checking
	    assert(l);

	    printf("%d, ",l->value);

	}
	printf("\n");

}

/* 
	Add an item to the bag
	param: 	lst		pointer to the bag
	param: 	v		value to be added
	pre:	lst is not null
	post:	a link storing val is added to the bag
 */
void addList(struct linkedList *lst, TYPE v)
{
    //NULL checking
    assert(lst);
    assert(lst->lastLink);

    _addLinkBefore(lst,lst->lastLink,v);
}

/*	Returns boolean (encoded as an int) demonstrating whether or not
	the specified value is in the collection
	true = 1
	false = 0

	param:	lst		pointer to the bag
	param:	e		the value to look for in the bag
	pre:	lst is not null
	pre:	lst is not empty
	post:	no changes to the bag
*/
int containsList (struct linkedList *lst, TYPE e) {

    //NULL checking
    assert(lst);
    assert(lst->lastLink);
    assert(lst->firstLink);
    assert(!isEmptyList(lst)); //check not empty

    for(struct DLink *l=lst->firstLink->next;
            l!=lst->lastLink;
            l=l->next){

        //null checking
        assert(l);

        if(l->value == e) return(1); //item found
    }

    return(0); //item not found

}

/*	Removes the first occurrence of the specified value from the collection
	if it occurs

	param:	lst		pointer to the bag
	param:	e		the value to be removed from the bag
	pre:	lst is not null
	pre:	lst is not empty
	post:	e has been removed
	post:	size of the bag is reduced by 1
*/
void removeList (struct linkedList *lst, TYPE e) {
    //NULL checking
    assert(lst);
    assert(lst->lastLink);
    assert(lst->firstLink);
    assert(!isEmptyList(lst)); //check not empty

    for(struct DLink *l=lst->firstLink->next;
           l!=lst->lastLink;
           l=l->next){

       //null checking
       assert(l);

       //item found
       if(l->value == e){
           _removeLink(lst,l);
           return;
       }
    }
}
