#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reader.h"

int main() {
    struct memoria mem = {0};
	struct reg_inst reginst = {0};
	struct reg_mem regmem = {0};
	struct reg_ab ab = {0};
	struct reg_ula ula = {0};
    struct controle_pc pc_aux = {0};
	struct estado estado_anterior;
    char nome[50];
    int num_linhas;
    int opt = -1;
	//int pc = 0;
	int registradores[8] = {0};
	int ciclos = 0, aux_run = 0;
	int tipoarquivo;

    while(opt != 0){
        printf("\n-------------MINI MIPS-------------\n");
        printf("1) Carregar Memoria\n");
        printf("2) Imprimir Memoria\n");
        printf("3) Imprimir Registradores\n");
        printf("4) Imprimir todo o simulador\n");
		printf("5) Salvar .asm\n");
        printf("6) Executar Programa (run)\n");
        printf("7) Executa um ciclo (Step)\n");
        printf("8) Volta um ciclo (back)\n");
		printf("9) Salvar Memoria\n");
        printf("0) Sair\n");
        printf("-----------------------------------\nOpcao: ");
        scanf("%d", &opt);

        switch (opt) {
            case 1:
				//MODIFICAÇÃO NA MEMÓRIA
				printf("Carregar memoria!\n");
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

			case 5:
				salva_asm(mem);
			break;
            case 6: 
				// Irá executar o código conforme o número de linhas que existem.
				printf("Memória = %d", mem.tamanho);
				while(aux_run < mem.tamanho) {
					if(ciclos < 2) { // Executa se não for os primeiros ciclos.
						printf("\nCiclo [%d] - Busca de Instrucao\n", ciclos);
						//1. Busca da Instrucao (e incremento do PC)
								strcpy(reginst.inst_char, mem.linhas[pc_aux.pc_soma]);
								printf("\nRegistrador de instrucoes - PC [%d]: %s", pc_aux.pc_soma, reginst.inst_char);
								pc_aux.pc_soma++;
								printf("\nPC + 1: %d", pc_aux.pc_soma);
							//Incrementando o contador de ciclos
							ciclos++;
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

					}

					else { // faz o resto dos ciclos.

					while(ciclos != 0) { // quando zerar os ciclos, faz novamente.
					executa_ciclos(&ciclos, registradores, &ab, reginst, &pc_aux, &regmem, &mem);
					}
					aux_run++;

					}

				}

                break;

            case 7: //STEP
				switch(ciclos){
					case 0:
						//(struct estado *estado, struct reg_inst *reginst, struct reg_mem *regmem, struct reg_ab *ab, struct reg_ula *ula, struct controle_pc *pc, int *registradores)
						salva_estado(&ciclos, &mem, &estado_anterior, &reginst, &regmem, &ab, &ula, &pc_aux, registradores);
						printf("\nCiclo [%d] - Busca de Instrucao\n", ciclos);
						//1. Busca da Instrucao (e incremento do PC)
								strcpy(reginst.inst_char, mem.linhas[pc_aux.pc_soma]);
								printf("Registrador de instrucoes - PC [%d]: %s", pc_aux.pc_soma, reginst.inst_char);
								pc_aux.pc_soma++;
								printf("\nPC + 1: %d", pc_aux.pc_soma);
							//Incrementando o contador de ciclos
							printf("\n\n----------------------------------------------------------\n");
							printf("Instrucao Assembly: ");
							mostra_asm(reginst);
							printf("----------------------------------------------------------\n");
							ciclos++;
						break;
					case 1:
						salva_estado(&ciclos, &mem, &estado_anterior, &reginst, &regmem, &ab, &ula, &pc_aux, registradores);
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
						printf("\n\n----------------------------------------------------------\n");
						printf("Instrucao Assembly: ");
						mostra_asm(reginst);
						printf("----------------------------------------------------------\n");
                        ciclos++;
					break;
					case 2:
						salva_estado(&ciclos, &mem, &estado_anterior, &reginst, &regmem, &ab, &ula, &pc_aux, registradores);
						executa_ciclos(&ciclos, registradores, &ab, reginst, &pc_aux, &regmem, &mem);
					break;
					case 3:
						salva_estado(&ciclos, &mem, &estado_anterior, &reginst, &regmem, &ab, &ula, &pc_aux, registradores);
						executa_ciclos(&ciclos, registradores, &ab, reginst, &pc_aux, &regmem, &mem);   
					break;                 
					case 4:
						salva_estado(&ciclos, &mem, &estado_anterior, &reginst, &regmem, &ab, &ula, &pc_aux, registradores);
						executa_ciclos(&ciclos, registradores, &ab, reginst, &pc_aux, &regmem, &mem);
					break;
					case 5:
						salva_estado(&ciclos, &mem, &estado_anterior, &reginst, &regmem, &ab, &ula, &pc_aux, registradores);
						executa_ciclos(&ciclos, registradores, &ab, reginst, &pc_aux, &regmem, &mem);
					break;
                }
                break;
				case 8:
					ciclos = estado_anterior.ciclos;
					ula = estado_anterior.ula;
					reginst = estado_anterior.reginst;
					regmem = estado_anterior.regmem;
					ab = estado_anterior.ab;
					pc_aux = estado_anterior.pc;
					memcpy(registradores, estado_anterior.registradores, sizeof(int) * 8);
				break;
				case 9:
					salva_mem(mem);
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