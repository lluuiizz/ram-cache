#include "headers/endereco.h"
#include "headers/ram.h"
#include "headers/cache.h"
#include <stdio.h>



int pegar_conjunto(int endereco, memory_selector cache_escolhida) {
	if (cache_escolhida == L1)
		return (endereco % CONJUNTOS(L1_MAX)) * BLOCOS_POR_CONJUNTO;
	else if (cache_escolhida == L2)
		return (endereco % CONJUNTOS(L2_MAX)) * BLOCOS_POR_CONJUNTO;
	else // Cache L3
		return (endereco % CONJUNTOS(L3_MAX)) * BLOCOS_POR_CONJUNTO;

	return -1;
}

void atualizar_controles_do_conjunto(caches *cache, endereco e, int end_bloco, memory_selector cache_escolhida) {
	int menos_recente;
	int conjunto_na_cache;

	if (cache_escolhida == L1) {
		conjunto_na_cache = pegar_conjunto(e.endbloco, L1);
		menos_recente = (end_bloco - conjunto_na_cache) == 0 ? 1 : 0;
		menos_recente += conjunto_na_cache;
		cache->cache_l1[end_bloco].mais_recente = 1;
		cache->cache_l1[menos_recente].mais_recente = 0;
	}
	else if (cache_escolhida == L2) {
		conjunto_na_cache = pegar_conjunto(e.endbloco, L2);
		menos_recente = (end_bloco - conjunto_na_cache) == 0 ? 1 : 0;
		menos_recente += conjunto_na_cache;
		cache->cache_l2[end_bloco].mais_recente = 1;
		cache->cache_l2[menos_recente].mais_recente = 0;
		printf("Informações gerais de atualização:\n");
		printf("O Conjunto para o endereço %d na cache L2 é -- %d\n", e.endbloco, conjunto_na_cache/BLOCOS_POR_CONJUNTO);
		printf("O bloco %d tem o valor de mais recente setado para -- %d\n", end_bloco, cache->cache_l2[end_bloco].mais_recente );
		printf("O valor de ja usado do bloco acima foi setado para %d\n", cache->cache_l2[end_bloco].ja_usado );
		printf("O bloco menos usado é %d\n", menos_recente);
	}
	else if (cache_escolhida == L3) {
		conjunto_na_cache = pegar_conjunto(e.endbloco, L3);
		menos_recente = (end_bloco - conjunto_na_cache) == 0 ? 1 : 0;
		menos_recente += conjunto_na_cache;
		cache->cache_l3[end_bloco].mais_recente = 1;
		cache->cache_l3[menos_recente].mais_recente = 0;
		printf("Informações gerais de atualização:\n");
		printf("O Conjunto para o endereço %d na cache L3 é -- %d\n", e.endbloco, conjunto_na_cache/BLOCOS_POR_CONJUNTO);
		printf("O bloco %d tem o valor de mais recente setado para -- %d\n", end_bloco, cache->cache_l3[end_bloco].mais_recente );
		printf("O valor de ja usado do bloco acima foi setado para %d\n", cache->cache_l3[end_bloco].ja_usado );
		printf("O bloco menos usado é %d\n", menos_recente);
	}
	else { // RAM_MEMORY
		cache->custo += 10110;
	}
}

