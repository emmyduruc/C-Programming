
/*****************************
Content: SOL1, Lab2, Exercise 3
Lecturer: Prof. Schoenen
Authors: Emmanuel duru and Hilary Ogalagu, HAW Hamburg
Date: 20201112
Short description:A program that displays using an array function to determine the siyes of an array in its function
******************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void print_int_array(int* array, int num) 
{
	int i;
	for (i = 0; i < num; i++) {					//Function to print the whole array
		printf("%d ", array[i]);
	}
	printf("\n\n");
}

void swap(int* a, int* b) //implementing the swap function to enable the program swap through the array as required
{
	int temporal = *a;
	*a = *b;
	*b = temporal;
}
int main() 
{
	int number[10];	// Definition of an array of int with 10 elements	
	int array_size = 10;
	int i;

	for (i = 0; i < array_size; i++) // implementing the for loop function 
	{
		printf("Please enter a number[%d]: ", 1 + i);		//this line sets the numbers in the array
		scanf_s("%d", &number[i]);
	}

	//b print the array
	print_int_array(&number[0], array_size);

	//c determining the size of the array in bytes and bits
	int bytes_size = sizeof(number);
	printf("The size of the array is %d bytes and %d bits\n\n", bytes_size, (8 * bytes_size)); //1 byte = 8 bits

	//d Shifting the array to the left
	printf("Shift towards the front:\n");
	int temp = number[0];
	for (i = 0; i < (array_size - 1); i++) 
	{
		number[i] = number[i + 1];
	}
	number[9] = temp;
	print_int_array(&number[0], array_size);

	//e shifting the arrays towards the right
	printf("Shift towards the back:\n");
	temp = number[9];
	for (i = 9; i > 0; i--) 
	{
		number[i] = number[(i - 1)];
	}
	number[0] = temp;
	print_int_array(&number[0], array_size);

	//f swapping a and b
	printf("Swap numbers 2 and 9:\n");
	swap(&number[1], &number[8]);
	print_int_array(&number[0], array_size);

	//g neighbour swapping   
	printf("Swap unsorted neighbors:\n");
	for (i = 0; i < 9; i++) 
	{
		if (number[i] > number[i + 1]) // IF first number > second number
			swap(&number[i], &number[(i + 1)]);
	}
	print_int_array(&number[0], array_size);

	//h swap the arrays 9 times towards the neighbour
	printf("Swap unsorted neighbors 9 times:\n");
	int a;
	for (a = 0; a < 9; a++) 
	{
		for (i = 0; i < 9; i++) 
		{
			if (number[i] > number[i + 1]) // IF first number > second number
				swap(&number[i], &number[(i + 1)]);
		}
	}
	print_int_array(&number[0], array_size);
	return 0;
}












/*
print_int_array(int numbers[10]);

int main() {

	int numbers[10];		// Definition of an array of int with 10 elements
	for (int i = 0; i <= 9; i++) {
		printf("Please enter a number \[%d\] ", 1 + i);
		scanf_s("%d", &numbers[i]);
	}

	print_int_array(numbers);
	return 0;
}


print_int_array(int numbers[10])
{
	for (int i = 0; i < 10; i++) {
		printf("%d ", numbers[i]);
	}
}
*/