#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reader.h"

int main() {
    struct memoria_instrucao mem_inst;
    int num_linhas;
    int opt = -1;
	int pc = 0;
	
    // Inicializa memoria zerada
    for (int i = 0; i < MAX; i++) {
        memset(mem_inst.mem_inst[i].inst_char, '\0', sizeof(mem_inst.mem_inst[i].inst_char));
        mem_inst.mem_inst[i].tipo_inst = '\0';
        mem_inst.mem_inst[i].opcode = 0;
		mem_inst.mem_inst[i].rs = 0;
		mem_inst.mem_inst[i].rt = 0;
		mem_inst.mem_inst[i].rd = 0;
		mem_inst.mem_inst[i].funct = 0;
		mem_inst.mem_inst[i].imm = 0;
		mem_inst.mem_inst[i].addr = 0;
    }
	
	int mem_dados[MAX];
	
	for (int i = 0; i < MAX; i++) {
		mem_dados[i] = 0;
    }
	
    //Inicia registradores com 0
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
					if(mem_inst.mem_inst[j].tipo_inst == 'R'){
					printf("[%i]:", j);
					printf("Instrucao: %s \n", mem_inst.mem_inst[j].inst_char);
					printf("    Tipo: %c \n", mem_inst.mem_inst[j].tipo_inst);
					printf("    opcode: %d \n", mem_inst.mem_inst[j].opcode);
					printf("    rs: %d \n", mem_inst.mem_inst[j].rs);
					printf("    rt: %d \n", mem_inst.mem_inst[j].rt);
					printf("    rd: %d \n", mem_inst.mem_inst[j].rd);
					printf("    funct: %d \n\n", mem_inst.mem_inst[j].funct);
					
					
					}else{
						if(mem_inst.mem_inst[j].tipo_inst == 'I'){
							printf("[%i]:", j);
							printf("Instrucao: %s \n", mem_inst.mem_inst[j].inst_char);
							printf("    Tipo: %c \n", mem_inst.mem_inst[j].tipo_inst);
							printf("    opcode: %d \n", mem_inst.mem_inst[j].opcode);
							printf("    rs: %d \n", mem_inst.mem_inst[j].rs);
							printf("    rt: %d \n", mem_inst.mem_inst[j].rt);
							printf("    imm: %d \n\n", mem_inst.mem_inst[j].imm);
						}else{
							if(mem_inst.mem_inst[j].tipo_inst == 'J'){
							printf("[%i]:", j);
							printf("Instrucao: %s \n", mem_inst.mem_inst[j].inst_char);
							printf("    Tipo: %c \n", mem_inst.mem_inst[j].tipo_inst);
							printf("    opcode: %d \n", mem_inst.mem_inst[j].opcode);
							printf("    addr: %d\n\n", mem_inst.mem_inst[j].addr);
							}
						}
					}
				}
                printf("\nMemoria de dados:\n");
                for (int j = 0; j < 16; j++) {
                    printf("[%i]: %d\n", j, mem_dados[j]);
                }
                break;
            case 3:
                printf("\nRegistradores:\n");
                for(int i=0;i<8;i++){
                    printf("Reg[%d]: %d\n", i, registradores[i]);
                }
                break;
            case 4:
                printf("\nMemoria de instrucoes:\n");
				for (int j = 0; j < 256; j++) {
					if(mem_inst.mem_inst[j].tipo_inst == 'R'){
					printf("[%i]:", j);
					printf("Instrucao: %s \n", mem_inst.mem_inst[j].inst_char);
					printf("    Tipo: %c \n", mem_inst.mem_inst[j].tipo_inst);
					printf("    opcode: %d \n", mem_inst.mem_inst[j].opcode);
					printf("    rs: %d \n", mem_inst.mem_inst[j].rs);
					printf("    rt: %d \n", mem_inst.mem_inst[j].rt);
					printf("    rd: %d \n", mem_inst.mem_inst[j].rd);
					printf("    funct: %d \n\n", mem_inst.mem_inst[j].funct);
					
					
					}else{
						if(mem_inst.mem_inst[j].tipo_inst == 'I'){
							printf("[%i]:", j);
							printf("Instrucao: %s \n", mem_inst.mem_inst[j].inst_char);
							printf("    Tipo: %c \n", mem_inst.mem_inst[j].tipo_inst);
							printf("    opcode: %d \n", mem_inst.mem_inst[j].opcode);
							printf("    rs: %d \n", mem_inst.mem_inst[j].rs);
							printf("    rt: %d \n", mem_inst.mem_inst[j].rt);
							printf("    imm: %d \n\n", mem_inst.mem_inst[j].imm);
						}else{
							if(mem_inst.mem_inst[j].tipo_inst == 'J'){
							printf("[%i]:", j);
							printf("Instrucao: %s \n", mem_inst.mem_inst[j].inst_char);
							printf("    Tipo: %c \n", mem_inst.mem_inst[j].tipo_inst);
							printf("    opcode: %d \n", mem_inst.mem_inst[j].opcode);
							printf("    addr: %d\n\n", mem_inst.mem_inst[j].addr);
							}
						}
					}
				}
                printf("\nMemoria de dados:\n");
                for (int j = 0; j < 16; j++) {
                    printf("[%i]: %d\n", j, mem_dados[j]);
                }
                printf("\nRegistradores:\n");
                for(int i=0;i<8;i++){
                    printf("Reg[%d]: %d\n", i, registradores[i]);
                }
                break;
            case 8:
				printf("\nPC [%d]\n", pc);
				switch(mem_inst.mem_inst[pc].opcode) {
				case 0:
					registradores[mem_inst.mem_inst[pc].rd] = result_ula(mem_inst.mem_inst[pc].opcode, mem_inst.mem_inst[pc].funct, registradores[mem_inst.mem_inst[pc].rs], registradores[mem_inst.mem_inst[pc].rt]);
					pc++;
					break;
				case 2:
					pc = mem_inst.mem_inst[pc].addr * 2;
					break;
				case 4:
					registradores[mem_inst.mem_inst[pc].rt] = result_ula(mem_inst.mem_inst[pc].opcode, 0, registradores[mem_inst.mem_inst[pc].rs], mem_inst.mem_inst[pc].imm);
					pc++;
					break;
				case 8: 
					pc++;
					break;
				case 11:
					registradores[mem_inst.mem_inst[pc].rt] = mem_dados[result_ula(mem_inst.mem_inst[pc].opcode, 0, mem_inst.mem_inst[pc].rs, mem_inst.mem_inst[pc].imm)];
					pc++;
					break;
				case 15:
					mem_dados[result_ula(mem_inst.mem_inst[pc].opcode, 0, mem_inst.mem_inst[pc].rs, mem_inst.mem_inst[pc].imm)] = registradores[mem_inst.mem_inst[pc].rt];
					pc++;
					break;
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