
#include "headers/ram.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


RAM * alocar_ram (int size){
	RAM *ram; ram = malloc (sizeof(RAM));
	ram->blocks = malloc(sizeof(bloco_memoria) * size);
	for (int i = 0; i < size; ++i){
		ram->blocks[i].modified  = 0;
	}
	ram->size = size;
	return ram;
}

RAM* realocar_ram (RAM* ram, int new_size){
	ram->size = new_size;
	ram->blocks= realloc(ram->blocks, new_size * sizeof(bloco_memoria));

	return ram;

}

RAM* liberar_ram(RAM *ram) {
	free(ram->blocks);
	free(ram);

	return NULL;

}
void ram_vazia (RAM *ram) {

	for (int i = 0; i < ram->size; i++){
		ram->blocks[i].end_bloco = i;
		for (int j = 0; j < MAX_PALAVRAS; ++j){
			ram->blocks[i].palavras[j] = 0;
		}
	}
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

