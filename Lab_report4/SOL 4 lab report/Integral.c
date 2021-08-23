/*****************************
Content: SOL1, Lab4, Exercise 1
Lecturer: Prof. Schoenen
Authors: Emmanuel Duru, and Jose Luis Roldan Rodriguez HAW Hamburg
Date: 20201112
Short description:
******************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#define COLUMNS 80

double f(double x) 
{
	return cos(M_PI * x); //pointing and mapping the midpoint to the value
}
//1a calculating the area of the rectangle 
double area(double left_x, double right_x) //a function to implement a solution to the area of the rectangles
{
	double x;
	x = (left_x + right_x) / 2; //deriving the midpoint (Ei)
	double width = right_x - left_x; //to derive the width (distance between the boundary Ei)
	double area = width * f(x); //an operation for the area of the rectangle (lenght * width)
	return area; //a returning value for the area of the rectangle
}
//1b. calculating the intermediate values (Ei) as the average between the interval boundaries 
double integral(double left_x, double right_x, int steps)
{
	double sum = 0;
	double left_side_x1, left_right_x2;
	double width = (right_x - left_x) / steps; //the difference between the midpoints (Ei) with the integration of the points
	for (int i = 0; i < steps; i++) // a foor loop 
	{
		left_side_x1 = left_x + width * i; //defines the left_x in addition to the length and its integral 
		left_right_x2 = width + left_side_x1; // defining the difference between the point (Ei) and 
		sum += area(left_side_x1, left_right_x2); //sum of the areas for both points of integration
	}
	return sum;
}


int main() {

	double result = area(-0.5, 0.5);
	printf("%lf\n", result);
	double ans = integral(-0.5, 0.5, 10);//the test steps to calculate the integration
	printf("%lf\n", ans);
}