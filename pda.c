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

    // Find the next possible transition
    pda_getPossibleTransition(pda);

    // Do transition
    pda_doTransition(pda);

    // Find the next possible transition
    pda_getPossibleTransition(pda);





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
 * pda_getNewState
 *
 * Function to check which transition of a state to take
 *
 * input:   - State *currentState
 *          - char *current input
 *          - State *nextState
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
    int transPushCheckFlag = 0;
    int transNumberCounter = 1;
    int nextTransition = 0;

    // Get first transition
    dlist_position currentTransPos = dlist_first(pda->currentState->transitions);

    // Loop through transitions until last position
    while(!dlist_isEnd(pda->currentState->transitions, currentTransPos)){

        // set Read, Pop and Push Check flag to zero
        transReadCheckFlag = 0;
        transPopCheckFlag = 0;
        transPushCheckFlag = 0;


        // Access current Transition
        Transition *currentTransition;
        currentTransition = (Transition*)dlist_inspect(pda->currentState->transitions, currentTransPos);
        printf("%s\n", currentTransition->description);


        // check for read condition
        if(transition_checkReadEpsilon(currentTransition)) {
            transReadCheckFlag = 1;
        } else {
            if(transition_checkRead(currentTransition, *pda->input)){
                printf("checkRead is OK\n");
                transReadCheckFlag = 1;
            } else {
                printf("checkRead fail\n");
            }
        }

        // check for pop condition
        if(transition_checkPopEpsilon(currentTransition)) {
            transPopCheckFlag = 1;
        } else {
            if(!stack_isEmpty(pda->pdaStack)){
                if(transition_checkPop(currentTransition,
                                       *(int*)stack_top(pda->pdaStack))){
                    printf("checkPop is OK\n");
                    transPopCheckFlag = 1;
                } else {
                    printf("checkPop fail\n");
                }

            } else {
                printf("checkPop fail, stack empty\n");
            }

        }


        //Check the push condition
        if(!transition_checkPushEpsilon(currentTransition)){
            transPushCheckFlag = 1;
            if(transition_checkPush(currentTransition)==256){
                printf("we push from input to stack\n");
                transPushCheckFlag = 1;
            }
        }

        // Check if all conditions met
        if (transReadCheckFlag + transPopCheckFlag + transPushCheckFlag == 3){
            if(transMainCheckFlag == 1){
                printf("pda is non-deterministic - "
                               "two viable transitions found");
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
        printf("The next transition is Nr. %d in the list\n", nextTransition);
        currentTransPos = dlist_first(pda->currentState->transitions);
        for(int iii = 0; iii < nextTransition; iii++){
            currentTransPos = dlist_next(pda->currentState->transitions, currentTransPos);
        }
        pda->possibleTransition = currentTransPos->data;


    } else {
        printf("No viable transition found!!!\n");
        return 0;
    }

    return 0;
}


/*
 * function to do transition
 */
int pda_doTransition(Pda *pda){


    // pop stack
    if(!transition_checkPopEpsilon(pda->possibleTransition)) {
        if(!stack_isEmpty(pda->pdaStack)){
            if(transition_checkPop(pda->possibleTransition,
                                   *(int*)stack_top(pda->pdaStack))){
                printf("checkPop is OK\n");
                stack_pop(pda->pdaStack);
            } else {
                printf("checkPop fail\n");
            }

        } else {
            printf("checkPop fail, stack empty\n");
        }

    }


    // push to stack
    if(!transition_checkPushEpsilon(pda->possibleTransition)){
        if(transition_checkPush(pda->possibleTransition)==256){
            printf("We're pushing %c from input to stack\n", pda->input[0]);
            stack_push(pda->pdaStack, &pda->input[0]);
        }
    }

    if(!transition_checkReadEpsilon(pda->possibleTransition)) {
        if(transition_checkRead(pda->possibleTransition, pda->input[0])){
            printf("checkRead is OK\n");
            pda->input = &pda->input[1];
            pda->inputLeft--;
        } else {
            printf("checkRead fail\n");
        }
    }


    // move to next state
    int *newstate;
    newstate = &pda->possibleTransition->destState;
    pda->currentState = table_lookup(pda->pdaStateTable, newstate);

    return 0;
}