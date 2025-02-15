#include "headers/cache.h"
#include <stdio.h>

void iniciar_cache(caches *cache) {
    cache->custo = 0;
    cache->cache_hit_l1 = 0; cache->cache_miss_l1 = 0;
    cache->cache_hit_l2 = 0; cache->cache_miss_l2 = 0;
    cache->cache_hit_l3 = 0; cache->cache_miss_l3 = 0;
    for (int i = 0; i < L1_MAX; ++i) {
        cache->cache_l1[i].modified = 0;
        cache->cache_l1[i].end_bloco = -1;
        cache->indices_used_cachel1[i]  = (L1_MAX-i-1);
    }

    for (int i = 0; i < L2_MAX; ++i) {
        cache->cache_l2[i].modified = 0;
        cache->cache_l2[i].end_bloco = -1;
        cache->indices_used_cachel2[i]  = (L2_MAX-i-1);
    }
    for (int i = 0; i < L3_MAX; ++i) {
        cache->cache_l3[i].modified = 0;
        cache->cache_l3[i].end_bloco = -1;
        cache->indices_used_cachel3[i]  = (L3_MAX-i-1);
    }
}

void change_lru(caches *cache, memory_selector memory, int indice) {
    printf("Estou em CHANGE LRU!!!");
    switch (memory) {
		int i;
        case L1:
            for (i = 0; cache->indices_used_cachel1[i] != indice; ++i);
            printf("Achou i de LRU em %d\n\n", i);
            for (; i < (L1_MAX - 1); i++)
                cache->indices_used_cachel1[i] = cache->indices_used_cachel1[i+1];
            cache->indices_used_cachel1[L1_MAX-1] = indice;
        break;

        case L2:
            for (i = 0; cache->indices_used_cachel2[i] != indice; ++i);
            for (; i < (L2_MAX - 1); i++)
                cache->indices_used_cachel2[i] = cache->indices_used_cachel2[i+1];
            cache->indices_used_cachel2[L2_MAX-1] = indice;
        break;

        case L3:
            for (i = 0; cache->indices_used_cachel3[i] != indice; ++i);
            for (; i < (L3_MAX - 1); i++)
                cache->indices_used_cachel3[i] = cache->indices_used_cachel3[i+1];
            cache->indices_used_cachel3[L3_MAX-1] = indice;
        break;
		default:
		break;

    }
}

void imprimir_cache(caches *cache, memory_selector memory){
    switch (memory) {
        case L1:
			printf("CACHE HITS:   %d\n", cache->cache_hit_l1);
			printf("CACHE MISSES: %d\n\n", cache->cache_miss_l1);
        for (int i = 0; i < L1_MAX; ++i) {
            printf("Bloco %d\n", i);
            printf("Endereco: %d\n", cache->cache_l1[i].end_bloco);
            printf("MODIFIED: %d\n", cache->cache_l1[i].modified);
            printf("Palavras: %d - %d - %d - %d\n", cache->cache_l1[i].palavras[0], cache->cache_l1[i].palavras[1], cache->cache_l1[i].palavras[2], cache->cache_l1[i].palavras[3]);

        }
        break;
        case L2:
        for (int i = 0; i < L2_MAX; ++i) {
            printf("Bloco %d\n", i);
            printf("Endereco: %d\n", cache->cache_l2[i].end_bloco);
            printf("MODIFIED: %d\n", cache->cache_l2[i].modified);
            printf("CACHE HITS: %d\n", cache->cache_hit_l2);
            printf("Palavras: %d - %d - %d - %d\n", cache->cache_l2[i].palavras[0], cache->cache_l2[i].palavras[1], cache->cache_l2[i].palavras[2], cache->cache_l2[i].palavras[3]);
        }
        break;
        case L3:
        for (int i = 0; i < L3_MAX; ++i) {
            printf("Bloco %d\n", i);
            printf("Endereco: %d\n", cache->cache_l3[i].end_bloco);
            printf("MODIFIED: %d\n", cache->cache_l3[i].modified);
            printf("CACHE HITS: %d\n", cache->cache_hit_l3);
            printf("Palavras: %d - %d - %d - %d\n", cache->cache_l3[i].palavras[0], cache->cache_l3[i].palavras[1], cache->cache_l3[i].palavras[2], cache->cache_l3[i].palavras[3]);
        }
        break;
		default:
		break;

    }
    printf("Custo Total: %d\n", cache->custo);

}
