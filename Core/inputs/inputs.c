
#include "inputs.h"
#include "gpio.h"

/*

UP_SW        → GPIO input with pull-up
DOWN_SW      → GPIO input with pull-up
PROXI_SENSE  → GPIO input with pull-up

Pressed / active = LOW
Released        = HIGH
*/

/* ----- Configuration ----- */

#define DEBOUNCE_MAX   5   // 5 samples @10ms = 50ms stable

/* ----- Types ----- */

typedef struct
{
    uint8_t state;
    uint8_t counter;
} debounce_t;

/* ----- Private State ----- */

static debounce_t up_db;
static debounce_t down_db;
static debounce_t prox_db;

static input_state_t instate;

/* ----- Local Debounce ----- */

static void debounce_update(debounce_t *db, uint8_t raw)
{
    /* active low input */
    if(raw == GPIO_PIN_RESET)
    {
        if(db->counter < DEBOUNCE_MAX)
            db->counter++;
    }
    else
    {
        if(db->counter > 0)
            db->counter--;
    }

    if(db->counter >= DEBOUNCE_MAX)
        db->state = 1;
    else if(db->counter == 0)
        db->state = 0;
}

/* ----- Public API ----- */

void inputs_init(void)
{
    up_db.state = up_db.counter = 0;
    down_db.state = down_db.counter = 0;
    prox_db.state = prox_db.counter = 0;

    instate.up = 0;
    instate.down = 0;
    instate.prox = 0;
}

/*
Call every 10ms from app layer
*/
void inputs_update(void)
{
    uint8_t raw_up =
        HAL_GPIO_ReadPin(UP_SW_GPIO_Port, UP_SW_Pin);

    uint8_t raw_down =
        HAL_GPIO_ReadPin(DOWN_SW_GPIO_Port, DOWN_SW_Pin);

    uint8_t raw_prox =
        HAL_GPIO_ReadPin(PROXI_SENSE_GPIO_Port, PROXI_SENSE_Pin);

    debounce_update(&up_db, raw_up);
    debounce_update(&down_db, raw_down);
    debounce_update(&prox_db, raw_prox);

    instate.up = up_db.state;
    instate.down = down_db.state;
    instate.prox = prox_db.state;
}

input_state_t inputs_get(void)
{
    return instate;
}



