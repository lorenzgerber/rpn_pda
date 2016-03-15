/*
 * These functions were implemented for an assignment in course DV2:
 * Algorithms and problemsolving 7.5 p, 5DV169
 */


#include <stdbool.h>
#include <ctype.h>

int isOperator(char toCheck){
    if(toCheck == 42 || toCheck == 43 || toCheck == 45 || toCheck == 47){
        return 1;
    }
    return 0;
}

int isEpsilon(char toCheck){
    return 3;
}