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
} Rpn;


/*
 * Function to create a new rpn calculation
 */
int *rpn_calc(char *input);


/*
 * creating a lookup table and functions
 * to parse char operators
 */
int (*ops[6])(int, int);
int mul(int f, int s);
int plus(int f, int s);
int sub(int f, int s);
int divi(int f, int s);


#endif /*RPN*/