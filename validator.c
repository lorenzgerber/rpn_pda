
#include "validator.h"


/*
 * building the rpn validator automaton
 */
void validator(Pda *rpn_pda){

    /*
    * Creating states for the Reverse Polish Notation Automaton
    */
    State *start = state_create(0, false, "start");
    State *first = state_create(1, false, "initialized");
    State *second = state_create(2, false, "unterminated");
    State *third = state_create(3, false, "terminated");
    State *fourth = state_create(4, false, "processing 1st operand");
    State *sixth = state_create(6, false, "check terminal");
    State *seventh = state_create(7, true, "success");


    /*
     * Creating transitions to Reverse Polish Notation Automaton
     * Comment, source, dest, read, pop, push
     */
    Transition *t_01 = trans_create(rpn_pda, "1, e,e->$", 1, NULL, NULL, dollarSymbol);
    Transition *t_02 = trans_create(rpn_pda, "2, B,e->e", 1, isBlank, NULL, NULL);
    Transition *t_03_1 = trans_create(rpn_pda, "3, N,e->I", 2, isdigit, NULL, pushInput);
    Transition *t_03_2 = trans_create(rpn_pda, "3, N,e->I", 2, isdigit, NULL, pushInput);
    Transition *t_03_3 = trans_create(rpn_pda, "3, N,e->I", 2, isdigit, NULL, pushInput);
    Transition *t_04 = trans_create(rpn_pda, "4, O,e->e", 4, isOperator, NULL, NULL);
    Transition *t_05 = trans_create(rpn_pda, "5, B,e->I", 3, isBlank, NULL, pushInput);
    Transition *t_06 = trans_create(rpn_pda, "6, T,N->e", 6, isTerminal, NULL, NULL);
    Transition *t_07 = trans_create(rpn_pda, "7, O,B->e", 4, isOperator, isBlank, NULL);
    Transition *t_08 = trans_create(rpn_pda, "8, T,B->e", 6, isTerminal, isBlank, NULL);
    Transition *t_09 = trans_create(rpn_pda, "9, e,N->e", 4, NULL, isdigit, NULL);
    Transition *t_10 = trans_create(rpn_pda, "10, e,B->B", 3, NULL, isBlank, blankChar);
    Transition *t_11 = trans_create(rpn_pda, "11, e,N->e", 6, NULL, isdigit, NULL);
    Transition *t_12 = trans_create(rpn_pda, "12, e,$->e", 7, NULL, isDollarSymbol, NULL);
    Transition *t_13 = trans_create(rpn_pda, "13, B,e->e", 3, isBlank, NULL, NULL);


    /*
     * Adding transitions to the states
     */
    state_addTransition(start, t_01);
    state_addTransition(first, t_02);
    state_addTransition(first, t_03_1);
    state_addTransition(second, t_03_2);
    state_addTransition(second, t_04);
    state_addTransition(second, t_05);
    state_addTransition(second, t_06);
    state_addTransition(third, t_03_3);
    state_addTransition(third, t_07);
    state_addTransition(third, t_08);
    state_addTransition(third, t_13);
    state_addTransition(fourth, t_09);
    state_addTransition(fourth, t_10);
    state_addTransition(sixth, t_11);
    state_addTransition(sixth, t_12);

    /*
     * Adding states to the pda
     */
    pda_addState(rpn_pda, start);
    pda_addState(rpn_pda, first);
    pda_addState(rpn_pda, second);
    pda_addState(rpn_pda, third);
    pda_addState(rpn_pda, fourth);
    pda_addState(rpn_pda, sixth);
    pda_addState(rpn_pda, seventh);



}