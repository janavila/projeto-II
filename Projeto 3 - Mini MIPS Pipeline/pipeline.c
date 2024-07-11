#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "reader.h"

void carrega_inst(struct memoria_instrucao *mem_inst){
	char nome_arquivo[32];
	FILE *file;
    char linha[TAMANHO + 2];
    int i = 0;
	int max_linhas = MAX;
	
	printf("Nome do arquivo: ");
    scanf("%s", nome_arquivo);
	
	file = fopen(nome_arquivo, "r");

    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
    }else{
	
	 // Le o arquivo e armazena na matriz
	
    while (fgets(linha, sizeof(linha), file) && i < max_linhas) {
        linha[strcspn(linha, "\n")] = '\0'; 
        strncpy(mem_inst->mem_inst[i].inst_char, linha, TAMANHO);
        memset(mem_inst->mem_inst[i].inst_char + strlen(linha), ' ', TAMANHO - strlen(linha));
		mem_inst->mem_inst[i].inst_char[TAMANHO] = '\0'; 
        
        // Decodifica a instrução e armazena na struct
        char opcode[5];
        strncpy(opcode, linha, 4);
        opcode[4] = '\0'; 
		char aux[8];
        
        mem_inst->mem_inst[i].tipo_inst = tipo(opcode);
        mem_inst->mem_inst[i].opcode = strtol(opcode, NULL, 2);
        
        if (mem_inst->mem_inst[i].tipo_inst == 'R') {
//----------------------------------------------------------------------
		// Instrução do tipo R
			
			strncpy(aux, linha + 4, 3);
			mem_inst->mem_inst[i].rs = strtol(aux, NULL, 2);
			memset(aux, '\0', sizeof(aux));
			
            strncpy(aux, linha + 7, 3);
			mem_inst->mem_inst[i].rt = strtol(aux, NULL, 2);
			memset(aux, '\0', sizeof(aux));
			
            strncpy(aux, linha + 10, 3);
			mem_inst->mem_inst[i].rd = strtol(aux, NULL, 2);
			memset(aux, '\0', sizeof(aux));
			
            strncpy(aux, linha + 13, 3);
			mem_inst->mem_inst[i].funct = strtol(aux, NULL, 2);
			memset(aux, '\0', sizeof(aux));
			
        } else if (mem_inst->mem_inst[i].tipo_inst == 'I') {
            // Instrução do tipo I
			
            strncpy(aux, linha + 4, 3);
			mem_inst->mem_inst[i].rs = strtol(aux, NULL, 2);
			memset(aux, '\0', sizeof(aux));
			
            strncpy(aux, linha + 7, 3);
			mem_inst->mem_inst[i].rt = strtol(aux, NULL, 2);
			memset(aux, '\0', sizeof(aux));
			
            strncpy(aux, linha + 10, 6);
			mem_inst->mem_inst[i].imm = extende_converte(aux);
			memset(aux, '\0', sizeof(aux));
			
        } else if (mem_inst->mem_inst[i].tipo_inst == 'J') {
            // Instrução do tipo J
			
            strncpy(aux, linha + 9, 7);
			mem_inst->mem_inst[i].addr = strtol(aux, NULL, 2);
			memset(aux, '\0', sizeof(aux));
        }
        
        i++;
    }
//-----------------------------------------------------------------------------------------
    fclose(file); 

    mem_inst->tamanho = i;
	printf("Arquivo carregado com sucesso!\n");
	}
}

char tipo(const char opcode[]){
    if (strcmp(opcode, "0010") == 0) {
        return 'J';
    } else {
        if(strcmp(opcode, "0000") != 0){
            return 'I';
        } else {
            return 'R';
        }
    }
}

