#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 256
#define TAMANHO 16

struct instrucao {
    char inst_char[17];
    char tipo_inst;
    int opcode; 
    int rs;
    int rt;
    int rd;
    int funct;
    int imm;
    int addr;
};

struct memoria_instrucao {
    struct instrucao mem_inst[MAX];
    int tamanho;
};

char tipo(const char opcode[]);
int lerEArmazenarArquivo(const char *filename, struct memoria_instrucao *mem_inst, int max_lines);
int result_ula(int opcode, int funct, int a, int b);