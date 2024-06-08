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

struct memoria {
	struct instrucao mem[MAX];
    int tamanho;
};

struct reg_inst{
	struct instrucao inst;
};


int lerEArmazenarArquivo(const char *filename, struct memoria *mem, int max_linhas);
char tipo(const char opcode[]);
int extende_converte(const char *imm);
int ULA(int opcode, int funct, int a, int b);
void imprime_mem(struct memoria *mem, int j);