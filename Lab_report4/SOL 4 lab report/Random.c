/*****************************
Content: SOL1, Lab4, Exercise 1
Lecturer: Prof. Schoenen
Authors: Emmanuel Duru, and Jose Luis Roldan Rodriguez HAW Hamburg
Date: 20201112
Short description:
******************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>		//Basic library, to implement scanf and printf
#define _USE_MATH_DEFINES	// for M_PI
#include <math.h>			//Library to implement some mathematical operations
#include <stdlib.h> /* for rand() */
#include <time.h> /* for time() in srand() */

#define CENTER 0.0
#define DEVIATION 1.0
#define DICES 4
#define EXPERIMENTS 200

//Global variables
int histogram_array[25] = { 0 }; //Enough for 4 dice (6 faces)

double gauss(double x);
int dice();
void dice_statistics(int throws, int experiments);
void avg_calculated();
void ave_experiment();

void main()
{
	time_t t;
	srand((unsigned)time(&t)); // random number generator initialization

	for (int i = -5; i <= 5; i++)
	{
		printf("x = %2d f(x) = %lf\n", i, gauss(i));
	}
	printf("\n");
	dice_statistics(DICES, EXPERIMENTS);
	avg_calculated();
	ave_experiment();
	return;
}


double gauss(double x) // function for the gauss expression
{
	double result = 0;
	result = (1.0 / (DEVIATION * sqrt(2.0 * M_PI))) * exp((-0.5) * (((x - CENTER) / DEVIATION)) * ((x - CENTER) / DEVIATION));// the gauss formular
	return result;
}

int dice() // function to get a random number between 1 and 6
{
	int random = rand() % 6 + 1;
	return random;
}

void dice_statistics(int throws, int experiments) //function that reads theough the throwing of dices and store the number repetation in the histogram
{
	int sum_throws;
	for (int i = 0; i < experiments; i++) //a loop function for throwing the number of experiment as declared above
	{
		sum_throws = 0;
		for (int a = 0; a < throws; a++) // a loop function that throws the dices via obtaining a random number
		{
			sum_throws += dice();
		}

		histogram_array[sum_throws] ++;
		printf("number %d times %d\n", sum_throws, histogram_array[sum_throws]); 
	}

	return;
}

void avg_calculated() //function for average calculation of the dice
{
	double result = ((1.0*DICES) + (6.0 * DICES)) / 2; //an operation that calculates the average of the operation
	printf("The calculated average result is : %lf\n", result);
	return;
}

void ave_experiment() //function for the average experiment of the random number of thrown dices 
{
	double  result = 0.0;
	for (int i = 0; i <= 24; i++) //a loop function that iterates through the dice and number of times to be thrown randomly
	{
		result += (i * 1.0) * histogram_array[i]; //an operation to place in the 
	}
	result = result / EXPERIMENTS; //an operation to declare the experiment average

	printf("The experiment average result is : %lf\n", result);
	return;
}

