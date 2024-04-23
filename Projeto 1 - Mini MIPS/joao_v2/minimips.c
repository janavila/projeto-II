#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "reader.h"

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

//le e armazena o arquivo
int lerEArmazenarArquivo(const char *filename, struct memoria_instrucao *mem_inst, int max_linhas) {
    FILE *file;
    char linha[TAMANHO + 2]; //o +2 é pra armazenar o '\n' e o '\0'
    int i = 0;

    file = fopen(filename, "r"); // Abre o arquivo

    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return -1;
    }

    // Le o arquivo e armazena na matriz
	
    while (fgets(linha, sizeof(linha), file) && i < max_linhas) {
        linha[strcspn(linha, "\n")] = '\0'; //remove o \n da linha e coloca \0
        // Copiando a linha para a memoria
        strncpy(mem_inst->mem_inst[i].inst_char, linha, TAMANHO);//copia os caracteres da string 'linha', até 'TAMANHO', para 'inst_char'
        memset(mem_inst->mem_inst[i].inst_char + strlen(linha), ' ', TAMANHO - strlen(linha));//essa linha preenche o resto do espaço livre na string com espaços em branco
        mem_inst->mem_inst[i].inst_char[TAMANHO] = '\0'; 
        
        // Decodifica a instrução e armazena na struct
        char opcode[5];
        strncpy(opcode, linha, 4);
        opcode[4] = '\0'; 
		char aux[8];
        
        mem_inst->mem_inst[i].tipo_inst = tipo(opcode);
        mem_inst->mem_inst[i].opcode = strtol(opcode, NULL, 2);//converte o opcode de uma string em binario pra um inteiro
        
        if (mem_inst->mem_inst[i].tipo_inst == 'R') {
//----------------------------------------------------------------------
//Essa parte é tudo igual, só vai mudar a posicao da linha, que é o argumento do meio, e a quantidade de caracteres que vai copiar, que é o ultimo argumento 
            
			// Instrução do tipo R
			
			strncpy(aux, linha + 4, 3); //copia '3' caracteres da instrucao a partir da posicao '4' para aux
			mem_inst->mem_inst[i].rs = strtol(aux, NULL, 2);//converte de string binaria para um inteiro, o ultimo argumento '2' é pra representar que a string ta em base binaria
			memset(aux, '\0', sizeof(aux));//limpa aux para nao dar problema
			
            strncpy(aux, linha + 7, 3);
			mem_inst->mem_inst[i].rt = strtol(aux, NULL, 2);
			memset(aux, '\0', sizeof(aux));
			
            strncpy(aux, linha + 10, 3);
			mem_inst->mem_inst[i].rd = strtol(aux, NULL, 2);
			memset(aux, '\0', sizeof(aux));
			
            strncpy(aux, linha + 13, 3);
			mem_inst->mem_inst[i].funct = strtol(aux, NULL, 2);
			memset(aux, '\0', sizeof(aux));
			
        } else if (mem_inst->mem_inst[i].tipo_inst == 'I') {
            // Instrução do tipo I
			
            strncpy(aux, linha + 4, 3);
			mem_inst->mem_inst[i].rs = strtol(aux, NULL, 2);
			memset(aux, '\0', sizeof(aux));
			
            strncpy(aux, linha + 7, 3);
			mem_inst->mem_inst[i].rt = strtol(aux, NULL, 2);
			memset(aux, '\0', sizeof(aux));
			
            strncpy(aux, linha + 10, 6);
			mem_inst->mem_inst[i].imm = strtol(aux, NULL, 2);
			memset(aux, '\0', sizeof(aux));
			
        } else if (mem_inst->mem_inst[i].tipo_inst == 'J') {
            // Instrução do tipo J
			
            strncpy(aux, linha + 9, 7);
			mem_inst->mem_inst[i].addr = strtol(aux, NULL, 2);
			memset(aux, '\0', sizeof(aux));
        }
        
        i++;
    }
