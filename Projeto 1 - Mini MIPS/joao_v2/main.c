#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reader.h"

int main() {
    struct memoria_instrucao mem_inst = {0};
    int num_linhas;
    int opt = -1;
    int pc = 0;
    int mem_dados[MAX] = {0};
    int registradores[8] = {0};

    while (opt != 0) {
        printf("\n-------------\n1) Carregar Memoria\n2) Imprimir Memoria\n3) Imprimir Registradores\n4) Imprimir todo o simulador\n5) Salvar .asm\n6) Salvar .mem\n7) Executar Programa (run)\n8) Executa uma instrucao (Step)\n9) Volta uma instrucao (back)\n0) Sair\n-------------\nOpcao: ");
        scanf("%d", &opt);
        switch (opt) {
            case 1:
                num_linhas = lerEArmazenarArquivo("inst.mem", &mem_inst, MAX);
                if (num_linhas == -1) {
                    return 1;
                } else {
                    printf("\nArquivo carregado com sucesso!\n");
                }
                break;
            case 2:
                printf("\nMemoria de instrucoes:\n");
                for (int j = 0; j < 256; j++) {
                    imprime_mem(&mem_inst, j);
                }
                imprime_dados(mem_dados);
                break;
            case 3:
                imprime_reg(registradores);
                break;
            case 4:
                printf("\nMemoria de instrucoes:\n");
                for (int j = 0; j < 256; j++) {
                    imprime_mem(&mem_inst, j);
                }
                imprime_dados(mem_dados);
                imprime_reg(registradores);
                break;
            
            case 5:
            salva_asm(mem_inst);
            break;

            case 6:
            salva_mem(mem_dados);
            break;

            case 7:
			for(pc;pc<=mem_inst.tamanho;0){
				executa_instrucao(&mem_inst, &pc, registradores, mem_dados);
			}
                break;
            case 8:
                executa_instrucao(&mem_inst, &pc, registradores, mem_dados);
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