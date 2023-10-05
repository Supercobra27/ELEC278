#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct list_node {
    int value;
    struct list_node *next;
};

typedef struct list_node *iterator;

void print_list(struct list_node *head){
    iterator iter = head;
    while(iter != NULL){
        printf("%d ",iter->value);
        iter = iter->next;
    }
}

struct list_node* insertFirst(struct list_node *head, int data) {
// TODO: implement this function for inserting the first node in an empty linked list(task 1).
struct list_node *node = malloc(sizeof(struct list_node));
node->value = data;
node->next = head;
return node;
}

void insert_at_tail(struct list_node **head, int value) {
// TODO: implement this function for inserting a node at the tail of the linked list  (task 1).
struct list_node *node = malloc(sizeof(struct list_node));
node->value = value;
node->next = NULL;

iterator iter = *head;
if(iter == NULL){
    iter = node;
}else{
    while(iter->next != NULL){
        iter = iter->next;
    }
    iter->next=node;
}

}


void swap_adjacent(struct list_node *head) {
    // TODO: implement this (task 2).
    iterator iter = head;
    while(iter != NULL && iter->next != NULL){
        int temp = iter->value;
        iter->value = iter->next->value;
        iter->next->value = temp;
        iter = iter->next->next;
    }
}

void double_list(struct list_node *head) {
    // TODO: implement this (task 3).
    int i;
    iterator iter = head;
    for(i;i<7;i++){
        struct list_node *node = malloc(sizeof(struct list_node));
        node->next = NULL;
        iter->next->next->next->next->next->next->next = node;
        node->value = iter->value;
        iter = iter->next;
    }

}


void remove_adjacent_duplicates(struct list_node *head) {
    // TODO: implement this (task 4).
    struct list_node *iter = head;
    while(iter != NULL && iter->next != NULL){
        if(iter->value == iter->next->value){
            struct list_node *temp = iter->next;
            iter->next = iter->next->next;
            free(temp);
        }else{
            iter=iter->next;
        }
    }
}


int main() {
    // List is initially empty.
    struct list_node *head = NULL;

    // insert head
    head = insertFirst(head, 1);
    insert_at_tail(&head, 2);
    insert_at_tail(&head, 3);
    insert_at_tail(&head, 3);
    insert_at_tail(&head, 4);
    insert_at_tail(&head, 5);
    insert_at_tail(&head, 6);


    printf("Original list: ");
    print_list(head);

    printf("\nSwapping adjacent items: ");
    swap_adjacent(head);
    print_list(head);

    printf("\nDuplicating all items: ");
    double_list(head);
    print_list(head);

    printf("\nRemoving adjacent duplicates: ");
    remove_adjacent_duplicates(head);
    print_list(head); 

    return 0;
}
