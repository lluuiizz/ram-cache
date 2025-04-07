#ifndef __PROGRAM_READER_H
#define __PROGRAM_READER_H

#include "ram.h"
#include "cpu.h"
#include "cache.h"
void ler_programa(char *nome_arquivo, RAM *ram, cpu *processor, caches *cache);
#endif // __PROGRAM_READER_H
