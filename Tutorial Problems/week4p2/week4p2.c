#include <stdbool.h>
#include <stdio.h>

// The size of the arrays at each node.
#define ARRAY_SIZE 4

// A linked list, where each node contains an array; null for an empty list.
typedef struct list_node *hybrid_list;

struct list_node {
    int values[ARRAY_SIZE];
    hybrid_list tail;
};

struct stack {
    // TODO: what fields do we need?
    //Null if stack is empty
    hybrid_list list;
    //Number of elements used in first node (>0). Ignore if list == NULL
    int first_length;
};

void push(struct stack *s, int value) {
    // TODO: implement this.
    if(s->list==NULL || s->first_length==ARRAY_SIZE){
        struct list_node *new_node = malloc(sizeof(struct list_node));
        new_node->tail = s->list; //Set end of node == to prev node
        s->list = new_node; //change to first node
        s->first_length = 0; //show that it is 0
    }

    s->list->values[s->first_length++]=value; //push it
}

bool pop(struct stack *s, int *out) {
    // TODO: implement this.
    if(s->list == NULL)
        return false;

        out = s->list->values[--s->first_length]; //Get the value and decrement the list

    if(s->first_length == 0){ //If node is empty
        strust list_node *old = s->list; //make pointer to empty
        s->list = old->tail; //reset pointers
        free(old); //free
        s->first_length == ARRAY_SIZE; //show that the item underneath is full
    }
    return false;
}

int main() {
    struct stack s = {
            // TODO: initialize all fields.
        .list = NULL;s
    };

    for (int i = 1; i <= 10; i++) {
        printf("push: %d\n", i);
        push(&s, i);
    }

    int value;
    while (pop(&s, &value))
        printf("pop: %d", value);

    return 0;
}
