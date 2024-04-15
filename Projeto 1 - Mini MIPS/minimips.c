#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "reader.h"


FILE *carrega_memoria(char *nome){

    FILE *aux=NULL;

    aux = fopen(nome,"r");

    if(aux == NULL) printf("Arquivo inválido!\n");
    else printf("Arquivo aberto com sucesso!!\n");

    return aux;

}

void imprimir_memoria(FILE *arquivo) {
    char instrucao[100];

    while (fgets(instrucao, sizeof(instrucao), arquivo) != NULL) {
    printf("%s", instrucao);
    }

}