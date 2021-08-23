/***************************************************************************************
Content: SOL1, Lab3, Exercise 1
Lecturer: Prof. Schoenen
Authors: Emmanuel Duru and ROkia Akter, HAW Hamburg
Date: 20201216
Short description: Angle
****************************************************************************************/


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <math.h>

#define _USE_MATH_DEFINES /* for M_PI */
#define PI 3.14159
#define COLUMNS 80
#define ROWS 40
#define DEBUG 0 /* 1==true to give a lot of output */
#define FIXED_DEV 0.8
#define XMIN -PI
#define XMAX +PI
#define XSTEP (2*PI/ROWS)
#define XEXTRA 0.01
#define getch _getch


double norm_angle(double x);
double sinus(double x, double deviation);
void x_rad_con_fixed_dev(double x);
void do_plotting_frontend(); 
void plot_function_by_key(char ch);
void plot_value(double value, double y_min, double y_max);
double zero_point(double lower, double upper);
double f(double x);
double d(double x, double h);
double extreme_value(double lower, double upper);

int main(void) {
	double x;
	for (x = -10; x < 10.1; x += 2.0) {
		printf(" The angle %12.8lf ( radiants ) corresponds to %12.8lf\n",
			x, norm_angle(x));
	}
	printf("\n");

	for (x = -PI; x <= PI+0.01; x += PI / 10) {
		printf("sinus(%lf) = %lf\n", x, sinus(x, 1e-6));
	}
	
	do_plotting_frontend();

	printf("Zero_point of Cosine : %15.10lf \n", zero_point(1.0, 2.0));
	//zero_point(1.0, 2.0);
	printf("Extrem: %lf", extreme_value(1.0, 2.0));
	
	return 0;
}

//Exercise 1.a
double norm_angle(double x) {
	double norm = x;
	while (norm > PI|| norm < -PI) {//Loop to set the input x into [pi,-pi]
		if (norm > PI)
			norm = -2 * PI + norm;
		else if (norm < -PI)
			norm = 2 * PI + norm;
	}
	return norm;
}

// Exercise 1b
double sinus(double x, double deviation) {
	x = norm_angle(x); //defining the intervals of [PI, -PI]
	double sk = x;		//initialzied the PI values to sequence
	double sum = sk;
	int k = 1;			 // starting value for the sequence
	while (sk > 0 && sk > deviation || sk < 0 && sk < -deviation) //a loop variable defining the sum of sequence
	{
		sk = sk * (-x * x / (2 * k * (2 * k + 1)));
		sum += sk;
		k++;		//iterating through the sequence
	}
	
	return sum;
}

//Exercise 1c
double f(double x) {
	return cos(x);//sinus(x,1e-6);
}


void do_plotting_frontend() {
	if (DEBUG) printf("### do_plotting_frontend()\n");
	char ch; // character from keyboard
	int key_pressed = ' '; // keyboard key value
	// loop:
	while (key_pressed != '.') {
		printf("Please select function to plot (keys a..z, .=quit)\n");
		key_pressed = getch();
		ch = key_pressed; // char <- int conversion
		if (DEBUG) printf("Key pressed was '%c'=%04d=0x%04X\n", ch, key_pressed, key_pressed);
		plot_function_by_key(ch);
	}
	if (DEBUG) printf("### do_plotting_frontend() finished.\n");
}

void plot_function_by_key(char ch) {
	if (DEBUG) printf("### plot_function_by_key('%c')\n", ch);
	int index = 0;
	double x, y, y_min = 0.0, y_max = 0.0;
	double x_array[100], y_array[100];
	// loop over range of x values:
	for (x = XMIN; x <= XMAX + XEXTRA; x = x + XSTEP) { // #steps is ROWS
		switch (ch) { // depend on key pressed
		case 's': y = sin(x); break;
		case 'c': y = cos(x); break;
		case 't': y = tan(x); break;
		case 'f': y = f(x); break;
		case 'l': y = x; break;
		case 'q': y = x * x; break;
		default: y = 0;
		}
		//if (DEBUG) printf("x=%.3lf y=%.3lf\n", x, y);
		x_array[index] = x; // store into table
		y_array[index] = y; // store into table
		y_min = (y < y_min) ? y : y_min;
		y_max = (y > y_max) ? y : y_max;
		index++; // increase the index
	}
	int num_values = index; // so many elements in the table
	if (DEBUG) printf("num_values=%d, y_min=%.3f, y_max=%.3f\n", num_values, y_min, y_max);
	for (index = 0; index < num_values; index++) { // #steps is ROWS
		x = x_array[index]; // read out values from table
		y = y_array[index];
		//if (DEBUG) printf("x=%.3lf y=%.3lf\n", x, y);
		printf("x=%6.3lf ", x);
		plot_value(y, y_min, y_max);
	}
	if (DEBUG) printf("### plot_function_by_key() finished.\n");
}

void plot_value(double value, double y_min, double y_max) {
	double range = y_max - y_min;
	int column = (value - y_min) / (range) * (COLUMNS - 10); // between 0 .. 80
	for (int i = 0; i < column; i++) {
		printf(" ");
	}
	printf("*\n");
}

double zero_point(double lower, double upper) {
	double middle, mid_region, lower_boundary, up_boundary, absolute_difference, difference_range; //defining the variables
	lower_boundary = 1;
	difference_range = 0.00000001;
	
	while (lower_boundary * lower_boundary > difference_range * difference_range)   //the loop variable
	{
		if (DEBUG) printf("Lower: %lf Upper: %lf\n", lower, upper);		//a loop condition displaying the lower and upper boundary in debbug
		lower_boundary = f(lower);
		up_boundary = f(upper);
		if (DEBUG) printf("F lower: %lf F upper: %lf\n", lower_boundary, up_boundary);	//display flow and fup only in debbug mode
		absolute_difference = fabs(fabs(lower_boundary) - fabs(up_boundary));
		if (DEBUG) printf("Absolute diff: %lf\n", absolute_difference);					//display absolute_difference only in debbug mode

		middle = (lower + upper) / 2;
		if (DEBUG) printf("Middle: %15.10lf\n", middle);					//display middle only in debbug mode
		mid_region = f(middle);
		if (DEBUG) printf("F middle: %lf\n\n\n", mid_region);					//display fmid only in debbug mode

		if (mid_region > 0)
			lower = middle;
		else
			upper = middle;
	}
	return middle;
}
double d(double x, double h) {
	return (f(x + h) - f(x - h)) / (2 * h);		//Derivated of a the function f
}

double extreme_value(double lower, double upper) {
	double operate, check;
	operate = (lower + upper) / 2;
	check = 0.00000001;

	while ((upper - lower) * (upper - lower) >= check * check) {
		operate = (lower + upper) / 2;
		if (d(lower, check) * d(operate, check) > 0) 
		{
			lower = operate;
		}
		else {
			upper = operate;
		}
	}
	return operate;
}
