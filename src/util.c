#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include "server.h"
#include "util.h"

void error_and_exit(const char* format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    exit(1);
}

struct hashmap_node new_hashmap_node(HASHMAP_KEY key, HASHMAP_VAL val) {
    struct hashmap_node ret;
    ret.key = key;
    ret.val = val;
    return ret;
}

struct linked_list* new_linked_list(struct hashmap_node value) {
    struct linked_list* ret = malloc(sizeof(struct linked_list));
    ret->value = value;
    ret->next = NULL;
    return ret;
}

struct linked_list* find_node(struct linked_list* list, HASHMAP_KEY key) {
    while (list != NULL) {
        if (list->value.key == key) {
            return list;
        }
        list = list->next;
    }
    return NULL;
}

void free_linked_list(struct linked_list* list) {
    struct linked_list* prev = list;
    while (list != NULL) {
        list = list->next;
        free(prev);
    }
}

void hashmap_insert(struct hashmap* map, HASHMAP_KEY key, HASHMAP_VAL val) {
    size_t hashed = key % (map->capacity);
    struct linked_list** entry = map->arr + hashed;
    if (*entry == NULL) {
        *entry = new_linked_list(new_hashmap_node(key, val));
        return;
    }
    struct linked_list* cur = *entry;
    while (1) {
        if (cur->value.key == key) {
            cur->value.val = val;
            return;
        }
        if (cur->next == NULL) {
            break;
        } else {
            cur = cur->next;
        }
    }
    cur->next = new_linked_list(new_hashmap_node(key, val));
}

