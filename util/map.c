#include "map.h"

#include <string.h>
#include <stdlib.h>

map_t* map_empty() {
    return (map_t*)0;
}

addr_t map_find(map_t * map, char* key) {
    while (map) {
        if (!strcmp(map->key, key)) {
            return map->val;
        }
        map = map->next;
    }
    return 0;
}

void map_add(map_t** map, char* key, addr_t val){
    map_t* curr = malloc(sizeof(map_t));
    curr->key = key;
    curr->val = val;
    if(*map) {
        curr->next = *map;
    }
    *map = curr;
}

map_t* map_concat(map_t* m1, map_t* m2) {
    if(!m1) return m2;
    map_t* m = m1;
    while(m1->next) {
        m1 = m1->next;
    }
    m1->next = m2;
    return m;
}
