#include "headers/endereco.h"
#include "headers/ram.h"
#include "headers/cache.h"
#include <stdio.h>

int procura_bloco_vazio (caches *cache, memory_selector cache_looking) {

    int i;
    switch (cache_looking) {
        case L1:    
            for (i = 0; cache->cache_l1[i].end_bloco != -1 && i < L1_MAX; ++i);
            return (i < L1_MAX) ? i : -1;
            break;
        case L2:
            for (i = 0; cache->cache_l2[i].end_bloco != -1 && i < L2_MAX; ++i);
            return (i < L2_MAX) ? i : -1;
            break;
        case L3:
            for (i = 0; cache->cache_l3[i].end_bloco != -1 && i < L3_MAX; ++i);
            return (i < L3_MAX) ? i : -1;
            break;
        default:
        break;

    }

}
bloco_memoria mover_caches (RAM *ram, caches *cache, int end_bloco, memory_selector begins) {
    if (begins == L1) {
        printf("Movendo para o registrador\n");
        return cache->cache_l1[end_bloco]; 
    }

    else if (begins == L2) {
        int bloco = procura_bloco_vazio(cache, L1);
        if (bloco != -1) {
            cache->cache_l1[bloco] = cache->cache_l2[end_bloco];
            cache->cache_l2[end_bloco].end_bloco = -1;
            printf("Movendo para L1\n");
            mover_caches(ram, cache, bloco, L1);
        }
    }
    else if (begins == L3) {
        int bloco = procura_bloco_vazio(cache, L2);
        if (bloco != -1) {
            cache->cache_l2[bloco] = cache->cache_l3[end_bloco];
            cache->cache_l3[end_bloco].end_bloco = -1;
            printf("Movendo para L2\n");
            mover_caches(ram, cache, bloco, L2);
        }
    }
    else if (begins == RAM_MEMORY) {
        int bloco = procura_bloco_vazio(cache,L2);
        if (bloco != -1) {
            cache->cache_l3[bloco] = ram->blocks[end_bloco];
            printf("Movendo para L3\n");
            mover_caches(ram, cache, bloco, L3);
        }
    }
}

int procura_nas_memorias(RAM *ram, caches *cache, endereco e, memory_selector choice) {
    switch(choice)
    {
    case  L1:
        for (int i = 0; i < L1_MAX; ++i) {
            if (cache->cache_l1[i].end_bloco == e.endbloco){
                cache->cache_l1[i].cache_hit += 1;
                cache->cache_l1[i].custo += 10;
                return i;
            }
        }
        break;
    case  L2:
        for (int i = 0; i < L2_MAX; ++i) {
            if (cache->cache_l1[i].end_bloco == e.endbloco){
                cache->cache_l2[i].custo += 110;
                cache->cache_l2[i].cache_hit += 1;
                return i;
            }
        }
        break;
    case L3:
        for (int i = 0; i < L3_MAX; ++i) {
            if (cache->cache_l3[i].end_bloco == e.endbloco){
                cache->cache_l3[i].custo += 1100;
                cache->cache_l3[i].cache_hit += 1;
                return i;
            }
        }
        break; 
    case RAM_MEMORY:
        for (int i = 0; i < ram->size; ++i) {
            if (ram->blocks[i].end_bloco == e.endbloco) {
                return i;
            }
        }
        break;
    default:
        break;
    }
    return -1;
}
bloco_memoria pegar_das_memorias (RAM *ram, endereco e, caches *cache) {
    int end_memoria = procura_nas_memorias(ram, cache, e, L1);
    memory_selector memory_hited = (end_memoria != -1) ? L1 : MISS;

    if (end_memoria == -1){
        end_memoria = procura_nas_memorias(ram, cache, e, L2);
        memory_hited = L2;
    }
    if (end_memoria == -1){
        end_memoria = procura_nas_memorias(ram, cache, e, L3);
        memory_hited = L3;
    }
    if (end_memoria == -1) {
        end_memoria = procura_nas_memorias(ram, cache, e, RAM_MEMORY);
        printf("Achou na ram!!! no bloco %d\n", end_memoria);
        memory_hited = RAM_MEMORY;
    }



    switch (memory_hited) {
        case L1:
        printf("Estou em l1!\n");
            return cache->cache_l1[end_memoria];
            break;
        case L2:
        printf("Estou em l2!\n");
            return mover_caches(ram, cache, end_memoria, L2);
            break;
        case L3:
        printf("Estou rm l3!\n");
            return mover_caches(ram, cache, end_memoria, L3);
            break;
        case RAM_MEMORY:   
        printf("Estou rm ram!\n");
        return mover_caches(ram, cache, end_memoria, RAM_MEMORY );
        break;
        default:
        break;

    }


}