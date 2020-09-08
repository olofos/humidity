#ifndef NODE_H_
#define NODE_H_

struct node {
    uint64_t firmware_hash;
    struct node *next;
    uint8_t node_id;
    uint8_t protocol_version;
};

struct node *node_get(uint8_t node_id);
struct node *node_register(uint8_t node_id, uint64_t firmware_hash, uint8_t protocol_version);

#endif
