/*
 * These functions were implemented for an assignment in course DV2:
 * Algorithms and problemsolving 7.5 p, 5DV169
 */


#include <stdbool.h>

/*
 * Function that checks for operator. If the provided argument
 * is one of the four base operators, the function returns 1
 */
int isOperator(int toCheck);


/*
 * Function used as epsilon condition in transitions
 */
int isEpsilon(int toCheck);

/*
 * Function that returns the argument
 */
int pushInput(int);

/*
 * Function that checks for a blank.
 */
int isBlank(int toCheck);

/*
 * Function to check if input is empty/used up
 * if inputLeft = zero, function returns true
 */
int isTerminal(int input);

/*
 * Function that returns the int value ofa a '$' char
 */
int dollarSymbol(int notUser);

/*
 * Function that returns the int value ofa a '$' char
 */
int isDollarSymbol(int toCheck);

/*
 * Function that returns the int value of a blank char
 */
int blankChar(int notUsed);

/*
 * Function that checks for a '(' char
 */
int isOpeningBracket(int toCheck);


/*
 * Function that checks for a ')' char
 */
int isClosingBracket(int toCheck);

/*
 * Function that returns the int value ofa a '(' char
 */
int openingBracket(int notUsed);

/*
 * Function to assemble multi digit numbers
 */
int mulitDigitAssemble(int toCheck);

/*
 * Function to use the two top values of the
 * stack with operand from input
 */
int calcTopTwoStack(int notUsed);

/*
 * Function to Print the top of the stack to stdout
 */
int printTopStack(int notUsed);