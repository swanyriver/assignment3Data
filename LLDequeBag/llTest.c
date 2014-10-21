#include <stdio.h>
#include <assert.h>
#include "linkedList.h"

/* Double Link Struture */
struct DLink {
    TYPE value;/* value of the link */
    struct DLink * next;/* pointer to the next link */
    struct DLink * prev;/* pointer to the previous link */
};
/* Double Linked List with Head and Tail Sentinels  */

struct linkedList{
    int size;
    struct DLink *firstLink;
    struct DLink *lastLink;
};


void printList(struct linkedList* lst)
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

int main(){

    struct linkedList *b = createLinkedList();
    for(int i = 0 ; i < 15 ; i++) {
        addList(b, (TYPE)i);/*Add elements*/
        printList(b);
    }


}
