#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reader.h"

int main() {
    int opt = -1;
	
	struct memoria_instrucao mem_inst = {0};
	struct memoria_dados mem_dados = {0};
	struct registradores reg = {0};
	struct controle pc = {0};
	struct estado novo_estado;
	
	struct desc_Pilha *minhaPilha = CriaPilha();

    while (opt != 0) {
        printf("\n-------------MINI MIPS-------------\n");
		printf("1) Carregar Memoria de Instrucoes\n");
		printf("2) Carregar Memoria de Dados (.dat)\n");
		printf("3) Salvar arquivo .asm\n");
		printf("4) Salvar arquivos .dat\n");
		printf("5) Imprimir Memorias\n");
		printf("6) Imprimir Registradores\n");
		printf("7) Imprimir todo o simulador\n");
		printf("8) Executar uma instrucao (Step)\n");
		printf("9) Executar Programa (run)\n");
		printf("10) Volta uma instrucao (back)\n");
		printf("0) Sair\n");
		printf("-----------------------------------\n");
		printf("Opcao: ");
        scanf("%d", &opt);
		printf("-----------------------------------\n\n");
        switch (opt) {
            case 1:
				carrega_inst(&mem_inst);
            break;
            case 2:
				carrega_dados(&mem_dados);
			break;
            case 3:
				salva_asm(&mem_inst);
			break;
            case 4: 
				salva_dat(&mem_dados);
			break;
            case 5:
				imprime_mem_inst(&mem_inst);
				imprime_mem_dados(&mem_dados);
            break;
            case 6:
				imprime_reg(&reg);
            break;
            case 7:
				imprime_mem_inst(&mem_inst);
				imprime_mem_dados(&mem_dados);
				imprime_reg(&reg);
			break;
            case 8:
				salva_estado(&novo_estado, &mem_inst, &mem_dados, &reg, &pc);
				struct nodo * novoNodo = CriaNodo(&novo_estado);
				minhaPilha = PUSH(minhaPilha, novoNodo);
				Imprime(minhaPilha);
				
				printf("PC: %d\n", pc.pc);
				mostra_asm(&mem_inst.mem_inst[pc.pc]);
				executar(&mem_inst.mem_inst[pc.pc], &mem_dados, &reg, &pc);
			break;
			case 9:
				while(pc.pc<MAX){
					printf("PC: %d\n", pc.pc);
					mostra_asm(&mem_inst.mem_inst[pc.pc]);
					executar(&mem_inst.mem_inst[pc.pc], &mem_dados, &reg, &pc);
				}
			break;
            case 10: 
				if (EMPTY(minhaPilha)==1) {
					Imprime(minhaPilha);
					back(minhaPilha, &mem_inst, &mem_dados, &reg, &pc);
					minhaPilha = POP(minhaPilha);
				} else {
					printf("Lista Vazia\n");
				}
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