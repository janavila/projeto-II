#include <stdio.h>
#include <string.h>

//3 - Leia duas strings. Se as strings forem iguais escreva "strings iguais". Caso contrário, cancatene as duas strings e imprima
//a string resultante e a quantia de caracteres existentes nela.

int main(){
	
	char string1[24], string2[24];
	char concat[48];
	
	printf("String 1: ");
	scanf("%s", string1);
	printf("String 1: ");
	scanf("%s", string2);
	
	if(strcmp(string1, string2)==0){
		printf("Strings iguais!");
	}else{
		
		printf("\nConcatenação: %s", strcat(string1, string2));
		printf("\nTamanho: %d", strlen(string1));
	}
	
	return 0;
}