#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#define min(a,b) (((a) < (b) ? (a) : (b)))

void change(float*, int);
float energy(float*, int);
float magnetization(float*, int);

int main(){
        srand((unsigned int)time(NULL));
        int size=0, iteration=0, i=0, j=0;
        float standard, probability, energy1, energy2;

	FILE *fp;

        fp = fopen("result.txt","wt");
	
	printf("System size is ");
        scanf("%d", &size);

	printf("Number of iteration is ");
	scanf(" %d", &iteration);	

        float *spin = malloc(sizeof(float)*size);
	float *tmp = malloc(sizeof(float)*size);
	float *Eplot = malloc(sizeof(float)*(iteration+1));
	float *Mplot = malloc(sizeof(float)*(iteration+1));
		
	//Initialize
        for(i=0;i<size;i++){
                standard = rand()/(float)RAND_MAX;
                if(standard<=0.5){
                        spin[i] = 1;
                }
                else{
                        spin[i] = -1;
                }
    	} 
	
	Mplot[0] = magnetization(spin, size);
	Eplot[0] = energy(spin, size);

	//iteration
	for(j=0;j<iteration;j++){

		//1. copy system
		memmove(tmp, spin, sizeof(float)*size);

		energy1 = energy(tmp, size);
		/*
		printf("%d\n", j+1);
		printf("original state\n");
                for(i=0;i<size;i++){
                        printf("%.2f\t", tmp[i]);
                }
                printf("\n\n");
		*/
		//2. change system
        	change(spin, size);
        	energy2 = energy(spin, size);
		/*
		printf("tried state\n");
                for(i=0;i<size;i++){
                        printf("%.2f\t", spin[i]);
                }
                printf("\n\n");
		*/
		//3. energy compare
		
        	//printf("energy diff:(tried) %.2f -(original) %.2f = %.2f\n", energy2, energy1, (energy2-energy1));
		probability = min(1,exp(-(energy2-energy1)));
		//printf("prob is %f\n", probability);
		
		//4. decision
		if((rand()/(float)RAND_MAX)>probability){
			memmove(spin, tmp, sizeof(float)*size);
			//printf("Not changed! (%f)\n\n", probability);
		}
		else{
			//printf("Changed! (%f)\n\n", probability);
		}
		
		Mplot[j+1] = magnetization(spin, size);	
		Eplot[j+1] = energy(spin, size);
	}
	
	for(i=0;i<iteration;i++){
		printf("Energy (%d, %.2f), Magnetization (%d, %.2f)\n", i, Eplot[i], i, Mplot[i]);
		fprintf(fp, "%d %.2f\n", i, Eplot[i]);
	}

	fclose(fp);
	
        return 0;
}

void change(float *p, int size){

	int change = 0;	
	int i = 0;
	
	for(i=0;i<size;i++){
		change = (int)rand()%size;
		p[change] = -p[change];
	}
	/*	
	for(i=0;i<size;i++){
		printf("%f\t", p[i]);
	}

	printf("\n");
	*/
}

float energy(float *p, int size){
	float e = 0;
	int i=0;

	for(i=0;i<(size-1);i++){
		e = e-p[i]*p[i+1];
	}
	e = e-p[size-1]*p[0];
	/*
	printf("energy is %f\n", e);
	*/
	return e;
}

float magnetization(float *p, int size){
	float M = 0;
	int i=0;

	for(i=0; i<size; i++){
		M = M+p[i];
	}

	M = M/size;

	return M;
}

