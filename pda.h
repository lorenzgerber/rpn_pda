/*
 * This datatype was designed and implemented for an assignment in course DV2:
 * Algorithms and problemsolving 7.5 p, 5DV169
 */

#ifndef PDA
#define PDA

#include <stdbool.h>
#include "table.h"
#include "stack_1cell.h"
#include "state.h"

typedef struct {
    Table *pdaStateTable;
    stack *pdaStack;
    memFreeFunc *freeFunc;
} Pda;

/*
 * compare function used to compare machine states
 */
int compareInt(void *ip,void *ip2);

/*
 * function to create a new pda machine
 */
Pda * pda_create();

/*
 * Function to add a new state
 */
void *pda_addState(Pda *pda, State *state);

/*
 * Function to execute a pda
 */
int *pda_execute(Pda *pda, char *input);


/*
 * Function to check if there is a zero state
 */
int pda_checkStartState(Pda *pda);




#endif /*PDA*/