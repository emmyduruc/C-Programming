/*

	Course:	SOL1 WS2020
	Exercise: 1
	Author: Emmanuel Duru
	Date:	20.01.2021
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define _USE_MATH_DEFINES /* for M_PI */
#include <math.h>
#include <stdlib.h> /* for rand() */
#include <time.h> /* for time() in srand() */
#include <stdbool.h>//boolean

#define SIZE 1
int DEBUG = 1;

// global:
enum enum_command { NOTHING = 0, SUM, MUL } command = 0;
int arg_list_start_index = 1;

typedef struct struct_complex {
	double real;
	double imag;
}complex;
const complex I = { 0.0, 1.0 }; // imaginary unit
const complex ONE = { 1.0, 0.0 }; // real unit

#define MAX_STACK_DEPTH 10
typedef struct {
	complex item[MAX_STACK_DEPTH];
	int stack_index;
} complex_stack;
complex_stack global_stack = { 0 }; // global var for stack, empty

void print_complex(complex c) {
	printf("%.3lf+%.3lfj", c.real, c.imag);
}

complex mul_complex_numbers(complex c1, complex c2)
{
	complex result;
	result.real = c1.real * c2.real - c1.imag * c2.imag;
	result.imag = c1.real * c2.imag + c1.imag * c2.real;

	return result;
}

complex complex_division(complex c1, complex c2) {
	complex result = { 0,0 };
	//result.real = c1.real + c2.real;
	//result.imag = c1.imag + c2.imag;

	return result;
}
complex complex_squared(complex c) {
	complex result;
	result.real = c.real * c.real;
	result.imag = c.imag * c.imag;
	return result;
}

complex complex_addition(complex c, complex b) {
	complex result;
	result.real = c.real + b.real;
	result.imag = c.imag + b.imag;

	return result;
}
complex subtract_complex(complex c1, complex c2) {
	complex result;
	result.real = c1.real - c2.real;
	result.imag = c1.imag - c2.imag;

	return result;
}
complex power(complex c1, int pow) {
	complex loop = { c1.real,c1.imag };
	complex result = { 0,0 };
	printf("loop = (%.1f,%.lf)", c1.real, c1.imag);
	for (int i = 1; i < pow; i++)
	{
		result.real = (loop.real * c1.real) - (loop.imag * c1.imag);
		result.imag = (loop.real * c1.imag) - (loop.imag * c1.real);
	}
	printf("%.1lf+%.1lf\n", result.real, result.imag);
	return result;
}

complex complex_operation(char operator, complex c1, complex c2) {
	complex result = { 0, 0 };
	switch (operator) {
		//checking the operator entered by the user inorder to determine the operation to do
	case '-': result = subtract_complex(c1, c2); break;
	case '+': result = complex_addition(c1, c2); break;
	case '*': result = mul_complex_numbers(c1, c2); break;
	case '/': result = complex_division(c1, c2); break;
	case '^': result = power(c1, c2.real); break;
	default: printf("this is a wrong operator\n"); //alert at a given wrong expression
	}
	return result;
}

complex complex_calc(int argc, char **argv) {
	complex result = { 0, 0 };
	complex c;
	complex c1 = { 0, 0 };
	complex c2 = { 0, 0 }; //storing result of the operation
	char operator = ' ';
	int arg_count = 0, arg_pow = 0;

	//if (DEBUG)printf("arg_pow = %d ,argv[3]= %s\n", arg_pow, argv[3]); //displaying the third argument from the command line

	for (int i = 1; i < argc; i++) //using for loop to assign values to complex variables
	{
		int rv = sscanf(argv[i], "(%lf,%lf)", &c.real, &c.imag); //usinf sscanf to obtain values from the users

		if (rv > 0) //if the input contains values
		{
			if (DEBUG) { printf("stack[%d]=", global_stack.stack_index); print_complex(c); printf("\n"); }
			global_stack.item[global_stack.stack_index++] = c; // push onto the stack
			
		//if (DEBUG) printf("arg_count= %d\n", arg_count); //print_complex(c)
			if (++arg_count == 1) //if the count is 1 that is the first argument
			{
				c1 = c; //assign the first complex variable c1
				if (DEBUG) { printf("c1="); print_complex(c1); printf("\n"); }
			}
			else //otherwise, the count is greater than 1 that is we have more than one argument
			{
				c2 = c; //assign the second complex variable c2
				if (DEBUG) { printf("c2="); print_complex(c2); printf("\n"); }
			}
		}
		else // the sscanf fails or operator no input or error
		{
			operator = argv[i][0];
			// with RPN:
			// global_stack.stack_index was == 2
			c2 = global_stack.item[--global_stack.stack_index]; // pop
			c1 = global_stack.item[--global_stack.stack_index]; // pop
			if (DEBUG) { printf("c1=stack[%d]=", global_stack.stack_index + 1); print_complex(c1); printf("\n"); }
			if (DEBUG) { printf("c2=stack[%d]=", global_stack.stack_index + 2); print_complex(c2); printf("\n"); }
			result = complex_operation(operator, c1, c2);
			if (DEBUG) { printf("r=stack[%d]=", global_stack.stack_index); print_complex(result); printf("\n"); }
			global_stack.item[global_stack.stack_index++] = result; // push
		}
	} // for
	//result = complex_operation(operator, c1, c2); // without RPN
	result = global_stack.item[--global_stack.stack_index]; // pop
	return result;
}

// int main() { // Standardized for implementing this arithematic of complex numbers in cmd
int main(int argc, char** argv) {
	for (int i = 1; i < argc; i++) { //using for loop to assign values to complex variables
		if (DEBUG) printf("argv[%d]= %s\n", i, argv[i]);
	}
	complex result = complex_calc(argc, argv);
	printf("result="); print_complex(result); printf("\n"); 
}