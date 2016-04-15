/*
 * This program was designed and implemented for a mandatory assignment in the
 * course DV2: Algorithms and problemsolving 7.5 p, 5DV169
 *
 * This program creates and configures a Push Down Automaton that
 * validates one commandline argument for 'Bracket matching'.
 *
 * @input: command line arg expression, between double quotes
 *
 */

#include <stdio.h>
#include "pda.h"
#include "functions.h"



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


    /*
     * Creating states for the Reverse Polish Notation Automaton
     */
    State *start = state_create(0, false, "start");
    State *first = state_create(1, true, "q1");
    State *second = state_create(2, false, "q2");


    /*
     * Creating transitions to Reverse Polish Notation Automaton
     * Comment, source, dest, read, pop, push
     */
    Transition *t_01 = trans_create(rpn_pda, "1, e,e->$", 1, NULL, NULL, dollarSymbol);
    Transition *t_02 = trans_create(rpn_pda, "2, (,e->(", 2, isOpeningBracket, NULL, openingBracket);
    Transition *t_03 = trans_create(rpn_pda, "3, e,$->$", 1, NULL, isDollarSymbol, dollarSymbol);
    Transition *t_04 = trans_create(rpn_pda, "4, (,e->(", 2, isOpeningBracket, isOpeningBracket, openingBracket);
    Transition *t_05 = trans_create(rpn_pda, "5, ),(->e", 2, isClosingBracket, isOpeningBracket,NULL);



    /*
     * Adding transitions to the states
     */
    state_addTransition(start, t_01);
    state_addTransition(first, t_02);
    state_addTransition(second, t_03);
    state_addTransition(second, t_04);
    state_addTransition(second, t_05);


    /*
     * Adding states to the pda
     */
    pda_addState(rpn_pda, start);
    pda_addState(rpn_pda, first);
    pda_addState(rpn_pda, second);



    /*
     * actual pda execution
     * The third argument will do diagnostic printout on the screen when true.
     */
    pda_execute(rpn_pda, argv[1], false);

    // if the pda ends in an accepted state, report it
    if (rpn_pda->succeed) {
        printf("Accepted\n");
    }


    /*
     * Clean up
     */
    pda_free(rpn_pda);


    return 0;
}

int wrongArgs(void){
    printf("Wrong args\n");
    return 0;
}