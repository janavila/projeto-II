#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reader.h"

//teste

int lerEArmazenarArquivo(const char *filename, struct memoria *mem, int max_linhas) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return -1;
    }

    char linha[TAMANHO + 1];
    int count = 0;

    while (fgets(linha, sizeof(linha), file) != NULL && count < max_linhas) {
        linha[strcspn(linha, "\r\n")] = '\0';

        // Verifica se a linha não está vazia
        if (strlen(linha) > 0) {
            strncpy(mem->linhas[count], linha, TAMANHO);
			mem->tipo[count] = 1;
            mem->linhas[count][TAMANHO] = '\0'; 
            count++;
        }
    }

    mem->tamanho = count;
	//DEFININDO O TIPO Instrucao NA STRUCT
    fclose(file);

    return count;
}

int ULA(int opcode, int funct, int a, int b) {
    switch(opcode) {
        case 0:
            switch(funct) {
                case 0: return a + b;
                case 2: return a - b;
                case 4: return a & b;
                case 5: return a | b;
                default: return 0;
            }
        case 4: return a + b;
        case 8: return a - b;
        case 11: return a + b;
        case 15: return a + b;
        default: return 0;
    }
}

void imprime_mem(struct memoria *mem, int j) {
    if (j < 0 || j >= mem->tamanho) {
        printf("Erro na impressão!\n");
        return;
    }
    printf("[%i]: %s\n", j, mem->linhas[j]);
}

void imprime_reg(int registradores[], struct reg_ab regs){
    

	printf("\nRegistradores:\n");
    for(int i=0;i<8;i++){
        printf("Reg[%d]: %d\n", i, registradores[i]);
    }
}

void decodificar(struct reg_inst *inst){
	char *linha = inst->inst_char;
	char aux[8];
    char opcode[5];
    strncpy(opcode, linha, 4);
    opcode[4] = '\0';
	
    inst->inst.opcode = strtol(opcode, NULL, 2);
	inst->inst.tipo_inst = tipo(opcode);
     
    if (inst->inst.tipo_inst == 'R') {
       
		// linhaução do tipo R
		
		strncpy(aux, linha + 4, 3); 
		inst->inst.rs = strtol(aux, NULL, 2);
		memset(aux, '\0', sizeof(aux));
		
        strncpy(aux, linha + 7, 3);
		inst->inst.rt = strtol(aux, NULL, 2);
		memset(aux, '\0', sizeof(aux));
		
        strncpy(aux, linha + 10, 3);
		inst->inst.rd = strtol(aux, NULL, 2);
		memset(aux, '\0', sizeof(aux));
		
        strncpy(aux, linha + 13, 3);
		inst->inst.funct = strtol(aux, NULL, 2);
		memset(aux, '\0', sizeof(aux));
		
    } else if (inst->inst.tipo_inst == 'I') {
         // linhaução do tipo I
		
        strncpy(aux, linha + 4, 3);
		inst->inst.rs = strtol(aux, NULL, 2);
		memset(aux, '\0', sizeof(aux));
		
        strncpy(aux, linha + 7, 3);
		inst->inst.rt = strtol(aux, NULL, 2);
		memset(aux, '\0', sizeof(aux));
		
        strncpy(aux, linha + 10, 6);
		inst->inst.imm = extende_converte(aux);
		//inst->inst.imm = strtol(aux, NULL, 2);
		memset(aux, '\0', sizeof(aux));
		
    } else if (inst->inst.tipo_inst == 'J') {
         // linhaução do tipo J
		
        strncpy(aux, linha + 9, 7);
		inst->inst.addr = strtol(aux, NULL, 2);
		memset(aux, '\0', sizeof(aux));
    }
}

char tipo(const char opcode[]) {
    if (strcmp(opcode, "0010") == 0) {
        return 'J';
    } else {
        if(strcmp(opcode, "0000") != 0){
            return 'I';
        } else {
            return 'R';
        }
    }
}

int extende_converte(const char *imm){
	int decimal = 0;
	int tamanho = 0;
	
	char extendido[9];
	
	//printf("imm: %s\n", imm);
	//printf("Lenght imm: %d\n", strlen(imm));
	
	//EXTENDE PARA 8 BITS REPETINDO O MAIS SIGNIFFICATIVO
	strncpy(extendido, imm, 1);
	strncpy(extendido + 1, imm, 1);
	strncpy(extendido + 2, imm, 6);
	extendido[8] = '\0';
	
	tamanho = strlen(extendido) - 1;
	
	//printf("Lenght extendido: %d\n", strlen(extendido));
	//printf("Extendido: %s\n", extendido);
	
	//Negativo
	if(extendido[0]=='1'){
		
		//Subtraindo 1
		while(tamanho>0 && extendido[tamanho]=='0'){
			tamanho--;
			printf("Trocando caracteres[%d]:%s\n", tamanho, extendido);
		}
		//printf("Posicao que vai trocar: %d\n", tamanho);
		if (tamanho > 0) {
			extendido[tamanho] = '0'; // troca o primeiro 1 encontrado por 0
		}
		for(tamanho;tamanho<strlen(extendido);tamanho++){
		if(tamanho+1<=strlen(extendido)-1 && extendido[tamanho+1]=='0'){
			extendido[tamanho+1] = '1';
		}
		}
		//printf("Extendido depois de subtrair 1: %s\n", extendido);
		
		//Inverter os bits
		for(int i = 0;i < strlen(extendido);i++){
			if(extendido[i]=='0'){
				extendido[i] = '1';
			}else if(extendido[i]=='1'){
				extendido[i] = '0';
			}
			//printf("Invertendo os bits no loop[%d]: %s\n", i, extendido);
		}
		decimal = -strtol(extendido, NULL, 2);
		//Positivo
	}else if(extendido[0]=='0'){
		decimal = strtol(extendido, NULL, 2);
	}
	
	//printf("Extendido final: %s\n", extendido);
	//printf("Decimal: %d\n", decimal);
	return decimal;
}



