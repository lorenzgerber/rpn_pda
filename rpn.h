/*
 * This datatype was designed and implemented for an assignment in course DV2:
 * Algorithms and problemsolving 7.5 p, 5DV169
 */

#ifndef RPN
#define RPN

#include <stdbool.h>
#include "stack_1cell.h"

typedef struct {
    stack *rpnStack;
    int firstOperand;
    int secondOperand;
    char *input;
    int decCount;
    int assemble;
    int inputPos;
    int inputLeft;
    memFreeFunc *freeFunc;
} Rpn;


/*
 * Function to create a new rpn calculation
 */
int *rpn_calc(char *input);






#endif /*RPN*/