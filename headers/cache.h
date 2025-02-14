#ifndef __CACHE_H
#define __CACHE_H


#include "bloco_memoria.h"

#define L1_MAX 10
#define L2_MAX 100
#define L3_MAX 1000

#define BLOCOS_POR_CONJUNTO 2
#define CONJUNTOS(CACHE) (CACHE/BLOCOS_POR_CONJUNTO)

#define TRUE  1
#define FALSE 0


typedef struct {
    bloco_memoria cache_l1[L1_MAX];  int cache_hit_l1;
    bloco_memoria cache_l2[L2_MAX];  int cache_hit_l2;
    bloco_memoria cache_l3[L3_MAX];  int cache_hit_l3;
    int custo;
} caches; 

void iniciar_cache(caches *cache);
void imprimir_cache(caches *cache, memory_selector memory);
#endif