int limpar_conjuntos(RAM *ram, caches *cache, endereco e, memory_selector begins) {
	int conjunto_em_l1, conjunto_em_l2, conjunto_em_l3;
	switch (begins) {
		int bloco_mais_antigo;
		case L1:
			conjunto_em_l1 = pegar_conjunto(e.endbloco, L1);
			bloco_mais_antigo = (cache->cache_l1[conjunto_em_l1].mais_recente == FALSE ? 0 : 1);
			bloco_mais_antigo += conjunto_em_l1;
			
			conjunto_em_l2 = pegar_conjunto(e.endbloco, L2);

			if (cache->cache_l2[conjunto_em_l2].end_bloco == -1){
				cache->cache_l2[conjunto_em_l2] = cache->cache_l1[bloco_mais_antigo];
				cache->cache_l1[bloco_mais_antigo].end_bloco = -1;
				atualizar_controles_do_conjunto(cache, e, conjunto_em_l2, L2);
				return bloco_mais_antigo;
			}
			else if (cache->cache_l2[conjunto_em_l2+1].end_bloco == -1){
				cache->cache_l2[conjunto_em_l2+1] = cache->cache_l1[bloco_mais_antigo];
				cache->cache_l1[bloco_mais_antigo].end_bloco = -1;
				atualizar_controles_do_conjunto(cache, e, conjunto_em_l2+1, L2);
				return bloco_mais_antigo;
			}
			else {
				int mais_antigo_l2 = (cache->cache_l2[conjunto_em_l2].mais_recente == FALSE ? 0 : 1);
				mais_antigo_l2 += conjunto_em_l2;

				endereco tmp; tmp.endbloco = cache->cache_l2[mais_antigo_l2].end_bloco;

				limpar_conjuntos(ram, cache, tmp, L2);

				if (cache->cache_l2[conjunto_em_l2].end_bloco == -1){
					cache->cache_l2[conjunto_em_l2] = cache->cache_l1[bloco_mais_antigo];
					cache->cache_l1[bloco_mais_antigo].end_bloco = -1;
				}
				else if (cache->cache_l2[conjunto_em_l2+1].end_bloco == -1){
					cache->cache_l2[conjunto_em_l2+1] = cache->cache_l1[bloco_mais_antigo];
					cache->cache_l1[bloco_mais_antigo].end_bloco = -1;
				}
				return bloco_mais_antigo;
			}
				
			break;
		case L2:
			conjunto_em_l2 = pegar_conjunto(e.endbloco, L2);
			bloco_mais_antigo = (cache->cache_l2[conjunto_em_l2].mais_recente == FALSE ? 0 : 1);
			bloco_mais_antigo += conjunto_em_l2;
			
			conjunto_em_l3 = pegar_conjunto(e.endbloco, L3);

			if (cache->cache_l3[conjunto_em_l3].end_bloco == -1){
				cache->cache_l3[conjunto_em_l3] = cache->cache_l2[bloco_mais_antigo];
				cache->cache_l2[bloco_mais_antigo].end_bloco = -1;
				atualizar_controles_do_conjunto(cache, e, conjunto_em_l3, L3);
				return bloco_mais_antigo;
			}
			else if (cache->cache_l3[conjunto_em_l3+1].end_bloco == -1){
				cache->cache_l3[conjunto_em_l3+1] = cache->cache_l2[bloco_mais_antigo];
				cache->cache_l2[bloco_mais_antigo].end_bloco = -1;
				atualizar_controles_do_conjunto(cache, e, conjunto_em_l3+1, L3);
				return bloco_mais_antigo;
			}
			else {
				int mais_antigo_l3 = (cache->cache_l2[conjunto_em_l3].mais_recente == FALSE ? 0 : 1);
				mais_antigo_l3 += conjunto_em_l3;

				endereco tmp; tmp.endbloco = cache->cache_l2[mais_antigo_l3].end_bloco;

				limpar_conjuntos(ram, cache, tmp, L3);

				if (cache->cache_l3[conjunto_em_l3].end_bloco == -1){
					cache->cache_l3[conjunto_em_l3] = cache->cache_l2[bloco_mais_antigo];
					cache->cache_l2[bloco_mais_antigo].end_bloco = -1;
				}
				else if (cache->cache_l3[conjunto_em_l3+1].end_bloco == -1){
					cache->cache_l3[conjunto_em_l3+1] = cache->cache_l2[bloco_mais_antigo];
					cache->cache_l2[bloco_mais_antigo].end_bloco = -1;
				}
				return bloco_mais_antigo;
			}		
			break;
		case L3:
			conjunto_em_l3 = pegar_conjunto(e.endbloco, L3);
			bloco_mais_antigo = (cache->cache_l3[conjunto_em_l3].mais_recente == FALSE ? 0 : 1);
			bloco_mais_antigo += conjunto_em_l3;

			if (cache->cache_l3[bloco_mais_antigo].ja_usado == 1){
			
				int endereco = cache->cache_l3[bloco_mais_antigo].end_bloco;
				ram->blocks[endereco] = cache->cache_l3[bloco_mais_antigo];
				ram->blocks[endereco].ja_usado = 0;
			}
			cache->cache_l3[bloco_mais_antigo].end_bloco = -1;
			return bloco_mais_antigo;
			
			break;
		default:
			break;


	}


}

