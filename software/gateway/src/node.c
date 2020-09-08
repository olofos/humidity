#include <stdint.h>
#include <stdlib.h>

#include "node.h"

#ifdef UNIT_TESTING
struct node *first_node;
#else
static struct node *first_node;
#endif

#ifdef UNIT_TESTING
extern void* _test_malloc(const size_t size, const char* file, const int line);
#define malloc(size) _test_malloc(size, __FILE__, __LINE__)
#endif

struct node *node_register(uint8_t node_id, uint64_t firmware_hash, uint8_t protocol_version)
{
    struct node *node = node_get(node_id);

    if(!node) {
        node = malloc(sizeof(*node));
        if(node) {
            node->next = first_node;
            first_node = node;
        }
    }

    if(node) {
        node->node_id = node_id;
        node->firmware_hash = firmware_hash;
        node->protocol_version = protocol_version;
    }

    return node;
}

struct node *node_get(uint8_t node_id)
{
    for(struct node *node = first_node; node; node = node->next) {
        if(node->node_id == node_id) {
            return node;
        }
    }

    return 0;
}
