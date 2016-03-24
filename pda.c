/*
 * This datatype was designed and implemented for an assignment in course DV2: 
 * Algorithms and problemsolving 7.5 p, 5DV169
 */


#include "pda.h"
#include "state.h"
#include "transition.h"
#include <stdlib.h>
#include <string.h>
#include "functions.h"


/*
 * function to create a new pda
 */
Pda *pda_create()
{
    Pda *pda = calloc(sizeof (Pda),1);
    if (!pda)
        return NULL;



    // initialize states table
    pda->pdaStateTable = table_create(compareInt);

    table_setKeyMemHandler(pda->pdaStateTable, free);
    table_setValueMemHandler(pda->pdaStateTable, free);

    // initialize stack
    pda->pdaStack = stack_empty();
    stack_setMemHandler(pda->pdaStack, free);

    return pda;
}

/*
 * Function to add a new state
 */
void *pda_addState(Pda *pda, State *state){
    int * stateId = calloc(1, sizeof(int));
    *stateId = state->id;
    table_insert(pda->pdaStateTable, stateId, state);
    return 0;
}

int compareInt(void *ip,void *ip2){
    return (*(int*)ip) - (*(int*)ip2);
}

/*
 * Function to execute a pda
 */
int *pda_execute(Pda *pda, char *input){

    /*
     * INITIALIZE PDA EVALUATION
     */


    /*
     * Register input and input length
     * to pda
     */

    pda->input = input;
    pda->inputLeft = (int)strlen(pda->input);



    /*
     * Set start state
     */
    if(!pda_setStartState(pda)){
        printf("There is no start state! \n");
        return 0;
    }


    while(pda->bailout == false && pda->succeed == false){
        pda_getPossibleTransition(pda);
        if(pda->bailout == false && pda->succeed == false){
            pda_doTransition(pda);
            printf("From State %d, done transition %s\n", pda->currentState->id, pda->possibleTransition->description);
            printf("input %c, input left %d\n", pda->input[0], pda->inputLeft);
            printf("bailout %d, succeed %d\n", pda->bailout, pda->succeed);
        }
    }

    return 0;

}




/*
 * Function that searches the States for the start state and
 * sets pda->currentState to start state
 */
int pda_setStartState(Pda *pda){
    // check if there is a start state (0)
    int *zero = calloc(1,sizeof(int));
    *zero = 0;
    State *start = (State*)table_lookup(pda->pdaStateTable, zero);

    if(start){
        // Start state found, will be set as currentState
        pda->currentState = (State*)table_lookup(pda->pdaStateTable, zero);
        free(zero);
        return 1;
    } else {
        free(zero);
        return 0;
    }
}

/*
 * pda_getPossibleTransition
 *
 * Function that checks the next transition to take. If two transitions
 * are possible, the function set's the bailout flag in the pda as the
 * current implementation supports just deterministic pda's.
 *
 * input:   - State *currentState
 *          - char *current input
 *
 * return   - int 0 if succeeded
 *
 */
