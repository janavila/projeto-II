#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reader.h"

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
    printf("Reg [A]: %d\nReg [B]: %d", regs.reg_a, regs.reg_b);

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