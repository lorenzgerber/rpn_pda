/*
 * These functions were implemented for an assignment in course DV2:
 * Algorithms and problemsolving 7.5 p, 5DV169
 */


#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>


/*
 * Function that checks for operator. If the provided argument
 * is one of the four base operators, the function returns 1
 */
int isOperator(char toCheck){
    if(toCheck == 42 || toCheck == 43 || toCheck == 45 || toCheck == 47){
        return 1;
    }
    return 0;
}

/*
 * Function that checks for a blank.
 */
int isBlank(char toCheck){
    if(toCheck == 32){
        printf("This is a blank\n");
        return 1;
    }
    return 0;

}

/*
 * Function used as epsilon condition in transitions
 */
int isEpsilon(char notUsed){
    return 1;
}

int pushInput(int notUsed){
    return 256;
}

/*
 * Function to check if input is empty/used up
 */
int isTerminal(int inputLeft){
    if(inputLeft == 0){
        printf("input is empty/used up");
        return 1;
    }
    return 0;
}