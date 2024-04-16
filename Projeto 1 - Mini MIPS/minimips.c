#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "reader.h"


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

    instructions->tamanho = 256;
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
    struct instrucao *auxiliar = malloc (sizeof(struct instrucao));
    char opcode[5];
    int contador = 0;

     while(contador < 256) {

        strncpy(opcode, aux->mem_inst[contador].inst_char, 4);
        opcode[4] = '\0';

        if (strcmp(opcode, "0000") == 0) { // tipo R
        aux->mem_inst[contador].tipo_inst = 'R';
      } else if (strcmp(opcode, "0100") == 0 || strcmp(opcode, "1011") == 0 || strcmp(opcode, "1111") == 0 || strcmp(opcode, "1000") == 0)  { // tipo I
        aux->mem_inst[contador].tipo_inst = 'I';
        } else if (strcmp(opcode, "0010") == 0) { // tipo J
        aux->mem_inst[contador].tipo_inst = 'J';
        } else {
//            printf("Instrução Inválida, tipo não encontrado");
    }

//    printf("Tipo: %c\n", aux->mem_inst[contador].tipo_inst);


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





