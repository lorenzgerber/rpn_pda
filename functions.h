/*
 * These functions were implemented for an assignment in course DV2:
 * Algorithms and problemsolving 7.5 p, 5DV169
 */


#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "pda.h"

/*
 * Functions that check the input value for a certain
 * condition (value) and return true or false
 */



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
 * Function that checks for a blank.
 */
int isBlank(int toCheck);

/*
 * Function to check if input is empty/used up
 * if inputLeft = zero, function returns true
 */
int isTerminal(int input);


/*
 * Function that checks for the int value of a '$' char
 */
int isDollarSymbol(int toCheck);






/*
 * functions that provide output for the push operation
 */



/*
 * Function that returns the int 256. 256 is
 * evaluated in the push condition of a transition
 * as 'push Input on the stack'
 */
int pushInput(void* pda);


/*
 * Function that returns the int value of a '$' char
 */
int dollarSymbol(void *pda);


/*
 * Function that returns the int value of a blank char
 * Used in the 'push' condition of a transition.
 */
int blankChar(void *pda);


/*
 * Function to assemble multi digit numbers
 */
int multiDigitAssemble(void *pda);

/*
 * Function to use the two top values of the
 * stack with operand from input
 */
int calcTopTwoStack(void *pda);

/*
 * Function to Print the top of the stack to stdout
 */
int printTopStack(void *pda);






// functions used for the bracket machine

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