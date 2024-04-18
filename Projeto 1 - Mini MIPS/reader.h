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

struct dado{
char dado_char[8];
int dado;
};

struct memoria_dados{
struct dado *mem_dados;
int tamanho;
};

struct registradores{
    int valor;
};



FILE *carrega_memoria(char *nome);
void imprimir_memoria(struct memoria_instrucao *mem);
struct memoria_instrucao *decodifica_memoria(FILE *arquivo);
struct memoria_instrucao *parser(struct memoria_instrucao *mem);
struct memoria_dados *cria_dados();
void imprime_dados(struct memoria_dados *data);
struct registradores *cria_registrador();
void imprime_registradores(struct registradores *regs);
struct instrucao tipoI(char *inst_char);
struct instrucao tipoJ(char *inst_char);
struct instrucao tipoR(char *inst_char);
int binario_decimal(char *binario);