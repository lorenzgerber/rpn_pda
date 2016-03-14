/*
 * This datatype was designed and implemented for an assignment in course DV2:
 * Algorithms and problemsolving 7.5 p, 5DV169
 */


#include <string.h>
#include <stdlib.h>
#include "transition.h"

/*
 * function to create a new transition
 */
Transition * transition_create(char description[255],
                               int sourceState,
                               int destState,
                               int (*read) (int),
                               int (*pop) (int),
                               int (*push) (int),
                               int (*process) (int))
{
    Transition *new_transition = calloc(sizeof(Transition),1);
    if (!new_transition)
        return NULL;

    strcpy(new_transition->description, description);
    new_transition->sourceState = sourceState;
    new_transition->destState = destState;
    new_transition->read = read;
    new_transition->pop = pop;
    new_transition->push = push;
    new_transition->process = process;

    return new_transition;
}

