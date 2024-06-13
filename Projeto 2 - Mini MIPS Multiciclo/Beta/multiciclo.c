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


void executa_ciclo();