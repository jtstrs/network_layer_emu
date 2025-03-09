#include <stdint.h>
#include <stdio.h>

#include "queue.h"

void test_queue() {
    queue *q = create_queue();

    int32_t NODES_COUNT = 10;

    for (int32_t i = 0; i < NODES_COUNT; ++i) {
        push_queue(q, &i, sizeof(int32_t));
    }

    for (int32_t i = 0; i < NODES_COUNT; ++i) {
        int32_t *item = (int32_t *)(queue_last_item(q));
        printf("q[%d]=%d\n", i, *item);
        pop_queue(q);
    }
}

int32_t main(int32_t argc, char *argv[]) {
#ifdef RUN_TESTS
    test_queue();
#endif
    return 0;
}