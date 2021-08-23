//preprocessor
#include <stdio.h>

main()
{ 
	//using a data type of float for the following variables u, i, r
	float u, i, r;
	//using the printf function to output the text as shown below which gives the lines of code a good definition on the output
	printf("Please enter voltage in Volts:\n ");
	//using the scanf function to store the value of the initial variable: u
	scanf_s("%f", &u);
	//printing the ouptput, value of voltage
	printf("Voltage = %f\n", u);
	//priniting the atatement telling us to type in the value of our current on the output
	printf("Please enter current in Ampere:\n ");
	//using  scanf as a placeholder, and storing it
	scanf_s("%f", &i);
	//printing the value of the current
	printf("current = %f\n", i);
	//making a cacluation of ohms law...as mathematically rep. below
	r = u / i;
	//printing the general of the given expression ohms = division of the both variable u/i
	printf("The value of resistance R = %f/%f = %f Ohm.",u, i, r);

}