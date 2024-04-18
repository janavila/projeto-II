#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reader.h"


void main () {

    int choice=-1;
    char nome[50];
    FILE *memoria;
    struct memoria_instrucao *instructions;
    struct memoria_dados *data_memory;
    struct registrador *regs;

    do{
    printf("----MINI MIPS----\n");
    printf("1) Carregar Memória\n2) Imprimir Memória\n3) Imprimir Registradores\n4) Imprimir todo o simulador\n5) Salvar .asm\n6) Salvar .mem\n7) Executar Programa (run)\n8) Executa uma instrução (Step)\n9) Volta uma instrução (back)\n0) Sair\n-------------\nOpção: ");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
        printf("Diga o nome do arquivo (com a extensão .mem): ");
        //scanf("%s", nome);
        strcpy(nome,"programaTestaInstrucoes.mem");
        memoria = carrega_memoria(nome); // carrega as informações do arquivo.
        instructions = decodifica_memoria(memoria); // passa as informações para a struct.
        instructions = parser(instructions); // códifica o tipo da instrução.
        data_memory = cria_dados(); // cria a memória de dados.
        regs = cria_registrador(); // cria registradores;
        break;
        case 2:
        imprimir_memoria(instructions);
        break;
        case 3:
        imprime_registradores(regs);
        break;
        case 4:
        imprimir_memoria(instructions);
        imprime_dados(data_memory);
        imprime_registradores(regs);
        break;
        case 5:
        break;
        case 6:
        break;
        case 7:
        break;
        case 8:
        //executa_instrucao(instructions, data_memory, regs);
        break;
        case 9:
        break;
        case 0:
        printf("Obrigado por utilizar!!\n");
        break;
    };
    }while (choice != 0);


    fclose(memoria);
}