#include <stdio.h>

//3 - Escreva um programa que leia o raio de um círculo e faça duas funções: uma função
//chamada área que calcula e retorna a área do círculo e outra função chamada perímetro
//que calcula e retorna o perímetro do círculo. Área = PI * r2. Perímetro = PI * 2 * r

float area(int r);
float perimetro(int r);

int main(){

int raio;
printf("Valor do raio:");
scanf("%d", &raio);
printf("\nRaio: %.2f\n", area(raio));
printf("\nPerimetro: %.2f\n", perimetro(raio));

return 0;
}

float area(int r){
	
	float area;
	
	area = 3.14*(r*r);
	
	return area;
}


float perimetro(int r){
	
	float perimetro;
	
	perimetro = 2*3.14*r;
	
	return perimetro;
}