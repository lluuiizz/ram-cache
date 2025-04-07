#ifndef __RAM_H
#define __RAM_H

#include "bloco_memoria.h"

#define DEFAULT 1000
typedef struct {
	bloco_memoria *blocks;
	int *indices_used_ram;
	int size;
	int custo;

} RAM;
RAM* alocar_ram (int size);
RAM* realocar_ram (RAM* ram, int new_size);
void liberar_ram(RAM *ram);
void change_lru_ram(RAM *ram, int end_bloco);
void ram_vazia (RAM *ram);
void ram_aleatoria (RAM *ram);
void colocar_dado (RAM *ram, int addr, bloco_memoria conteudo);
bloco_memoria ler_dado (RAM *ram, int addr);
void imprimir (RAM *ram);



#endif
