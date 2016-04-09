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

#include "rpn.h"
#include <stdio.h>
#include "pda.h"
#include <ctype.h>
#include "functions.h"
#include "validator.h"





int wrongArgs(void);

int main(int argc, char **argv) {

    /*
     * Check number of command line arguments
     */
    if(argc <= 1){
        return wrongArgs();
    }


    /*
     * Creating a Push Down Automaton
     */
    Pda *rpn_pda = pda_create();


    validator(rpn_pda);






    /*
     * make copy of input string for rpn calculation
     */
    char *rpn_input = calloc(strlen(argv[1]),255);
    strcpy(rpn_input, argv[1]);



    /*
     * actual pda execution
     * The third argument will do diagnostic printout on the screen when true.
     */
    pda_execute(rpn_pda, argv[1], false);

    // if the pda ends in an accepted state, start the calculation function
    if (rpn_pda->succeed) {
        rpn_calc(rpn_input);
    }


    /*
     * Clean up
     */
    free(rpn_input);
    pda_free(rpn_pda);


    return 0;
}

/*
 * screen output in case of missing argument
 */
int wrongArgs(void){
    printf("Wrong args\n");
    return 0;
}