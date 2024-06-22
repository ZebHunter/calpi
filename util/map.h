#ifndef MAP
#define MAP


typedef struct map {
    char* key;
    void* val;

    struct map* next;
    struct map* prev;
} map_t;


void* map_find(map_t * map, char* key);
map_t* map_empty();
void map_add(map_t* map, char* key, void* val);

#endif