void executa_ciclos(int *ciclos, int *registradores, struct reg_ab *ab, struct reg_inst inst, struct controle_pc *pc, struct reg_mem *rmem, struct memoria *mem) {
	struct reg_inst aux = inst; // auxiliar

	switch(*ciclos) {
		case 2:
		printf("\nCiclo [%d] - Executa Instrucoes\n", *ciclos);
			switch(aux.inst.tipo_inst) {

				case ('R'): // executa os ciclos conforme o tipo R.
				printf("Instrucao tipo R\n");
				pc->saida_ula = ULA(aux.inst.opcode, aux.inst.funct, ab->reg_a, ab->reg_b);
				printf("ULA Saída = [%d]", pc->saida_ula);
				*ciclos = *ciclos + 1; // não funciona fazer *ciclos++; blz kkkkk
				break;

				case ('I'):
				switch(inst.inst.opcode){
					//ADDI
					case 4:
						printf("Instrucao tipo I - Instrucao de referencia a memória\n");
						pc->saida_ula = ab->reg_a + aux.inst.imm;
						printf("ULA Saída = [%d]", pc->saida_ula);
						*ciclos = *ciclos + 1;
					break;
					//BEQ
					case 8:
						if(ULA(aux.inst.opcode, aux.inst.funct, ab->reg_a, ab->reg_b)==0){
							printf("\nCiclo [%d] - Final da Execução Tipo R\n", *ciclos);
							pc->pc_soma = pc->saida_ula;
							printf("Posicao PC: %d\n", pc->pc_soma);
							printf("Ciclo Finalizado!");
						}else{
							printf("\nCiclo [%d] - Final da Execução Tipo R\n", *ciclos);
							printf("Posicao PC: %d\n", pc->pc_soma);
							printf("Ciclo Finalizado!");
							*ciclos = 0;
						}
					break;
					//LW
					case 11:
						printf("Instrucao tipo I - Instrucao de referencia a memória\n");
						pc->saida_ula = ab->reg_a + aux.inst.imm;
						printf("ULA Saída = [%d]", pc->saida_ula);
						*ciclos = *ciclos + 1;
					break;
					//SW
					case 15:
						printf("Instrucao tipo I - Instrucao de referencia a memória\n");
						pc->saida_ula = ab->reg_a + aux.inst.imm;
						printf("ULA Saída = [%d]", pc->saida_ula);
						*ciclos = *ciclos + 1;
					break;
				}
				break;

				case ('J'):




				break;
				default: printf("Erro!!");
			}
			break;
		
		case 3:
			switch(aux.inst.tipo_inst) {
				case 'R': // executa os ciclos conforme o tipo R.
				printf("\nCiclo [%d] - Final da Execução Tipo R\n", *ciclos);
				registradores[aux.inst.rd] = pc->saida_ula;
				printf("Registrador [%d] = %d\n", aux.inst.rd, pc->saida_ula);
				printf("Ciclo Finalizado!");
				*ciclos = 0; // flag para pular para próxima Instrucao.
				break;

				case 'I': // executa os ciclos conforme o tipo I.
				switch(inst.inst.opcode){
					//ADDI
					case 4:
						printf("Ciclo [%d] - Final da Execução ADDI\n", *ciclos);
						registradores[aux.inst.rt] = pc->saida_ula;
						printf("Registrador [%d] = %d\n", aux.inst.rt, pc->saida_ula);
						printf("Ciclo Finalizado!");
						*ciclos = 0;
					break;
					//LW
					case 11:
						if(mem->tipo[pc->saida_ula]==2){
							rmem->dados = strtol(mem->linhas[pc->saida_ula], NULL, 10);
						}else{
							rmem->dados = 0;
						}
						printf("Registrador de memoria: %d\n", rmem->dados);
						*ciclos = *ciclos + 1;
					break;
					//SW
					case 15:
						printf("Ciclo [%d] - Final da Execução SW\n", *ciclos);
						sprintf(mem->linhas[pc->saida_ula], "%d", ab->reg_b);
						mem->tipo[pc->saida_ula] = 2;
						printf("Memoria[%d]: %s\n", pc->saida_ula, mem->linhas[pc->saida_ula]);
						printf("Ciclo Finalizado!");
						*ciclos = 0;
					break;
				}
				break;


				case 'J': // executa os ciclos conforme o tipo J.
				break;

			

			}
		break;

		case 4:
			printf("Ciclo [%d] - Final da Execução SW\n", *ciclos);
			registradores[aux.inst.rt] = rmem->dados;
			printf("Registrador[%d]: %d\n", aux.inst.rt, registradores[aux.inst.rt]);
			printf("Ciclo Finalizado!");
			*ciclos = 0;
		break;

}

}