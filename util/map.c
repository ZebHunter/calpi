#include "map.h"

#include <string.h>
#include <stdlib.h>

void* map_find(map_t * map, char* key) {
    while (map) {
        if (!strcmp(map->key, key)) {
            return map->val;
        }
        map = map->next;
    }
}

void map_add(map_t** map, char* key, void* val){
    map_t* curr = malloc(sizeof(map_t));
    curr->key = key;
    curr->val = val;
    if(*map) {
        curr->next = *map;
        (*map)->prev = curr;
    }
    *map = curr;
}

map_t* map_empty() {
    return (map_t*) 0;
}