/*
 * These functions were implemented for an assignment in course DV2:
 * Algorithms and problemsolving 7.5 p, 5DV169
 */


#include <stdbool.h>
#include <ctype.h>


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
 * Function used as epsilon condition in transitions
 */
int isEpsilon(char toCheck){
    return 1;
}

char pushInput(char toPush){
    return toPush;
}