#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REGSIZE 8
#define MEMSIZE 256
#define MAX_LINE_LENGTH 256

// Registradores
#define REG_ZERO 0
#define REG_R1 1
#define REG_R2 2
#define REG_R3 3
#define REG_R4 4
#define REG_R5 5
#define REG_R6 6
#define REG_SW 7
#define REG_LED 7

// Operações
#define OP_ADD 0
#define OP_SUB 1
#define OP_AND 2
#define OP_OR 3
#define OP_ADDI 4
#define OP_LW 5
#define OP_SW 6
#define OP_BEQ 7
#define OP_J 8

// Estrutura de controle para instruções
typedef struct {
    int opcode;
    int rs;
    int rt;
    int rd;
    int imm;
} Instruction;

// Funções para manipular registradores
void write_register(int reg, int data, int *registers) {
    if (reg != REG_ZERO && reg != REG_SW) // Não permite escrever no registrador zero ou SW
        registers[reg] = data;
}

int read_register(int reg, int *registers, int switch_value) {
    if (reg == REG_SW)
        return switch_value;
    return registers[reg];
}

// Função para executar instruções
void execute_instruction(Instruction instr, int *registers, int *memory, int *PC, int switch_value) {
    int result = 0;
    switch (instr.opcode) {
        case OP_ADD:
            result = read_register(instr.rs, registers, switch_value) + read_register(instr.rt, registers, switch_value);
            write_register(instr.rd, result, registers);
            break;
        case OP_SUB:
            result = read_register(instr.rs, registers, switch_value) - read_register(instr.rt, registers, switch_value);
            write_register(instr.rd, result, registers);
            break;
        case OP_AND:
            result = read_register(instr.rs, registers, switch_value) & read_register(instr.rt, registers, switch_value);
            write_register(instr.rd, result, registers);
            break;
        case OP_OR:
            result = read_register(instr.rs, registers, switch_value) | read_register(instr.rt, registers, switch_value);
            write_register(instr.rd, result, registers);
            break;
        case OP_ADDI:
            result = read_register(instr.rs, registers, switch_value) + instr.imm;
            write_register(instr.rt, result, registers);
            break;
        case OP_LW:
            result = memory[read_register(instr.rs, registers, switch_value) + instr.imm];
            write_register(instr.rt, result, registers);
            break;
        case OP_SW:
            memory[read_register(instr.rs, registers, switch_value) + instr.imm] = read_register(instr.rt, registers, switch_value);
            break;
        case OP_BEQ:
            if (read_register(instr.rs, registers, switch_value) == read_register(instr.rt, registers, switch_value))
                *PC += instr.imm * 2;
            break;
        case OP_J:
            *PC = instr.imm * 2;
            break;
    }
}

// Função para ler as instruções do arquivo
int load_instructions(const char *filename, int *memory) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Erro ao abrir o arquivo %s\n", filename);
        return -1;
    }

    int address = 0;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, file)) {
        char instruction_str[17]; // 16 caracteres para a instrução + 1 para o caractere nulo
        strncpy(instruction_str, line, 16); // Copia os primeiros 16 caracteres da linha
        instruction_str[16] = '\0'; // Adiciona o caractere nulo ao final da string

        int instruction1 = 0;
        int instruction2 = 0;
        for (int i = 0; i < 8; i++) {
            if (instruction_str[i] == '1') {
                instruction1 |= (1 << (7 - i)); // Define o bit em 1 na primeira parte da instrução
            } else if (instruction_str[i] != '0') {
                printf("Caractere inválido '%c' na linha %d\n", instruction_str[i], address);
                fclose(file);
                return -1;
            }
        }

        for (int i = 8; i < 16; i++) {
            if (instruction_str[i] == '1') {
                instruction2 |= (1 << (15 - i)); // Define o bit em 1 na segunda parte da instrução
            } else if (instruction_str[i] != '0') {
                printf("Caractere inválido '%c' na linha %d\n", instruction_str[i], address);
                fclose(file);
                return -1;
            }
        }

        memory[address++] = instruction1;
        memory[address++] = instruction2;
    }

    fclose(file);
    return 0;
}



void print_memory(int *memory, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d: %d\n", i, memory[i]);
    }
}

