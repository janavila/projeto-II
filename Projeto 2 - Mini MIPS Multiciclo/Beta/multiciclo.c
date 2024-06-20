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
			//printf("Trocando caracteres[%d]:%s\n", tamanho, extendido);
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
				printf("\n\n----------------------------------------------------------\n");
				printf("Instrucao Assembly: ");
				mostra_asm(inst);
				printf("----------------------------------------------------------\n");
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
							*ciclos = 0;
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
				printf("\n\n----------------------------------------------------------\n");
				printf("Instrucao Assembly: ");
				mostra_asm(inst);
				printf("----------------------------------------------------------\n");
				break;

				case ('J'): // Duvida nesse parte.
					printf("Ciclo %d - Final da Execução tipo J\n", *ciclos);
					pc->jump = aux.inst.addr + 1;
					printf("Jump - [%d]", pc->jump);
					pc->pc_soma = pc->jump; // atribuir no pc soma pra não mudar a lógica ou fazer um if caso for jump?
					printf("\nCiclo Finalizado!");
					*ciclos = 0;
					printf("\n\n----------------------------------------------------------\n");
					printf("Instrucao Assembly: ");
					mostra_asm(inst);
					printf("----------------------------------------------------------\n");
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
				printf("\n\n----------------------------------------------------------\n");
				printf("Instrucao Assembly: ");
				mostra_asm(inst);
				printf("----------------------------------------------------------\n");
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
							rmem->dados = strtol(mem->linhas[pc->saida_ula], NULL, 2);
						printf("Registrador de memoria: %d\n", rmem->dados);
						*ciclos = *ciclos + 1;
					break;
					//SW
					case 15:
						printf("Ciclo [%d] - Final da Execução SW\n", *ciclos);
						char* binario = converte_binario(ab->reg_b);
						strcpy(mem->linhas[pc->saida_ula], binario);
						//sprintf(mem->linhas[pc->saida_ula], "%d", ab->reg_b);
						printf("Memoria[%d]: %s\n", pc->saida_ula, mem->linhas[pc->saida_ula]);
						printf("Ciclo Finalizado!");
						*ciclos = 0;
					break;
				}
				break;

			}
			printf("\n\n----------------------------------------------------------\n");
			printf("Instrucao Assembly: ");
			mostra_asm(inst);
			printf("----------------------------------------------------------\n");
		break;

		case 4:
			printf("Ciclo [%d] - Final da Execução LW\n", *ciclos);
			registradores[aux.inst.rt] = rmem->dados;
			printf("Registrador[%d]: %d\n", aux.inst.rt, registradores[aux.inst.rt]);
			printf("Ciclo Finalizado!");
			*ciclos = 0;
			printf("\n\n----------------------------------------------------------\n");
			printf("Instrucao Assembly: ");
			mostra_asm(inst);
			printf("----------------------------------------------------------\n");
		break;

}

}


char *escolhe_registrador(int reg) {

    switch(reg) {
        case 0: return "$0";
        case 1: return "$r1";
        case 2: return "$r2";
        case 3: return "$r3";
        case 4: return "$r4";
        case 5: return "$r5";
        case 6: return "$r6";
        case 7: return "SWs";
        case 8: return "LEDs";
    }

    return "Error"; // caso não escolha o registrador. (erro na instrução)

}


void salva_asm(struct memoria mem) {
    FILE *save = NULL;
    save = fopen("instrucoes.asm", "w");
    struct memoria aux = mem;
    int contador = 0, tamanho = mem.tamanho;
    char tipo[20];
	struct reg_inst aux_reginst; // auxiliar para decodificar a memoria de dados.

    if(save != NULL) {
        printf("Arquivo salvo com sucesso!\n");


    while (contador < tamanho) {
		strcpy(aux_reginst.inst_char, mem.linhas[contador]);
		decodificar(&aux_reginst);


    switch(aux_reginst.inst.opcode) { // verifica qual operação vai ser realizada e salva na variável TIPO;
        case 0:
            switch(aux_reginst.inst.funct) {
                case 0:
                strcpy(tipo, "add");
                break;
                case 2:
                strcpy(tipo, "sub");
                break;
                case 4:
                strcpy(tipo, "and");
                case 5:
                strcpy(tipo, "or");
                break;
            }
        fprintf(save,"%s %s, %s, %s\n", tipo, escolhe_registrador(aux_reginst.inst.rd), escolhe_registrador(aux_reginst.inst.rs), escolhe_registrador(aux_reginst.inst.rt));
        break;
        case 2:
        strcpy(tipo,"j");
        fprintf(save,"%s %d\n", tipo, aux_reginst.inst.addr);
        break;
        case 4:
        strcpy(tipo,"addi");
        fprintf(save,"%s %s, %s, %d\n", tipo, escolhe_registrador(aux_reginst.inst.rt), escolhe_registrador(aux_reginst.inst.rs), aux_reginst.inst.imm);
        break;
        case 8:
        strcpy(tipo, "beq");
        fprintf(save,"%s %s, %s, %d\n", tipo, escolhe_registrador(aux_reginst.inst.rt), escolhe_registrador(aux_reginst.inst.rs), aux_reginst.inst.imm);
        break;
        case 11:
        strcpy(tipo, "lw");
        fprintf(save,"%s %s, %d(%s)\n", tipo, escolhe_registrador(aux_reginst.inst.rt), aux_reginst.inst.imm, escolhe_registrador(aux_reginst.inst.rs));
        break;
        case 15:
        strcpy(tipo,"sw");
        fprintf(save,"%s %s, %d(%s)\n", tipo, escolhe_registrador(aux_reginst.inst.rt), aux_reginst.inst.imm, escolhe_registrador(aux_reginst.inst.rs));
        break;
    }

	contador++;

    }

	}

    else {
        printf("Erro salvar o arquivo!!\n");
    }

    fclose(save);

}

