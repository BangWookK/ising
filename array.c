#include <stdio.h>
#include <stdlib.h>

int main(){
	
	int i = 0;

	float temperature = 100;	

	float *Mean_energy = malloc(sizeof(float)*((int)temperature));

	Mean_energy[0] = Mean_energy[0]+1;
	
	for(i=0; i<temperature ; i++){
		printf("%f\t", Mean_energy[i]);
	}
	

	return 0;	
}
