#include "network_layer.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

const int32_t MAX_IP_LENGHT = 16;
const int32_t OTHER_STUFF_SIZE = 10;
const int32_t PACKET_NAME_SIZE = 20;

#define LISTEN 1
#define NOT_LISTEN 0

typedef struct NetworkLayer {
    queue* packets_queue;
    pthread_mutex_t* queue_mutex;
    pthread_t queue_thread_pid;

    int32_t is_listen;
    pthread_mutex_t* listen_mutex;

    NetworkLayerPacketReceivedCallback packet_received_callback;
} NetworkLayer;

typedef struct NetworkLayerPacket {
    char meta_packet_name[PACKET_NAME_SIZE];
} NetworkLayerPacket;

NetworkLayerPacket* create_packet(char* name) {
    NetworkLayerPacket* pkt =
        (NetworkLayerPacket*)(malloc(sizeof(NetworkLayerPacket)));
    if (pkt == NULL) {
        return NULL;
    }
    mark_packet(pkt, name);
    return pkt;
}

void release_packet(NetworkLayerPacket* pkt) { free(pkt); }

void mark_packet(NetworkLayerPacket* pkt, char* name) {
    if (pkt == NULL) {
        return;
    }
    memcpy(pkt->meta_packet_name, name, strlen(name));
}

char* packet_name(NetworkLayerPacket* pkt) { return pkt->meta_packet_name; }

pthread_mutex_t* create_mutex() {
    pthread_mutex_t* mutex =
        (pthread_mutex_t*)(malloc(sizeof(pthread_mutex_t)));
    pthread_mutex_init(mutex, NULL);
    return mutex;
}

void release_mutex(pthread_mutex_t* mutex) {
    pthread_mutex_destroy(mutex);
    free(mutex);
}

void* exec_listen(void* layer_raw) {
    NetworkLayer* layer = (NetworkLayer*)layer_raw;

    while (1) {
        if (is_listen(layer) == NOT_LISTEN) {
            pthread_exit(0);
        }
        pthread_mutex_lock(layer->queue_mutex);

        if (queue_size(layer->packets_queue) == 0) {
            pthread_mutex_unlock(layer->queue_mutex);
        } else {
            NetworkLayerPacket* pkt =
                (NetworkLayerPacket*)queue_last_item(layer->packets_queue);
            if (layer->packet_received_callback != NULL) {
                layer->packet_received_callback(pkt);
            }
            pop_queue(layer->packets_queue);
            pthread_mutex_unlock(layer->queue_mutex);
        }
    }
}

NetworkLayer* create_layer() {
    NetworkLayer* layer = (NetworkLayer*)malloc(sizeof(NetworkLayer));

    if (layer == NULL) {
        return NULL;
    }

    layer->packets_queue = create_queue();

    if (layer->packets_queue == NULL) {
        free(layer);
        return NULL;
    }

    layer->is_listen = NOT_LISTEN;
    layer->packet_received_callback = NULL;

    layer->queue_mutex = create_mutex();
    layer->listen_mutex = create_mutex();

    return layer;
}

void release_layer(NetworkLayer* layer) {
    release_queue(layer->packets_queue);
    release_mutex(layer->queue_mutex);
    release_mutex(layer->listen_mutex);
    free(layer);
}

void listen(NetworkLayer* layer) {
    if (is_listen(layer) == LISTEN) {
        stop_listen(layer);
    }

    pthread_mutex_lock(layer->listen_mutex);
    layer->is_listen = LISTEN;
    int32_t err = pthread_create(&layer->queue_thread_pid, NULL, exec_listen,
                                 (void*)layer);
    pthread_mutex_unlock(layer->listen_mutex);

    if (err != 0) {
        printf("Cannot create layer thread. Error code: %d\n", err);
        return;
    }
}

int32_t is_listen(NetworkLayer* layer) {
    pthread_mutex_lock(layer->listen_mutex);
    int32_t res = layer->is_listen;
    pthread_mutex_unlock(layer->listen_mutex);
    return res;
}

void stop_listen(NetworkLayer* layer) {
    if (layer == NULL) {
        return;
    }

    if (is_listen(layer) == LISTEN) {
        pthread_mutex_lock(layer->listen_mutex);
        layer->is_listen = NOT_LISTEN;
        pthread_mutex_unlock(layer->listen_mutex);

        pthread_join(layer->queue_thread_pid, NULL);
    }
}

void send_packet(NetworkLayer* layer, NetworkLayerPacket* pkt) {
    pthread_mutex_lock(layer->queue_mutex);
    push_queue(layer->packets_queue, pkt, sizeof(NetworkLayerPacket));
    pthread_mutex_unlock(layer->queue_mutex);
}

void read_packet(NetworkLayer* layer, NetworkLayerPacket* pkt) {}

void register_on_packet_received_callback(
    NetworkLayer* layer, NetworkLayerPacketReceivedCallback callback) {
    layer->packet_received_callback = callback;
}
