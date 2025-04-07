#ifndef __MMU_C
#define __MMU_C

#include "bloco_memoria.h"
#include "ram.h"
#include "cache.h"
#include "endereco.h"

int procura_bloco_vazio (caches *cache,RAM *ram, memory_selector cache_looking);
bloco_memoria *mover_caches (RAM *ram, caches *cache, int end_bloco, memory_selector begins);
bloco_memoria* mover_memorias (RAM *ram, caches *cache, int end_bloco, memory_selector begins);
int procura_nas_memorias(RAM *ram, caches *cache, endereco e, memory_selector choice);
bloco_memoria *pegar_das_memorias (RAM *ram, endereco e, caches *cache);
#endif
