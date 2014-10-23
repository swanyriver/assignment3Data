#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <float.h>
#include "cirListDeque.h"

/* Double Link Struture */
struct DLink {
	TYPE value;/* value of the link */
	struct DLink * next;/* pointer to the next link */
	struct DLink * prev;/* pointer to the previous link */
};

# define TYPE_SENTINEL_VALUE DBL_MAX 


/* ************************************************************************
 Deque ADT based on Circularly-Doubly-Linked List WITH Sentinel
 ************************************************************************ */

struct cirListDeque {
	int size;/* number of links in the deque */
	struct DLink *Sentinel;	/* pointer to the sentinel */
};
/* internal functions prototypes */
struct DLink* _createLink (TYPE val);
void _addLinkAfter(struct cirListDeque *q, struct DLink *lnk, TYPE v);
void _removeLink(struct cirListDeque *q, struct DLink *lnk);



/* ************************************************************************
	Deque Functions
************************************************************************ */

/* Initialize deque.

	param: 	q		pointer to the deque
	pre:	q is not null
	post:	q->Sentinel is allocated and q->size equals zero
*/
void _initCirListDeque (struct cirListDeque *q) 
{
    //null checking
  	assert(q);

  	q->Sentinel = _createLink(0);

  	//sentinal points to itself in empty list
  	q->Sentinel->next = q->Sentinel;
  	q->Sentinel->prev = q->Sentinel;

  	q->size=0;  //init size
}

/*
 create a new circular list deque
 
 */

struct cirListDeque *createCirListDeque()
{
	struct cirListDeque *newCL = malloc(sizeof(struct cirListDeque));
	_initCirListDeque(newCL);
	return(newCL);
}


/* Create a link for a value.

	param: 	val		the value to create a link for
	pre:	none
	post:	a link to store the value
*/
struct DLink * _createLink (TYPE val)
{
	struct DLink *newLink = malloc(sizeof(struct DLink));
	assert(newLink);    //null checking

	newLink->value=val; //assign value

	return newLink;

}

/* Adds a link after another link

	param: 	q		pointer to the deque
	param: 	lnk		pointer to the existing link in the deque
	param: 	v		value of the new link to be added after the existing link
	pre:	q is not null
	pre: 	lnk is not null
	pre:	lnk is in the deque 
	post:	the new link is added into the deque after the existing link
*/
void _addLinkAfter(struct cirListDeque *q, struct DLink *lnk, TYPE v)
{
	//null checking
    assert(q);
    assert(lnk);
    assert(lnk->next);
    assert(lnk->prev);

    struct DLink *newLink = _createLink(v);

    //position link in list
    newLink->prev = lnk;
    newLink->next = lnk->next;

    //adjacent links point at new link
    lnk->next->prev = newLink;
    lnk->next = newLink;

    q->size++;  //the only function that increments size

}

/* Adds a link to the back of the deque

	param: 	q		pointer to the deque
	param: 	val		value for the link to be added
	pre:	q is not null
	post:	a link storing val is added to the back of the deque
*/
void addBackCirListDeque (struct cirListDeque *q, TYPE val) 
{
    //null checking
	assert(q);
	assert(q->Sentinel);
	assert(q->Sentinel->prev);

	_addLinkAfter(q,q->Sentinel->prev,val);

}

/* Adds a link to the front of the deque

	param: 	q		pointer to the deque
	param: 	val		value for the link to be added
	pre:	q is not null
	post:	a link storing val is added to the front of the deque
*/
void addFrontCirListDeque(struct cirListDeque *q, TYPE val)
{
    //null checking
    assert(q);
    assert(q->Sentinel);

    _addLinkAfter(q,q->Sentinel,val);

}

/* Get the value of the front of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	none
	ret: 	value of the front of the deque
*/
TYPE frontCirListDeque(struct cirListDeque *q) 
{
    //null checking
    assert(q);
    assert(q->Sentinel);
    assert(q->Sentinel->next);
	assert(!isEmptyCirListDeque(q));

	return(q->Sentinel->next->value);
}

/* Get the value of the back of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	none
	ret: 	value of the back of the deque
*/
TYPE backCirListDeque(struct cirListDeque *q)
{
    //null checking
    assert(q);
    assert(q->Sentinel);
    assert(q->Sentinel->prev);
    assert(!isEmptyCirListDeque(q));

    return(q->Sentinel->prev->value);
}

/* Remove a link from the deque

	param: 	q		pointer to the deque
	param: 	lnk		pointer to the link to be removed
	pre:	q is not null and q is not empty
	post:	the link is removed from the deque
*/
void _removeLink(struct cirListDeque *q, struct DLink *lnk)
{
    //null checking
    assert(q);
    assert(lnk);
    assert(lnk->next);
    assert(lnk->prev);
    assert(!isEmptyCirListDeque(q));

    //remove link from chain
    lnk->prev->next = lnk->next;
    lnk->next->prev = lnk->prev;

    //free up memory
    free(lnk);

    q->size--;  //the only function that decrements size

}

/* Remove the front of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	the front is removed from the deque
*/
void removeFrontCirListDeque (struct cirListDeque *q) {

    //null checking
    assert(q);
    assert(q->Sentinel);
    assert(q->Sentinel->next);
    assert(!isEmptyCirListDeque(q));

    _removeLink(q,q->Sentinel->next);
}


/* Remove the back of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	the back is removed from the deque
*/
void removeBackCirListDeque(struct cirListDeque *q)
{
    //null checking
    assert(q);
    assert(q->Sentinel);
    assert(q->Sentinel->prev);
    assert(!isEmptyCirListDeque(q));

    _removeLink(q,q->Sentinel->prev);
}

/* De-allocate all links of the deque

	param: 	q		pointer to the deque
	pre:	none
	post:	All links (including Sentinel) are de-allocated
*/
void freeCirListDeque(struct cirListDeque *q)
{
    assert(q);
    assert(q->Sentinel);
    assert(q->Sentinel->next);

    struct DLink *lnk = q->Sentinel->next;
	while(lnk!=q->Sentinel){
	    assert(lnk);
	    assert(lnk->next);
	    struct DLink *holder = lnk->next;

	    free(lnk);

	    lnk=holder;
	}
	
	free(lnk); //free sentinel
}

/* Check whether the deque is empty

	param: 	q		pointer to the deque
	pre:	q is not null
	ret: 	1 if the deque is empty. Otherwise, 0.
*/
int isEmptyCirListDeque(struct cirListDeque *q) {

    assert(q); //null checking

	return(q->size==0);
}

/* Print the links in the deque from front to back

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post: 	the links in the deque are printed from front to back
*/
void printCirListDeque(struct cirListDeque *q)
{
	//null checking
    assert(q);
    assert(q->Sentinel);
    assert(!isEmptyCirListDeque(q));


    for(struct DLink *l=q->Sentinel->next; l!=q->Sentinel; l=l->next){
        assert(l);

        printf("%g, ",l->value);
    }
    printf("\n");

}

/* Reverse the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post: 	the deque is reversed
*/
void reverseCirListDeque(struct cirListDeque *q)
{
    //null checking
    assert(q);
    assert(!isEmptyCirListDeque(q));

    struct DLink *l=q->Sentinel;

    do{
        assert(l);

        //swap next and prev pointers
        struct DLink *preserved_next = l->next;
        l->next = l->prev;
        l->prev = preserved_next;

        //move to next link
        l=preserved_next;

    }while(l!=q->Sentinel);

}
