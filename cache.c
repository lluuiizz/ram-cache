#include "headers/cache.h"
#include <stdio.h>

void iniciar_cache(caches *cache) {
    for (int i = 0; i < L1_MAX; ++i) {
        cache->cache_l1[i].custo = 0;
        cache->cache_l1[i].modified = 0;
        cache->cache_l1[i].cache_hit = 0;
        cache->cache_l1[i].end_bloco = -1;
    }
    for (int i = 0; i < L2_MAX; ++i) {
        cache->cache_l2[i].custo = 0;
        cache->cache_l2[i].modified = 0;
        cache->cache_l2[i].cache_hit = 0;
        cache->cache_l2[i].end_bloco = -1;
    }
    for (int i = 0; i < L3_MAX; ++i) {
        cache->cache_l3[i].custo = 0;
        cache->cache_l3[i].modified = 0;
        cache->cache_l3[i].cache_hit = 0;
        cache->cache_l3[i].end_bloco = -1;
    }
}

void imprimir_cache(caches *cache, memory_selector memory){
    switch (memory) {
        case L1:
        for (int i = 0; i < L1_MAX; ++i) {
            printf("Bloco %d\n", i);
            printf("Endereco: %d\n", cache->cache_l1[i].end_bloco);
            printf("MODIFIED: %d\n", cache->cache_l1[i].modified);
            printf("CACHE HITS: %d\n", cache->cache_l1[i].cache_hit);
            printf("CUSTO: %d\n", cache->cache_l1[i].custo);
            printf("Palavras: %d - %d - %d - %d\n", cache->cache_l1[i].palavras[0], cache->cache_l1[i].palavras[1], cache->cache_l1[i].palavras[2], cache->cache_l1[i].palavras[3]);

        }
        break;
        case L2:
        for (int i = 0; i < L2_MAX; ++i) {
            printf("Bloco %d\n", i);
            printf("Endereco: %d\n", cache->cache_l2[i].end_bloco);
            printf("MODIFIED: %d\n", cache->cache_l2[i].modified);
            printf("CACHE HITS: %d\n", cache->cache_l2[i].cache_hit);
            printf("CUSTO: %d\n", cache->cache_l2[i].custo);
            printf("Palavras: %d - %d - %d - %d\n", cache->cache_l2[i].palavras[0], cache->cache_l2[i].palavras[1], cache->cache_l2[i].palavras[2], cache->cache_l2[i].palavras[3]);
        }
        break;
        case L3:
        for (int i = 0; i < L3_MAX; ++i) {
            printf("Bloco %d\n", i);
            printf("Endereco: %d\n", cache->cache_l3[i].end_bloco);
            printf("MODIFIED: %d\n", cache->cache_l3[i].modified);
            printf("CACHE HITS: %d\n", cache->cache_l3[i].cache_hit);
            printf("CUSTO: %d\n", cache->cache_l3[i].custo);
            printf("Palavras: %d - %d - %d - %d\n", cache->cache_l3[i].palavras[0], cache->cache_l3[i].palavras[1], cache->cache_l3[i].palavras[2], cache->cache_l3[i].palavras[3]);
        }
        break;

    }

}