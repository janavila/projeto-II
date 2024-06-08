#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reader.h"

int main() {
	struct memoria mem = {0};
    char nome[50];
    int num_linhas;
    int opt = -1;
	int erro = 1;
	int pc = 0;
    

    while (opt != 0) {
        printf("\n-------------MINI MIPS-------------\n1) Carregar Memoria\n2) Imprimir Memoria\n3) Imprimir Registradores\n4) Imprimir todo o simulador\n7) Executar Programa (run)\n8) Executa uma instrucao (Step)\n9) Volta uma instrucao (back)\n0) Sair\n-----------------------------------\nOpcao: ");
        scanf("%d", &opt);
        switch (opt) {
            case 1:
				printf("Nome do arquivo: ");
                scanf("%s", nome);
                num_linhas = lerEArmazenarArquivo(nome, &mem, MAX);
                if (num_linhas == -1) {
                    return 1;
                } else {
                    printf("\nArquivo carregado com sucesso!\n");
                    erro = 0;
                }
                break;
            case 2: 
				printf("\nMemoria:\n");
                for (int j = 0; j < 256; j++) {
                    imprime_mem(&mem, j);
                }
                break;
            case 3: 
                break;
            case 4: 
                break;
            case 5:
				break;
            case 6:
				break;
            case 7: 
                break;
            case 8: 
                break;
			case 9: 
				break;
            case 10:
                break;
            case 0:
                printf("Saindo do programa...");
                break;
            default:
                printf("Opcao invalida");
                break;
        }
    }

    return 0;
}