//-----------------------------------------------------------------------------------------
    fclose(file); 

    mem_inst->tamanho = i;

    return i;
}

//representa a ULA (ainda falta colocar uma variavel pra flag q vai precisar pro BEQ)
int result_ula(int opcode, int funct, int a, int b){
	switch(opcode){
		case 0:
			switch(funct){
				case 0:
				return a+b;
				break;
				case 2:
				return a-b;
				break;
				case 4:
				return a&b;
				break;
				case 5:
				return a|b;
				break;
			}
		case 4:
			return a+b;
		break;
		case 11:
			return a+b;
		break;
		case 15:
			return a+b;
		break;
		default:
		return 0;
	}
}

//imprime a memoria de instrucoes
void imprime_mem(struct memoria_instrucao *mem_inst, int j) {
    if (mem_inst->mem_inst[j].tipo_inst == 'R') {
        printf("[%i]:", j);
        printf("Instrucao: %s \n", mem_inst->mem_inst[j].inst_char);
        printf("    Tipo: %c \n", mem_inst->mem_inst[j].tipo_inst);
        printf("    opcode: %d \n", mem_inst->mem_inst[j].opcode);
        printf("    rs: %d \n", mem_inst->mem_inst[j].rs);
        printf("    rt: %d \n", mem_inst->mem_inst[j].rt);
        printf("    rd: %d \n", mem_inst->mem_inst[j].rd);
        printf("    funct: %d \n\n", mem_inst->mem_inst[j].funct);
    } else {
        if (mem_inst->mem_inst[j].tipo_inst == 'I') {
            printf("[%i]:", j);
            printf("Instrucao: %s \n", mem_inst->mem_inst[j].inst_char);
            printf("    Tipo: %c \n", mem_inst->mem_inst[j].tipo_inst);
            printf("    opcode: %d \n", mem_inst->mem_inst[j].opcode);
            printf("    rs: %d \n", mem_inst->mem_inst[j].rs);
            printf("    rt: %d \n", mem_inst->mem_inst[j].rt);
            printf("    imm: %d \n\n", mem_inst->mem_inst[j].imm);
        } else {
            if (mem_inst->mem_inst[j].tipo_inst == 'J') {
                printf("[%i]:", j);
                printf("Instrucao: %s \n", mem_inst->mem_inst[j].inst_char);
                printf("    Tipo: %c \n", mem_inst->mem_inst[j].tipo_inst);
                printf("    opcode: %d \n", mem_inst->mem_inst[j].opcode);
                printf("    addr: %d", mem_inst->mem_inst[j].addr);
            }
        }
    }
}

//imprime a memoria de dados
void imprime_dados(int mem_dados[]){
	printf("\n\nMemoria de dados:\n");
    for (int j = 0; j < 256; j++) {
        printf("[%i]: %d\t", j, mem_dados[j]);
    }
}

//imprime os registradores
void imprime_reg(int registradores[]){
	printf("\nRegistradores:\n");
    for(int i=0;i<8;i++){
        printf("Reg[%d]: %d\n", i, registradores[i]);
    }
}

//funçao pra controlar o que deve ser executado
void executa_instrucao(struct memoria_instrucao *mem_inst, int *pc, int *registradores, int *mem_dados) {
    printf("\nPC [%d]\n", *pc);
    imprime_mem(mem_inst, *pc);
    
    switch (mem_inst->mem_inst[*pc].opcode) {
		//ADD, SUB, OR ou And
        case 0:
            registradores[mem_inst->mem_inst[*pc].rd] = result_ula(mem_inst->mem_inst[*pc].opcode, mem_inst->mem_inst[*pc].funct, registradores[mem_inst->mem_inst[*pc].rs], registradores[mem_inst->mem_inst[*pc].rt]);
            (*pc)++;
            break;
			//JUMP
        case 2:
            *pc = mem_inst->mem_inst[*pc].addr * 2;
            break;
			//ADDI
        case 4:
            registradores[mem_inst->mem_inst[*pc].rt] = result_ula(mem_inst->mem_inst[*pc].opcode, 0, registradores[mem_inst->mem_inst[*pc].rs], mem_inst->mem_inst[*pc].imm);
            (*pc)++;
            break;
			//BEQ
        case 8: 
            (*pc)++;
            break;
			//LW
        case 11:
            registradores[mem_inst->mem_inst[*pc].rt] = mem_dados[result_ula(mem_inst->mem_inst[*pc].opcode, 0, mem_inst->mem_inst[*pc].rs, mem_inst->mem_inst[*pc].imm)];
            (*pc)++;
            break;
			//SW
        case 15:
            mem_dados[result_ula(mem_inst->mem_inst[*pc].opcode, 0, mem_inst->mem_inst[*pc].rs, mem_inst->mem_inst[*pc].imm)] = registradores[mem_inst->mem_inst[*pc].rt];
            (*pc)++;
            break;
    }
	printf("Instrucao concluida!");
}


