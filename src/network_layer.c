#include "network_layer.h"
#include "queue.h"
#include <stdlib.h>

const int32_t MAX_IP_LENGHT = 16;
const int32_t OTHER_STUFF_SIZE = 10;

typedef struct NetworkLayer {
    queue * packets_queue;
    int32_t is_listen;
    NetworkLayerPacketReceivedCallback packet_received;
} NetworkLayer;

typedef struct NetworkLayerPacket {
    char transport_layer_data[OTHER_STUFF_SIZE];
    char ip[MAX_IP_LENGHT];
    char lower_levels_data[OTHER_STUFF_SIZE];
} NetworkLayerPacket;

NetworkLayer * create_layer() {

}

void release_layer(NetworkLayer * layer) {

}

void listen(NetworkLayer * layer) {

}

int32_t is_listen(NetworkLayer * layer) {

}

void stop_listen(NetworkLayer * layer) {

}

void send_packet(NetworkLayer * layer, NetworkLayerPacket * pkt) {

}

void read_packet(NetworkLayer * layer, NetworkLayerPacket * pkt) {

}

void register_on_packet_received_callback(NetworkLayer * layer, NetworkLayerPacketReceivedCallback callback) {

}
