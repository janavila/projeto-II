#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 256
#define TAMANHO 16

struct desc_Pilha{
struct nodo *primeiro;
int tamanho;
};

struct nodo{
struct nodo *prox;
struct estado *info;
};

struct instrucao{
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

struct memoria_instrucao{
    struct instrucao mem_inst[MAX];
    int tamanho;
};

struct memoria_dados{
	int dados[MAX];
};

struct registradores{
	int dados[8];
};

struct controle{
	int pc;
};

struct result_ula{
	int resultado;
	int reg_c;
};

struct ab{
	struct instrucao inst;
	int reg_a;
	int reg_b;
	int reg_c;
	int opcode;
	int funct;
};

struct estado{
	struct memoria_instrucao mem_inst;
	struct memoria_dados mem_dados;
	struct controle pc;
	struct registradores reg;
};

struct desc_Pilha * CriaPilha();
struct nodo * CriaNodo(struct estado *estado);
struct desc_Pilha * PUSH(struct desc_Pilha * minhaPilha, struct nodo * novoNodo);
struct desc_Pilha * POP(struct desc_Pilha * minhaPilha);
int EMPTY(struct desc_Pilha * minhaPilha);

void carrega_inst(struct memoria_instrucao *mem_inst);
char tipo(const char opcode[]);
int extende_converte(const char *imm);
void carrega_dados(struct memoria_dados *mem_dados);
void imprime_mem_inst(struct memoria_instrucao *mem_inst);
void imprime_mem_dados(struct memoria_dados *mem_dados);
void imprime_reg(struct registradores *reg);
void executar(struct instrucao *inst, struct memoria_dados *mem_dados, struct registradores *reg, struct controle *controle, struct result_ula *ula);
int ula(struct instrucao *inst, int a, int b);
void mostra_asm(struct instrucao *aux_reginst);
char *escolhe_registrador(int reg);
void salva_asm(struct memoria_instrucao *mem_inst);
void salva_dat(struct memoria_dados *data);
void salva_estado(struct estado *estado, struct memoria_instrucao *mem_inst, struct memoria_dados *mem_dados, struct registradores *reg, struct controle *pc);
void back(struct desc_Pilha *estado, struct memoria_instrucao *mem_inst, struct memoria_dados *mem_dados, struct registradores *reg, struct controle *pc);
void stage1(struct instrucao *inst, struct controle *controle, struct instrucao *reg_inst);
void stage2(struct instrucao *inst, struct registradores *reg, struct ab *ab);
void stage3(struct ab *ab, struct result_ula *ula);
void stage4(struct instrucao *inst, struct memoria_dados *mem_dados, struct registradores *reg, struct controle *controle, struct result_ula *ula);
void stage5(struct instrucao *inst, struct memoria_dados *mem_dados, struct registradores *reg, struct controle *controle, struct result_ula *ula);
	
//---------------------------------------------------------------------------------------------------------------------------

void Imprime(struct desc_Pilha * minhaPilha);
void printaNodo(struct nodo *nodoAtual);
void printaEstado(struct estado *estado);