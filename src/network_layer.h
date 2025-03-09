#include <stdint.h>

typedef struct NetworkLayer NetworkLayer;
typedef struct NetworkLayerPacket NetworkLayerPacket;
typedef void (*NetworkLayerPacketReceivedCallback)(NetworkLayerPacket*);

NetworkLayer * create_layer();
void release_layer(NetworkLayer * layer);

void listen(NetworkLayer * layer);
int32_t is_listen(NetworkLayer * layer);
void stop_listen(NetworkLayer * layer);

void send_packet(NetworkLayer * layer, NetworkLayerPacket * pkt);
void read_packet(NetworkLayer * layer, NetworkLayerPacket * pkt);

void register_on_packet_received_callback(NetworkLayer * layer, NetworkLayerPacketReceivedCallback callback);
