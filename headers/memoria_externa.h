#ifndef _MEMORIA_EXTERNA_H
#define _MEMORIA_EXTERNA_H

#include "bloco_memoria.h"

void gerar_memoria_externa(void);
bloco_memoria obter_bloco(int bloco_end);
void modificar_bloco(bloco_memoria bloco_novo, int end_memoria);




#endif // _MEMORIA_EXTERNA_H

