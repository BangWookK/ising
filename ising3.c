#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define min(a,b) (((a) < (b) ? (a) : (b)))

void change(float*, int);
float energy(float*, int);
float magnetization(float*, int);
float variance(float*, int);

int main(){
	srand((unsigned int)time(NULL));
	int size = 0, iteration = 0, i = 0, j = 0, k = 0, temperature;
	float standard, probability, energy1, energy2;

	FILE *fp;

	printf("System size is ");
	scanf("%d", &size);

	printf("Number of iteration is ");
	scanf(" %d", &iteration);

	printf("Maximum temperature is ");
	scanf(" %d", &temperature);
	
	float *spin = malloc(sizeof(float)*size);
	float *tmp = malloc(sizeof(float)*size);
	float *Eplot = malloc(sizeof(float)*(iteration+1));
	float *Mplot = malloc(sizeof(float)*(iteration+1));
	float *Temp = malloc(sizeof(float)*temperature);
	float *Mean_energy = malloc(sizeof(float)*temperature);
	float *Mean_magnetization = malloc(sizeof(float)*temperature);

	for(i=0; i<temperature; i++){
		Temp[i] = i;
	}
	
	for(i=0; i<temperature; i++){
		//About ith temperature
		for(j=0; j<size; j++){
			//Initialize system
			standard = rand()/(float)RAND_MAX;
			if(standard>0.5){
				spin[j] = 1;
			}
			else{
				spin[j] = -1;
			}
		}
		
		Eplot[0] = energy(spin, size);
		Mplot[0] = magnetization(spin, size);
		
		for(j=0; j<iteration; j++){
			for(k=0; k<size; k++){
				memmove(tmp, spin, sizeof(float)*size);
				change(spin, size);
				
				//Compare energy
				energy1 = energy(tmp, size);
				energy2 = energy(spin, size);
				
				probability = min(1, exp(-(energy2-energy1)/Temp[i]));
				
				//Decision
				if((rand()/(float)RAND_MAX)>probability){
					memmove(spin, tmp, sizeof(float)*size);
				}	
			}
			
			Eplot[j+1] = energy(spin, size);
			Mplot[j+1] = magnetization(spin, size);
		}
		
		for(j=20; j<iteration; j++){
			Mean_energy[i] = Mean_energy[i] + Eplot[j];
			Mean_magnetization[i] = Mean_magnetization[i] + Mplot[j];
		}

		Mean_energy[i] = Mean_energy[i]/(iteration-20);
		Mean_magnetization[i] = Mean_magnetization[i]/(iteration-20);
	}	

	fp = fopen("Mean_energy.txt", "wt");

	for(i=0; i<temperature; i++){
		fprintf(fp, "%d %f\n", i, Mean_energy[i]);
        }
	
	fclose(fp);

	fp = fopen("Mean_magnetization.txt", "wt");

	for(i=0; i<temperature; i++){
		fprintf(fp, "%d %f\n", i, Mean_magnetization[i]);
        }
	
	fclose(fp);


	return 0;
}

void change(float *spin, int size){
	int c = 0;
	c = (int)rand()%size;
	spin[c] = -spin[c];
	
}

float energy(float *spin, int size){
	int e = 0, i = 0;
	
	for(i=0; i<(size-1); i++){
		e = e-spin[i]*spin[i+1];
	}
	
	e = e-spin[size-1]*spin[0];

	return e;
}

float magnetization(float *spin, int size){
	float m = 0;
	int i = 0;

	for(i=0; i<size; i++){
		m = m + spin[i];
	}

	m = m/size;

	return m;
}

float variance (float *array, int size){
	float v;

	return v;
}
