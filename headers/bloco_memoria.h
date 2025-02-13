#ifndef __BLOCO_MEMORIA_H
#define __BLOCO_MEMORIA_H

#define MAX_PALAVRAS 4
typedef struct {
    int palavras[MAX_PALAVRAS];
    int end_bloco;
    int mais_recente;
    int ja_usado;
} bloco_memoria;

typedef enum {
    L1,
    L2,
    L3,
    RAM_MEMORY,
    MISS

} memory_selector;
#endif