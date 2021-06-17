#include <stdio.h>

float variance (float *array, int iteration){
        float v;
        float mean_of_square = 0, square_of_mean = 0;
        int i = 0;
        
        for(i=0; i<iteration; i++){
                square_of_mean = square_of_mean + array[i];
                mean_of_square = mean_of_square + array[i]*array[i];
        }

        square_of_mean = square_of_mean/(iteration);
        square_of_mean = square_of_mean*square_of_mean;

        mean_of_square = mean_of_square/(iteration);

	printf("mean_of_square is %f", mean_of_square);
	printf("square_of_mean is %f", square_of_mean);

        v = mean_of_square - square_of_mean;

        return v;
}

int main(){
	float spin[3];
	float var;
	
	spin[0] = 20;
	spin[1] = 20;
	spin[2] = 30;

	var = variance(spin, 3);

	printf("%f\n", var);

	return 0;
}
