#include <malloc.h>
#include <stdlib.h>
#include "stack.h"
#include <assert.h>

struct stack {
    // Points to dynamically allocated array of size 'capacity', or is NULL.
    char *data;
    // The capacity of the array.
    size_t capacity;
    // The number of entries currently in the stack.
    size_t length;
};

stack_ptr stack_new() {
    stack_ptr s = malloc(sizeof(struct stack));
    s->data = NULL;
    s->capacity = 0;
    s->length = 0;
    return s;
}

void stack_free(stack_ptr s) {
    if (s->data != NULL)
        free(s->data);
    free(s);
}

void stack_push(stack_ptr s, char c) {
    // TODO (task 2): how do we push an entry onto the stack?
    if(s->length == s->capacity){ //check if array is full 
        if(s->capacity == 0){ //Check if the array exists and has length, if it does. 
            s->capacity++;
            s->data = malloc(s->capacity*sizeof(char));
        }else{
            s->capacity *= 2; //doubles the capacity, if it is 0 set to 1
            s->data = realloc(s->data, s->capacity*sizeof(char)); //Realloc based on the data by the new_capacity
        }
        assert(s->data!=NULL);
    }
    s->data[s->length] = c; //put it in the array based on length
    s->length++; //increment the length

}

bool stack_pop(stack_ptr s, char *out) {
    // TODO (task 2): how do we pop an entry from the stack?
    if(s==NULL || s->data==NULL){ //if stack DNE, return
        return false;
    }
    *out = s->data[--s->length]; //print the stack item, dereferences which makes it char = char
    /*s->capacity--; //decrease the overall capacity
    realloc(s->data, s->capacity*sizeof(char)); //realloc with 1 less element (IDK IF I NEED THIS) */

    return true;
}
