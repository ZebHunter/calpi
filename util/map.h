#ifndef MAP
#define MAP

#include <stdint.h>

typedef uint16_t addr_t;
typedef struct map {
    struct map* next;
    char* key;
    addr_t val;
} map_t;




map_t* map_empty();
addr_t map_find(map_t * map, char* key);
void map_add(map_t** map, char* key, addr_t val);
map_t* map_concat(map_t* m1, map_t* m2);
#endif