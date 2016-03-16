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
    printf("%s\n", input);
    printf("%lu\n", strlen(input));



    // detect input string length
    int inputLength = (int)strlen(input);



    // Check if there is a start state
    if(!pda_checkStartState(pda)){
        printf("There is no start state! \n");
        return 0;
    }

    // get start state
    int *zero = calloc(1,sizeof(int));
    *zero = 0;
    State *start = (State*)table_lookup(pda->pdaStateTable, zero);


    // get first input char
    int inputPos = 0;
    pda->currentInput = input[inputPos];

    // dlist position variable for transition to do
    dlist_position *possibleTransPos;


    // Get first position in transitions dlist of start state
    dlist_position currentTransPos = dlist_first(start->transitions);



    int transMainCheckFlag = 0;
    int transReadCheckFlag = 0;
    int transPopCheckFlag = 0;
    int transPushCheckFlag = 0;
    int transNumberCounter = 1;
    int nextTransition = 0;

    // Loop through transitions until last position
    while(!dlist_isEnd(start->transitions, currentTransPos)){

        // set Read, Pop and Push Check flag to zero
        transReadCheckFlag = 0;
        transPopCheckFlag = 0;
        transPushCheckFlag = 0;


        // Access current Transition
        Transition *currentTransition;
        currentTransition = (Transition*)dlist_inspect(start->transitions, currentTransPos);
        printf("%s\n", currentTransition->description);


        // check for read condition
        if(transition_checkReadEpsilon(currentTransition)) {
            transReadCheckFlag = 1;
        } else {
            if(transition_checkRead(currentTransition, *input)){
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
        currentTransPos = dlist_next(start->transitions, currentTransPos);
    }

    // announce the next transition
    if(transMainCheckFlag){
        printf("The next transition is Nr. %d in the list", nextTransition);
    } else {
        printf("No viable transition found!!!\n");
        return 0;
    }

    return 0;
}




/*
 * Function to check if there is a zero state
 */
int pda_checkStartState(Pda *pda){
    // check if there is a start state (0)
    int *zero = calloc(1,sizeof(int));
    *zero = 0;
    State *start = (State*)table_lookup(pda->pdaStateTable, zero);

    if(start){
        printf("start state found\n");
        free(zero);
        return 1;
    } else {
        printf("start state missing\n");
        free(zero);
        return 0;
    }

}

