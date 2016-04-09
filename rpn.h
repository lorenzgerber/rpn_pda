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
 * Function to start a new rpn calculation
 */
int *rpn_calc(char *input);


/*
 * lookup table and functions
 * to parse char operators
 * This method was adapted freely
 * from a StackOverflow post:
 * http://stackoverflow.com/a/22114821
 */
int (*ops[6])(int, int);
int mul(int f, int s);
int plus(int f, int s);
int sub(int f, int s);
int divi(int f, int s);


#endif /*RPN*/