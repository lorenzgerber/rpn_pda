/*
 * This datatype was designed and implemented for an assignment in course DV2:
 * Algorithms and problemsolving 7.5 p, 5DV169
 */

#ifndef TRANSITION
#define TRANSITION

#include <stdbool.h>
#include "dlist.h"

typedef struct {
    char description[255];
    int sourceState;
    int destState;
    int (*read) (int);
    int (*pop) (int);
    int (*push) (int);
    int (*process) (int);
    
} Transition;

/*
 * function to create a new transition
 */
Transition * transition_create(char description[255],
                               int sourceState,
                               int destState,
                               int (*read) (int),
                               int (*pop) (int),
                               int (*push) (int),
                               int (*process) (int));

/*
 * function to check whether a transition is possible
 */
int * transition_check(Transition * transition, char input, char stack);


#endif /*TRANSITION*/