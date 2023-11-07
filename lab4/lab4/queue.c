#include "queue.h"
#include <assert.h>

void init_queue(struct queue *q) {
    q->data = NULL;
    q->capacity = 0;
    q->offset = 0;
    q->length = 0;
}

void clear_queue(struct queue *q) {
    if (q->data != NULL) {
        free(q->data);
        init_queue(q);
    }
}

void enqueue(struct queue *q, int value) {
    // TODO: Task 1: add an element to the circular queue.
    if(q->length == q->capacity){
        q->capacity = q->capacity == 0 ? 1 : q->capacity*2;
        q->data = realloc(q->data, sizeof(int)*q->capacity);
    }
    q->data[(q->offset+q->length)%q->capacity] = value;
    q->length++;
}

bool dequeue(struct queue *q, int *out) {
    // TODO: Task 1: remove an element from the circular queue.
    if(q->length == 0){
        return false;
    }
    *out = q->data[q->offset];
    q->length--;
    q->offset = (q->offset+1)%q->capacity;
    if((q->length > q->capacity)/4){
        q->capacity /= 2;
        q->data = realloc(q->data, sizeof(int)*q->capacity);
    }
    return true;
}

bool queue_empty(struct queue *q) {
    // TODO: Task 1: check whether the queue is empty.
    return q->length==0;
}
