#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(){

srand(time(NULL));
 
int v1[5], v2[5];
int i, j;

for(i=0;i<5;i++){
	v1[i]= rand()%10;
	v2[i]= rand()%10;
	printf("\nv1: %d || v2: %d", v1[i], v2[i]);
}

for(i=0;i<5;i++){
	for(j=0;j<5;j++){
		if(v1[i]==v2[j]){
			printf("\nv1[%d]: %d e v2[%d]: %d\n", i, v1[i], j, v2[j]);
		}
	}
	
}

return 0;
}
