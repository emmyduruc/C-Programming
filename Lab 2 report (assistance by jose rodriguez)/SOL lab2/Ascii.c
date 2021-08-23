
/***************************************************************************************
Content: SOL1, Lab2, Exercise 1
Lecturer: Prof. Schoenen
Authors: Emmanuel duru and Hilary Ogalagu, HAW Hamburg
Date: 20201112
Short description: A program displaying the ASCII table
****************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>


void main()
{
    int i;                  // loop variable
    char input[40];         // Array to enter an operate a text
    void print_binary(i);   // Function to display binary codes of ASCII char.
   // char ch = 0;

    // Ex 1a, print ASCII table on the screen
    printf("       ASCII-code \n\n");
    printf("dec   hex    bin        char\n");

    for (i = 0; i <= 255; i++)                                              // for loop expression running an iteration of the Ascii code
    {

        printf("%3d    ", i);                                               // dispalying output in decimal
        printf("%2X    ", i);                                               // displaying output in hexadecimal
        print_binary(i);                                                    // dispalying output in binary
        if (i < 32)                                                         // a condition to eliminate the invalid characters 
        {
            printf("    '' \n");
        }
        else
        {
            printf("    \'%c\' \n", i);
        }      
     
    }
    //Ex 1b+c+d+e+f
    printf("\nEnter a text input: ");                                        //giving the user a command
    scanf("%s", &input);                                                     // storing the users command as the variable
    printf("\nThe text is: '%s' ",input);                                    //outputing the users command
    printf("\nThe length of the text is:%d\n", strlen(input));               // indicating the length of the command after strlened 
 
    for (int index = 0; index < strlen(input); index++)                     //a loop variable itirating through to get the users command line from the ASCII codes
    {
        char c = input[index];                                              //the index is stored assigned to c variable
        printf("%d\t %02X\t", c, c);                                        //to display the decimal and hexadecimal
        print_binary(c);                                                    // for binary output display
        printf("\t'%c'\n", c);                                              //outputing the users command
    }
    
    // Ex 1d
    char ch=" ";                                                            // declared viarable

    while ( ch != '.')                                                      // a loop variable not to 
    {
        printf("\nplease enter a character:");
        ch = getch();
        printf("%d\t %02X\t", ch, ch);
        print_binary(ch);
        printf("\t'%c'\n", ch);
    }
    return;
}
// Function to display binary codes of ASCII char.
void print_binary(int num) {
    for (int i = 8; i >= 0; i--)
    {
        int j = num >> i;

        if (j & 1)
            printf("1");
        else
            printf("0");
    }
    return;
}

