/*
 * These functions were implemented for an assignment in course DV2:
 * Algorithms and problemsolving 7.5 p, 5DV169
 */


#include <stdbool.h>

/*
 * Function that checks for operator. If the provided argument
 * is one of the four base operators, the function returns 1
 */
int isOperator(char toCheck);


/*
 * Function used as epsilon condition in transitions
 */
int isEpsilon(char toCheck);

/*
 * Function that returns the argument
 */
int pushInput(int);