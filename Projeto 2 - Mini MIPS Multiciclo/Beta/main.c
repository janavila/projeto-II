#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reader.h"

int main() {
    struct memoria mem = {0};
	struct reg_inst reginst = {0};
	struct reg_mem regmem = {0};
	struct reg_ab ab = {0};
    struct controle_pc pc_aux = {0};
    char nome[50];
    int num_linhas;
    int opt = -1;
	//int pc = 0;
	int registradores[8] = {0};
	int ciclos = 0;

    while (opt != 0) {
        printf("\n-------------MINI MIPS-------------\n");
        printf("1) Carregar Memoria\n");
        printf("2) Imprimir Memoria\n");
        printf("3) Imprimir Registradores\n");
        printf("4) Imprimir todo o simulador\n");
        printf("7) Executar Programa (run)\n");
        printf("8) Executa um ciclo (Step)\n");
        printf("9) Volta uma instrucao (back)\n");
        printf("0) Sair\n");
        printf("-----------------------------------\nOpcao: ");
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
                }
                break;
            case 2: 
                printf("\nMemoria:\n");
                for (int j = 0; j < mem.tamanho; j++) {
                    imprime_mem(&mem, j);
                }
                break;
            case 3: 
				printf("\nRegistradores:\n");
				imprime_reg(registradores, ab);
                break;
            case 4: 
				printf("\nMemoria:\n");
                for (int j = 0; j < mem.tamanho; j++) {
                    imprime_mem(&mem, j);
                }
				printf("\nRegistradores:\n");
				imprime_reg(registradores, ab);
                break;
            case 7: 
                break;
            case 8: //STEP
				switch(ciclos){
					case 0:
						printf("\nCiclo 1 - Busca de Instrução\n");
						//1. Busca da Instrução (e incremento do PC)
						strcpy(reginst.inst_char, mem.linhas[pc_aux.pc_soma]);
						printf("\nRegistrador de instrucoes: %s", reginst.inst_char);
						pc_aux.pc_soma++;
						printf("\nPC + 1: %d", pc_aux.pc_soma);
						//Incrementando o contador de ciclos
						ciclos++;
					break;
					case 1:
                        printf("\nCiclo 2 - Decodificação de Instruções\n");
                        //2. Decodificação de Instruções.
                        //ab.reg_a = 
                        //ab.reg_b = 

					break;
					case 2:
					break;
				}
                break;
            case 9: 
                break;
            case 0:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opcao invalida\n");
                break;
        }
    }

    return 0;
}