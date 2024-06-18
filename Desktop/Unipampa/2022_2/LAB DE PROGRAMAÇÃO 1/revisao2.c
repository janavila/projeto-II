#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//2 - Criar um algoritmo que leia os elementos de uma matriz inteira de 3 x 3 e imprimir
//todos os elementos, exceto os elementos da diagonal principal.

int main(){
srand(time(NULL));

int mat[3][3];
int i,j;

for(i=0;i<3;i++){
	for(j=0;j<3;j++){
		mat[i][j]=rand()%99;
	}
}
for(i=0;i<3;i++){
	for(j=0;j<3;j++){
		if(i!=j){
		printf("%d  ", mat[i][j]);
		}else{
			printf("   ");
		}
	}
	printf("\n");
}

return 0;
}