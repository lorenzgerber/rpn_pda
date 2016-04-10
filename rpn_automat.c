/*
 * This program was designed and implemented for a mandatory assignment in the
 * course DV2: Algorithms and Problemsolving 7.5 p, 5DV169
 *
 * This program creates and configures a Push Down Automaton that
 * validates one commandline argument to be of the language 'Reverse
 * Polish Notation'. If correct, the expression will be evaluated/calculated.
 *
 * @input: command line arg expression, between double quotes
 *
 */
#include <stdio.h>
#include "pda.h"
#include <ctype.h>
#include "functions.h"
#include "validator.h"
#include "calculator.h"





int wrongArgs(void);

int main(int argc, char **argv) {

    /*
     * Check number of command line arguments
     */
    if(argc <= 1){
        return wrongArgs();
    }

    /*
     * make copy of input string for rpn calculation
     */
    char *rpn_input = calloc(strlen(argv[1]),255);
    strcpy(rpn_input, argv[1]);


    /*
     * Creating and execute RPN Validator
     * Push Down Automaton
     */
    Pda *val_pda = pda_create();
    validator(val_pda);
    pda_execute(val_pda, argv[1], false);


    /*
     * creating and executing RPN Calculator
     * Push Down Automaton
     */
    if(val_pda->succeed) {
        Pda *calc_pda = pda_create();
        calculator(calc_pda);
        pda_execute(calc_pda, rpn_input, false);
        pda_free(calc_pda);
    }


    /*
     * Clean up
     */
    free(rpn_input);
    pda_free(val_pda);


    return 0;
}

/*
 * screen output in case of missing argument
 */
int wrongArgs(void){
    printf("Wrong args\n");
    return 0;
}