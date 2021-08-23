
/*****************************
Content: SOL1, Lab2, Exercise 2
Lecturer: Prof. Schoenen
Authors: emmanuel duru and Hilary Ogalagu, HAW Hamburg
Date: 20201112
Short description: A program that displays the using a maths function to determine a scalar and vector quantity.
******************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

double sum_up(double* array, int num_elements);
double average(double* array, int elements);
double scalar_product(double* vector1, double* vector2, int dim);
double distance(double* vector1, double* vector2, int dim);


int main(void) {
	double numbers[4] = { 1.0, 4.0, 7.7, 10.9 }; // example numbers
	double sum =
		sum_up(&numbers[0], 4); // Address of start of array
		// and length of the array
	printf("The sum is %4.2f\n", sum);

	double aver = average(&numbers[0], 4);
	printf("The average is:%2.2lf\n", aver);

	double vector1[3];
	double vector2[3];

	printf("please enter three numbers:\n");
	for (int i = 0; i < 3; i++) {
		printf(" enter vector1:");
		scanf("%lf", &vector1[i]);
	}

	printf("please enter three numbers again:\n");
	for (int i = 0; i < 3; i++) {
		printf(" enter vector2:");
		scanf("%lf", &vector2[i]);
	}
	double scalar = scalar_product(vector1, vector2, 3); //implementing the variables of the scalar product
	printf("The product of 2 vector is %2.2lf\n", scalar);

	double distances = distance(vector1, vector2, 3);
	printf("The Euclidian distance is %2.2lf", distances);

	return 0;
}

double sum_up(double* array, int num_elements) {
	double summe = 0.0;
	for (int i = 0; i < num_elements; i = i + 1) // all from 0 to num_elements-1
		summe = summe + array[i]; // sum up
	return summe;
}

//1b
double average(double* array, int num_elements) {
	double sum = sum_up(array, num_elements);			//Calculate the avarage by calling the sum_up function 
	double aver = sum / (double)num_elements;
	return aver;
}

//1c
double scalar_product(double* vector1, double* vector2, int dim)
{
	double scalar = 0.0;
	for (int i = 0; i < dim; i++)
		scalar += vector1[i] * vector2[i];
	return scalar;
	
}

//1d. the euclidian distance between the points represented by the vectors
double distance(double* vector1, double* vector2, int dim)
{
	double distance = 0.0;
	for (int i = 0; i < dim; i++)// implementing a for loop to iterate through the progression
	{
		distance += (vector1[i] - vector2[i]) * (vector1[i] - vector2[i]);

	}
	sqrt(distance);

	return distance;
}







/*float sum_up(float* array, int num_elements);
float average(float* array, int num_elements)
{
	float summe = 0.0;
	for (int i = 0; i < num_elements; i = i + 1) // all from 0 to num_elements-1
		summe = summe + array[i]; // sum up
	return summe;
}
int main(void)
{
	float numbers[4] = { 1.0, 4.0, 7.7, 10.9 }; // example numbers
	float sum =
		sum_up(&numbers[0], 4); // Address of start of array
		// and length of the array
	printf("The sum is %4.2f\n", sum);
}
*/
