#ifndef __CACHE_H
#define __CACHE_H


#include "bloco_memoria.h"
#include "ram.h"

#define L1_MAX 10
#define L2_MAX 30
#define L3_MAX 60


typedef struct {
    bloco_memoria cache_l1[L1_MAX]; int indices_used_cachel1[L1_MAX]; int cache_hit_l1; int cache_miss_l1;
    bloco_memoria cache_l2[L2_MAX]; int indices_used_cachel2[L2_MAX]; int cache_hit_l2; int cache_miss_l2;
    bloco_memoria cache_l3[L3_MAX]; int indices_used_cachel3[L3_MAX]; int cache_hit_l3; int cache_miss_l3;
    int custo;
} caches; 

void iniciar_cache(caches *cache);
void imprimir_cache(caches *cache, memory_selector memory);
void change_lru(caches *cache, memory_selector memory, int indice);
#endif