int extende_converte(const char *imm){
	int decimal = 0;
	int tamanho = 0;
	
	char extendido[9];
	
	//EXTENDE PARA 8 BITS REPETINDO O MAIS SIGNIFFICATIVO
	strncpy(extendido, imm, 1);
	strncpy(extendido + 1, imm, 1);
	strncpy(extendido + 2, imm, 6);
	extendido[8] = '\0';
	
	tamanho = strlen(extendido) - 1;
	
	//Negativo
	if(extendido[0]=='1'){
		
		//Subtraindo 1
		while(tamanho>0 && extendido[tamanho]=='0'){
			tamanho--;
		}
		if (tamanho > 0) {
			extendido[tamanho] = '0'; // troca o primeiro 1 encontrado por 0
		}
		for(tamanho;tamanho<strlen(extendido);tamanho++){
		if(tamanho+1<=strlen(extendido)-1 && extendido[tamanho+1]=='0'){
			extendido[tamanho+1] = '1';
		}
		}
		
		//Inverter os bits
		for(int i = 0;i < strlen(extendido);i++){
			if(extendido[i]=='0'){
				extendido[i] = '1';
			}else if(extendido[i]=='1'){
				extendido[i] = '0';
			}
		}
		decimal = -strtol(extendido, NULL, 2);
		//Positivo
	}else if(extendido[0]=='0'){
		decimal = strtol(extendido, NULL, 2);
	}
	
	return decimal;
}

void carrega_dados(struct memoria_dados *mem_dados){
	FILE *mem = NULL;
    int contador = 0, aux_contador = 0;
    char nome[50], aux[10], num;

    printf("Nome do arquivo da memoria de dados: ");
    scanf("%s", nome);

    mem = fopen(nome, "r");

    while ((num = fgetc(mem)) != EOF) {
        if(num != '\n') {
            aux[contador] = num;
            contador++;
        }
        else{
            mem_dados->dados[aux_contador] = atoi(aux);
            contador = 0;
            aux_contador++;
            memset(aux, '\0', sizeof(aux));
        }

    }
	printf("Arquivo carregado com sucesso!\n");
}

void imprime_mem_inst(struct memoria_instrucao *mem_inst){
	printf("\nMemoria de instrucoes:\n");
	int j;
    for (int j = 0; j < 256; j++) {
		if (mem_inst->mem_inst[j].tipo_inst == 'R') {
			printf("[%i]:", j);
			printf("Instrucao: %s \n", mem_inst->mem_inst[j].inst_char);
			printf("    Tipo: %c \n", mem_inst->mem_inst[j].tipo_inst);
			printf("    opcode: %d \n", mem_inst->mem_inst[j].opcode);
			printf("    rs: %d \n", mem_inst->mem_inst[j].rs);
			printf("    rt: %d \n", mem_inst->mem_inst[j].rt);
			printf("    rd: %d \n", mem_inst->mem_inst[j].rd);
			printf("    funct: %d \n\n", mem_inst->mem_inst[j].funct);
		} else {
			if (mem_inst->mem_inst[j].tipo_inst == 'I') {
				printf("[%i]:", j);
				printf("Instrucao: %s \n", mem_inst->mem_inst[j].inst_char);
				printf("    Tipo: %c \n", mem_inst->mem_inst[j].tipo_inst);
				printf("    opcode: %d \n", mem_inst->mem_inst[j].opcode);
				printf("    rs: %d \n", mem_inst->mem_inst[j].rs);
				printf("    rt: %d \n", mem_inst->mem_inst[j].rt);
				printf("    imm: %d \n\n", mem_inst->mem_inst[j].imm);
			} else {
				if (mem_inst->mem_inst[j].tipo_inst == 'J') {
					printf("[%i]:", j);
					printf("Instrucao: %s \n", mem_inst->mem_inst[j].inst_char);
					printf("    Tipo: %c \n", mem_inst->mem_inst[j].tipo_inst);
					printf("    opcode: %d \n", mem_inst->mem_inst[j].opcode);
					printf("    addr: %d", mem_inst->mem_inst[j].addr);
				}
			}
		}
	}
}

void imprime_mem_dados(struct memoria_dados *mem_dados){
	printf("\n\nMemoria de dados:\n");
	int j;
    for (int j = 0; j < 256; j++) {
        printf("[%i]: %d\t", j, mem_dados->dados[j]);
    }
	printf("\n\n");
}

void imprime_reg(struct registradores *reg){
	printf("Registradores:\n");
	int j;
	for (int j = 0; j < 8; j++) {
        printf("[%i]: %d\n", j, reg->dados[j]);
    }
	printf("\n");
}

void executar(struct instrucao *inst, struct memoria_dados *mem_dados, struct registradores *reg, struct controle *controle, struct result_ula *ula){
	
}

