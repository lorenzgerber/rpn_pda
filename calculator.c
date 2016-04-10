#include "calculator.h"


void calculator(Pda *rpn){

    /*
* Creating states for the Reverse Polish Notation Automaton
*/
    State *start_calc = state_create(0, false, "start");
    State *first_calc = state_create(1, false, "accumulator");
    State *second_calc = state_create(2, false, "remove blanks");
    State *third_calc = state_create(3, true, "end");


    /*
     * Creating transitions to Reverse Polish Notation Automaton
     * Comment, source, dest, read, pop, push
     */
    Transition *t_01_calc = trans_create(rpn, "1, B,e->e", 0, isBlank, NULL, NULL);
    Transition *t_02_calc = trans_create(rpn, "2, N,e->I", 1, isdigit, NULL, pushInputInt);
    Transition *t_03_calc = trans_create(rpn, "3, N,e->A", 1, isdigit, NULL, multiDigitAssemble);
    Transition *t_04_calc = trans_create(rpn, "4, O,e->C", 1, isOperator, NULL, calcTopTwoStack);
    Transition *t_05_calc = trans_create(rpn, "5, B,e->e", 2, isBlank, NULL, NULL);
    Transition *t_06_calc = trans_create(rpn, "6, N,e->I", 1, isdigit, NULL, pushInputInt);
    Transition *t_07_calc = trans_create(rpn, "7, B,e->e", 2, isBlank, NULL, NULL);
    Transition *t_08_calc = trans_create(rpn, "8, O,e->C", 1, isOperator, NULL, calcTopTwoStack);
    Transition *t_09_calc = trans_create(rpn, "9, T,e->P", 3, isTerminal, NULL, printTopStack);
    Transition *t_10_calc = trans_create(rpn, "10, T,e->P", 3, isTerminal, NULL, printTopStack);

    /*
     * Adding transitions to the states
     */
    state_addTransition(start_calc, t_01_calc);
    state_addTransition(start_calc, t_02_calc);
    state_addTransition(first_calc, t_03_calc);
    state_addTransition(first_calc, t_04_calc);
    state_addTransition(first_calc, t_05_calc);
    state_addTransition(second_calc, t_06_calc);
    state_addTransition(second_calc, t_07_calc);
    state_addTransition(second_calc, t_08_calc);
    state_addTransition(second_calc, t_09_calc);
    state_addTransition(first_calc, t_10_calc);


    /*
     * Adding states to the pda
     */
    pda_addState(rpn, start_calc);
    pda_addState(rpn, first_calc);
    pda_addState(rpn, second_calc);
    pda_addState(rpn, third_calc);

}