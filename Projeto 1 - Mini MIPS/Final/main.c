#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reader.h"

int main() {
    struct memoria_instrucao mem_inst = {0};
    char nome[50];
    int num_linhas;
    int opt = -1;
    int pc = 0, erro = 1;
    int mem_dados[MAX] = {0};
    int registradores[8] = {0};
	struct Estado estado_anterior;

    while (opt != 0) {
        printf("\n-------------MINI MIPS-------------\n1) Carregar Memoria\n2) Imprimir Memoria\n3) Imprimir Registradores\n4) Imprimir todo o simulador\n5) Salvar .asm\n6) Salvar .mem e .dat\n7) Executar Programa (run)\n8) Executa uma instrucao (Step)\n9) Volta uma instrucao (back)\n10) Carregar Memória de Dados (.dat)\n0) Sair\n-----------------------------------\nOpcao: ");
        scanf("%d", &opt);
        switch (opt) {
            case 1:
                printf("Nome do arquivo: ");
                scanf("%s", nome);
                num_linhas = lerEArmazenarArquivo(nome, &mem_inst, MAX);
                if (num_linhas == -1) {
                    return 1;
                } else {
                    printf("\nArquivo carregado com sucesso!\n");
                    erro = 0;
                }
                break;
            case 2: if (erro == 0) {
                printf("\nMemoria de instrucoes:\n");
                for (int j = 0; j < 256; j++) {
                    imprime_mem(&mem_inst, j);
                }
                imprime_dados(mem_dados);
                }
            else printf("Você deve abrir um arquivo!!\n");
                break;
            case 3: if (erro == 0) imprime_reg(registradores);
            else printf("Você deve abrir um arquivo!!\n");
                break;
            case 4: if(erro == 0) {
                printf("\nMemoria de instrucoes:\n");
                for (int j = 0; j < 256; j++) {
                    imprime_mem(&mem_inst, j);
                }
                imprime_dados(mem_dados);
                imprime_reg(registradores);
            }
            else printf("Você deve abrir um arquivo!!\n");
                break;
            
            case 5: if (erro == 0) salva_asm(mem_inst);
            else printf("Você deve abrir um arquivo!!\n");
            break;

            case 6: if (erro == 0) salva_mem(mem_dados);
            else printf("Você deve abrir um arquivo!!\n");
            break;

            case 7: if(erro == 0) {
			for(pc;pc<=mem_inst.tamanho;0){
				salva_estado(&estado_anterior, pc, registradores, mem_dados);
				executa_instrucao(&mem_inst, &pc, registradores, mem_dados);
			}
            }
            else printf("Você deve abrir um arquivo!!\n");
                break;
            case 8: if(erro == 0) {
				salva_estado(&estado_anterior, pc, registradores, mem_dados);
                executa_instrucao(&mem_inst, &pc, registradores, mem_dados);
            }
            else printf("Você deve abrir um arquivo!!\n");
                break;
			case 9: if (erro == 0) {
				pc = estado_anterior.pc;
                memcpy(registradores, estado_anterior.registradores, sizeof(registradores));
                memcpy(mem_dados, estado_anterior.memoria_dados, sizeof(mem_dados));
            }
            else printf("Você deve abrir um arquivo!!\n");
				break;

            case 10: carrega_dados(mem_dados);
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