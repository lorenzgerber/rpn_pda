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
 * Function to calculate an rpn expression
 */
int *rpn_calc(char *input){
    Rpn *rpn = calloc(sizeof(Rpn), 1);
    if(!rpn)
        return NULL;

    rpn->rpnStack = stack_empty();
    stack_setMemHandler(rpn->rpnStack, free);

    //printf("\nnow calculating the rpn expression \n");

    // Register input and input length to pda
    rpn->input = input;
    rpn->inputLeft = (int)strlen(rpn->input);
    rpn->inputPos = 0;
    rpn->decCount = 0;
    rpn->assemble = 0;



    while(rpn->inputLeft > 0){
        //printf("current input %c\n", rpn->input[rpn->inputPos]);
        if (rpn->input[rpn->inputPos] == 32) {
            //printf("this is a blank\n");

            if(rpn->decCount > 0){
                int *pushHandle = calloc(1, sizeof(int));
                *pushHandle = rpn->assemble;
                //printf("push to stack: %d\n", *pushHandle);
                stack_push(rpn->rpnStack, pushHandle);
                //free(pushHandle);
                rpn->assemble = 0;
                rpn->decCount = 0;
            }

        }

        if (isdigit(rpn->input[rpn->inputPos])) {
            //printf("this is a digit\n");
            char *charHandle = calloc(1, sizeof(char));
            *charHandle = rpn->input[rpn->inputPos];
            rpn->assemble = rpn->assemble * 10 + atoi(charHandle);
            free(charHandle);
            rpn->decCount++;

        }

        if (rpn->input[rpn->inputPos] == 42){
            //printf("this is a *\n");

            if(rpn->decCount > 0){
                int *pushHandle = calloc(1, sizeof(int));
                *pushHandle = rpn->assemble;
                //printf("push to stack: %d\n", *pushHandle);
                stack_push(rpn->rpnStack, pushHandle);
                //free(pushHandle);
                rpn->assemble = 0;
                rpn->decCount = 0;
            }

            rpn->secondOperand = *(int*)stack_top(rpn->rpnStack);
            stack_pop(rpn->rpnStack);
            rpn->firstOperand = *(int*)stack_top(rpn->rpnStack);
            stack_pop(rpn->rpnStack);
            int *pushHandle = calloc(1, sizeof(int));
            *pushHandle = rpn->firstOperand * rpn->secondOperand;
            stack_push(rpn->rpnStack, pushHandle);

        }

        if (rpn->input[rpn->inputPos] == 43){
            //printf("this is a +\n");

            if(rpn->decCount > 0){
                int *pushHandle = calloc(1, sizeof(int));
                *pushHandle = rpn->assemble;
                //printf("push to stack: %d\n", *pushHandle);
                stack_push(rpn->rpnStack, pushHandle);
                //free(pushHandle);
                rpn->assemble = 0;
                rpn->decCount = 0;
            }

            rpn->secondOperand = *(int*)stack_top(rpn->rpnStack);
            stack_pop(rpn->rpnStack);
            rpn->firstOperand = *(int*)stack_top(rpn->rpnStack);
            stack_pop(rpn->rpnStack);
            int *pushHandle = calloc(1, sizeof(int));
            *pushHandle = rpn->firstOperand + rpn->secondOperand;
            stack_push(rpn->rpnStack, pushHandle);

        }

        if (rpn->input[rpn->inputPos] == 45){
            //printf("this is a -\n");

            if(rpn->decCount > 0){
                int *pushHandle = calloc(1, sizeof(int));
                *pushHandle = rpn->assemble;
                //printf("push to stack: %d\n", *pushHandle);
                stack_push(rpn->rpnStack, pushHandle);
                //free(pushHandle);
                rpn->assemble = 0;
                rpn->decCount = 0;
            }

            rpn->secondOperand = *(int*)stack_top(rpn->rpnStack);
            stack_pop(rpn->rpnStack);
            rpn->firstOperand = *(int*)stack_top(rpn->rpnStack);
            stack_pop(rpn->rpnStack);
            int *pushHandle = calloc(1, sizeof(int));
            *pushHandle = rpn->firstOperand - rpn->secondOperand;
            stack_push(rpn->rpnStack, pushHandle);

        }

        if(rpn->input[rpn->inputPos] == 47){
            //printf("this is a /\n");

            if(rpn->decCount > 0){
                int *pushHandle = calloc(1, sizeof(int));
                *pushHandle = rpn->assemble;
                //printf("push to stack: %d\n", *pushHandle);
                stack_push(rpn->rpnStack, pushHandle);
                //free(pushHandle);
                rpn->assemble = 0;
                rpn->decCount = 0;
            }

            rpn->secondOperand = *(int*)stack_top(rpn->rpnStack);
            stack_pop(rpn->rpnStack);
            rpn->firstOperand = *(int*)stack_top(rpn->rpnStack);
            stack_pop(rpn->rpnStack);
            int *pushHandle = calloc(1, sizeof(int));
            *pushHandle = rpn->firstOperand / rpn->secondOperand;
            stack_push(rpn->rpnStack, pushHandle);
        }


        rpn->inputLeft--;
        rpn->inputPos++;
    }

    printf("result = %d \n", *(int*)stack_top(rpn->rpnStack));


    return 0;
}


