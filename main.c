/*
 * This program was designed and implemented for a mandatory assignment in the
 * course DV2: Algorithms and problemsolving 7.5 p, 5DV169
 */

#include <stdbool.h>
#include <stdio.h>
#include "pda.h"
#include <ctype.h>
#include "dlist.h"
#include "functions.h"

int wrongArgs(void);

int main(int argc, char **argv) {

    /*
     * Defining and Initializing Variables
     */


    /*
     * Starting up Push Down Automaton
     */
    Pda *rpn_pda = pda_create();


    // Test creating states
    //State *first = calloc(1, sizeof(State));
    State *start = state_create(0, false, "Accept number or blank");
    State *first = state_create(1, true, "Non-terminated number");
    State *second = state_create(2, false, "top of stack to be discareded");
    State *third = state_create(3, true, "Accept number or blank");


    // Test creating transitions
    // Comment, source, dest, read, pop, push
    Transition *trans1 = transition_create("transition when first input is a blank",2, isBlank, NULL, pushInput);
    Transition *trans2 = transition_create("this is the transition from b to c",2, isdigit, isBlank, NULL);
    Transition *trans3 = transition_create("pop the top of the stack, then back to 0",0, NULL, isBlank, NULL);
    Transition *trans4 = transition_create("first input is a number", 1, isdigit, NULL, pushInput);
    Transition *trans5 = transition_create("terminating first number", 3, isBlank, NULL, pushInput);


    // Test adding transitions to state
    state_addTransition(start, trans1);
    state_addTransition(start, trans4);
    state_addTransition(first, trans4);
    state_addTransition(first, trans5);
    state_addTransition(second, trans3);

    // Test adding state to pda
    pda_addState(rpn_pda, start);
    pda_addState(rpn_pda, first);
    pda_addState(rpn_pda, second);
    pda_addState(rpn_pda, third);


    /*
     * Processing input
     */

	// Check number of command line arguments
    if(argc <= 1){
        return wrongArgs();
    }
    printf("%s\n", argv[1]);


    /*
     * actual pda exectuion
     */

    pda_execute(rpn_pda, argv[1]);

    return 0;
}

int wrongArgs(void){
    printf("Wrong args\n");
    return 0;
}