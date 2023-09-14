#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

//4 - Durante uma corrida de automóveis com N voltas de duração foram anotados
//para um piloto, na ordem, os tempos registrados em cada volta. Fazer um programa para ler os tempos
// das N voltas, calcular e imprimir.

int main(){
	
	srand(time(NULL));
	
	int voltas;
	float tempo, ttotal=0;
	
	
	printf("Numero de voltas:");
	scanf("%d", &voltas);
	
	int i;
	
	for(i=0;i<voltas;i++){
		tempo=rand()%50;
		ttotal+=tempo;
		printf("%\nTempo %d: %.2f", i, tempo);
	}
	
	printf("\nTempo total: %.2f", ttotal);
	
	return 0;
}