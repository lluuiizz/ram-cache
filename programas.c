#include "headers/cpu.h"
#include "headers/ram.h"
#include "headers/mmu.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void programaFibonacci  (RAM *ram, cpu *processor, int termos);
void programaProgressaoA(RAM *ram, cpu *processor, int primeiro, int razao, int n);
void programaLogN		(RAM *ram, cpu *processor, int base, int n);
void programaExpo	    (RAM *ram, cpu *processor, int base, int expoente);
void programaSumMatriz  (RAM *ram, cpu *processor, int cardinalidade);
void programaFat	    (RAM *ram, cpu *processor, int fat  );
void programaMult       (RAM *ram, cpu *processor, int multiplicando, int multiplicador);
void programaDiv        (RAM *ram, cpu *processor, int dividendo, int divisor);

int main(void) {
	RAM *ram; ram = alocar_ram(DEFAULT);
	cpu *processor; processor = malloc (sizeof(cpu));
	caches *cache; cache = malloc(sizeof(caches));

	iniciar_cache(cache);

	ram_aleatoria(ram);

	instrucao_str trecho1[2];

	instrucao_str inst0;
	inst0.opcode = SUBTRAI;
	inst0.addr1.endbloco = 1;   // BLOCO 1
	inst0.addr2.endbloco = 10; //  BLOCO 10
	inst0.addr3.endbloco = 15;  // BLOCO 15

	inst0.addr1.endpalavra = 1; // PALAVRA 1 BLOCO 1
	inst0.addr2.endpalavra = 0; // PALAVRA 0 BLOCO 10 
	inst0.addr3.endpalavra = 2; // PALAVRA 2 BLOCO 15

	trecho1[0] = inst0;

	instrucao_str inst1;
	inst1.opcode = HALT;

	trecho1[1] = inst1;

	iniciar(trecho1, processor, ram, cache);



	ram = liberar_ram(ram); free (processor); free(cache);
	
	return 0;
}
/*
void programaFibonacci(RAM *ram, cpu *processor, int termos) {
	if (DEFAULT < termos)
		ram = realocar_ram(ram, termos);

	instrucao_str **iniciaFib; iniciaFib = malloc (sizeof(instrucao_str) * 3);

	instrucao_str inst0;
	inst0.opcode = SALVA_nREG;
	inst0.addr1 = 1;
	inst0.addr2 = 1;
	
	iniciaFib[0] = &inst0;

	instrucao_str inst1;
	inst1.opcode = COPIA_pRAM;
	inst1.addr1 = 1;
	inst1.addr2 = 1;

	iniciaFib[1] = &inst1;

	instrucao_str inst2;
	inst2.opcode = HALT;
	
	iniciaFib[2] = &inst2;
	iniciar(*iniciaFib, processor, ram); free(iniciaFib);

	for (int i = 2; i < termos; ++i) {
		instrucao_str **somaFib; somaFib = malloc(sizeof(instrucao_str) * 2);

		instrucao_str inst3;
		inst3.opcode = SOMA;
		inst3.addr1 = i-2;
		inst3.addr2 = i-1;
		inst3.addr3 = i;

		somaFib[0] = &inst3;
		
		instrucao_str inst4;
		inst4.opcode = HALT;

		somaFib[1] = &inst4;
		iniciar (*somaFib, processor, ram);
	}

}

void programaProgressaoA(RAM *ram, cpu *processor, int primeiro, int razao, int n){
	if (DEFAULT < n) 
		ram = realocar_ram(ram, n);

	instrucao_str **trecho1; trecho1 = malloc(sizeof(instrucao_str) * 4);

	instrucao_str inst0;
	inst0.opcode = SALVA_nREG;
	inst0.addr1  = 1;
	inst0.addr2  = primeiro;

	trecho1[0] = &inst0;

	instrucao_str inst1;
	inst1.opcode = COPIA_pRAM;
	inst1.addr1  = 1;
	inst1.addr2  = 0;

	trecho1[1] = &inst1;

	instrucao_str inst2;
	inst2.opcode = OBTEM_dREG;
	inst2.addr1  = 1;
	inst2.addr2  = -1;
	inst2.addr3  = -1;

	trecho1[2] = &inst2;

	instrucao_str inst3;
	inst3.opcode = HALT;

	trecho1[3] = &inst3;

	iniciar(*trecho1, processor, ram); free(trecho1);

	for (int i = 2, j = 1; i <= n; i++, j++) {
		instrucao_str **trecho2; trecho2 = malloc(sizeof(instrucao_str) * 3);
		instrucao_str inst4;
		inst4.opcode = SALVA_nREG;
		inst4.addr1  = 2;
		inst4.addr2  = inst2.addr2 + (i-1)*razao;

		trecho2[0] = &inst4;

		instrucao_str inst5;
		inst5.opcode = COPIA_pRAM;
		inst5.addr1  = 2;
		inst5.addr2  = j;

		trecho2[1] = &inst5;

		instrucao_str inst6;
		inst6.opcode = HALT;

		trecho2[2] = &inst6;

		iniciar(*trecho2, processor, ram); free(trecho2);
	}

}

void programaLogN		(RAM *ram, cpu *processor, int base, int n){
	instrucao_str **trecho1; trecho1 = malloc(sizeof(trecho1) * 5);

	instrucao_str inst0;
	inst0.opcode = SALVA_nREG;
	inst0.addr1  = 1;
	inst0.addr2  = n;

	trecho1[0] = &inst0;

	instrucao_str inst1;
	inst1.opcode = OBTEM_dREG;
	inst1.addr1  = 1;
	inst1.addr2  = -1;
	inst1.addr3  = -1;
	
	trecho1[1] = &inst1;

	instrucao_str inst2;
	inst2.opcode = SALVA_nREG;	
	inst2.addr1  = 2;
	inst2.addr2  = 1;

	trecho1[2] = &inst2;

	instrucao_str inst3;
	inst3.opcode = COPIA_pRAM;
	inst3.addr1  = 2;
	inst3.addr2  = 4;



	iniciar(*trecho1, processor, ram); free(trecho1);


	while (inst1.addr1 > base) {
		programaDiv(ram, processor, inst1.addr1, base);



	}

}
void programaExpo(RAM *ram, cpu *processor, int base, int expoente){
	int base_still = base;
	for (int i = 1; i < expoente; ++i){
		programaMult(ram, processor, base, base_still);

		instrucao_str **trecho1; trecho1 = malloc(sizeof(instrucao_str) * 3);

		instrucao_str inst0;
		inst0.opcode = COPIA_pREG;
		inst0.addr1  = 1;
		inst0.addr2  = 0;

		trecho1[0] = &inst0;

		instrucao_str inst1;
		inst1.opcode = OBTEM_dREG;
		inst1.addr1  = 1;
		inst1.addr2  = -1;
		inst1.addr3  = -1;

		trecho1[1] = &inst1;

		instrucao_str inst2;
		inst2.opcode = HALT;

		trecho1[2] = &inst2;

		iniciar(*trecho1, processor, ram); free(trecho1);

		base = inst1.addr2;
	}
}
void programaSumMatriz(RAM *ram, cpu *processor, int cardinalidade){
	int card_quadrado = cardinalidade*cardinalidade;
	int quantidade_elementos = 3 * card_quadrado;
	ram = realocar_ram(ram, quantidade_elementos);

	int matriz1[cardinalidade][cardinalidade];
	int matriz2[cardinalidade][cardinalidade];

	srand(time(NULL));

	for (int i = 0; i < cardinalidade; i++) {
		for (int j = 0; j < cardinalidade; j++) {
			matriz1[i][j] = rand() % 100;
			matriz2[i][j] = rand() % 100;
		}
	}
	
	ram_vazia(ram);

	int end_ram = 0;

	for (int i = 0; i < cardinalidade; ++i){
		for (int j = 0; j < cardinalidade; ++j) {
			instrucao_str **trecho1; trecho1 = malloc(sizeof(instrucao_str) * 3);

			instrucao_str inst0;
			inst0.opcode = SALVA_nREG;
			inst0.addr1  = 1;
			inst0.addr2  = matriz1[i][j];
			trecho1[0]   = &inst0;

			instrucao_str inst1;
			inst1.opcode = COPIA_pRAM;
			inst1.addr1  = 1;
			inst1.addr2  = end_ram;
			trecho1[1]   = &inst1;

			instrucao_str inst2;
			inst2.opcode = HALT;
			trecho1[2]   = &inst2;

			iniciar(*trecho1, processor, ram); free(trecho1);

			end_ram++;

		}
	}
	for (int i = 0; i < cardinalidade; ++i){
		for (int j = 0; j < cardinalidade; ++j) {
			instrucao_str **trecho2; trecho2 = malloc(sizeof(instrucao_str) * 3);

			instrucao_str inst0;
			inst0.opcode = SALVA_nREG;
			inst0.addr1  = 1;
			inst0.addr2  = matriz2[i][j];
			trecho2[0]   = &inst0;

			instrucao_str inst1;
			inst1.opcode = COPIA_pRAM;
			inst1.addr1  = 1;
			inst1.addr2  = end_ram;
			trecho2[1]   = &inst1;

			instrucao_str inst2;
			inst2.opcode = HALT;
			trecho2[2]   = &inst2;

			iniciar(*trecho2, processor, ram); free(trecho2);

			end_ram++;

		}
	}
	end_ram   = 0;
	int delta = card_quadrado;

	for (int i = 0; i < cardinalidade; ++i) {
		for (int j = 0; j < cardinalidade; ++j) {
			instrucao_str **trecho3; trecho3 = malloc(sizeof(instrucao_str) * 2);

			instrucao_str inst0;
			inst0.opcode = SOMA;
			inst0.addr1  = end_ram;
			inst0.addr2  = end_ram + delta;
			inst0.addr3  = end_ram + (2*delta);
			trecho3[0] = &inst0;

			instrucao_str inst1;
			inst1.opcode = HALT;
			trecho3[1] = &inst1;

			iniciar(*trecho3, processor, ram); free(trecho3);
			
			end_ram++;
		}


	}
}
void programaFat (RAM *ram, cpu *processor, int fat) {
	int j = 1;

	for (int i = 1; i <= fat; ++i) {
		programaMult(ram, processor, j, i);

		instrucao_str **trecho1; trecho1 = malloc(sizeof(instrucao_str) * 3);

		instrucao_str inst0;
		inst0.opcode = COPIA_pREG;
		inst0.addr1  = 1;
		inst0.addr2  = 0;
		inst0.addr3  = -1;

		trecho1[0] = &inst0;

		instrucao_str inst1;
		inst1.opcode = OBTEM_dREG;
		inst1.addr1  = 1;
		inst1.addr2  = -1;
		inst1.addr3  = -1;

		trecho1[1] = &inst1;

		instrucao_str inst2;
		inst2.opcode = HALT;

		trecho1[2] = &inst2;

		iniciar(*trecho1, processor, ram); free(trecho1);
		

		j = inst1.addr2;

	}

	instrucao_str **trecho2; trecho2 = malloc(sizeof(instrucao_str) * 3);
	
	instrucao_str inst3;
	inst3.opcode = COPIA_pREG;
	inst3.addr1  = 1;
	inst3.addr2  = 0;
	inst3.addr3  = -1;

	trecho2[0] = &inst3;

	instrucao_str inst4;
	inst4.opcode = OBTEM_dREG;
	inst4.addr1 = 1;
	inst4.addr2 = -1;
	inst4.addr3 = -1;

	trecho2[1] = &inst4;

	instrucao_str inst5;
	inst5.opcode = HALT;

	trecho2[2] = &inst5;

	iniciar(*trecho2, processor, ram); free(trecho2);

	printf("O valor do fatorial de %d eh: %d\n", fat, inst4.addr2);

}

void programaMult (RAM *ram, cpu *processor, int multiplicando, int multiplicador){

	ram_vazia(ram);

	instrucao_str trecho1[3];
	instrucao_str inst0;

	inst0.opcode = SALVA_nREG;
	inst0.addr1 = 1;
	inst0.addr2 = multiplicando;
	trecho1[0] = inst0;

	instrucao_str inst1;
	inst1.opcode = COPIA_pRAM;
	inst1.addr1 = 1;
	inst1.addr2 = 1;
	trecho1[1] = inst1;

	instrucao_str inst2;
	inst2.opcode = HALT;
	trecho1[2] = inst2;

	iniciar(trecho1, processor, ram);

	for (int i = 0; i < multiplicador; ++i){
		instrucao_str trecho2[2];

		instrucao_str inst3;
		inst3.opcode = SOMA;
		inst3.addr1 = 0;
		inst3.addr2 = 1;
		inst3.addr3 = 0;
		trecho2[0] = inst3;

		instrucao_str inst4;
		inst4.opcode = HALT;
		trecho2[1] = inst4;

		iniciar(trecho2, processor, ram);

	}

	instrucao_str **trecho3;
	trecho3 = malloc(sizeof(instrucao_str) * 3);
	instrucao_str inst5;
	inst5.opcode = COPIA_pREG;
	inst5.addr1 = 1;
	inst5.addr2 = 0;
	inst5.addr3 = -1;
	
	trecho3[0] = &inst5;

	instrucao_str inst6;
	inst6.opcode = OBTEM_dREG;
	inst6.addr1= 1;
	inst6.addr2 = -1;
	inst6.addr3 = -1;

	trecho3[1] = &inst6;

	instrucao_str inst7;
	inst7.opcode = HALT;
	trecho3[2] = &inst7;

	iniciar (*trecho3, processor, ram); free(trecho3);

	printf("O resultado da multiplicacao eh: %d\n", inst6.addr2);


}

void programaDiv  (RAM *ram, cpu *processor, int dividendo, int divisor){
	ram_vazia(ram);

	instrucao_str **trecho1;	
	trecho1 = malloc(sizeof(instrucao_str) * 5);

	instrucao_str inst0; // Carrega o divisor no reg 1
	inst0.opcode = SALVA_nREG;
	inst0.addr1 = 1;
	inst0.addr2 = dividendo;
	trecho1[0] = &inst0; 


	instrucao_str inst1; // Passa o valor do dividendo para RAM[0]
	inst1.opcode = COPIA_pRAM;
	inst1.addr1 = 1;
	inst1.addr2 = 0;
	trecho1[1] = &inst1;

	instrucao_str inst2; // Carrega o valor do divisor no reg 2
	inst2.opcode = SALVA_nREG;
	inst2.addr1 = 2;
	inst2.addr2 = divisor;
	trecho1[2] = &inst2;

	instrucao_str inst3; // Carrega o valor do divisor para RAM[1]
	inst3.opcode = COPIA_pRAM;
	inst3.addr1 = 2;
	inst3.addr2 = 1;
	trecho1[3] = &inst3;


	instrucao_str inst4; // HALT
	inst4.opcode = HALT;
	trecho1[4] = &inst4;


	iniciar(*trecho1, processor, ram); free (trecho1);
	
	instrucao_str **trecho2;
	trecho2 = malloc(sizeof(instrucao_str) * 3);

	instrucao_str inst5; // Carrega o valor 1 no reg1
	inst5.opcode = SALVA_nREG; 
	inst5.addr1 = 1;
	inst5.addr2 = 1;
	trecho2[0] = &inst5;

	instrucao_str inst6; // Carrega o valor 1 de reg1 em RAM[2]
	inst6.opcode = COPIA_pRAM;
	inst6.addr1 = 1;
	inst6.addr2 = 2;
	trecho2[1] = &inst6;

	instrucao_str inst7; // HALT
	inst7.opcode = HALT;
	trecho2[2] = &inst7;

	iniciar(*trecho2, processor, ram);	free(trecho2);

	while (dividendo >= divisor){
		instrucao_str **trecho3;
		trecho3 = malloc(sizeof(instrucao_str) * 5);

		instrucao_str inst8;
		inst8.opcode = SUBTRAI;
		inst8.addr1 = 0;
		inst8.addr2 = 1;
		inst8.addr3 = 0;
		trecho3[0] = &inst8;

		instrucao_str inst9;
		inst9.opcode = SOMA;
		inst9.addr1 = 2;
		inst9.addr2 = 3;
		inst9.addr3 = 3;
		trecho3[1] = &inst9;

		instrucao_str inst10;
		inst10.opcode = COPIA_pREG;
		inst10.addr1 = 1;
		inst10.addr2 = 0;
		inst10.addr3 = -1;
		trecho3[2] = &inst10;

		instrucao_str inst11;
		inst11.opcode = OBTEM_dREG;
		inst11.addr1 = 1;
		inst11.addr2 = -1;
		inst11.addr3 = -1;
		trecho3[3] = &inst11;

		instrucao_str inst12;
		inst12.opcode = HALT;
		trecho3[4] = &inst12;

		iniciar(*trecho3, processor, ram); free(trecho3);
		dividendo = inst11.addr2;
	}

	instrucao_str **trecho4;
	trecho4 = malloc(sizeof(instrucao_str) * 3);

	instrucao_str inst13;
	inst13.opcode = COPIA_pREG;
	inst13.addr1 = 1;
	inst13.addr2 = 3;
	inst13.addr3 = -1;
	trecho4[0] = &inst13;

	instrucao_str inst14;
	inst14.opcode = OBTEM_dREG;
	inst14.addr1 = 1;
	inst14.addr2 = -1;
	inst14.addr3 = -1;
	trecho4[1] = &inst14;

	instrucao_str inst15;
	inst15.opcode = HALT;
	trecho4[2] = &inst15;

	iniciar(*trecho4, processor, ram); free(trecho4);
	printf("O resultado da divisao eh: %d\n", inst14.addr2);

}

*/
