#include "queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    void *data;
    int32_t data_sizeof;
    struct node *next;
    struct node *prev;
} node;

typedef struct queue {
    node *head;
    node *tail;
    size_t size;
} queue;

node *allocate_node(void *data, int32_t data_sizeof) {
    node *n = (node *)malloc(sizeof(node));
    n->data = malloc(data_sizeof);
    memcpy(n->data, data, data_sizeof);

    n->next = NULL;
    n->prev = NULL;
    return n;
}

size_t queue_size(queue *queue) {
    if (queue == NULL) {
        return 0;
    }
    return queue->size;
}

void push_queue(queue *queue, void *data, int32_t data_sizeof) {
    if (queue == NULL) {
        return;
    }

    queue->size++;

    if (queue->head == NULL) {
        queue->head = allocate_node(data, data_sizeof);
        queue->tail = queue->head;
        return;
    }

    node *new_tail = allocate_node(data, data_sizeof);
    new_tail->prev = queue->tail;
    queue->tail = new_tail;
}

void pop_queue(queue *queue) {
    if (queue == NULL) {
        return;
    }

    if (queue_size(queue) == 0) {
        return;
    }
    queue->size--;

    node *last_node = queue->tail;
    queue->tail = last_node->prev;

    free(last_node->data);
    free(last_node);
}

void *queue_last_item(struct queue *queue) {
    if (queue == NULL) {
        return NULL;
    }

    if (queue_size(queue) == 0) {
        return NULL;
    }
    return queue->tail->data;
}

queue *create_queue() {
    queue *q = (queue *)malloc(sizeof(queue));
    q->head = NULL;
    q->size = 0;

    return q;
}

void release_queue(queue *queue) {
    if (!queue) {
        return;
    }

    node *head = queue->head;
    if (head == NULL || queue_size(queue) == 0) {
        return;
    }

    while (queue_size(queue) != 0) {
        pop_queue(queue);
    }
}
