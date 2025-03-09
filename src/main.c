#include <stdint.h>
#include <stdio.h>

#include "network_layer.h"
#include "queue.h"

#define RUN_TESTS

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

void test_callback(NetworkLayerPacket *pkt) {
    printf("Received pkt with name: %s\n", packet_name(pkt));
}

void test_network_layer() {
    printf("Create layer\n");
    NetworkLayer *l1 = create_layer();
    register_on_packet_received_callback(l1, test_callback);

    printf("Start listen for layer\n");
    listen(l1);

    printf("Send packets\n");
    const int32_t PACKETS_TO_SEND = 100;
    for (int32_t i = 0; i < PACKETS_TO_SEND; ++i) {
        char packet_name[64];
        sprintf(packet_name, "Packet name: %d", i);
        NetworkLayerPacket *packet = create_packet(packet_name);
        send_packet(l1, packet);
    }
    printf("Packets are sent\n");

    if (is_listen(l1)) {
        printf("Layer is listening. Stop it\n");
        stop_listen(l1);
        printf("Listening stoped\n");
    }

    printf("Release layer\n");
    release_layer(l1);
}

int32_t main(int32_t argc, char *argv[]) {
#ifdef RUN_TESTS
    test_queue();
    test_network_layer();
#endif

    return 0;
}