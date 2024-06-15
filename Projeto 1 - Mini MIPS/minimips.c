#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "reader.h"
#include <math.h>


FILE *carrega_memoria(char *nome){

    FILE *aux=NULL;

    aux = fopen(nome,"r");

    if(aux == NULL) {
        printf("Arquivo inválido!\n");
    }
    else { 
        printf("Arquivo aberto com sucesso!!\n");
    }
    return aux;

}

struct memoria_instrucao *decodifica_memoria(FILE *arquivo) {

    FILE *aux = arquivo;
    struct instrucao *auxiliar = malloc (sizeof(struct instrucao));
    struct memoria_instrucao *instructions = malloc (sizeof(struct memoria_instrucao));
    char linha[17], caractere;
    int contador=0, aux_cont=0;


    instructions->mem_inst = (struct instrucao*) malloc (instructions->tamanho*sizeof(struct instrucao));


    while ((caractere = fgetc(aux)) != EOF) { // lê todos os caracteres do arquivo
        if(caractere != '\n') { // só pega os caracteres que não seja o enter
            linha[contador] = caractere;
            contador++;
        }
        else{
            strcpy(instructions->mem_inst[aux_cont].inst_char, linha);
            contador = 0;
            aux_cont++;

        }
    }

    instructions->tamanho = aux_cont; // Pega o número de instruções que tem no arquivo.
    aux_cont = 0;
    

    return instructions;
}

void imprimir_memoria(struct memoria_instrucao *mem) {

    int contador = 0;

    while(contador < 256) {
        printf("Memória [%d]: %s\n", contador, mem->mem_inst[contador].inst_char);
        contador++;
    }
}

struct memoria_instrucao *parser(struct memoria_instrucao *mem) {

    struct memoria_instrucao *aux = mem;
    struct instrucao auxiliar;
    char opcode[5], rs[4], rt[4], rd[4], funct[4], imm[7]; // variáveis de comparação.
    int contador = 0;

     while(contador < 256) {

        strncpy(opcode, aux->mem_inst[contador].inst_char, 4);
        opcode[4] = '\0';

        if (strcmp(opcode, "0000") == 0) { // tipo R
        aux->mem_inst[contador].tipo_inst = 'R';
        auxiliar = tipoR(aux->mem_inst[contador].inst_char);
        aux->mem_inst[contador] = auxiliar;

      } else if (strcmp(opcode, "0100") == 0 || strcmp(opcode, "1011") == 0 || strcmp(opcode, "1111") == 0 || strcmp(opcode, "1000") == 0)  { // tipo I
        aux->mem_inst[contador].tipo_inst = 'I';
        auxiliar = tipoI(aux->mem_inst[contador].inst_char);
        aux->mem_inst[contador] = auxiliar;

        } else if (strcmp(opcode, "0010") == 0) { // tipo J
        aux->mem_inst[contador].tipo_inst = 'J';
        auxiliar = tipoJ(aux->mem_inst[contador].inst_char);
        aux->mem_inst[contador] = auxiliar;

        } else {
//        printf("Instrução Inválida, tipo não encontrado");
    }
    
//       printf("Tipo: %c\n", aux->mem_inst[contador].tipo_inst);


        contador++;
}


    return aux;
}

struct memoria_dados *cria_dados() {
    struct memoria_dados *aux = malloc (sizeof(struct memoria_dados));

    aux->mem_dados = (struct dado*) malloc (sizeof(struct dado) * 256);
    aux->tamanho = 256;

    return aux;
}

void imprime_dados(struct memoria_dados *data) {
    int contador = 0;

    while(contador < 256) {
        printf("Dado [%d]: %d\n", contador, data->mem_dados[contador].dado); // arrumar essa parte aqui.
        contador++;
    }
}

struct registradores *cria_registrador(){

    struct registradores *aux = NULL;
    aux = (struct registradores*) malloc (sizeof(struct registradores) * 8);

    return aux;
}

void imprime_registradores(struct registradores *regs) {
    int contador = 0;

    while(contador < 8){
        printf("Registrador [%d]: %d\n", contador, regs[contador].valor);
        contador++;
    }

}

int binario_decimal(char *binario) {
    int tamanho = strlen(binario), decimal = 0;

    for (int i = tamanho - 1; i >= 0; i--) {
        if (binario[i] == '1') {
            decimal += pow(2, tamanho - i - 1);
        } else if (binario[i] != '0') {
            return -1; // Retornando um valor de erro
        }
    
    }

    return decimal;
}

struct instrucao tipoR(char *inst_char) {
    struct instrucao aux;
    char opcode[5], rs[4], rt[4], rd[4], funct[4];
    char *aux_char = inst_char;
    int contador = 0;

//    printf("Instrução carregada: %s\n", inst_char);
    
