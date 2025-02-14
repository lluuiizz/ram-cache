#include "headers/cache.h"
#include <stdio.h>

void iniciar_cache(caches *cache) {
    cache->custo = 0;
    cache->cache_hit_l1 = 0;
    cache->cache_hit_l2 = 0;
    cache->cache_hit_l3 = 0;
    for (int i = 0; i < L1_MAX; ++i) {
        cache->cache_l1[i].mais_recente = 0;
        cache->cache_l1[i].ja_usado = 0;
        cache->cache_l1[i].end_bloco = -1;
    }

    for (int i = 0; i < L2_MAX; ++i) {
        cache->cache_l2[i].mais_recente= 0;
        cache->cache_l2[i].ja_usado = 0;
        cache->cache_l2[i].end_bloco = -1;
    }
    for (int i = 0; i < L3_MAX; ++i) {
        cache->cache_l3[i].mais_recente= 0;
        cache->cache_l3[i].ja_usado= 0;
        cache->cache_l3[i].end_bloco = -1;
    }
}

void imprimir_cache(caches *cache, memory_selector memory){
    switch (memory) {
        case L1:
        for (int i = 0; i < L1_MAX; ++i) {
            printf("Bloco %d\n", i);
            printf("Endereco: %d\n", cache->cache_l1[i].end_bloco);
            printf("CACHE HITS: %d\n", cache->cache_hit_l1);
            printf("Palavras: %d - %d - %d - %d\n", cache->cache_l1[i].palavras[0], cache->cache_l1[i].palavras[1], cache->cache_l1[i].palavras[2], cache->cache_l1[i].palavras[3]);

        }
        break;
        case L2:
        for (int i = 0; i < L2_MAX; ++i) {
            printf("Bloco %d\n", i);
            printf("Endereco: %d\n", cache->cache_l2[i].end_bloco);
            printf("CACHE HITS: %d\n", cache->cache_hit_l2);
            printf("Palavras: %d - %d - %d - %d\n", cache->cache_l2[i].palavras[0], cache->cache_l2[i].palavras[1], cache->cache_l2[i].palavras[2], cache->cache_l2[i].palavras[3]);
        }
        break;
        case L3:
        for (int i = 0; i < L3_MAX; ++i) {
            printf("Bloco %d\n", i);
            printf("Endereco: %d\n", cache->cache_l3[i].end_bloco);
            printf("CACHE HITS: %d\n", cache->cache_hit_l3);
            printf("Palavras: %d - %d - %d - %d\n", cache->cache_l3[i].palavras[0], cache->cache_l3[i].palavras[1], cache->cache_l3[i].palavras[2], cache->cache_l3[i].palavras[3]);
        }
        break;

    }
    printf("Custo Total: %d\n", cache->custo);

}
