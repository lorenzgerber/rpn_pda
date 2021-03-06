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
Transition * trans_create(
        void *pda,
        char description[255],
        int destState,
        int (*read) (int),
        int (*pop) (int),
        int (*push) (void*))
{
    Transition *new_transition = calloc(sizeof(Transition),1);
    if (!new_transition)
        return NULL;

    new_transition->pda = pda;
    strcpy(new_transition->description, description);
    new_transition->destState = destState;
    new_transition->read = read;
    new_transition->pop = pop;
    new_transition->push = push;

    return new_transition;
}


/*
 * function to check if read is NULL hence Epsilon
 */
int transition_checkReadEpsilon(Transition * transition){
    if(*transition->read == NULL)
        return 1;
    return 0;
}

/*
 * function to check if pop is NULL hence Epsilon
 */
int transition_checkPopEpsilon(Transition * transition){
    if(*transition->pop == NULL)
        return 1;
    return 0;
}

/*
 * function to check if push is NULL hence Epsilon
 */
int transition_checkPushEpsilon(Transition * transition){
    if(*transition->push == NULL)
        return 1;
    return 0;
}

/*
 * function to check if read condition is fulfilled
 */
int transition_checkRead(Transition * transition, char input){
    if(transition->read(input))
        return 1;
    return 0;
}

/*
 * function to check if pop condition is fulfilled
 */
int transition_checkPop(Transition * transition, char topStack){
    if(transition->pop(topStack))
        return 1;
    return 0;
}

/*
 * Function to check whether to push from input or push a char
 * provided by the transition
 */
int transition_checkPush(Transition * transition){
    return transition->push(transition->pda);
}
