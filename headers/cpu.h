#ifndef __CPU_H
#define __CPU_H

#include "instrucao.h"
#include "ram.h"
#include "bloco_memoria.h"
#include "cache.h"
typedef struct {
	bloco_memoria reg1, reg2, reg3;
	int PC;
	
	instrucao_str *programa;
	int opcode;


} cpu;

void iniciar (instrucao_str *programa,cpu *processor, RAM *RAM);



#endif 
