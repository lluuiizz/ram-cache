#include "headers/cpu.h"
#include <stdlib.h>
#include <stdio.h>


void iniciar (instrucao_str *programa,cpu *processor, RAM *RAM) {
	
	processor->programa = programa;
	processor->PC = 0;
	processor->opcode = 0;


	caches cache;

	while (processor->opcode != -1){
		instrucao_str *inst;
		inst = malloc(sizeof(instrucao_str));
		inst = &processor->programa[processor->PC];
		processor->opcode = inst->opcode;

			

  /*
		switch (processor->opcode) {
			case HALT: // HALT
				printf("Programa terminou!!\n");
				imprimir(RAM);
				break;
			case SOMA: // SOMA
				processor->reg1 = ler_dado(RAM, inst->addr1 );
				processor->reg2 = ler_dado(RAM, inst->addr2 );
				processor->reg1 += processor->reg2;

				colocar_dado(RAM,inst->addr3, processor->reg1);

				printf("Inst sum - > RAM posição %d com conteudo %d\n", inst->addr3,processor->reg1) ;
				break;
			case SUBTRAI:  // SUBTRACAO
				processor->reg1 = ler_dado(RAM, inst->addr1 );
				processor->reg2 = ler_dado(RAM, inst->addr2 );
				processor->reg1 -= processor->reg2;

				colocar_dado(RAM,inst->addr3, processor->reg1);

				printf("Inst sub - > RAM posição %d com conteudo %d\n", inst->addr3,processor->reg1) ;
				break;
			case COPIA_pRAM: // Copia do reg1 para ram
				if (inst->addr1 == 1){
					colocar_dado(RAM, inst->addr2, processor->reg1);
					printf("Inst copy_reg_ram - > RAM posição %d com conteudo %d\n", inst->addr2, processor->reg1);


				} else if (inst->addr1 == 2){
					colocar_dado(RAM, inst->addr2, processor->reg2);
					printf("Inst copy_reg_ram - > RAM posição %d com conteudo %d\n", inst->addr2, processor->reg2);
				}

				break;
			case COPIA_pREG: // copia da ram para registrador 
				if (inst->addr1 == 1){
					processor->reg1 = ler_dado(RAM, inst->addr2);
					printf("Inst copy_ram_reg - > Registrador 1 com conteudo %d\n", processor->reg1);


				} else if (inst->addr1 == 2){
					processor->reg2 = ler_dado(RAM, inst->addr2);
					printf("Inst copy_ram_reg - > Registrador 2 com conteudo %d\n", processor->reg2);
				}

				break;
			case SALVA_nREG: // salva no registrador 
				if (inst->addr1 == 1){
					processor->reg1 = inst->addr2;
					printf("Inst save_reg - > Registrador 1 com conteudo %d\n", processor->reg1);


				} else if (inst->addr1 == 2){
					processor->reg2 = inst->addr2; 
					printf("Inst save_reg - > Registrador 2 com conteudo %d\n", processor->reg2);
				}

				break;
			case OBTEM_dREG: 
				if (inst->addr1 == 1){
					inst->addr2 = processor->reg1;
					printf("Inst obtain_reg - > Registrador 1 com conteudo %d\n", processor->reg1);


				} else if (inst->addr1 == 2){
					inst->addr2 = processor->reg2;
					printf("Inst obtain_reg - > Registrador 2 com conteudo %d\n", processor->reg2); }

				break;			
			default:
				break;


		}
	*/


		processor->PC += 1;


	}

}
