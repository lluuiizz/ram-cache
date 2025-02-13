#include "headers/endereco.h"
#include "headers/ram.h"
#include "headers/cache.h"
#include <stdio.h>

int procura_bloco_vazio (caches *cache, memory_selector cache_looking) {

    int i;
    switch (cache_looking) {
        case L1:    
            for (i = 0; cache->cache_l1[i].end_bloco != -1 && i < L1_MAX; i++);
            return (i < L1_MAX) ? i : -1;
            break;
        case L2:
            for (i = 0; cache->cache_l2[i].end_bloco != -1 && i < L2_MAX;i++);
            return (i < L2_MAX) ? i : -1;
            break;
        case L3:
            for (i = 0; cache->cache_l3[i].end_bloco != -1 && i < L3_MAX; i++);
            return (i < L3_MAX) ? i : -1;
            break;
        default:
        break;

    }

}
bloco_memoria mover_memorias (RAM *ram, caches *cache, int end_bloco, memory_selector begins) {
    if (begins == L1) {
        int conjunto_em_l1 = (end_bloco % CONJUNTOS(L1_MAX)) * BLOCOS_POR_CONJUNTO;
        int bloco_no_conjunto = (cache->cache_l1[conjunto_em_l1].mais_recente == 1)
            ? 0
            : 1;

        return cache->cache_l1[conjunto_em_l1+bloco_no_conjunto];
    }

    else if (begins == L2) {
        int conjunto_em_l2 = (end_bloco != 0) ? ((CONJUNTOS(L2_MAX)) % end_bloco )* BLOCOS_POR_CONJUNTO : 0;
        int bloco_no_conjunto = (cache->cache_l2[conjunto_em_l2].mais_recente == 1)
            ? 0
            : 1;
        int conjunto_em_l1 = (end_bloco != 0 ) ? (CONJUNTOS(L1_MAX) % end_bloco) * BLOCOS_POR_CONJUNTO : 0;
       
        if (cache->cache_l1[conjunto_em_l1].end_bloco == -1 && cache->cache_l1[conjunto_em_l1+1].end_bloco == -1) {
            bloco_memoria tmp = cache->cache_l1[conjunto_em_l1];
            printf("Conjunto Vazio\n");
            cache->cache_l1[conjunto_em_l1] = cache->cache_l2[conjunto_em_l2+bloco_no_conjunto] ;
            cache->cache_l1[conjunto_em_l1].mais_recente = 1;
            cache->cache_l1[conjunto_em_l1+1].mais_recente = 0;
            cache->cache_l2[conjunto_em_l2+bloco_no_conjunto] = tmp;
        }
        else if (cache->cache_l1[conjunto_em_l1].mais_recente == 0) {
            bloco_memoria tmp = cache->cache_l1[conjunto_em_l1];
            cache->cache_l1[conjunto_em_l1] = cache->cache_l2[conjunto_em_l2+bloco_no_conjunto];
            cache->cache_l1[conjunto_em_l1].mais_recente = 1;
            cache->cache_l1[conjunto_em_l1+1].mais_recente = 0;
            cache->cache_l2[conjunto_em_l2+bloco_no_conjunto] = tmp;
        }
        else {
            bloco_memoria tmp = cache->cache_l1[conjunto_em_l1+1];
            cache->cache_l1[conjunto_em_l1+1] = cache->cache_l2[conjunto_em_l2+bloco_no_conjunto];
            cache->cache_l1[conjunto_em_l1+1].mais_recente = 1;
            cache->cache_l1[conjunto_em_l1].mais_recente = 0;
            cache->cache_l2[conjunto_em_l2+bloco_no_conjunto] = tmp;
        }

        mover_memorias(ram, cache, end_bloco, L1);
 
    }
    else if (begins == L3) {
        int conjunto_em_l3 = (end_bloco != 0) ? (CONJUNTOS(L3_MAX) % end_bloco) * BLOCOS_POR_CONJUNTO : 0;
        int bloco_no_conjunto = (cache->cache_l3[conjunto_em_l3].mais_recente == 1)
            ? 0
            : 1;
        int conjunto_em_l2 = (end_bloco != 0) ? (CONJUNTOS(L2_MAX) % end_bloco) * BLOCOS_POR_CONJUNTO : 0;
       
        if (cache->cache_l2[conjunto_em_l2].end_bloco == -1 && cache->cache_l2[conjunto_em_l2+1].end_bloco == -1) {
            cache->cache_l2[conjunto_em_l2] = cache->cache_l3[conjunto_em_l3+bloco_no_conjunto] ;
            cache->cache_l2[conjunto_em_l2].mais_recente = 1;
            cache->cache_l2[conjunto_em_l2+1].mais_recente = 0;
            cache->cache_l3[conjunto_em_l3+bloco_no_conjunto].end_bloco = -1;
        }
        else if (cache->cache_l2[conjunto_em_l2].mais_recente == 0) {
            cache->cache_l2[conjunto_em_l2] = cache->cache_l3[conjunto_em_l3+bloco_no_conjunto];
            cache->cache_l2[conjunto_em_l2].mais_recente = 1;
            cache->cache_l2[conjunto_em_l2+1].mais_recente = 0;
            cache->cache_l3[conjunto_em_l3+bloco_no_conjunto].end_bloco = -1;
        }
        else {
            cache->cache_l2[conjunto_em_l2+1] = cache->cache_l3[conjunto_em_l3+bloco_no_conjunto];
            cache->cache_l2[conjunto_em_l2+1].mais_recente = 1;
            cache->cache_l2[conjunto_em_l2].mais_recente = 0;
            cache->cache_l3[conjunto_em_l3+bloco_no_conjunto].end_bloco = -1;
        }

        mover_memorias(ram, cache, end_bloco, L2);
        /*
        int bloco = procura_bloco_vazio(cache, L2);

        if (bloco != -1) {
            cache->cache_l2[bloco] = cache->cache_l3[end_bloco];
            cache->cache_l3[end_bloco].end_bloco = -1;
            printf("Movendo para L2\n");
            mover_memorias(ram, cache, bloco, L2);
        }else {
            bloco_memoria tmp = cache->cache_l2[cache->indices_used_cachel2[0]];
            cache->cache_l2[cache->indices_used_cachel2[0]] = cache->cache_l3[end_bloco];
            cache->cache_l3[end_bloco] = tmp;
            change_lru(cache, L2, cache->indices_used_cachel2[0]);
            change_lru(cache, L3, end_bloco);
        }*/
    }
    else if (begins == RAM_MEMORY) {
        int conjunto_em_l3 = (end_bloco != 0) ? (CONJUNTOS(L3_MAX) % end_bloco) * BLOCOS_POR_CONJUNTO : 0;
        int i;

        if (cache->cache_l3[conjunto_em_l3].end_bloco == -1 && cache->cache_l3[conjunto_em_l3+1].end_bloco == -1) {
            cache->cache_l3[conjunto_em_l3] = ram->blocks[end_bloco];
            cache->cache_l3[conjunto_em_l3].mais_recente = 1;
            cache->cache_l3[conjunto_em_l3+1].mais_recente = 0;
        }

        else if (cache->cache_l3[conjunto_em_l3].mais_recente == 0) {
            cache->cache_l3[conjunto_em_l3] = ram->blocks[end_bloco];
            cache->cache_l3[conjunto_em_l3].mais_recente = 1;
            cache->cache_l3[conjunto_em_l3+1].mais_recente = 0;
        }
        else {
            cache->cache_l3[conjunto_em_l3+1] = ram->blocks[end_bloco];
            cache->cache_l3[conjunto_em_l3+1].mais_recente = 1;
            cache->cache_l3[conjunto_em_l3].mais_recente = 0;
        }

        mover_memorias(ram, cache, end_bloco, L3);
        /*int bloco = procura_bloco_vazio(cache,L3);
        if (bloco != -1) {
            cache->cache_l3[bloco] = ram->blocks[end_bloco];
            printf("Movendo para L3\n");
            mover_memorias(ram, cache, bloco, L3);
        }
        else {
            bloco_memoria tmp = cache->cache_l3[cache->indices_used_cachel3[0]];
            cache->cache_l3[cache->indices_used_cachel3[0]] = ram->blocks[end_bloco];
            if (tmp.mais_recente == 1)
                ram->blocks[end_bloco] = tmp;
            change_lru(cache, L3, cache->indices_used_cachel3[0]);
        }*/
    }

}

