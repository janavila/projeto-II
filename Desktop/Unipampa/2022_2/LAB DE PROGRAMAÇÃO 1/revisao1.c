#include <stdio.h>

//1 - Criar uma função que retorna o seguinte: a função recebe 3 valores e retornar o
//quadrado do 1º + a soma dos outros dois.

int soma(int v1,int v2,int v3);

int main(){

int v1, v2, v3, i;
printf("Valor 1:");
scanf("%d", &v1);
printf("Valor 2:");
scanf("%d", &v2);
printf("Valor 3:");
scanf("%d", &v3);
soma(v1,v2,v3);
printf("%d", soma(v1, v2, v3));

return 0;
}

int soma(int v1,int v2,int v3){
	int total;
	total=((v1*v1)+(v2+v3));
	return total;
}