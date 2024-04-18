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

//le e armazenar o arquivo
int lerEArmazenarArquivo(const char *filename, struct memoria_instrucao *mem_inst, int max_linhas) {
    FILE *file;
    char line[TAMANHO + 2]; 
    int i = 0;

    file = fopen(filename, "r"); // Abrindo o arquivo para leitura

    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return -1;
    }

    // Le o arquivo e armazena na matriz
    while (fgets(line, sizeof(line), file) && i < max_linhas) {
        line[strcspn(line, "\n")] = '\0';
        // Copiando a linha para a memoria
        strncpy(mem_inst->mem_inst[i].inst_char, line, TAMANHO);
        // Preenchendo com espaços em branco se a linha tiver menos de 16 caracteres
        memset(mem_inst->mem_inst[i].inst_char + strlen(line), ' ', TAMANHO - strlen(line));
        mem_inst->mem_inst[i].inst_char[TAMANHO] = '\0'; 
        
        // Decodificar a instrução e armazenar na struct
        char opcode[5];
        strncpy(opcode, line, 4);
        opcode[4] = '\0'; // Terminador nulo
		char aux[8];
        
        mem_inst->mem_inst[i].tipo_inst = tipo(opcode);
        mem_inst->mem_inst[i].opcode = strtol(opcode, NULL, 2);
        
        if (mem_inst->mem_inst[i].tipo_inst == 'R') {
            // Instrução do tipo R
            strncpy(aux, line + 4, 3);
			mem_inst->mem_inst[i].rs = strtol(aux, NULL, 2);
			memset(aux, '\0', sizeof(aux));
            strncpy(aux, line + 7, 3);
			mem_inst->mem_inst[i].rt = strtol(aux, NULL, 2);
			memset(aux, '\0', sizeof(aux));
            strncpy(aux, line + 10, 3);
			mem_inst->mem_inst[i].rd = strtol(aux, NULL, 2);
			memset(aux, '\0', sizeof(aux));
            strncpy(aux, line + 13, 3);
			mem_inst->mem_inst[i].funct = strtol(aux, NULL, 2);
			memset(aux, '\0', sizeof(aux));
        } else if (mem_inst->mem_inst[i].tipo_inst == 'I') {
            // Instrução do tipo I
            strncpy(aux, line + 4, 3);
			mem_inst->mem_inst[i].rs = strtol(aux, NULL, 2);
			memset(aux, '\0', sizeof(aux));
            strncpy(aux, line + 7, 3);
			mem_inst->mem_inst[i].rt = strtol(aux, NULL, 2);
			memset(aux, '\0', sizeof(aux));
            strncpy(aux, line + 10, 6);
			mem_inst->mem_inst[i].imm = strtol(aux, NULL, 2);
			memset(aux, '\0', sizeof(aux));
        } else if (mem_inst->mem_inst[i].tipo_inst == 'J') {
            // Instrução do tipo J
            strncpy(aux, line + 9, 7);
			mem_inst->mem_inst[i].addr = strtol(aux, NULL, 2);
			memset(aux, '\0', sizeof(aux));
        }
        
        i++;
    }

    fclose(file); 

    mem_inst->tamanho = i;

    return i;
}

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