void mostra_asm(struct reg_inst aux_reginst){
	
    char tipo[20];
	
	decodificar(&aux_reginst);


    switch(aux_reginst.inst.opcode) { // verifica qual operação vai ser realizada e salva na variável TIPO;
        case 0:
            switch(aux_reginst.inst.funct) {
                case 0:
                strcpy(tipo, "add");
                break;
                case 2:
                strcpy(tipo, "sub");
                break;
                case 4:
                strcpy(tipo, "and");
                case 5:
                strcpy(tipo, "or");
                break;
            }
        printf("%s %s, %s, %s\n", tipo, escolhe_registrador(aux_reginst.inst.rd), escolhe_registrador(aux_reginst.inst.rs), escolhe_registrador(aux_reginst.inst.rt));
        break;
        case 2:
        strcpy(tipo,"j");
        printf("%s %d\n", tipo, aux_reginst.inst.addr);
        break;
        case 4:
        strcpy(tipo,"addi");
        printf("%s %s, %s, %d\n", tipo, escolhe_registrador(aux_reginst.inst.rt), escolhe_registrador(aux_reginst.inst.rs), aux_reginst.inst.imm);
        break;
        case 8:
        strcpy(tipo, "beq");
        printf("%s %s, %s, %d\n", tipo, escolhe_registrador(aux_reginst.inst.rt), escolhe_registrador(aux_reginst.inst.rs), aux_reginst.inst.imm);
        break;
        case 11:
        strcpy(tipo, "lw");
        printf("%s %s, %d(%s)\n", tipo, escolhe_registrador(aux_reginst.inst.rt), aux_reginst.inst.imm, escolhe_registrador(aux_reginst.inst.rs));
        break;
        case 15:
        strcpy(tipo,"sw");
        printf("%s %s, %d(%s)\n", tipo, escolhe_registrador(aux_reginst.inst.rt), aux_reginst.inst.imm, escolhe_registrador(aux_reginst.inst.rs));
        break;
    }
}

char *converte_binario(int num){
	int bits = 8; 
    char* Binario = (char*)malloc(bits + 1); // aloca memória para a string (+1 para o caractere nulo)
    if (Binario == NULL) {
        fprintf(stderr, "Falha na alocação de memória.\n");
        exit(1);
    }
    
    Binario[bits] = '\0'; // adiciona o caractere nulo no final da string

    for (int i = bits - 1; i >= 0; i--) {
        Binario[i] = (num & 1) ? '1' : '0'; // verifica o bit menos significativo e converte para '0' ou '1'
        num >>= 1; // desloca os bits do número para a direita
    }

    return Binario;
}

void salva_mem(struct memoria mem){
	FILE *save = NULL;
    save = fopen("memoria.mem", "w");
	int contador = 0, tamanho = MAX;
	
	if(save != NULL) {
        printf("Arquivo salvo com sucesso!\n");
		while (contador < tamanho) {
			fprintf(save,"%s\n", mem.linhas[contador]);
			contador++;
		}
	}else{
		printf("Erro salvar o arquivo!!\n");
	}
	fclose(save);
}

void salva_estado(int *ciclos, struct memoria *mem, struct estado *estado, struct reg_inst *reginst, struct reg_mem *regmem, struct reg_ab *ab, struct reg_ula *ula, struct controle_pc *pc, int *registradores){	
	estado->ciclos = *ciclos;
 	estado->mem = *mem;
	estado->ula = *ula;
    estado->reginst = *reginst;
    estado->regmem = *regmem;
    estado->ab = *ab;
    estado->pc = *pc;
    memcpy(estado->registradores, registradores, sizeof(int) * 8);
}

