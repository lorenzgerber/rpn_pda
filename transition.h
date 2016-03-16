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
} Transition;

/*
 * function to create a new transition
 */
Transition * transition_create(char description[255],
                               int sourceState,
                               int destState,
                               int (*read) (int),
                               int (*pop) (int),
                               int (*push) (int));


/*
 * function to check if read is NULL hence Epsilon
 */
int transition_checkReadEpsilon(Transition * transition);

/*
 * function to check if pop is NULL hence Epsilon
 */
int transition_checkPopEpsilon(Transition * transition);

/*
 * function to check if push is NULL hence Epsilon
 */
int transition_checkPushEpsilon(Transition * transition);

/*
 * function to check if read condition is fulfilled
 */
int transition_checkRead(Transition * transition, char input);

/*
 * function to check if pop condition is fulfilled
 */
int transition_checkPop(Transition * transition, char topStack);

/*
 * Function to check whether to push from input or push a char
 * provided by the transition
 */
int transition_checkPush(Transition * transition);



#endif /*TRANSITION*/