int procura_nas_memorias(RAM *ram, caches *cache, endereco e, memory_selector choice) {
    switch(choice)
    {
    case  L1:
        int bloco_em_l1 = (e.endbloco % CONJUNTOS(L1_MAX)) * BLOCOS_POR_CONJUNTO;
        if (cache->cache_l1[bloco_em_l1].end_bloco == e.endbloco) {
            cache->cache_hit_l1++;
            cache->custo += 10;
            return bloco_em_l1;
        }
        else if (cache->cache_l1[bloco_em_l1+1].end_bloco == e.endbloco){
            cache->cache_hit_l1++;
            cache->custo += 10;
            return bloco_em_l1+1;
        }
        break;
    case  L2:
        int bloco_em_l2 = (e.endbloco % CONJUNTOS(L2_MAX)) * BLOCOS_POR_CONJUNTO;
        if (cache->cache_l2[bloco_em_l2].end_bloco == e.endbloco) {
            cache->cache_hit_l2++;
            cache->custo += 110;
            return bloco_em_l2;
        }
        else if (cache->cache_l2[bloco_em_l2+1].end_bloco == e.endbloco) {
            cache->cache_hit_l2++;
            cache->custo += 110;
            return bloco_em_l2+1;
        }
        break;
    case L3:
        int conjunto_em_l3 = (e.endbloco % CONJUNTOS(L3_MAX)) * BLOCOS_POR_CONJUNTO;
        if (cache->cache_l3[conjunto_em_l3].end_bloco == e.endbloco) {
            cache->cache_hit_l3++;
            cache->custo += 1110;
            return conjunto_em_l3;
        }
        else if (cache->cache_l3[conjunto_em_l3+1].end_bloco == e.endbloco) {
            cache->cache_hit_l3++;
            cache->custo += 1110;
            return conjunto_em_l3+1;
        }

        break; 
    case RAM_MEMORY:
        for (int i = 0; i < ram->size; i++) {
            if (ram->blocks[i].end_bloco == e.endbloco) {
                cache->custo += 11110;
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
            return mover_memorias(ram, cache, end_memoria, L1);
            break;
        case L2:
        printf("Estou em l2!\n");
            return mover_memorias(ram, cache, end_memoria, L2);
            break;
        case L3:
        printf("Estou rm l3!\n");
            return mover_memorias(ram, cache, end_memoria, L3);
            break;
        case RAM_MEMORY:   
        printf("Estou rm ram!\n");
        return mover_memorias(ram, cache, end_memoria, RAM_MEMORY );
        break;
        default:
        break;

    }

}