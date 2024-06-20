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

struct estado{
	struct memoria mem;
	struct reg_inst reginst;
	struct reg_mem regmem;
	struct reg_ab ab;
	struct reg_ula ula;
	struct controle_pc pc;
	int registradores[8];
	int ciclos;
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
void mostra_asm(struct reg_inst aux_reginst);
char *converte_binario(int num);
void salva_mem(struct memoria mem);
void salva_estado(int *ciclos, struct memoria *mem, struct estado *estado, struct reg_inst *reginst, struct reg_mem *regmem, struct reg_ab *ab, struct reg_ula *ula, struct controle_pc *pc, int *registradores);