#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 99
#define MEM_SIZE 256
#define REG_SIZE 8

typedef struct {
    int size;
    unsigned char *data;
} MemoriaMIPS;

typedef struct {
    int size;
    unsigned char *data;
} RegistradoresMIPS;

void abrir_arquivo(char *filename) {
    // Tentativa de abrir o arquivo
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // Leitura do arquivo linha por linha
    char line[MAX];
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line); // Exibir linha na tela
    }

    // Fechar o arquivo
    fclose(file);
}

RegistradoresMIPS *inicializar_registradores() {
    RegistradoresMIPS *registradores = (RegistradoresMIPS *)malloc(sizeof(RegistradoresMIPS));
    if (registradores == NULL) {
        printf("Erro: Não foi possível alocar memória para os registradores do MIPS.\n");
        exit(1);
    }

    registradores->size = REG_SIZE;
    registradores->data = (unsigned char *)malloc(sizeof(unsigned char) * REG_SIZE);
    if (registradores->data == NULL) {
        printf("Erro: Não foi possível alocar memória para os dados dos registradores do MIPS.\n");
        free(registradores);
        exit(1);
    }

    // Inicializar todos os registradores com 0
    for (int i = 0; i < REG_SIZE; i++) {
        registradores->data[i] = 0;
    }

    return registradores;
}

MemoriaMIPS *inicializar_memoria() {
    MemoriaMIPS *memoria = (MemoriaMIPS *)malloc(sizeof(MemoriaMIPS));
    if (memoria == NULL) {
        printf("Erro: Não foi possível alocar memória para a memória do MIPS.\n");
        exit(1);
    }

    memoria->size = MEM_SIZE;
    memoria->data = (unsigned char *)malloc(sizeof(unsigned char) * MEM_SIZE);
    if (memoria->data == NULL) {
        printf("Erro: Não foi possível alocar memória para os dados da memória do MIPS.\n");
        free(memoria);
        exit(1);
    }

    // Inicializar todos os bytes da memória com 0
    for (int i = 0; i < MEM_SIZE; i++) {
        memoria->data[i] = 0;
    }

    return memoria;
}

int main() {
    int opcao;
    char filename[50];
	
	RegistradoresMIPS *registradores = inicializar_registradores();
	MemoriaMIPS *memoria = inicializar_memoria();

    do {
        printf("\nMenu:\n");
        printf("1 - Carregar arquivo .mem\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o nome do arquivo .mem: ");
                scanf("%49s", filename); // Limite de 49 caracteres para evitar buffer overflow
				printf("\n");
                abrir_arquivo(filename);
                break;
            case 0:
                printf("Saindo do programa.\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);
	
	//TESTE
	//registradores->data[1] = 42;
    //printf("Valor no registrador $1: %d\n", registradores->data[1]);
	
	//memoria->data[10] = 42;
    //printf("Valor no endereço 10: %d\n", memoria->data[10]);
	
	free(memoria->data);
    free(memoria);
	free(registradores->data);
    free(registradores);

	return 0;
}