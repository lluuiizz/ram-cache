#include "headers/cache.h"

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