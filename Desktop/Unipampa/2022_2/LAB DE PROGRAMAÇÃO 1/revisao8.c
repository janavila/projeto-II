#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(){
	
	srand(time(NULL));

float media=0;
float n = 1;
int i=0;

while(n!=0){
	printf("Digite um numero: ");
	scanf("%f", &n);
	if(n!=0){
	media+=n;
	i++;
	}
}

printf("\nMedia: %.2f", media/i); 

return 0;
}