#ifndef __CACHE_H
#define __CACHE_H


#include "bloco_memoria.h"

#define L1_MAX 10
#define L2_MAX 100
#define L3_MAX 1000


typedef struct {
    bloco_memoria cache_l1[L1_MAX];
    bloco_memoria cache_l2[L2_MAX];
    bloco_memoria cache_l3[L3_MAX];
} caches; 

void iniciar_cache(caches *cache);

#endif