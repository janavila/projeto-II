#include <stdio.h>

/*4 - Escreva um programa para ler o número de lados de um polígono regular e a medida
do lado (em cm). Faça um procedimento que receba como parâmetro o número de lados
e a medida do lado deste polígono e calcule e imprima o seguinte:
- Se o número de lados for igual a 3, escrever TRIÂNGULO e o valor do seu perímetro.
- Se o número de lados for igual a 4, escrever QUADRADO e o valor da sua área.
- Se o número de lados for igual a 5, escrever PENTÁGONO.
Observação: Considere que o usuário só informará os valores 3, 4 ou 5.
*/

int main(){
int nlados, medidas;
printf("Numero de lados:");
scanf("%d", &nlados);
printf("Valor das medidas:");
scanf("%d", &medidas);

if(nlados==3){
	printf("\nTRIANGULO\n");
	printf("\nPerimetro: %d\n", medidas*3);
}
if(nlados==4){
	printf("\nQUADRADO\n");
	printf("\nÁrea: %d\n", medidas*medidas);
}
if(nlados==5){
	printf("\nPENTAGONO\n");
}	


return 0;
}