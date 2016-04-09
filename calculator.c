#include "calculator.h"


void calculator(Pda *rpn){

    /*
* Creating states for the Reverse Polish Notation Automaton
*/
    State *start = state_create(0, false, "start");
    State *first = state_create(1, false, "accumulator");
    State *second = state_create(2, false, "remove blanks");
    State *third = state_create(3, true, "end");


    /*
     * Creating transitions to Reverse Polish Notation Automaton
     * Comment, source, dest, read, pop, push
     */
    Transition *t_01 = trans_create(rpn, "1, B,e->e", 0, isBlank, NULL, NULL);
    Transition *t_02 = trans_create(rpn, "2, N,e->I", 1, isdigit, NULL, pushInput);
    Transition *t_03 = trans_create(rpn, "3, N,e->I", 1, isdigit, NULL, multiDigitAssemble);
    Transition *t_04 = trans_create(rpn, "4, O,e->C", 1, isOperator, NULL, calcTopTwoStack);
    Transition *t_05 = trans_create(rpn, "5, B,e->e", 2, isBlank, NULL, NULL);
    Transition *t_06 = trans_create(rpn, "6, N,e->I", 1, isdigit, NULL, pushInput);
    Transition *t_07 = trans_create(rpn, "7, B,e->e", 2, isBlank, NULL, NULL);
    Transition *t_08 = trans_create(rpn, "8, O,e->C", 4, isOperator, NULL, calcTopTwoStack);
    Transition *t_09 = trans_create(rpn, "9, T,e->P", 3, isTerminal, NULL, printTopStack);
    Transition *t_10 = trans_create(rpn, "10, T,e->P", 3, isTerminal, NULL, printTopStack);

    /*
     * Adding transitions to the states
     */
    state_addTransition(start, t_01);
    state_addTransition(first, t_02);
    state_addTransition(first, t_03);
    state_addTransition(second, t_04);
    state_addTransition(second, t_05);
    state_addTransition(second, t_06);
    state_addTransition(second, t_07);
    state_addTransition(third, t_08);
    state_addTransition(third, t_09);
    state_addTransition(third, t_10);

}