void print_registers(int *registers, int size) {
    for (int i = 0; i < size; i++) {
        printf("Reg[%d]: %d\n", i, registers[i]);
    }
}

void save_asm(const char *filename, int *memory, int size) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Erro ao abrir o arquivo %s\n", filename);
        return;
    }

    for (int i = 0; i < size; i++) {
        fprintf(file, "%d: %d\n", i, memory[i]);
    }

    fclose(file);
}

void save_mem(const char *filename, int *memory, int size) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Erro ao abrir o arquivo %s\n", filename);
        return;
    }

    for (int i = 0; i < size; i++) {
        fprintf(file, "%d\n", memory[i]);
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    int registers[REGSIZE] = {0}; // Inicializa registradores com zero
    int memory[MEMSIZE] = {0}; // Inicializa a memória com zero
    int PC = 0; // Inicializa o contador de programa
    int switch_value = 0; // Valor dos switches (SW)
    
    if (argc != 2) {
        printf("Uso: %s <arquivo de instruções .mem>\n", argv[0]);
        return 1;
    }

    if (load_instructions(argv[1], memory) != 0)
        return 1;

    int opcao;
    do {
        printf("\nMenu principal:\n");
        printf("1. Carregar memória\n");
        printf("2. Imprimir memória\n");
        printf("3. Imprimir registradores\n");
        printf("4. Imprimir todo o simulador\n");
        printf("5. Salvar .asm\n");
        printf("6. Salvar .mem\n");
        printf("7. Executa Programa (run)\n");
        printf("8. Executa uma instrução (Step)\n");
        printf("9. Volta uma instrução (Back)\n");
        printf("0. Sair\n");

        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Carregando memória...\n");
				if (load_instructions("inst.mem", memory) != 0) {
				printf("Erro ao carregar a memória.\n");
				} else {
				printf("Memória carregada com sucesso.\n");
				}
                break;
            case 2:
                print_memory(memory, MEMSIZE);
                break;
            case 3:
                print_registers(registers, REGSIZE);
                break;
            case 4:
                printf("Memória:\n");
                print_memory(memory, MEMSIZE);
                printf("Registradores:\n");
                print_registers(registers, REGSIZE);
                break;
            case 5:
                save_asm("program.asm", memory, MEMSIZE);
                printf("Memória salva como program.asm.\n");
                break;
            case 6:
                save_mem("program.mem", memory, MEMSIZE);
                printf("Memória salva como program.mem.\n");
                break;
            case 7:
                printf("Executando programa...\n");
                while (PC < MEMSIZE) {
                    int instr_word = memory[PC];
                    Instruction instr;
                    instr.opcode = (instr_word >> 4) & 0xF;
                    instr.rs = (instr_word >> 3) & 0x7;
                    instr.rt = (instr_word >> 2) & 0x7;
                    instr.rd = (instr_word >> 1) & 0x7;
                    instr.imm = (instr_word >> 1) & 0x3F;

                    execute_instruction(instr, registers, memory, &PC, switch_value);

                    PC += 2; // Avança para a próxima instrução (cada instrução ocupa 2 bytes na memória)
                }
                printf("Programa executado.\n");
                break;
            case 8:
                printf("Executando uma instrução...\n");
                if (PC < MEMSIZE) {
                    int instr_word = memory[PC];
                    Instruction instr;
                    instr.opcode = (instr_word >> 4) & 0xF;
                    instr.rs = (instr_word >> 3) & 0x7;
                    instr.rt = (instr_word >> 2) & 0x7;
                    instr.rd = (instr_word >> 1) & 0x7;
                    instr.imm = (instr_word >> 1) & 0x3F;

                    execute_instruction(instr, registers, memory, &PC, switch_value);

                    PC += 2; // Avança para a próxima instrução (cada instrução ocupa 2 bytes na memória)
                } else {
                    printf("Fim da memória alcançado.\n");
                }
                break;
            case 9:
                printf("Voltando uma instrução...\n");
                if (PC > 0) {
                    PC -= 2; // Volta para a instrução anterior
                } else {
                    printf("Início da memória alcançado.\n");
                }
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida\n");
        }
    } while (opcao != 0);

    return 0;
}
