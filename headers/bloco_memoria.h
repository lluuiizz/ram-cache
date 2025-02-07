#ifndef __BLOCO_MEMORIA_H
#define __BLOCO_MEMORIA_H

#define MAX_PALAVRAS 4
typedef struct {
    int palavras[MAX_PALAVRAS];
    int end_bloco;
    int modified;
    int custo;
    int cache_hit;
    int timestamp;
} bloco_memoria;

typedef enum {
    L1,
    L2,
    L3,
    RAM_MEMORY,
    MISS

} memory_selector;
#endif