int ula(struct instrucao *inst, int a, int b){
	switch(inst->opcode){
		case 0:
			switch(inst->funct){
				case 0:
				return a+b;
				break;
				case 2:
				return a-b;
				break;
				case 4:
				return a&b;
				break;
				case 5:
				return a|b;
				break;
			}
		case 4:
			return a+b;
		break;
		case 8:
			return a-b;
		break;
		case 11:
			return a+b;
		break;
		case 15:
			return a+b;
		break;
		default:
		return 0;
	}
	printf("\nInstrucao concluida!\n");
}

void mostra_asm(struct instrucao *aux_reginst){
	
    char tipo[20];

    switch(aux_reginst->opcode) { 
        case 0:
            switch(aux_reginst->funct) {
                case 0:
                strcpy(tipo, "add");
                break;
                case 2:
                strcpy(tipo, "sub");
                break;
                case 4:
                strcpy(tipo, "and");
                case 5:
                strcpy(tipo, "or");
                break;
            }
        printf("%s %s, %s, %s\n", tipo, escolhe_registrador(aux_reginst->rd), escolhe_registrador(aux_reginst->rs), escolhe_registrador(aux_reginst->rt));
        break;
        case 2:
        strcpy(tipo,"j");
        printf("%s %d\n", tipo, aux_reginst->addr);
        break;
        case 4:
        strcpy(tipo,"addi");
        printf("%s %s, %s, %d\n", tipo, escolhe_registrador(aux_reginst->rt), escolhe_registrador(aux_reginst->rs), aux_reginst->imm);
        break;
        case 8:
        strcpy(tipo, "beq");
        printf("%s %s, %s, %d\n", tipo, escolhe_registrador(aux_reginst->rt), escolhe_registrador(aux_reginst->rs), aux_reginst->imm);
        break;
        case 11:
        strcpy(tipo, "lw");
        printf("%s %s, %d(%s)\n", tipo, escolhe_registrador(aux_reginst->rt), aux_reginst->imm, escolhe_registrador(aux_reginst->rs));
        break;
        case 15:
        strcpy(tipo,"sw");
        printf("%s %s, %d(%s)\n", tipo, escolhe_registrador(aux_reginst->rt), aux_reginst->imm, escolhe_registrador(aux_reginst->rs));
        break;
    }
}

char *escolhe_registrador(int reg){

    switch(reg) {
        case 0: return "$0";
        case 1: return "$r1";
        case 2: return "$r2";
        case 3: return "$r3";
        case 4: return "$r4";
        case 5: return "$r5";
        case 6: return "$r6";
        case 7: return "SWs";
        case 8: return "LEDs";
    }

    return "Error"; 

}

void salva_asm(struct memoria_instrucao *mem_inst){
    FILE *save = NULL;
    save = fopen("instrucoes.asm", "w");
    struct memoria_instrucao aux = *mem_inst;
    int contador = 0, tamanho = mem_inst->tamanho;
    char tipo[20];

    if(save != NULL) {
    printf("Arquivo salvo com sucesso!\n");

    while (contador < tamanho) {

    switch(aux.mem_inst[contador].opcode) { // verifica qual operação vai ser realizada e salva na variável TIPO;
        case 0:
            switch(aux.mem_inst[contador].funct) {
                case 0:
                strcpy(tipo, "add");
                break;
                case 2:
                strcpy(tipo, "sub");
                break;
                case 4:
                strcpy(tipo, "and");
                case 5:
                strcpy(tipo, "or");
                break;
            }
        fprintf(save,"%s %s, %s, %s\n", tipo, escolhe_registrador(aux.mem_inst[contador].rd), escolhe_registrador(aux.mem_inst[contador].rs), escolhe_registrador(aux.mem_inst[contador].rt));
        break;
        case 2:
        strcpy(tipo,"j");
        fprintf(save,"%s %d\n", tipo, aux.mem_inst[contador].addr);
        break;
        case 4:
        strcpy(tipo,"addi");
        fprintf(save,"%s %s, %s, %d\n", tipo, escolhe_registrador(aux.mem_inst[contador].rt), escolhe_registrador(aux.mem_inst[contador].rs), aux.mem_inst[contador].imm);
        break;
        case 8:
        strcpy(tipo, "beq");
        fprintf(save,"%s %s, %s, %d\n", tipo, escolhe_registrador(aux.mem_inst[contador].rt), escolhe_registrador(aux.mem_inst[contador].rs), aux.mem_inst[contador].imm);
        break;
        case 11:
        strcpy(tipo, "lw");
        fprintf(save,"%s %s, %d(%s)\n", tipo, escolhe_registrador(aux.mem_inst[contador].rt), aux.mem_inst[contador].imm, escolhe_registrador(aux.mem_inst[contador].rs));
        break;
        case 15:
        strcpy(tipo,"sw");
        fprintf(save,"%s %s, %d(%s)\n", tipo, escolhe_registrador(aux.mem_inst[contador].rt), aux.mem_inst[contador].imm, escolhe_registrador(aux.mem_inst[contador].rs));
        break;
    }

    contador++;

    }
    }

    else {
        printf("Erro salvar o arquivo!!\n");
    }

    fclose(save);

}

