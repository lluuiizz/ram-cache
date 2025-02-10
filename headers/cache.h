#ifndef __CACHE_H
#define __CACHE_H


#include "bloco_memoria.h"

#define L1_MAX 10
#define L2_MAX 100
#define L3_MAX 1000


typedef struct {
    bloco_memoria cache_l1[L1_MAX]; int indices_used_cachel1[L1_MAX];
    bloco_memoria cache_l2[L2_MAX]; int indices_used_cachel2[L2_MAX];
    bloco_memoria cache_l3[L3_MAX]; int indices_used_cachel3[L3_MAX];
    int custo;
} caches; 

void iniciar_cache(caches *cache);
void imprimir_cache(caches *cache, memory_selector memory);
void change_lru(caches *cache, memory_selector memory, int indice);
int pega_lru (caches *cache, memory_selector memory);
#endif