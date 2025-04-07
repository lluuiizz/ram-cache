
#include "headers/ram.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


RAM * alocar_ram (int size){
	RAM *ram; ram = (RAM*) malloc (sizeof(RAM));
	ram->indices_used_ram = (int*) malloc(sizeof(int) * size);
	ram->blocks = malloc(sizeof(bloco_memoria) * size);
	for (int i = 0; i < size; ++i){
		ram->blocks[i].modified  = 0;
		ram->indices_used_ram[i] = i;
	}


	ram->size = size;
	return ram;
}

RAM* realocar_ram (RAM* ram, int new_size){
	ram->size = new_size;
	ram->blocks= realloc(ram->blocks, new_size * sizeof(bloco_memoria));

	return ram;

}

void liberar_ram(RAM *ram) {
	free(ram->blocks);
	free(ram->indices_used_ram);
	free(ram);


}
void ram_vazia (RAM *ram) {

	for (int i = 0; i < ram->size; i++){
		ram->blocks[i].end_bloco = -1;
		for (int j = 0; j < MAX_PALAVRAS; ++j){
			ram->blocks[i].palavras[j] = 0;
		}
	}
}

void change_lru_ram(RAM *ram, int end_bloco){
	int i;
	for (i = 0; ram->indices_used_ram[i] != end_bloco; ++i);
	//printf("Achou i de LRU em %d\n\n", i);
	for (; i < (ram->size - 1); i++)
		ram->indices_used_ram[i] = ram->indices_used_ram[i+1];
	ram->indices_used_ram[ram->size-1] = end_bloco;
}

void ram_aleatoria (RAM *ram){

	srand(time(NULL));

	for (int i = 0; i < ram->size; ++i){
		ram->blocks[i].end_bloco = i;
		for (int j = 0; j < MAX_PALAVRAS; ++j){
				ram->blocks[i].palavras[j] = rand() % 101;
		}
	}
}
void colocar_dado (RAM *ram, int addr, bloco_memoria conteudo){
	ram->blocks[addr] = conteudo;
}
bloco_memoria ler_dado (RAM *ram, int addr){
	return ram->blocks[addr];
}
void imprimir (RAM *ram){
	for (int i = 0; i < ram->size; ++i) {
		for (int j = 0; j < MAX_PALAVRAS; ++j) {
			printf("%d  ", ram->blocks[i].palavras[j]);
		}
		printf("\n");
	}
}