void salva_dat(struct memoria_dados *data){
    FILE *save_dat = NULL;
    struct memoria_dados *aux = data;
	int contador = 0;

    save_dat = fopen("dados.dat", "w");

    if (save_dat != NULL) { // verifica se os arquivos foram abertos com sucesso.
    
    while(contador < 256) {
        fprintf(save_dat, "%d\n", aux->dados[contador]);
        contador++;
    }

    printf("Arquivo salvo com sucesso!");
    }

    else {
        printf("Erro em salvar o arquivo!!");
    }

    fclose(save_dat);

}

void salva_estado(struct estado *estado, struct memoria_instrucao *mem_inst, struct memoria_dados *mem_dados, struct registradores *reg, struct controle *pc){	
 	struct nodo *novo = malloc(sizeof(struct nodo));
	
	estado->mem_inst = *mem_inst;
 	estado->mem_dados = *mem_dados;
 	estado->reg = *reg;	
    estado->pc = *pc;
	
}

void back(struct desc_Pilha *estado, struct memoria_instrucao *mem_inst, struct memoria_dados *mem_dados, struct registradores *reg, struct controle *pc){
    *mem_inst = estado->primeiro->info->mem_inst;
    *mem_dados = estado->primeiro->info->mem_dados;
    *reg = estado->primeiro->info->reg;
    *pc = estado->primeiro->info->pc;
	printf("Voltando uma instrucao!");
}

//-------------------------------------------------------------------------------------------------------------------------------------------

struct desc_Pilha * CriaPilha(){
	struct desc_Pilha * novaPilha = (struct desc_Pilha*)malloc(sizeof(struct desc_Pilha));
	novaPilha->primeiro=NULL;
	novaPilha->tamanho=0;
	return novaPilha;
}

struct nodo * CriaNodo(struct estado *estados){
	struct nodo *novoNodo = (struct nodo*)malloc(sizeof(struct nodo));
	novoNodo->info=estados;
	novoNodo->prox=NULL;
	return novoNodo;
}

struct desc_Pilha * PUSH(struct desc_Pilha * minhaPilha, struct nodo * novoNodo){
	if(minhaPilha->tamanho==0){
		minhaPilha->primeiro=novoNodo;
		minhaPilha->tamanho++;
		return minhaPilha;
	}else{
		novoNodo->prox=minhaPilha->primeiro;
		minhaPilha->primeiro=novoNodo;
		minhaPilha->tamanho++;
		return minhaPilha;
	}
}

struct desc_Pilha * POP(struct desc_Pilha * minhaPilha){
		if(minhaPilha->tamanho==1){
			struct nodo * aux = minhaPilha->primeiro;
			minhaPilha->primeiro=NULL;
			free(aux);
			minhaPilha->tamanho--;
			return minhaPilha;
		}else{
			struct nodo * aux = minhaPilha->primeiro;
			minhaPilha->primeiro=aux->prox;
			aux->prox=NULL;
			free(aux);
			minhaPilha->tamanho--;
			return minhaPilha;
		}
}

int EMPTY(struct desc_Pilha * minhaPilha){
	if((minhaPilha->tamanho==0)){
		return 0;
	}else{
		return 1;
	}
}

void Imprime(struct desc_Pilha * minhaPilha){
		struct nodo* aux = minhaPilha->primeiro;
		while(aux!=NULL){
			printaNodo(aux);
			aux=aux->prox;
	}
}

void printaNodo(struct nodo *nodoAtual){
	printaEstado(nodoAtual->info);
}

