#ifndef __MMU_C
#define __MMU_C

#include "bloco_memoria.h"
#include "ram.h"
#include "cache.h"
#include "endereco.h"

int limpar_conjuntos(RAM *ram, caches *cache, endereco e, memory_selector begins) ;
int procura_nas_memorias(RAM *ram, caches *cache, endereco e, memory_selector choice);
int pegar_conjunto(int endereco, memory_selector cache_escolhida);

void atualizar_controles_do_conjunto(caches *cache, endereco e, int end_bloco, memory_selector cache_escolhida);

bloco_memoria* mover_memorias (RAM *ram, caches *cache, endereco e, memory_selector begins);
bloco_memoria* pegar_das_memorias (RAM *ram, endereco e, caches *cache);
#endif
