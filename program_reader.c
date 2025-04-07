#include "headers/cpu.h"
#include "headers/ram.h"
#include "headers/memoria_externa.h"
#include <stdlib.h>
#include <stdio.h>

void ler_programa(char *nome_arquivo, RAM *ram, cpu *processor, caches *cache){

	FILE *fp = fopen(nome_arquivo, "r");


	char line_buffer[100];

	instrucao_str instr;

	while (feof(fp) == 0) {
		fgets(line_buffer, 100, fp);
		sscanf(line_buffer, "%d:%d:%d:%d:%d:%d:%d", &instr.opcode, &instr.addr1.endbloco, &instr.addr1.endpalavra, &instr.addr2.endbloco, &instr.addr2.endpalavra, &instr.addr3.endbloco, &instr.addr3.endpalavra);

		instrucao_str halt;
		halt.opcode = HALT;

		instrucao_str trecho[2];
		trecho[0] = instr;
		trecho[1] = halt;

		iniciar(trecho, processor, ram, cache);

	}

	fclose(fp);

}
int main(void) {
	RAM *ram; ram = alocar_ram(DEFAULT);
	cpu *processor; processor = malloc (sizeof(cpu));
	caches *cache; cache = malloc(sizeof(caches));

	iniciar_cache(cache);
	ram_vazia(ram);

	if (!(ram != NULL && cache != NULL && processor != NULL)) {
		printf("Aconteceu algum erro na alocação!\n");
		return -1;

	}
	gerar_memoria_externa();

	
	ler_programa("instructions.txt", ram, processor, cache);


	liberar_ram(ram); free (processor); free(cache);
	
	return 0;
}

