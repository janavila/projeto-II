struct instrucao{
char inst_char[17], tipo_inst;
int opcode; 
int rs;
int rt;
int rd;
int funct;
int imm;
int addr;
};

struct memoria_instrucao{
struct instrucao *mem_inst;
int tamanho;
};
/*
struct dado{
char dado_char[8];
int dado;
};

struct memoria_dados{
struct instrucao *mem_dados;
int tamanho;
};

*/


FILE *carrega_memoria(char *nome);
void imprimir_memoria(struct memoria_instrucao *mem);
struct memoria_instrucao *decodifica_memoria(FILE *arquivo);
struct memoria_instrucao *parser(struct memoria_instrucao *mem);