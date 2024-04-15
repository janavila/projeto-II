#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "reader.h"


FILE *carrega_memoria(char *nome){

    FILE *aux=NULL;

    aux = fopen(nome,"r");

    if(aux == NULL) printf("Arquivo inválido!\n");
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
            printf("[%d]: %s\n",aux_cont,instructions->mem_inst[aux_cont].inst_char);
            aux_cont++;

        }
    }

    aux_cont = 0;

    return instructions;
}

void imprimir_memoria(struct memoria_instrucao *mem) {

    int contador = 0;

    while(contador < 256) {
        printf("Posição [%d]: %s\n", contador, mem->mem_inst[contador].inst_char);
        contador++;
    }
}

