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
	int tipoarquivo;

    while(opt != 0){
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
				//MODIFICAÇÃO NA MEMÓRIA
				printf("Carregar Instrucoes (1) ou Dados (2): ");
				scanf("%d", &tipoarquivo);
				switch(tipoarquivo){
					//Instrucao
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
					
					//DADOS
					case 2:
						
					break;
					
					//INVÁLIDO
					default:
						printf("Invalido!");
					break;
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
						printf("\nCiclo [%d] - Busca de Instrucao\n", ciclos);
						//1. Busca da Instrucao (e incremento do PC)
							if(mem.tipo[pc_aux.pc_soma]==1){
								strcpy(reginst.inst_char, mem.linhas[pc_aux.pc_soma]);
								printf("\nRegistrador de instrucoes - PC [%d]: %s", pc_aux.pc_soma, reginst.inst_char);
								pc_aux.pc_soma++;
								printf("\nPC + 1: %d", pc_aux.pc_soma);
							//Incrementando o contador de ciclos
							ciclos++;
							}else{
									printf("A posicao indicada nao eh uma instrucao!");
									pc_aux.pc_soma++;
								}
					break;
					case 1:
                        printf("\nCiclo [%d] - Decodificacao de Instrucoes\n", ciclos);
                        //2. Decodificação de Instruções.
						decodificar(&reginst);
						
                        printf("tipo_inst: %c\n", reginst.inst.tipo_inst);
                        printf("opcode: %d\n", reginst.inst.opcode);
                        printf("rs: %d\n", reginst.inst.rs);
                        printf("rt: %d\n", reginst.inst.rt);
                        printf("rd: %d\n", reginst.inst.rd);
                        printf("funct: %d\n", reginst.inst.funct);
                        printf("imm: %d\n", reginst.inst.imm);
                        printf("addr: %d\n", reginst.inst.addr);

						//TIPO R CORRIGIDO
                        ab.reg_a = registradores[reginst.inst.rs];
                        ab.reg_b = registradores[reginst.inst.rt];
						
                        pc_aux.saida_ula = (pc_aux.pc_soma + 1) + reginst.inst.imm;
                        printf("\nA: %d - B: %d - SaidaULA = %d", ab.reg_a, ab.reg_b, pc_aux.saida_ula);
                        ciclos++;
					break;
					case 2:
						executa_ciclos(&ciclos, registradores, &ab, reginst, &pc_aux, &regmem, &mem);
					break;
					case 3:
						executa_ciclos(&ciclos, registradores, &ab, reginst, &pc_aux, &regmem, &mem);   
					break;                 
					case 4:
						executa_ciclos(&ciclos, registradores, &ab, reginst, &pc_aux, &regmem, &mem);
					break;
					case 5:
						executa_ciclos(&ciclos, registradores, &ab, reginst, &pc_aux, &regmem, &mem);
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