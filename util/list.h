#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_SIZE 1024

#define List(value_t) struct { \
    value_t* data;  \
    uint64_t size;  \
    uint64_t capacity;  \
}

#define listInit(l) do {   \
    (l).data = NULL;    \
    (l).size = 0;       \
    (l).capacity = 0;   \
} while(0)

#define listDestroy(l) do { \
    free((l).data); \
} while(0)

#define getListSize(l) ((l).size)

#define getListCapacity(l) ((l).capacity)

#define getElement(l, index) ((l).data[(index)])

#define listClear(l) do {(l).size = 0;} while(0)

static inline bool listRealloc(void** p, uint64_t size){
    void* new_ptr = realloc(*p, size);
    if(new_ptr || !size){
        *p = new_ptr;
        return true;
    } else return false;
}

#define listReserveCapacity(l, new_capacity, value_t) ( \
    (new_capacity) > (l).capacity ? \
		( \
            (new_capacity) * sizeof(value_t) > (l).capacity * sizeof(value_t) ? ( \
				listRealloc((void**) &((l).data), (new_capacity) * sizeof(value_t)) ? \
					((l).capacity = (new_capacity), true) : \
					false \
			) : false \
		) : \
		true \
)

#define listResize(l, size, value_t) (  \
    listReserveCapacity((l), (size), value_t) ? ((l).size = (size), true) : false \
)

#define listPush(l, value_t, element) (     \
    (l).capacity > (l).size ? \
        ((getElement((l), (l).size++) = (element)), true) : ( \
            (l).capacity < MAX_SIZE / 2 ? ( \
                (listReserveCapacity((l), (((l).capacity) ? ((l).capacity * 2) : 1), value_t)) ? \
                    (getElement((l), (l).size++) = (element), true) : \
                    false                                      \
            ) : false \
        ) \
)

#define listFor(l, index) for(uint64_t index = 0; index < (l).size; index++)
#endif