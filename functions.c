/*
 * These functions were implemented for an assignment in course DV2:
 * Algorithms and problemsolving 7.5 p, 5DV169
 */
#include "functions.h"


/*
 * Functions that check the input value for a certain
 * condition (value) and return true or false
 */



/*
 * Function that checks for operator. If the provided argument
 * is one of the four base operators, the function returns 1
 */
int isOperator(int toCheck){
    if(toCheck == 42 || toCheck == 43 || toCheck == 45 || toCheck == 47)
        return 1;
    return 0;
}

/*
 * Function that checks for a blank.
 * returns 'true' if toCheck is a Blank
 */
int isBlank(int toCheck){
    if(toCheck == 32)
        return 1;
    return 0;

}

/*
 * Function used as epsilon condition in transitions:
 * on calling, it always returns true.
 */
int isEpsilon(int notUsed){
    return 1;
}



/*
 * Function to check if input is empty/used up.
 * Returns 'true' if input is the EOF ascii character 4.
 */
int isTerminal(int input){
    if(input == 4)
        return 1;
    return 0;
}


/*
 * Function that checks for a '$' char. returns
 * 'true' if 'toCheck' is 36 (ascii value for dollar symbol).
 */
int isDollarSymbol(int toCheck){
    if(toCheck == 36)
        return 1;
    return 0;
}






/*
 * functions that provide output for the push operation
 */

int pushAlphabet(void *pda){
    int *pusherHandle = calloc(1, sizeof(int));
    *pusherHandle = transition_checkPush(((Pda *)pda)->possibleTransition);
    stack_push( ((Pda *) pda)->pdaStack, pusherHandle);

}

/*
 * Function that returns the int 256. 256 is
 * evaluated in the push condition of a transition
 * as 'push Input on the stack'
 */
int pushInput(void *pda){
    int *pusherHandle = calloc(1, sizeof(int));
    *pusherHandle = (int) ((Pda *)pda)->input[0];
    stack_push( ((Pda *) pda)->pdaStack, pusherHandle);
    return 256;
}


/*
 * Function that returns the int value of a '$' char.
 * Used in the 'push' condition of a transition.
 */
int dollarSymbol(void *pda){
    return 36;
}



/*
 * Function that returns the int value of a blank char.
 * Used in the 'push' condition of a transition.
 */
int blankChar(void *pda){
    return 32;
}



/*
 * Function to assemble multi digit numbers
 * and return the assembled value
 */
int mulitDigitAssemble(void *pda){

    return 1;
}

/*
 * Function to use the two top values of the
 * stack with operand from input and return
 * the result
 *
 */
int calcTopTwoStack(void *pda){

    return 1;
}

/*
 * Function that returns the top of the stack
 */
int printTopStack(void *pda){

    return 1;
}










/*
 * Function that checks for a '(' char
 */
int isOpeningBracket(int toCheck){
    if(toCheck == 40)
        return 1;
    return 0;
}


/*
 * Function that checks for a ')' char
 */
int isClosingBracket(int toCheck){
    if(toCheck == 41)
        return 1;
    return 0;
}

/*
 * Function that returns the int value ofa a '(' char.
 * Used in the 'push' condition of a transition.
 */
int openingBracket(int notUsed){
    return 40;
}