void printaEstado(struct estado *estado){
	printf("Teste\n");
	printf("%d\n", estado->pc.pc);
	printf("%d\n", estado->reg.dados[0]);
	printf("%s\n", estado->mem_inst.mem_inst[0].inst_char);
}

void stage1(struct memoria_instrucao inst, int pc, struct instrucao *reg_inst){
	printf("Estagio 1: Busca da instrucao [BI]\n");
	printf("PC: %d\n", pc);
	*reg_inst = inst.mem_inst[pc];
	printf("Instrucao: %d\n", inst.mem_inst[pc].inst_char); // NÃO ESTÁ TENDO NADA NO INST_CHAR.
	mostra_asm(reg_inst);
	//controle->pc++;
}

void stage2(struct instrucao *inst,  struct registradores *reg, struct ab *ab){
	printf("\nTESTE: %s\n", inst->tipo_inst);
	switch(inst->tipo_inst){
		case 'J':
			ab->reg_a = inst->addr;
		break;
		
		case 'I':
			switch(inst->opcode){
				//ADDI
				case 4:
					ab->reg_a = reg->dados[inst->rs];
					ab->reg_b = inst->imm;
					ab->reg_c = inst->rt;
				break;
				//BEQ
				case 8:
					ab->reg_a = reg->dados[inst->rs];
					ab->reg_b = reg->dados[inst->rt];
					ab->reg_c = inst->imm;
				break;
				//LW
				case 11:
					ab->reg_a = reg->dados[inst->rs];
					ab->reg_b = inst->imm;
					ab->reg_c = inst->rt;
				break;
				//SW
				case 15:
					ab->reg_a = reg->dados[inst->rs];
					ab->reg_b = inst->imm;
					ab->reg_c = inst->rt;
				break;
			}
		break;
		
		case 'R':
			ab->reg_a = reg->dados[inst->rs];
			ab->reg_b = reg->dados[inst->rt];
			ab->funct = inst->funct;
			ab->reg_c = inst->rd;
		break;
	}
	ab->opcode = inst->opcode;
	ab->inst = *inst;
	printf("\nEstagio 2: \n");
	printf("Reg a: %d\n", ab->reg_a);
	printf("Reg b: %d\n", ab->reg_b);
	printf("Reg c: %d\n", ab->reg_c);
}

void stage3(struct ab *ab, struct result_ula *rula){
	switch(ab->opcode){
		//TIPO R
		case 0:
			switch(ab->funct){
			//ADD
			case 0:
				rula->resultado = ula(&ab->inst,ab->reg_a,ab->reg_b);
				rula->reg_c = ab->reg_c;
			break;
			//SUB
			case 2:
				rula->resultado =  ula(&ab->inst,ab->reg_a,ab->reg_b);
				rula->reg_c = ab->reg_c;
			break;
			//AND
			case 4:
				rula->resultado =	 ula(&ab->inst,ab->reg_a,ab->reg_b);
				rula->reg_c = ab->reg_c;
			break;
			//OR
			case 5:
				rula->resultado =  ula(&ab->inst,ab->reg_a,ab->reg_b);
				rula->reg_c = ab->reg_c;
			break;			
			}
		break;
		//Jump
		case 2:
			rula->resultado =  ab->reg_a;
		break;
		//ADDI
		case 4:
			rula->resultado =  ula(&ab->inst,ab->reg_a,ab->reg_b);
			rula->reg_c = ab->reg_c;
		break;
		//BEQ
		case 8:
			if(ula(&ab->inst,ab->reg_a,ab->reg_b)==0){
				rula->resultado = ab->reg_c;
			}else{
				rula->resultado = 1;
			}
		break;
		//LW
		case 11:
			rula->resultado =  ula(&ab->inst,ab->reg_a,ab->reg_b);
			rula->reg_c = ab->reg_c;
		break;
		//SW
		case 15:
			rula->resultado =  ula(&ab->inst,ab->reg_a,ab->reg_b);
			rula->reg_c = ab->reg_c;
		break;
	}
	printf("\nEstagio 3:\n");
	printf("Resultado ULA: %d\n", rula->resultado);
}

void stage4(struct instrucao *inst, struct memoria_dados *mem_dados, struct registradores *reg, struct controle *controle, struct result_ula *ula){
	
}

void stage5(struct instrucao *inst, struct memoria_dados *mem_dados, struct registradores *reg, struct controle *controle, struct result_ula *ula){
	
}