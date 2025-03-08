#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  void *data;
  node *next;
  node *prev;
} node;

typedef struct queue {
  node *head;
  size_t size;
} queue;

queue *create_queue() { queue *q = (queue *)malloc(sizeof(queue)); }
queue *release_queue() {}

void push_queue(queue *queue, void *data) {}
void *queue_last_item() {}
void pop_queue(queue *queue) {}
size_t queue_size(queue *queue) {}