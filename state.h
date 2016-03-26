/*
 * This datatype was designed and implemented for an assignment in course DV2:
 * Algorithms and problemsolving 7.5 p, 5DV169
 */

#ifndef STATE
#define STATE

#include <stdbool.h>
#include "table.h"
#include "dlist.h"
#include "transition.h"

typedef struct {
    int id;
    bool accepted;
    char description[255];
    dlist * transitions;
} State;

/*
 * function to create a state that can host transitions
 */
State * state_create(int id, bool accepted,
                     char description[255]);


/*
 * function to add a transition to the current state
 */
void * state_addTransition(State * state,
                            Transition * transition
);



#endif /*STATE*/