int pda_getPossibleTransition(Pda *pda){


    /*
     * define and set some variables
     *
     */

    int transMainCheckFlag = 0;
    int transReadCheckFlag = 0;
    int transPopCheckFlag = 0;
    int transNumberCounter = 1;
    int nextTransition = 0;

    // Get first transition
    dlist_position currentTransPos = dlist_first(pda->currentState->transitions);

    // Loop through transitions until last position
    while(!dlist_isEnd(pda->currentState->transitions, currentTransPos)){

        // set Read, Pop and Push Check flag to zero
        transReadCheckFlag = 0;
        transPopCheckFlag = 0;

        // Access current Transition
        Transition *currentTransition;
        currentTransition = (Transition*)dlist_inspect(pda->currentState->transitions, currentTransPos);


        // check for read condition
        if(transition_checkReadEpsilon(currentTransition)) {
            transReadCheckFlag = 1;
        } else {
            if(transition_checkRead(currentTransition, *pda->input)){
                transReadCheckFlag = 1;
            }
        }

        // check for pop condition
        if(transition_checkPopEpsilon(currentTransition)) {
            transPopCheckFlag = 1;
        } else {
            if(!stack_isEmpty(pda->pdaStack)){
                if(transition_checkPop(currentTransition,
                                       *(int*)stack_top(pda->pdaStack))){
                    transPopCheckFlag = 1;
                }

            }

        }


        // Check if all conditions met
        if (transReadCheckFlag + transPopCheckFlag == 2){
            if(transMainCheckFlag == 1){
                printf("pda is non-deterministic - "
                               "two viable transitions found");

                // set bailout true to stop the processing
                pda->bailout = true;
            }
            transMainCheckFlag = 1;
            nextTransition = transNumberCounter;
        }

        // keep count of which transition in the list we look at
        transNumberCounter++;


        // go to next transition
        currentTransPos = dlist_next(pda->currentState->transitions, currentTransPos);
    }

    // announce the next transition
    if(transMainCheckFlag){
        currentTransPos = dlist_first(pda->currentState->transitions);
        for(int iii = 0; iii < nextTransition; iii++){
            currentTransPos = dlist_next(pda->currentState->transitions, currentTransPos);
        }
        pda->possibleTransition = currentTransPos->data;


    } else {
        printf("No viable transition found!!!\n");
        if(pda->currentState->accepted==true){
            if(pda->inputLeft==0){
                pda->succeed = true;
            }
            pda->bailout = true;
        } else {
            pda->bailout = true;
        }
        return 0;
    }

    return 0;
}


/*
 * function to do transition
 */
int pda_doTransition(Pda *pda){

    /*
     * Pop stack a,B->c
     * ----------------
     *
     * If epsilon:
     * - nothing happens, no check, no pop
     *   even if stack empty no bail-out is thrown
     *
     * If stack alphabet function:
     * - if stack empty, throw bail-out
     * - if stack alphabet function returns true, pop
     * - if stack alphabet function returns false: do nothing.
     *   Currently keep this. In the future should be possible
     *   to remove as this case should not happen because checked
     *   in get_possibleTransition().
     */

    if(!transition_checkPopEpsilon(pda->possibleTransition)) {
        if(!stack_isEmpty(pda->pdaStack)){
            if(transition_checkPop(pda->possibleTransition,
                                   *(int*)stack_top(pda->pdaStack))){
                stack_pop(pda->pdaStack);
            }
        }
    }


    /*
     * push to stack, a,b->C
     * ---------------------
     *
     * If epsilon:
     * - do nothing
     *
     * If push function returns value 0-255:
     * - push the corresponding ascii char to the
     *   the stack
     *
     * If push function returns 256:
     * - push the current input char to the stack
     *
     */
    if(!transition_checkPushEpsilon(pda->possibleTransition)){
        if(transition_checkPush(pda->possibleTransition)==256){
            int *pusherHandle = calloc(1, sizeof(char));
            *pusherHandle = (int)pda->input[0];
            stack_push(pda->pdaStack, pusherHandle);
        } else {
            int *pusherHandle = calloc(1, sizeof(char));
            *pusherHandle = transition_checkPush(pda->possibleTransition);
            stack_push(pda->pdaStack, pusherHandle);
        }
    }

    /*
     * Read transition A,b->c
     * ----------------------
     *
     * If epsilon:
     * - do nothing
     *
     * If current input alphabet function returns true:
     * - move pointer on input char array and reduce
     *   inputLeft variable by one.
     *
     * If current input alphabet function returns false:
     * - do nothing. This can be removed later as it should
     *   not happen. Should be checked already in
     *   get_possibleTransition() function
     *
     */
    if(!transition_checkReadEpsilon(pda->possibleTransition)) {
        if(transition_checkRead(pda->possibleTransition, pda->input[0])){
            pda->input = &pda->input[1];
            pda->inputLeft--;
        }
    }


    // move to next state
    int *newstate;
    newstate = &pda->possibleTransition->destState;
    pda->currentState = table_lookup(pda->pdaStateTable, newstate);

    return 0;
}