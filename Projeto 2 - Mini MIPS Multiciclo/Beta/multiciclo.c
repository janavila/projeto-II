#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "reader.h"

int lerEArmazenarArquivo(const char *filename, struct memoria *mem, int max_linhas) {
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
        strncpy(mem->mem[i].inst_char, linha, TAMANHO);//copia os caracteres da string 'linha', até 'TAMANHO', para 'inst_char'
        memset(mem->mem[i].inst_char + strlen(linha), ' ', TAMANHO - strlen(linha));//essa linha preenche o resto do espaço livre na string com espaços em branco
        mem->mem[i].inst_char[TAMANHO] = '\0'; 
        
        // Decodifica a instrução e armazena na struct
        char opcode[5];
        strncpy(opcode, linha, 4);
        opcode[4] = '\0'; 
		char aux[8];
        
        mem->mem[i].tipo_inst = tipo(opcode);
        mem->mem[i].opcode = strtol(opcode, NULL, 2);//converte o opcode de uma string em binario pra um inteiro
        
        if (mem->mem[i].tipo_inst == 'R') {
//----------------------------------------------------------------------
//Essa parte é tudo igual, só vai mudar a posicao da linha, que é o argumento do meio, e a quantidade de caracteres que vai copiar, que é o ultimo argumento 
            
			// Instrução do tipo R
			
			strncpy(aux, linha + 4, 3); //copia '3' caracteres da instrucao a partir da posicao '4' para aux
			mem->mem[i].rs = strtol(aux, NULL, 2);//converte de string binaria para um inteiro, o ultimo argumento '2' é pra representar que a string ta em base binaria
			memset(aux, '\0', sizeof(aux));//limpa aux para nao dar problema
			
            strncpy(aux, linha + 7, 3);
			mem->mem[i].rt = strtol(aux, NULL, 2);
			memset(aux, '\0', sizeof(aux));
			
            strncpy(aux, linha + 10, 3);
			mem->mem[i].rd = strtol(aux, NULL, 2);
			memset(aux, '\0', sizeof(aux));
			
            strncpy(aux, linha + 13, 3);
			mem->mem[i].funct = strtol(aux, NULL, 2);
			memset(aux, '\0', sizeof(aux));
			
        } else if (mem->mem[i].tipo_inst == 'I') {
            // Instrução do tipo I
			
            strncpy(aux, linha + 4, 3);
			mem->mem[i].rs = strtol(aux, NULL, 2);
			memset(aux, '\0', sizeof(aux));
			
            strncpy(aux, linha + 7, 3);
			mem->mem[i].rt = strtol(aux, NULL, 2);
			memset(aux, '\0', sizeof(aux));
			
            strncpy(aux, linha + 10, 6);
			mem->mem[i].imm = extende_converte(aux);
			//mem->mem[i].imm = strtol(aux, NULL, 2);
			memset(aux, '\0', sizeof(aux));
			
        } else if (mem->mem[i].tipo_inst == 'J') {
            // Instrução do tipo J
			
            strncpy(aux, linha + 9, 7);
			mem->mem[i].addr = strtol(aux, NULL, 2);
			memset(aux, '\0', sizeof(aux));
        }
        
        i++;
    }
//-----------------------------------------------------------------------------------------
    fclose(file); 

    mem->tamanho = i;

    return i;
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

int ULA(int opcode, int funct, int a, int b){
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
		case 8:
			return a-b;
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

void imprime_mem(struct memoria *mem, int j) {
    if (mem->mem[j].tipo_inst == 'R') {
        printf("[%i]:", j);
        printf("Instrucao: %s \n", mem->mem[j].inst_char);
        printf("    Tipo: %c \n", mem->mem[j].tipo_inst);
        printf("    opcode: %d \n", mem->mem[j].opcode);
        printf("    rs: %d \n", mem->mem[j].rs);
        printf("    rt: %d \n", mem->mem[j].rt);
        printf("    rd: %d \n", mem->mem[j].rd);
        printf("    funct: %d \n\n", mem->mem[j].funct);
    } else {
        if (mem->mem[j].tipo_inst == 'I') {
            printf("[%i]:", j);
            printf("Instrucao: %s \n", mem->mem[j].inst_char);
            printf("    Tipo: %c \n", mem->mem[j].tipo_inst);
            printf("    opcode: %d \n", mem->mem[j].opcode);
            printf("    rs: %d \n", mem->mem[j].rs);
            printf("    rt: %d \n", mem->mem[j].rt);
            printf("    imm: %d \n\n", mem->mem[j].imm);
        } else {
            if (mem->mem[j].tipo_inst == 'J') {
                printf("[%i]:", j);
                printf("Instrucao: %s \n", mem->mem[j].inst_char);
                printf("    Tipo: %c \n", mem->mem[j].tipo_inst);
                printf("    opcode: %d \n", mem->mem[j].opcode);
                printf("    addr: %d", mem->mem[j].addr);
            }
        }
    }
}