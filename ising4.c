#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define min(a,b) (((a) < (b) ? (a) : (b)))

void change(float*, int);
float energy(float*, int);
float magnetization(float*, int);
float variance(float*, int, int);

int main(){
	srand((unsigned int)time(NULL));
	int size = 0, iteration = 0, i = 0, j = 0, k = 0, temperature = 10, temp_seg_num = 1000;
	float standard, probability, energy1, energy2;
	const int relaxation = 20;

	FILE *fp;

	printf("System size is ");
	scanf("%d", &size);

	printf("Number of iteration is (need to greater than 20) ");
	scanf(" %d", &iteration);
	
	float *spin = malloc(sizeof(float)*size);
	float *tmp = malloc(sizeof(float)*size);
	float *Eplot = malloc(sizeof(float)*(iteration+1));
	float *Mplot = malloc(sizeof(float)*(iteration+1));
	float *Temp = malloc(sizeof(float)*temp_seg_num);
	float *Mean_energy = malloc(sizeof(float)*temp_seg_num);
	float *Mean_magnetization = malloc(sizeof(float)*temp_seg_num);
	float *Var_energy = malloc(sizeof(float)*temp_seg_num);
	float *Var_magnetization = malloc(sizeof(float)*temp_seg_num);
	float *Eplot_T0 = malloc(sizeof(float)*(iteration+1));
	float *Mplot_T0 = malloc(sizeof(float)*(iteration+1));

	for(i=0; i<temp_seg_num; i++){
		Temp[i] = (i+1)/(temp_seg_num/(float)temperature);
		printf("%f\n", Temp[i]);
	}
	
	for(i=0; i<temp_seg_num; i++){
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
				/*
				if (i == 0 && k == 0) {
					int x = 0;
					for (x = 0; x < 100; x++) printf("%s", (spin[x] == 1)? "■": "□");
					printf("\n");
				}
				*/
				//Decision
				if((rand()/(float)RAND_MAX)>probability){
					memmove(spin, tmp, sizeof(float)*size);
				}	
			}
			
			Eplot[j+1] = energy(spin, size);
			Mplot[j+1] = magnetization(spin, size);
		}
		
		for(j=relaxation; j<iteration; j++){
			Mean_energy[i] = Mean_energy[i] + Eplot[j];
			Mean_magnetization[i] = Mean_magnetization[i] + Mplot[j];
		}

		Mean_energy[i] = Mean_energy[i]/(iteration-relaxation);
		Mean_magnetization[i] = Mean_magnetization[i]/(iteration-relaxation);
		
		Var_energy[i] = variance(Eplot, (iteration+1), relaxation);
		Var_magnetization[i] = variance(Mplot, (iteration+1), relaxation);
	}	

	fp = fopen("Mean_energy.txt", "wt");

	for(i=0; i<temp_seg_num; i++){
		fprintf(fp, "%f %f\n", Temp[i], Mean_energy[i]);
        }
	
	fclose(fp);

	fp = fopen("Mean_magnetization.txt", "wt");

	for(i=0; i<temp_seg_num; i++){
		fprintf(fp, "%f %f\n", Temp[i], Mean_magnetization[i]);
        }
	
	fclose(fp);

	fp = fopen("Var_energy.txt", "wt");

	for(i=0; i<temp_seg_num; i++){
		fprintf(fp, "%f %f\n", Temp[i], Var_energy[i]);
        }
	
	fclose(fp);

	fp = fopen("Var_magnetization.txt", "wt");

	for(i=0; i<temp_seg_num; i++){
		fprintf(fp, "%f %f\n", Temp[i], Var_magnetization[i]);
        }
	
	fclose(fp);

	printf("Complete!\n");
	
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

float variance (float *array, int size, int start){
	float v;
	float mean_of_square = 0, square_of_mean = 0;
        int i = 0;

        for(i=start; i<size; i++){
                square_of_mean = square_of_mean + array[i];
                mean_of_square = mean_of_square + array[i]*array[i];
        }

        square_of_mean = square_of_mean/(size - start);
        square_of_mean = square_of_mean*square_of_mean;

        mean_of_square = mean_of_square/(size - start);

        v = mean_of_square - square_of_mean;

	return v;
}