bloco_memoria* mover_memorias (RAM *ram, caches *cache, endereco e, memory_selector begins) {
	int conjunto_em_l1, conjunto_em_l2, conjunto_em_l3;
	int i;
	switch(begins) {
		case L1:
			break;
		case L2:
			break;
		case L3:
			conjunto_em_l3 = pegar_conjunto(e.endbloco, L3);
			conjunto_em_l2 = pegar_conjunto(e.endbloco, L2);

			int bloco_mais_recente = (cache->cache_l3[conjunto_em_l3].mais_recente == 1) ? 0: 1;
			bloco_mais_recente += conjunto_em_l3;

			for (i = conjunto_em_l2; i < (conjunto_em_l2+BLOCOS_POR_CONJUNTO); ++i) 
				if (cache->cache_l2[i].end_bloco == -1) break;

			printf("BLOCO MAIS RECENTE: %d\n\n\n", bloco_mais_recente);
			if (i < (conjunto_em_l2 + BLOCOS_POR_CONJUNTO)) {
				cache->cache_l2[i] = cache->cache_l3[bloco_mais_recente];
				cache->cache_l3[bloco_mais_recente].end_bloco = -1;
				printf("Estou enviando o bloco para L2!!1\n\n");
				atualizar_controles_do_conjunto(cache, e, i, L2);
			}
			else {
				printf("Estou aqui dentro pois L2 Está cheio!!!\n\n\n");
				if (cache->cache_l2[conjunto_em_l2].mais_recente == FALSE) {
					bloco_memoria tmp = cache->cache_l2[conjunto_em_l2];
					endereco tmp_end; tmp_end.endbloco = cache->cache_l2[conjunto_em_l2].end_bloco;

					cache->cache_l2[conjunto_em_l2] = cache->cache_l3[bloco_mais_recente];
					atualizar_controles_do_conjunto(cache, e, conjunto_em_l2, L2);
					cache->cache_l3[bloco_mais_recente].end_bloco = -1;

					conjunto_em_l3 = pegar_conjunto(tmp_end.endbloco, L3);
					for (i = conjunto_em_l3; i < (conjunto_em_l3 + BLOCOS_POR_CONJUNTO); ++i) 
						if (cache->cache_l3[i].end_bloco == -1) break;

					if (i < (conjunto_em_l3 + BLOCOS_POR_CONJUNTO)){
						cache->cache_l3[i] = tmp;
						atualizar_controles_do_conjunto(cache, tmp_end, i, L3);

					}
					else {
						int bloco_vazio = limpar_conjuntos(ram, cache, tmp_end, L3);
						cache->cache_l3[bloco_vazio] = tmp;
						atualizar_controles_do_conjunto(cache, tmp_end, i, L3);

					}

				}

			}

			break;

		case RAM_MEMORY:
			conjunto_em_l3 = pegar_conjunto(e.endbloco, L3);

			for (i = conjunto_em_l3; i < (conjunto_em_l3+BLOCOS_POR_CONJUNTO); ++i)
				if (cache->cache_l3[i].end_bloco == -1) break;
			if (i < (conjunto_em_l3+BLOCOS_POR_CONJUNTO)) {
				cache->cache_l3[i] = ram->blocks[e.endbloco];
				atualizar_controles_do_conjunto(cache, e, i, L3);
			}
			else {
				if (cache->cache_l3[conjunto_em_l3].mais_recente == FALSE) {
					if (cache->cache_l3[conjunto_em_l3].ja_usado == TRUE){
						int endereco = cache->cache_l3[conjunto_em_l3].end_bloco;
						ram->blocks[endereco] = cache->cache_l3[conjunto_em_l3];
						ram->blocks[endereco].ja_usado = 0;
						printf("Entrou o bloco de endereco %d da RAM\n", e.endbloco);
						printf("No bloco de endereco %d da cache l3\n", conjunto_em_l3+1);
						printf("Com isso, o bloco acima que continhao endereco % da RAM\n", endereco);
						printf("Atualizou o seu valor!\n");
					} 
					cache->cache_l3[conjunto_em_l3] = ram->blocks[e.endbloco];
					atualizar_controles_do_conjunto(cache, e, conjunto_em_l3, L3);
				}
				else {
					if (cache->cache_l3[conjunto_em_l3+1].ja_usado == TRUE){
						int endereco = cache->cache_l3[conjunto_em_l3+1].end_bloco;
						ram->blocks[endereco] = cache->cache_l3[conjunto_em_l3+1];
						ram->blocks[endereco].ja_usado = 0;
						printf("Entrou o bloco de endereco %d da RAM\n", e.endbloco);
						printf("No bloco de endereco %d da cache l3\n", conjunto_em_l3+1);
						printf("Com isso, o bloco acima que continhao endereco % da RAM\n", endereco);
						printf("Atualizou o seu valor!\n");
					}
					cache->cache_l3[conjunto_em_l3+1] = ram->blocks[e.endbloco];
					atualizar_controles_do_conjunto(cache, e, conjunto_em_l3+1, L3);
				}

			}
			mover_memorias(ram, cache, e, L3);
			break;
		case MISS:
			break;
	}
}


