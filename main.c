/*
 * This program was designed and implemented for a mandatory assignment in the
 * course DV2: Algorithms and problemsolving 7.5 p, 5DV169
 */

#include "rpn.h"
#include <stdbool.h>
#include <stdio.h>
#include "pda.h"
#include <ctype.h>
#include "dlist.h"
#include "functions.h"
#include <string.h>


int wrongArgs(void);

int main(int argc, char **argv) {

    // Check number of command line arguments
    if(argc <= 1){
        return wrongArgs();
    }

    /*
     * Defining and Initializing Variables
     */


    /*
     * Starting up Push Down Automaton
     */
    Pda *rpn_pda = pda_create();


    // Test creating states
    //State *first = calloc(1, sizeof(State));
    State *start = state_create(0, false, "start");
    State *first = state_create(1, false, "initialized");
    State *second = state_create(2, false, "unterminated");
    State *third = state_create(3, false, "terminated");
    State *fourth = state_create(4, false, "processing 1st operand");
    State *fifth = state_create(5, false, "processing 2nd operand");
    State *sixth = state_create(6, false, "check terminal");
    State *seventh = state_create(7, true, "success");


    // Creating transitions to check for RPN
    // Comment, source, dest, read, pop, push
    Transition *trans_01 = transition_create("1, e,e->$", 1, NULL, NULL, dollarSymbol);
    Transition *trans_02 = transition_create("2, B,e->e", 1, isBlank, NULL, NULL);
    Transition *trans_03_1 = transition_create("3, N,e->I", 2, isdigit, NULL, pushInput);
    Transition *trans_03_2 = transition_create("3, N,e->I", 2, isdigit, NULL, pushInput);
    Transition *trans_03_3 = transition_create("3, N,e->I", 2, isdigit, NULL, pushInput);
    Transition *trans_04 = transition_create("4, O,e->e", 4, isOperator, NULL, NULL);
    Transition *trans_05 = transition_create("5, B,e->I", 3, isBlank, NULL, pushInput);
    Transition *trans_06 = transition_create("6, T,N->e", 6, isTerminal, NULL, NULL);
    Transition *trans_07 = transition_create("7, O,B->e", 4, isOperator, isBlank, NULL);
    Transition *trans_08 = transition_create("8, T,B->e", 6, isTerminal, isBlank, NULL);
    Transition *trans_09 = transition_create("9, e,N->e", 4, NULL, isdigit, NULL);
    Transition *trans_10 = transition_create("10, e,B->e", 5, NULL, isBlank, NULL);
    Transition *trans_11 = transition_create("11, e,e->B", 3, NULL, NULL, blankChar);
    Transition *trans_12 = transition_create("12, e,N->e", 6, NULL, isdigit, NULL);
    Transition *trans_13 = transition_create("13, e,$->e", 7, NULL, isDollarSymbol, NULL);
    Transition *trans_14 = transition_create("14, B,e->e", 3, isBlank, NULL, NULL);


    // Adding transitions to state
    state_addTransition(start, trans_01);
    state_addTransition(first, trans_02);
    state_addTransition(first, trans_03_1);
    state_addTransition(second, trans_03_2);
    state_addTransition(second, trans_04);
    state_addTransition(second, trans_05);
    state_addTransition(second, trans_06);
    state_addTransition(third, trans_03_3);
    state_addTransition(third, trans_07);
    state_addTransition(third, trans_08);
    state_addTransition(third, trans_14);
    state_addTransition(fourth, trans_09);
    state_addTransition(fourth, trans_10);
    state_addTransition(fifth, trans_11);
    state_addTransition(sixth, trans_12);
    state_addTransition(sixth, trans_13);

    // Adding states to pda
    pda_addState(rpn_pda, start);
    pda_addState(rpn_pda, first);
    pda_addState(rpn_pda, second);
    pda_addState(rpn_pda, third);
    pda_addState(rpn_pda, fourth);
    pda_addState(rpn_pda, fifth);
    pda_addState(rpn_pda, sixth);
    pda_addState(rpn_pda, seventh);


    /*
     * Processing input
     */



    /*
     * make copy of input string for rpn calculation
     */
    char *rpn_input = calloc(strlen(argv[1]),255);
    strcpy(rpn_input, argv[1]);

    /*
     * actual pda exectuion
     */

    pda_execute(rpn_pda, argv[1]);
    if (rpn_pda->succeed) {
        rpn_calc(rpn_input);

    }

    free(rpn_input);

    pda_free(rpn_pda);

    return 0;
}

int wrongArgs(void){
    printf("Wrong args\n");
    return 0;
}