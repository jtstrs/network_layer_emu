#include <stdlib.h>

struct queue;
typedef struct queue queue;

queue *create_queue();
void release_queue(queue *);

void push_queue(queue *, void *, int32_t data_sizeof);
void *queue_last_item(queue *);
void pop_queue(queue *);
size_t queue_size(queue *);