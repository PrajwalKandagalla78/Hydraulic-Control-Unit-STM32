
#ifndef HYDRAULIC_HYDRAULIC_SM_H_
#define HYDRAULIC_HYDRAULIC_SM_H_

#include "main.h"

/* ----- Hydraulic States ----- */

typedef enum
{
    HYD_IDLE = 0,
    HYD_MOVING_UP,
    HYD_MOVING_DOWN,
    HYD_ERROR
} hyd_state_t;

/* ----- API ----- */

void hydraulic_sm_init(void);
void hydraulic_sm_update(void);

hyd_state_t hydraulic_sm_get_state(void);
uint8_t hydraulic_sm_get_error_flags(void);

#endif /* HYDRAULIC_HYDRAULIC_SM_H_ */
