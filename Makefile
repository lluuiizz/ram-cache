all: ram.o cpu.o mmu.o cache.o
	@gcc programas.c ram.o cpu.o mmu.o cache.o -o exe -Wall
	@rm -rf *.o


ram.o: ram.c headers/ram.h
	@gcc -c ram.c

cpu.o: cpu.c headers/cpu.h
	@gcc -c cpu.c
mmu.o: mmu.c headers/endereco.h headers/cache.h headers/ram.h
	@gcc -c mmu.c

cache.o: cache.c headers/cache.h
	@gcc -c cache.c

val: 
	valgrind --leak-check=full ./exe



