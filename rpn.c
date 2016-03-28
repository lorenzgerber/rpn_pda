/*
 * This datatype was designed and implemented for an assignment in course DV2:
 * Algorithms and problemsolving 7.5 p, 5DV169
 */

#include "rpn.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>


/*
 * creating a lookup table and functions
 * to parse char operators
 */
int (*ops[6])(int, int);
int mul(int f, int s) { return f * s; }
int plus(int f, int s) { return f + s; }
int sub(int f, int s) { return f - s; }
int divi(int f, int s) { return f / s; }



/*
 * Function to calculate an rpn expression
 */
int *rpn_calc(char *input){
    Rpn *rpn = calloc(sizeof(Rpn), 1);
    if(!rpn)
        return NULL;

    rpn->rpnStack = stack_empty();
    stack_setMemHandler(rpn->rpnStack, free);


    // Register input and input length to pda
    rpn->input = input;
    rpn->inputLeft = (int)strlen(rpn->input);
    rpn->inputPos = 0;
    rpn->decCount = 0;
    rpn->assemble = 0;

    ops[0] = &mul;
    ops[1] = &plus;
    ops[3] = &sub;
    ops[5] = &divi;




    while(rpn->inputLeft > 0){

        // checking for blanks
        if (rpn->input[rpn->inputPos] == 32) {
            if(rpn->decCount > 0){
                //pushing to stack
                int *pushHandle = calloc(1, sizeof(int));
                *pushHandle = rpn->assemble;
                stack_push(rpn->rpnStack, pushHandle);
                rpn->assemble = 0;
                rpn->decCount = 0;
            }

        }

        // check for a digit
        if (isdigit(rpn->input[rpn->inputPos])) {
            char *charHandle = calloc(2, sizeof(char));
            *charHandle = rpn->input[rpn->inputPos];
            rpn->assemble = rpn->assemble * 10 + atoi(charHandle);
            free(charHandle);
            rpn->decCount++;

        }


        /*
         * The actual calculation part.
         * uses a lookup table to parse the
         * operators
         */
        if (rpn->input[rpn->inputPos] == 42 ||
                rpn->input[rpn->inputPos] == 43 ||
                rpn->input[rpn->inputPos] == 45 ||
                rpn->input[rpn->inputPos] == 47){

            if(rpn->decCount > 0){
                // push to the stack first
                int *pushHandle = calloc(1, sizeof(int));
                *pushHandle = rpn->assemble;
                stack_push(rpn->rpnStack, pushHandle);
                rpn->assemble = 0;
                rpn->decCount = 0;
            }

            // read second operand from stack
            rpn->secondOperand = *(int*)stack_top(rpn->rpnStack);
            stack_pop(rpn->rpnStack);

            // read first operand from stack
            rpn->firstOperand = *(int*)stack_top(rpn->rpnStack);
            stack_pop(rpn->rpnStack);

            int *pushHandle = calloc(1, sizeof(int));

            // actual calculation
            *pushHandle =  ops[rpn->input[rpn->inputPos] - 42]
                    (rpn->firstOperand, rpn->secondOperand);

            // push result back on the stack
            stack_push(rpn->rpnStack, pushHandle);

        }




        rpn->inputLeft--;
        rpn->inputPos++;
    }

    // screen output of result
    if(rpn->decCount!=0){
        printf("%d\n", rpn->assemble);
    } else {
        printf("%d\n", *(int*)stack_top(rpn->rpnStack));
    }
    stack_free(rpn->rpnStack);
    free(rpn);

    return 0;
}


