#ifndef __INSTRUCAO_H
#define __INSTRUCAO_H


#define HALT -1
#define	SOMA 0
#define SUBTRAI 1
#define	COPIA_pRAM 2
#define COPIA_pREG 3
#define SALVA_nREG 4
#define	OBTEM_dREG 5

#include "endereco.h"

typedef struct {
	endereco addr1;
	endereco addr2;
	endereco addr3;
	int opcode;

} instrucao_str;

#endif 
