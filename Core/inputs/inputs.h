

#ifndef INPUTS_INPUTS_H_
#define INPUTS_INPUTS_H_

#include "main.h"

/* ----- Debounced Input State ----- */

typedef struct
{
    uint8_t up;      // UP button pressed
    uint8_t down;    // DOWN button pressed
    uint8_t prox;    // proximity switch active
} input_state_t;

/* ----- API ----- */

void inputs_init(void);
void inputs_update(void);
input_state_t inputs_get(void);

#endif /* INPUTS_INPUTS_H_ */
