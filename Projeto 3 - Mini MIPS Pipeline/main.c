#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reader.h"

//Separar em 5 partes
//BI: Busca da instrução 
//DI: Decodif. da instrução/Leitura do banco de regs. 
//EX: Execução/Cálculo do endereço
//MEM: acesso à memória
//ER: escrita no banco de registradores

//Só pode ser usado em cada estágio
/*
 Memória de instruções
 Portas de leitura do banco de registradores
 ULA
 Memória de dados
 Porta de escrita do banco de registradores
*/

int main() {
    int opt = -1, flag_estados = 1;
	int i = 0;
	
	struct memoria_instrucao mem_inst = {0};
	struct memoria_dados mem_dados = {0};
	struct registradores reg = {0};
	struct controle pc = {0};
	struct estado novo_estado;
	struct estado4 estado4 = {0};
	struct estado3 estado3 = {0};
	struct estado2 estado2 = {0};
	struct estado1 estado1 = {0};
	
	struct desc_Pilha *minhaPilha = CriaPilha();

    while (opt != 0) {
        printf("\n-------------MINI MIPS-------------\n");
		printf("1) Carregar Memoria de Instrucoes\n");
		printf("2) Carregar Memoria de Dados (.dat)\n");
		printf("3) Salvar arquivo .asm\n");
		printf("4) Salvar arquivos .dat\n");
		printf("5) Imprimir Memorias\n");
		printf("6) Imprimir Registradores\n");
		printf("7) Imprimir todo o simulador\n");
		printf("8) Executar uma instrucao (Step)\n");
		printf("9) Executar Programa (run)\n");
		printf("10) Volta uma instrucao (back)\n");
		printf("0) Sair\n");
		printf("-----------------------------------\n");
		printf("Opcao: ");
        scanf("%d", &opt);
		printf("-----------------------------------\n\n");
        switch (opt) {
            case 1:
				carrega_inst(&mem_inst);
            break;
            case 2:
				carrega_dados(&mem_dados);
			break;
            case 3:
				salva_asm(&mem_inst);
			break;
            case 4: 
				salva_dat(&mem_dados);
			break;
            case 5:
				imprime_mem_inst(&mem_inst);
				imprime_mem_dados(&mem_dados);
            break;
            case 6:
				imprime_reg(&reg);
            break;
            case 7:
				imprime_mem_inst(&mem_inst);
				imprime_mem_dados(&mem_dados);
				imprime_reg(&reg);
			break;
            case 8:
				salva_estado(&novo_estado, &mem_inst, &mem_dados, &reg, &pc);
				struct nodo * novoNodo = CriaNodo(&novo_estado);
				minhaPilha = PUSH(minhaPilha, novoNodo);
				//Imprime(minhaPilha);
				// adicionar bolhas para o beq (nops)
				
				switch (flag_estados) {
				case 1:
					if(pc.pc+i <mem_inst.tamanho){
					stage1(&mem_inst,pc.pc+i, &estado1);
					}
					flag_estados++;
					break;
				case 2:
					if(pc.pc+i <mem_inst.tamanho+1){
					stage2(&estado1, &reg, &estado2);
					}
					if(pc.pc+i <mem_inst.tamanho){
					stage1(&mem_inst,pc.pc+i, &estado1);
					}
					flag_estados++;
					break;
				case 3: 
					if(pc.pc+i <mem_inst.tamanho+2){
					stage3(&estado2, &estado3);
					}
					if(pc.pc+i <mem_inst.tamanho+1){
					stage2(&estado1, &reg, &estado2);
					}
					if(pc.pc+i <mem_inst.tamanho){
					stage1(&mem_inst,pc.pc+i, &estado1);
					}
					flag_estados++;
					break;
				case 4:
					if(pc.pc+i <mem_inst.tamanho+3){
					stage4(&estado3, &estado4, &mem_dados);
					}
					if(pc.pc+i <mem_inst.tamanho+2){
					stage3(&estado2, &estado3);
					}
					if(pc.pc+i <mem_inst.tamanho+1){
					stage2(&estado1, &reg, &estado2);
					}
					if(pc.pc+i <mem_inst.tamanho){
					stage1(&mem_inst,pc.pc+i, &estado1);
					}
					flag_estados++;
					break;
				case 5:
					if(pc.pc+i <mem_inst.tamanho+4){
					stage5(&estado4, &reg, &i);
					}
					if(pc.pc+i <mem_inst.tamanho+3){
					stage4(&estado3, &estado4, &mem_dados);
					}
					if(pc.pc+i <mem_inst.tamanho+2){
					stage3(&estado2, &estado3);
					}
					if(pc.pc+i <mem_inst.tamanho+1){
					stage2(&estado1, &reg, &estado2);
					}
					if(pc.pc+i <mem_inst.tamanho){
					stage1(&mem_inst,pc.pc+i, &estado1);
					}
					flag_estados++;
					break;
				default:
					if(pc.pc+i <mem_inst.tamanho+4){
					stage5(&estado4, &reg, &i);
					}
					if(pc.pc+i <mem_inst.tamanho+3){
					stage4(&estado3, &estado4, &mem_dados);
					}
					if(pc.pc+i <mem_inst.tamanho+2){
					stage3(&estado2, &estado3);
					}
					if(pc.pc+i <mem_inst.tamanho+1){
					stage2(&estado1, &reg, &estado2);
					}
					if(pc.pc+i <mem_inst.tamanho){
					stage1(&mem_inst,pc.pc+i, &estado1);
					}
					flag_estados++;
					break;
				}
				i++;
			break;
			case 9:
				while(flag_estados<=mem_inst.tamanho+4){
					salva_estado(&novo_estado, &mem_inst, &mem_dados, &reg, &pc);
				struct nodo * novoNodo = CriaNodo(&novo_estado);
				minhaPilha = PUSH(minhaPilha, novoNodo);
				//Imprime(minhaPilha);
				// adicionar bolhas para o beq (nops)
				
				switch (flag_estados) {
				case 1:
					if(pc.pc+i <mem_inst.tamanho){
					stage1(&mem_inst,pc.pc+i, &estado1);
					}
					flag_estados++;
					break;
				case 2:
					if(pc.pc+i <mem_inst.tamanho+1){
					stage2(&estado1, &reg, &estado2);
					}
					if(pc.pc+i <mem_inst.tamanho){
					stage1(&mem_inst,pc.pc+i, &estado1);
					}
					flag_estados++;
					break;
				case 3: 
					if(pc.pc+i <mem_inst.tamanho+2){
					stage3(&estado2, &estado3);
					}
					if(pc.pc+i <mem_inst.tamanho+1){
					stage2(&estado1, &reg, &estado2);
					}
					if(pc.pc+i <mem_inst.tamanho){
					stage1(&mem_inst,pc.pc+i, &estado1);
					}
					flag_estados++;
					break;
				case 4:
					if(pc.pc+i <mem_inst.tamanho+3){
					stage4(&estado3, &estado4, &mem_dados);
					}
					if(pc.pc+i <mem_inst.tamanho+2){
					stage3(&estado2, &estado3);
					}
					if(pc.pc+i <mem_inst.tamanho+1){
					stage2(&estado1, &reg, &estado2);
					}
					if(pc.pc+i <mem_inst.tamanho){
					stage1(&mem_inst,pc.pc+i, &estado1);
					}
					flag_estados++;
					break;
				case 5:
					if(pc.pc+i <mem_inst.tamanho+4){
					stage5(&estado4, &reg, &i);
					}
					if(pc.pc+i <mem_inst.tamanho+3){
					stage4(&estado3, &estado4, &mem_dados);
					}
					if(pc.pc+i <mem_inst.tamanho+2){
					stage3(&estado2, &estado3);
					}
					if(pc.pc+i <mem_inst.tamanho+1){
					stage2(&estado1, &reg, &estado2);
					}
					if(pc.pc+i <mem_inst.tamanho){
					stage1(&mem_inst,pc.pc+i, &estado1);
					}
					flag_estados++;
					break;
				default:
					if(pc.pc+i <mem_inst.tamanho+4){
					stage5(&estado4, &reg, &i);
					}
					if(pc.pc+i <mem_inst.tamanho+3){
					stage4(&estado3, &estado4, &mem_dados);
					}
					if(pc.pc+i <mem_inst.tamanho+2){
					stage3(&estado2, &estado3);
					}
					if(pc.pc+i <mem_inst.tamanho+1){
					stage2(&estado1, &reg, &estado2);
					}
					if(pc.pc+i <mem_inst.tamanho){
					stage1(&mem_inst,pc.pc+i, &estado1);
					}
					flag_estados++;
					break;
				}
				i++;
				}
			break;
            case 10: 
				if (EMPTY(minhaPilha)==1) {
					Imprime(minhaPilha);
					back(minhaPilha, &mem_inst, &mem_dados, &reg, &pc);
					minhaPilha = POP(minhaPilha);
				} else {
					printf("Lista Vazia\n");
				}
			break;
            case 0:
                printf("Saindo do programa...");
            break;
            default:
                printf("Opcao invalida");
            break;
        }
    }

    return 0;
}