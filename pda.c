/*
 * This datatype was designed and implemented for an assignment in course DV2: 
 * Algorithms and problemsolving 7.5 p, 5DV169
 */


#include "pda.h"
#include "state.h"
#include <stdlib.h>
#include <string.h>



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

    int* stateId;
    stateId = &state->id;
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

    // is there a state 0 (start state)
    int* zero;
    zero = 0;
    //State* start;
    //start = (State*) table_lookup(pda->pdaStateTable, zero);



    // set current state, current input and current stack in pda





    // looping through the input string
    for(int iii = 0; iii < strlen(input);iii++){

        printf("%c\n", input[iii]);





    }


    return 0;
}
