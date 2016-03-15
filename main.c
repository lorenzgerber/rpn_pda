/*
 * This program was designed and implemented for a mandatory assignment in the
 * course DV2: Algorithms and problemsolving 7.5 p, 5DV169
 */

#include <stdbool.h>
#include <stdio.h>
#include "pda.h"
#include <ctype.h>
#include "dlist.h"

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
    State *first = state_create(0, false, "This is the first state");
    State *second = state_create(1, true, "This is the second state");


    // Test creating transitions
    Transition *trans1 = transition_create("this is the transition from a to b",0, 1, isdigit, isdigit,isdigit,NULL);
    Transition *trans2 = transition_create("this is the transition from b to c",0, 1, isdigit, isdigit, isdigit, NULL);
    Transition *trans3 = transition_create("this is the transition fron c to d",0, 1, isdigit, isdigit, isdigit, NULL);




    // Test adding states to state
    state_addTransition(first, trans1);
    state_addTransition(first, trans2);
    printf("state id %d\n", state_getId(first));

    state_addTransition(second, trans3);

    if(!state_isEmpty(first))
        printf("no longer empty\n");

    // Test adding state to pda
    pda_addState(rpn_pda, first);
    pda_addState(rpn_pda, second);



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