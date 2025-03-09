#include <stdint.h>
#include <stdio.h>

#include "queue.h"
#include "network_layer.h"

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

void test_network_layer() {
    NetworkLayer * l1 = create_layer();

    listen(l1);
    
    const int32_t PACKETS_TO_SEND = 100;
    for (int32_t i = 0; i < PACKETS_TO_SEND; ++i) {
        NetworkLayerPacket * packet = NULL;
        send_packet(l1, packet);
    }

    if (is_listen(l1)) {
        stop_listen(l1);
    }

    release_layer(l1);
}

int32_t main(int32_t argc, char *argv[]) {
#ifdef RUN_TESTS
    test_queue();
    test_network_layer();
#endif

    return 0;
}