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




    // check if there is a start state (0)
    int *zero = calloc(1,sizeof(int));
    *zero = 0;
    State *start = (State*)table_lookup(pda->pdaStateTable, zero);

    if(start){
        printf("start state found\n");
    } else {
        printf("start state missing\n");
        free(zero);
        return 0;
    }

    int inputPos = 0;
    pda->currentInput = input[inputPos];


    // get first position in transitions dlist
    dlist_position currentTransPos = dlist_first(start->transitions);

    // dlist position of transition to do
    dlist_position possibleTransPos;

    // Loop through transitions until last position
    while(!dlist_isEnd(start->transitions, currentTransPos)){
        printf("not the end yet\n");

        // Access data of current Transition

        Transition *currentTransition;
        currentTransition = (Transition*)dlist_inspect(start->transitions, currentTransPos);
        printf("%s\n", currentTransition->description);



        // first check if Read is epsilon, if so, skip
        // check for type
        if(!transition_checkReadEpsilon(currentTransition)){
            if(transition_checkRead(currentTransition, *input)){
                printf("checkRead is OK\n");
            } else {
                printf("checkRead fail\n");
            }
        }


        // first check if Pop is epsilon, if so, skip
        // check for type
        if(!transition_checkPopEpsilon(currentTransition)){
            if(transition_checkPop(currentTransition,
                                   *(int*)stack_top(pda->pdaStack))){
                printf("checkPop is OK\n");
            } else {
                printf("checkPop fail\n");
            }
        }


        if(!transition_checkPushEpsilon(currentTransition)){
            if(transition_checkPush(currentTransition)==256){
                printf("we push from input to stack\n");
            }
        }


        // Check if current transition is possible
        if(currentTransition->read(pda->currentInput)){
            if(stack_isEmpty(pda->pdaStack)){

                printf("Stack is empty\n");

            } else {
                printf("Stack is not empty\n");
            }
        } else {
            printf("input data does not fit\n");
        }

        int * toStack = calloc(1, sizeof(int));
        *toStack = input[inputPos];

        stack_push(pda->pdaStack, toStack);
        free(toStack);



        // go to next transition
        currentTransPos = dlist_next(start->transitions, currentTransPos);
    }

    printf("test stack %d\n", *(int*)stack_top(pda->pdaStack));

    // do an actual transition

    // looping through the input string
    for(int iii = 0; iii < strlen(input);iii++){
        //printf("%c\n", input[iii]);

    }


    return 0;
}
