#include <malloc.h>
#include "stack.h"
#include <assert.h>

struct stack_node {
    // TODO (task 1): what fields do we need here?
    char val;
    struct stack_node *tail;
};

struct stack {
    // Null if the stack is empty.
    struct stack_node *head;
};

stack_ptr stack_new() {
    stack_ptr s = malloc(sizeof(struct stack));
    s->head = NULL;
    return s;
}

void stack_free(stack_ptr s) {
    // TODO (task 1): how do we make sure the nodes don't leak memory?
    struct stack_node *curr;
    while(s->head!=NULL){ //if the top pointer exists
        if(s->head->tail == NULL){ //if the element below does not exist
            free(s->head); //free up the node itself no other logic
        }else{
            curr = s->head; //create an iterator-type element to the curr element
            s->head = curr->tail; //set top pointer to below
            free(curr); //free top node
        }
    }
    free(s);
}

void stack_push(stack_ptr s, char c) {
    // TODO (task 1): how do we push an entry onto the stack?
    struct stack_node *pushed = malloc(sizeof(struct stack_node)); //Makes a node based on size of stack_node
    pushed->tail = s->head; //Sets the new top element's tail to point to the element below it
    pushed->val = c; //add the val to the node
    s->head = pushed; //reset the top pointer
}

bool stack_pop(stack_ptr s, char *out) {
    // TODO (task 1): how do we pop an entry from the stack?
    if(s->head==NULL) return false; //If list does not exist
    if(s->head!=NULL){
    struct stack_node *popped = s->head; //makes popped pointer to head
    *out = popped->val; //use the popped pointer -> value
    s->head = popped->tail; //sets top pointer == to node below
    free(popped); //free the memory
    return true;
    }
}