    strncpy(opcode, aux_char, 4);
    opcode[4] = '\0';
    aux.opcode = binario_decimal(opcode);
    strncpy(rs, aux_char + 4, 3);
    rs[3] = '\0';
    aux.rs = binario_decimal(rs);
    strncpy(rt, aux_char + 7, 3);
    rt[3] = '\0';
    aux.rt = binario_decimal(rt);
    strncpy(rd,aux_char + 10, 3);
    rd[3] = '\0';
    aux.rd = binario_decimal(rd);
    strncpy(funct, aux_char + 13, 3);
    funct[3] = '\0';
    aux.funct = binario_decimal(funct);
//    printf("Opcode: %s\nRS: %s\nRT: %s\nRD: %s\nFunct: %s\n", opcode, rs, rt, rd, funct); // Mostra as funções em binário
//    printf("Decodificadas - Opcode: %d - RS: %d - RT: %d - RD: %d - Funct: %d\n", aux.opcode, aux.rs, aux.rt, aux.rd, aux.funct); // Mostra em decimal.
    strcpy(aux.inst_char, inst_char);
    return aux;

}


struct instrucao tipoI(char *inst_char) {
    struct instrucao aux;
    char opcode[5], rs[4], rt[4], imm[7];
    char *aux_char = inst_char;
    int contador = 0;

//    printf("Instrução carregada: %s\n", inst_char);
    
    strncpy(opcode, aux_char, 4);
    opcode[4] = '\0';
    aux.opcode = binario_decimal(opcode);
    strncpy(rs, aux_char + 4, 3);
    rs[3] = '\0';
    aux.rs = binario_decimal(rs);
    strncpy(rt, aux_char + 7, 3);
    rt[3] = '\0';
    aux.rt = binario_decimal(rt);
    strncpy(imm,aux_char + 10, 6);
    imm[6] = '\0';
    aux.imm = binario_decimal(imm);

//    printf("Opcode: %s\nRS: %s\nRT: %s\nImm: %s\n", opcode, rs, rt, imm); // Mostra as funções em binário
//    printf("Decodificadas - Opcode: %d - RS: %d - RT: %d - Imm: %d\n", aux.opcode, aux.rs, aux.rt, aux.imm); // Mostra em decimal.
    strcpy(aux.inst_char, inst_char);
    return aux;

}

struct instrucao tipoJ(char *inst_char) {
    struct instrucao aux;
    char opcode[5], addr[8];
    char *aux_char = inst_char;
    int contador = 0;

//    printf("Instrução carregada: %s\n", inst_char);
    
    strncpy(opcode, aux_char, 4);
    opcode[4] = '\0';
    aux.opcode = binario_decimal(opcode);
    strncpy(addr, aux_char + 10, 6);
    addr[7] = '\0';
    aux.addr = binario_decimal(addr);

//    printf("Opcode: %s\nADR: %s\n", opcode, addr); // Mostra as funções em binário
//    printf("Decodificadas - Opcode: %d - ADR: %d\n", aux.opcode, aux.addr); // Mostra em decimal.

    strcpy(aux.inst_char, inst_char);
    return aux;

}

void executa_instrucao(struct memoria_instrucao *mem, int program_counter, struct registradores *regs) {
    struct memoria_instrucao *aux = mem;
    int resultado;
    
    switch(aux->mem_inst[program_counter].opcode) { //  ULA.
        case 0: // tipo R
        printf("-----Instrução a ser executada-----\nTipo: R\n Opcode [%d] - RS [%d] - RT [%d] - RD [%d] - Funct [%d]\n", aux->mem_inst[program_counter].opcode, aux->mem_inst[program_counter].rs, aux->mem_inst[program_counter].rt, aux->mem_inst[program_counter].rd, aux->mem_inst[program_counter].funct);
            switch(aux->mem_inst[program_counter].funct) {
                case 0: // soma
                resultado = regs[aux->mem_inst[program_counter].rs].valor + regs[aux->mem_inst[program_counter].rt].valor;
                regs[aux->mem_inst[program_counter].rd].valor = resultado;
                break;
                case 2: // subtrai
                resultado = regs[aux->mem_inst[program_counter].rs].valor - regs[aux->mem_inst[program_counter].rt].valor;
                regs[aux->mem_inst[program_counter].rd].valor = resultado;
                break;
                case 4: // and
                resultado = regs[aux->mem_inst[program_counter].rs].valor & regs[aux->mem_inst[program_counter].rt].valor;
                regs[aux->mem_inst[program_counter].rd].valor = resultado;
                break;
                case 5: // or
                resultado = regs[aux->mem_inst[program_counter].rs].valor | regs[aux->mem_inst[program_counter].rt].valor;
                regs[aux->mem_inst[program_counter].rd].valor = resultado;
                break;
            }
        break;

        case 4: // tipo I - addi
        printf("-----Instrução a ser executada-----\nTipo: I\n Opcode [%d] - RS [%d] - RT [%d] - Imm [%d]\n", aux->mem_inst[program_counter].opcode, aux->mem_inst[program_counter].rs, aux->mem_inst[program_counter].rt, aux->mem_inst[program_counter].imm);
        resultado = regs[aux->mem_inst[program_counter].rs].valor + aux->mem_inst[program_counter].imm;
        regs[aux->mem_inst[program_counter].rt].valor = resultado;
        break;

    }
}


