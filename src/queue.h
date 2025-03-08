#include <stdlib.h>

struct queue;
typedef struct queue queue;

queue *create_queue();
queue *release_queue();

void push_queue(queue *queue, void *data);
void *queue_last_item();
void pop_queue(queue *queue);
size_t queue_size(queue *queue);