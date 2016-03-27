/*
 * This datatype was designed and implemented for an assignment in course DV2:
 * Algorithms and problemsolving 7.5 p, 5DV169
 */


#include <stdlib.h>
#include <string.h>
#include "state.h"



/*
 * function to create a state that can host transitions
 */
State * state_create(int id, bool accepted,
                     char description[255]){
    State *new_state = calloc(sizeof(State),1);
    if (!new_state)
        return NULL;

    new_state->transitions = dlist_empty();
    dlist_setMemHandler(new_state->transitions,free);


    new_state->id = id;
    new_state->accepted = accepted;
    strcpy(new_state->description, description);

    return new_state;
};


/*
 * function to add a transition to the current state
 */
void * state_addTransition(State * state,
                            Transition * transition) {
    dlist_position list_pos;

    // find last position
    list_pos = dlist_first(state->transitions);

    while(!dlist_isEnd(state->transitions, list_pos)){
        list_pos = dlist_next(state->transitions, list_pos);
    }

    // insert current_transition into current_state
    dlist_insert(state->transitions, list_pos,
                 transition);

    return state;

};

/*
 * function to free the allocated memory
 */
void state_free(void *state){
    State *s = (State*)state;
    dlist_free(s->transitions);
    free(s);
}