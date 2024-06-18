#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int main(){

srand(time(NULL));

int n[20], i, j;

for(i=0;i<20;i++){
	n[i]=rand()%10;
	for(j=0;j<=n[i];j++){
		printf("\n%d * %d = %d ", n[i], j, n[i]*j);
	}
	
}

return 0;
}