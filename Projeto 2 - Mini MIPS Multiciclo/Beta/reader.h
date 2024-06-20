#define MAX 256
#define TAMANHO 16

struct instrucao {
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
    char linhas[MAX][TAMANHO + 1];
    int tamanho;
	//ADICIONEI ESSA VARIAVEL PRA SABER SE O QUE ESTA ARMAZENADO É UMA INSTRUÇÃO OU UM DADO
	int tipo[MAX]; //Instrucao (1) - Dados (2)
};

struct reg_inst {
	char inst_char[17];
    struct instrucao inst;
};

struct reg_mem {
    int dados;
};

struct reg_ab {
    int reg_a;
    int reg_b;
};

struct reg_ula {
    int saida;
};

struct controle_pc {
    int pc_soma;
    int saida_ula;
    int jump;
};

int lerEArmazenarArquivo(const char *filename, struct memoria *mem, int max_linhas);
int ULA(int opcode, int funct, int a, int b);
void imprime_mem(struct memoria *mem, int j);
void imprime_reg(int registradores[], struct reg_ab ab);
void decodificar(struct reg_inst *inst);
char tipo(const char opcode[]);
int extende_converte(const char *imm);
void executa_ciclos(int *ciclos, int *registradores, struct reg_ab *ab, struct reg_inst inst, struct controle_pc *pc, struct reg_mem *rmem, struct memoria *mem);
char *escolhe_registrador(int reg);
void salva_asm(struct memoria mem);