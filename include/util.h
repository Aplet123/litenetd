#ifndef ND_UTIL_H
#define ND_UTIL_H

#include <arpa/inet.h>

#ifndef HASHMAP_STARTING_LEN
#define HASHMAP_STARTING_LEN 16
#endif

#ifndef HASHMAP_GROWTH_FACTOR
#define HASHMAP_GROWTH_FACTOR 2
#endif

#ifndef HASHMAP_GROWTH_CONSTANT
#define HASHMAP_GROWTH_CONSTANT 1
#endif

#ifndef HASHMAP_MAXIMUM_LOAD
#define HASHMAP_MAXIMUM_LOAD 1.0
#endif

// HASHMAP_KEY should be an unsigned type
#ifndef HASHMAP_KEY
#define HASHMAP_KEY in_addr_t
#endif

#ifndef HASHMAP_VAL
#define HASHMAP_VAL int
#endif

void error_and_exit(const char* format, ...);

struct hashmap_node {
    HASHMAP_KEY key;
    HASHMAP_VAL val;
};

struct linked_list {
    struct hashmap_node value;
    struct linked_list* next;
};

struct hashmap_node new_hashmap_node(HASHMAP_KEY key, HASHMAP_VAL val);
struct linked_list* new_linked_list(struct hashmap_node value);
struct linked_list* find_node(struct linked_list* list, HASHMAP_KEY key);
void free_linked_list(struct linked_list* list);

struct hashmap {
    struct linked_list** arr;
    size_t entries;
    size_t capacity;
};

struct hashmap new_hashmap();
void hashmap_insert(struct hashmap* map, HASHMAP_KEY key, HASHMAP_VAL val);

#endif
