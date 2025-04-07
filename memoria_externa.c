#include "headers/memoria_externa.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>



void gerar_memoria_externa(void){
    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    // Abre o arquivo para escrita
    FILE *arquivo = fopen("memoria_externa.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return ;
    }

    // Gera 10 mil linhas com 4 números cada
    for (int i = 0; i < 10000; i++) {
        for (int j = 0; j < 4; j++) {
            // Gera um número entre 0 e 999
            int numero = rand() % 1000;
            fprintf(arquivo, "%d", numero);
            
            // Adiciona espaço, exceto após o último número
            if (j < 3) {
                fprintf(arquivo, " ");
            }
        }
        fprintf(arquivo, "\n"); // Nova linha após cada conjunto de 4 números
    }

    // Fecha o arquivo
    fclose(arquivo);
    printf("Arquivo gerado com sucesso: numeros.txt\n");



}

bloco_memoria obter_bloco(int bloco_end){
	FILE *arquivo = fopen("memoria_externa.txt", "r");
    char linha[200];
    int linhaAtual = 0;

	bloco_memoria bloco_encontrado;

    // Percorre o arquivo até encontrar a linha desejada
    while (fgets(linha, 200, arquivo) != NULL) {
        if (linhaAtual == bloco_end) {
            // Extrai os 4 valores da linha
            char *token = strtok(linha, " ");
            for (int i = 0; i < 4 && token != NULL; i++) {
                bloco_encontrado.palavras[i] = atoi(token);
                token = strtok(NULL, " ");
            }
            fclose(arquivo);
			bloco_encontrado.end_bloco = bloco_end;
            return bloco_encontrado;
        }
        linhaAtual++;
    }

    fclose(arquivo);

	bloco_encontrado.end_bloco = -1;
	return bloco_encontrado;

}

void modificar_bloco(bloco_memoria bloco_novo, int end_memoria){
	FILE *arquivo = fopen("memoria_externa.txt", "r");
	FILE *tmp = fopen("tmp.txt", "w");
	char linha[200];
	int linhaAtual = 0;



	printf("Palavras do bloco novo: %d - %d\n\n\n", bloco_novo.palavras[0], bloco_novo.palavras[1]);
	while (fgets(linha, 200, arquivo) != NULL){
		if (linhaAtual == end_memoria) {
			fprintf(tmp, "%d %d %d %d\n", bloco_novo.palavras[0], bloco_novo.palavras[1], bloco_novo.palavras[2], bloco_novo.palavras[3]);
		}
		else {
			fputs(linha, tmp);
		}
		linhaAtual++;
	}

	fclose(arquivo);
	fclose(tmp);


	remove("memoria_externa.txt");
	rename("tmp.txt", "memoria_externa.txt");
		
}
