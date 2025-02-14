#ifndef __RAM_H
#define __RAM_H

#include "bloco_memoria.h"

#define DEFAULT 5031
typedef struct {
	bloco_memoria *blocks;
	int size;

} RAM;
RAM* alocar_ram (int size);
RAM* realocar_ram (RAM* ram, int new_size);
RAM* liberar_ram(RAM *ram);
void ram_vazia (RAM *ram);
void ram_aleatoria (RAM *ram);
void colocar_dado (RAM *ram, int addr, bloco_memoria conteudo);
bloco_memoria ler_dado (RAM *ram, int addr);
void imprimir (RAM *ram);



#endif
