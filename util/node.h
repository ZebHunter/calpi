#ifndef NODE
#define NODE

typedef enum {
    NAp,
    NSupercomb,
    NNum,
} node_type_e;

typedef struct{
    addr_t a1;
    addr_t a2;
} ap_t;


//TODO remove
typedef struct{} expr_t;
typedef struct{
    char* name;
    char** args;
    expr_t* body;
} supercomp_t;

typedef struct{
    node_type_e type;

    union {
        ap_t ap;
        supercomp_t supercomb;
        int32_t n;
    };

} node_t;

#endif