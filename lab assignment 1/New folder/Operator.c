/*
* Program : Operator.c
* Course : SOL1 WS2020
* Author : Duru Emmanuel & Morjurul Islam zhimon
* Date : 24.12.2020

*/

//preprocessors
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

//implementing the maths function so as to power the expression as given in the lab sheet 
int mathpower(int n, int p);


//implementing the main function so as to enable the printf and scanf functions to work effectively 
int main()
{
	//we implemented the data type of int and initialized the variables n, and n to be 0
	int n = 0, p = 0;
	// we called the print function to enable me enter the number n as directed in the exercise
	printf("\nPlease enter your number n: ");
	// we called the scanf function below so as to be able to store the number and place it as the value of n
	scanf("%d", &n);
	// we called the print function to enable me enter the number p as directed in the exercise
	printf("\nEnter the power number p: ");
	// we called the scanf function below so as to be able to store the number and place it as the value of p
	scanf("%d", &p);
	// we called the printf function to able me print the results of the aformentioned input above which is 2*n  
	printf("\n2*%d = %d\n", n, 2 * n);

	// we called the printf function to able me print the results of the power of n 
	printf("\n%d ^ 2 = %d\n", n, n * n);

	mathpower(n, p);

	return 0;

}
// implementing the math function for a successful expression of mathematics as been given in the exercise with the data type of int and initializing the variables n and p.
int mathpower(int n, int p)

{   //initialzing a new variablle of res of type int and assign a value of 1 to it
	int res = 1;
    //implementing a for loop which enables us to have a loop of whatever ever we assign the loop to run for
	//we have a variable of M and initialize a value of 1 to it and then M is less or equal to the initial value of p as stated above 
	//then the itiration indicates that for every itiration a value of 1 is added to p.
	for (int m = 1; m <= p; m++)
	{
		//res is a local variable that performs the calculation 
		res = res * n;
		//the printf function printed the power of n to m and adopted the expression of res. and print if out in association of the given lop expression above.
		printf("%d^%d = %d\n ", n, m, res);
	}
	return 0;
}//we endevoured to close the complete set of code with the curly braces so that the compiler does not throw an error message to us .


	