#include "headers/endereco.h"
#include "headers/ram.h"
#include "headers/cache.h"
#include "headers/memoria_externa.h"
#include <stdio.h>

int procura_bloco_vazio (caches *cache, RAM *ram, memory_selector cache_looking) {

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
		case RAM_MEMORY:
            for (i = 0; ram->blocks[i].end_bloco != -1 && i < DEFAULT; i++);
            return (i < DEFAULT) ? i : -1;
            break;
			break;
        default:
        break;

    }
	return -1;

}
bloco_memoria* mover_memorias (RAM *ram, caches *cache, int end_bloco, memory_selector begins) {
    if (begins == L1) {
        change_lru(cache, L1, end_bloco);
        //printf("Movendo para o registrador\n");
        return &cache->cache_l1[end_bloco]; 

    }

    else if (begins == L2) {
        int bloco = procura_bloco_vazio(cache, ram,  L1);
        if (bloco != -1) {
            cache->cache_l1[bloco] = cache->cache_l2[end_bloco];
            cache->cache_l2[end_bloco].end_bloco = -1;
            //printf("Movendo para L1\n");
            mover_memorias(ram, cache, bloco, L1);
        }else {
            bloco_memoria tmp = cache->cache_l1[cache->indices_used_cachel1[0]];
			int tmp_indice = cache->indices_used_cachel1[0];
            cache->cache_l1[cache->indices_used_cachel1[0]] = cache->cache_l2[end_bloco];
            cache->cache_l2[end_bloco] = tmp;
            change_lru(cache, L1, cache->indices_used_cachel1[0]);
            change_lru(cache, L2, end_bloco);
			mover_memorias(ram, cache, tmp_indice, L1);
            //printf("Movendo bloco Endereco %d de L2 para o bloco de endereco %d de L1:", end_bloco, cache->indices_used_cachel1[0]);
            //printf("Resultado: %d\n", cache->cache_l1[cache->indices_used_cachel1[0]].palavras[0]);
        }
    }
    else if (begins == L3) {
        int bloco = procura_bloco_vazio(cache, ram,  L2);
        if (bloco != -1) {
            cache->cache_l2[bloco] = cache->cache_l3[end_bloco];
            cache->cache_l3[end_bloco].end_bloco = -1;
            //printf("Movendo para L2\n");
            mover_memorias(ram, cache, bloco, L2);
        }else {
            bloco_memoria tmp = cache->cache_l2[cache->indices_used_cachel2[0]];
			int tmp_indice = cache->indices_used_cachel2[0];
            cache->cache_l2[cache->indices_used_cachel2[0]] = cache->cache_l3[end_bloco];
            cache->cache_l3[end_bloco] = tmp;
            change_lru(cache, L2, cache->indices_used_cachel2[0]);
            change_lru(cache, L3, end_bloco);
			mover_memorias(ram, cache, tmp_indice, L2);
        }
    }
    else if (begins == RAM_MEMORY) {
        int bloco = procura_bloco_vazio(cache, ram, L3);
        if (bloco != -1) {
            cache->cache_l3[bloco] = ram->blocks[end_bloco];
            //printf("Movendo para L3\n");
            mover_memorias(ram, cache, bloco, L3);
        }
        else {
            bloco_memoria tmp = cache->cache_l3[cache->indices_used_cachel3[0]];
            cache->cache_l3[cache->indices_used_cachel3[0]] = ram->blocks[end_bloco];
            if (tmp.modified == 1)
                ram->blocks[end_bloco] = tmp;
			int tmp_indice = cache->indices_used_cachel3[0];
            change_lru(cache, L3, cache->indices_used_cachel3[0]);
			change_lru_ram(ram,  end_bloco);
			mover_memorias(ram, cache, tmp_indice, L3);
        }
    }
	else {
        int bloco = procura_bloco_vazio(cache, ram, RAM_MEMORY);
        if (bloco != -1) {
			ram->blocks[bloco] = obter_bloco(end_bloco);
			ram->blocks[bloco].end_bloco = end_bloco;
			ram->blocks[bloco].modified = 0;
            mover_memorias(ram, cache, bloco, RAM_MEMORY);
        }
        else {
            bloco_memoria tmp = ram->blocks[ram->indices_used_ram[0]];
			int tmp_indice = ram->indices_used_ram[0];
            ram->blocks[tmp_indice] = obter_bloco(end_bloco);
			ram->blocks[tmp_indice].end_bloco = end_bloco;
			ram->blocks[tmp_indice].modified = 0;
            if (tmp.modified == 1)
				modificar_bloco(tmp, tmp.end_bloco);
            change_lru_ram( ram, ram->indices_used_ram[0]);
			mover_memorias(ram, cache, tmp_indice, RAM_MEMORY);
        }

	}
    
}

int procura_nas_memorias(RAM *ram, caches *cache, endereco e, memory_selector choice) {
    switch(choice)
    {
    case  L1:
        for (int i = 0; i < L1_MAX; i++) {
            if (cache->cache_l1[i].end_bloco == e.endbloco){
                cache->cache_hit_l1 ++;
                cache->custo += 10;
                return i;
            }
        }
        break;
    case  L2:
        for (int i = 0; i < L2_MAX; i++) {
            if (cache->cache_l2[i].end_bloco == e.endbloco){
                cache->cache_hit_l2++;
				cache->cache_miss_l1++;
                cache->custo += 110;
                return i;
            }
        }
        break;
    case L3:
        for (int i = 0; i < L3_MAX; i++) {
            if (cache->cache_l3[i].end_bloco == e.endbloco){
				cache->cache_miss_l1++;
				cache->cache_miss_l2++;
                cache->cache_hit_l3++;
                cache->custo += 1110;
                return i;
            }
        }
        break; 
    case RAM_MEMORY:
        for (int i = 0; i < ram->size; i++) {
            if (ram->blocks[i].end_bloco == e.endbloco) {
				cache->cache_miss_l1++;
				cache->cache_miss_l2++;
				cache->cache_miss_l3++;
                cache->custo += 10110;
                return i;
            }
        }
        break;
    default:
        break;
    }
    return -1;
}
bloco_memoria* pegar_das_memorias (RAM *ram, endereco e, caches *cache) {
	memory_selector onde_procurar[] = {L1, L2, L3, RAM_MEMORY, EXTERNA, MISS};
    memory_selector memoria_encontrada;

	int end_memoria;
	int i = 0;

	do 
	{
		end_memoria = procura_nas_memorias(ram, cache, e, onde_procurar[i++]);

	}   while(end_memoria == -1 && onde_procurar[i] != MISS);

	memoria_encontrada = onde_procurar[i-1];


    switch (memoria_encontrada) {
        case L1:
            //printf("Estou em l1!\n");
            return mover_memorias(ram, cache, end_memoria, L1);
            break;
        case L2:
        //printf("Estou em l2!\n");
            return mover_memorias(ram, cache, end_memoria, L2);
            break;
        case L3:
        //printf("Estou rm l3!\n");
            return mover_memorias(ram, cache, end_memoria, L3);
            break;
        case RAM_MEMORY:   
        return mover_memorias(ram, cache, end_memoria, RAM_MEMORY );
        break;
        default:
			return mover_memorias(ram, cache, e.endbloco, MISS);
        break;

    }

}