void salva_mem(int *data) {
    FILE *save = NULL;
    int *aux = data, contador = 0;
    char memoria[9];

    save = fopen("memoria_dados.mem", "w");
    memset(memoria, '0', 8); // preenche todos espaços da memoria com '0'
    memoria[8] = '\0';

    if (save != NULL) {
    
    while(contador < 256) {

        for(int i = 7; i >= 0; i--){ 
        memoria[i] = (aux[contador] & 1) ? '1' : '0'; // Faz a operação And com o contador, compara posição por posição.
        aux[contador] >>= 1;
        }

        fprintf(save, "[%d] : %s\n", contador, memoria);
        contador++;
    }
    printf("Arquivo salvo com sucesso");
    }

    else {
        printf("Erro em salvar o arquivo!!");
    }

    fclose(save);

}


void salva_asm(struct memoria_instrucao mem_inst) {
    FILE *save = NULL;
    save = fopen("instrucoes.asm", "w");
    struct memoria_instrucao aux = mem_inst;
    int contador = 0, tamanho = mem_inst.tamanho;
    char tipo[20];

    if(save != NULL) {
        printf("Arquivo salvo com sucesso!\n");

    //    printf("Opcode: %d", aux.mem_inst[contador].opcode);

    while (contador < tamanho) {

    switch(aux.mem_inst[contador].opcode) { // verifica qual operação vai ser realizada e salva na variável TIPO;
        case 0:
            switch(aux.mem_inst[contador].funct) {
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
        fprintf(save,"%s %s, %s, %s\n", tipo, escolhe_registrador(aux.mem_inst[contador].rd), escolhe_registrador(aux.mem_inst[contador].rs), escolhe_registrador(aux.mem_inst[contador].rt));
        break;
        case 2:
        strcpy(tipo,"j");
        fprintf(save,"%s %d\n", tipo, aux.mem_inst[contador].addr);
        break;
        case 4:
        strcpy(tipo,"addi");
        fprintf(save,"%s %s, %s, %d\n", tipo, escolhe_registrador(aux.mem_inst[contador].rt), escolhe_registrador(aux.mem_inst[contador].rs), aux.mem_inst[contador].imm);
        break;
        case 8:
        strcpy(tipo, "beq");
        fprintf(save,"%s %s, %s, %d\n", tipo, escolhe_registrador(aux.mem_inst[contador].rt), escolhe_registrador(aux.mem_inst[contador].rs), aux.mem_inst[contador].imm);
        break;
        case 11:
        strcpy(tipo, "lw");
        fprintf(save,"%s %s, %d(%s)\n", tipo, escolhe_registrador(aux.mem_inst[contador].rt), aux.mem_inst[contador].imm, escolhe_registrador(aux.mem_inst[contador].rs));
        break;
        case 15:
        strcpy(tipo,"sw");
        fprintf(save,"%s %s, %d(%s)\n", tipo, escolhe_registrador(aux.mem_inst[contador].rt), aux.mem_inst[contador].imm, escolhe_registrador(aux.mem_inst[contador].rs));
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