int procura_nas_memorias(RAM *ram, caches *cache, endereco e, memory_selector choice) {
    switch(choice)
    {
    case  L1:
        int bloco_em_l1 = pegar_conjunto(e.endbloco, L1);
        if (cache->cache_l1[bloco_em_l1].end_bloco == e.endbloco) {
            return bloco_em_l1;
        }
        else if (cache->cache_l1[bloco_em_l1+1].end_bloco == e.endbloco){
            return bloco_em_l1+1;
        }
        break;
    case  L2:
        int bloco_em_l2 = pegar_conjunto(e.endbloco, L2);
        if (cache->cache_l2[bloco_em_l2].end_bloco == e.endbloco) {
            return bloco_em_l2;
        }
        else if (cache->cache_l2[bloco_em_l2+1].end_bloco == e.endbloco) {
            return bloco_em_l2+1;
        }
        break;
    case L3:
        int conjunto_em_l3 = pegar_conjunto(e.endbloco, L3);
        if (cache->cache_l3[conjunto_em_l3].end_bloco == e.endbloco) {
            return conjunto_em_l3;
        }
        else if (cache->cache_l3[conjunto_em_l3+1].end_bloco == e.endbloco) {
            return conjunto_em_l3+1;
        }
break; 
    case RAM_MEMORY:
        for (int i = 0; i < ram->size; i++) {
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
bloco_memoria* pegar_das_memorias (RAM *ram, endereco e, caches *cache) {
	memory_selector memorys_to_search [] = {L1, L2, L3, RAM_MEMORY, MISS};
    memory_selector memory_hited;

	int end_memoria;
	int i = 0; 
	do {
		end_memoria = procura_nas_memorias (ram, cache, e, memorys_to_search[i++]);
	} while (end_memoria == -1 && memorys_to_search[i] != MISS);

	memory_hited = memorys_to_search[i-1];



    switch (memory_hited) {
        case L1:
			cache->cache_hit_l1++;
			cache->cache_l1[end_memoria].ja_usado = 1;
			cache->custo += 10;
			atualizar_controles_do_conjunto(cache, e, end_memoria, L1);
            return mover_memorias(ram, cache, e, L1);
            break;

        case L2:
			cache->cache_hit_l2++;
			cache->cache_l2[end_memoria].ja_usado = 1;
			cache->custo += 110;
			atualizar_controles_do_conjunto(cache, e, end_memoria, L2);
            return mover_memorias(ram, cache, e, L2);
            break;

        case L3:
			cache->cache_hit_l3++;
			cache->cache_l3[end_memoria].ja_usado = 1;
			cache->custo += 1110;
			atualizar_controles_do_conjunto(cache, e, end_memoria, L3);
            return mover_memorias(ram, cache, e, L3);
            break;

        case RAM_MEMORY:   
			cache->custo += 11110;
			atualizar_controles_do_conjunto(cache, e, end_memoria, RAM_MEMORY);
			return mover_memorias(ram, cache, e, RAM_MEMORY );
			break;

        default:
			printf("O bloco pesquisado não pertence a memória!\n");
			break;

    }

}
