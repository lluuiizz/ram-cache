#include "headers/cpu.h"
#include <stdlib.h>
#include <stdio.h>


void iniciar (instrucao_str *programa,cpu *processor, RAM *RAM, caches *cache) {
	
	processor->programa = programa;
	processor->PC = 0;
	processor->opcode = -1;



	while (processor->opcode != HALT){
		instrucao_str *inst;
		inst = malloc(sizeof(instrucao_str));
		inst = &processor->programa[processor->PC];
		processor->opcode = inst->opcode;

		if (inst->opcode != HALT){
			processor->reg1 = pegar_das_memorias(RAM, inst->addr1, cache); 
			processor->reg2 = pegar_das_memorias(RAM, inst->addr2, cache);
			processor->reg3 = pegar_das_memorias(RAM, inst->addr3, cache);
		}

			

  
		switch (processor->opcode) {
			case HALT: // HALT
				printf("Programa terminou!!\n");
				//imprimir(RAM);
				break;
				
			case SOMA: // SOMA
				processor->reg3->palavras[inst->addr3.endpalavra] = processor->reg1->palavras[inst->addr1.endpalavra] + processor->reg2->palavras[inst->addr2.endpalavra];
				processor->reg3->modified = 1;

				printf("Inst sum -> RAM posicao %d com conteudo na cache 1 %d\n", inst->addr3.endpalavra, processor->reg3->palavras[inst->addr3.endpalavra]);
				printf("Custo até o momento: %d\n", cache->custo);
				printf("Até o momento HITS C1: %d MISSES C1: %d\n",cache->cache_hit_l1, cache->cache_miss_l1);
				printf("Até o momento HITS C2: %d MISSES C2: %d\n",cache->cache_hit_l2, cache->cache_miss_l2);
				printf("Até o momento HITS C3: %d MISSES C3: %d\n",cache->cache_hit_l3, cache->cache_miss_l3);


				break;
				
			case SUBTRAI:  // SUBTRACAO
				processor->reg3->palavras[inst->addr3.endpalavra] = processor->reg1->palavras[inst->addr1.endpalavra] - processor->reg2->palavras[inst->addr2.endpalavra];
				processor->reg3->modified = 1;

				printf("Inst sub -> RAM posicao %d com conteudo na cache 1 %d\n", inst->addr3.endpalavra, processor->reg3->palavras[inst->addr3.endpalavra]);
				printf("Custo até o momento: %d\n", cache->custo);
				printf("Até o momento HITS C1: %d MISSES C1: %d\n",cache->cache_hit_l1, cache->cache_miss_l1);
				printf("Até o momento HITS C2: %d MISSES C2: %d\n",cache->cache_hit_l2, cache->cache_miss_l2);
				printf("Até o momento HITS C3: %d MISSES C3: %d\n",cache->cache_hit_l3, cache->cache_miss_l3);




				break;
				/*
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

				break;			*/
			default:
				break;

		}

		free(inst);
		processor->PC += 1;


	}

}
