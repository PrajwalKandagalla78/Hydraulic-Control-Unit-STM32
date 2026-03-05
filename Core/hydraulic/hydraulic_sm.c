
#include "hydraulic_sm.h"

#include "sensors.h"
#include "inputs.h"
#include "can_if.h"
#include "tim.h"
#include "gpio.h"
#include "log.h"


/* ----- Safety Limits ----- */

#define MAX_CURRENT_A       80.0f
#define MAX_PRESSURE_MPA    28.0f
#define MAX_MOS_TEMP_C      90.0f
#define MIN_LEVEL_PERCENT   10.0f
#define MIN_BUS_VOLTAGE     42.0f

/* ----- Private State ----- */

static hyd_state_t hyd_state = HYD_IDLE;
static uint8_t error_flags = 0;

/* ----- Error Bit Map ----- */

#define ERR_OVERCURRENT   (1 << 0)
#define ERR_OVERPRESS     (1 << 1)
#define ERR_OVERTEMP      (1 << 2)
#define ERR_LOWLEVEL      (1 << 3)
#define ERR_UNDERVOLT     (1 << 4)

/* ----- Local Functions ----- */

static void safety_check(sensor_data_t s);
static void outputs_apply(uint8_t up, uint8_t down);
static void pwm_set_percent(uint8_t percent);

/* ----- Public ----- */

void hydraulic_sm_init(void)
{
    hyd_state = HYD_IDLE;
    error_flags = 0;
}

hyd_state_t hydraulic_sm_get_state(void)
{
    return hyd_state;
}

uint8_t hydraulic_sm_get_error_flags(void)
{
    return error_flags;
}

/* ----- Main State Machine ----- */

void hydraulic_sm_update(void)
{
    sensor_data_t s = sensors_get();
    input_state_t  in = inputs_get();

    uint8_t up_cmd =
        in.up || can_if_up_cmd();

    uint8_t down_cmd =
        in.down || can_if_down_cmd();

    /* ----- Safety evaluation ----- */
    safety_check(s);

    if(error_flags)
    {
        hyd_state = HYD_ERROR;
    }

    switch(hyd_state)
    {
        case HYD_IDLE:

            if(up_cmd)
                hyd_state = HYD_MOVING_UP;
            else if(down_cmd)
                hyd_state = HYD_MOVING_DOWN;

            break;

        case HYD_MOVING_UP:

            if(!up_cmd)
                hyd_state = HYD_IDLE;

            break;

        case HYD_MOVING_DOWN:

            /* stop automatically at zero position */
            if(in.prox)
                hyd_state = HYD_IDLE;

            if(!down_cmd)
                hyd_state = HYD_IDLE;

            break;

        case HYD_ERROR:

            /* auto clear when fault gone */
            if(error_flags == 0)
                hyd_state = HYD_IDLE;

            break;
    }

    /* ----- Apply outputs ----- */

    switch(hyd_state)
    {
        case HYD_MOVING_UP:
            outputs_apply(1, 0);
            log_printf("STATE -> MOVING_UP\r\n");
            break;

        case HYD_MOVING_DOWN:
            outputs_apply(0, 1);
            log_printf("STATE -> MOVING_DOWN\r\n");
            break;

        default:
            outputs_apply(0, 0);
            log_printf("STATE -> DEFAULT\r\n");
            break;
    }
}

/* ----- Safety Check ----- */

static void safety_check(sensor_data_t s)
{
    error_flags = 0;

    if(s.current > MAX_CURRENT_A)
        error_flags |= ERR_OVERCURRENT;

    if(s.pressure > MAX_PRESSURE_MPA)
        error_flags |= ERR_OVERPRESS;

    if(s.mos_temp > MAX_MOS_TEMP_C)
        error_flags |= ERR_OVERTEMP;

    if(s.level < MIN_LEVEL_PERCENT)
        error_flags |= ERR_LOWLEVEL;

    if(s.bus_v < MIN_BUS_VOLTAGE)
        error_flags |= ERR_UNDERVOLT;
}

/* ----- Output Layer ----- */

static void outputs_apply(uint8_t up, uint8_t down)
{
    if(up && !down)
    {
        HAL_GPIO_WritePin(UP_RLY_GPIO_Port,
                          UP_RLY_Pin,
                          GPIO_PIN_SET);

        HAL_GPIO_WritePin(DOWN_RLY_GPIO_Port,
                          DOWN_RLY_Pin,
                          GPIO_PIN_RESET);

        pwm_set_percent(50);
    }
    else if(down && !up)
    {
        HAL_GPIO_WritePin(DOWN_RLY_GPIO_Port,
                          DOWN_RLY_Pin,
                          GPIO_PIN_SET);

        HAL_GPIO_WritePin(UP_RLY_GPIO_Port,
                          UP_RLY_Pin,
                          GPIO_PIN_RESET);

        pwm_set_percent(0);
    }
    else
    {
        HAL_GPIO_WritePin(UP_RLY_GPIO_Port,
                          UP_RLY_Pin,
                          GPIO_PIN_RESET);

        HAL_GPIO_WritePin(DOWN_RLY_GPIO_Port,
                          DOWN_RLY_Pin,
                          GPIO_PIN_RESET);

        pwm_set_percent(0);
    }
}

/* ----- PWM Helper ----- */

static void pwm_set_percent(uint8_t percent)
{
    uint32_t period = __HAL_TIM_GET_AUTORELOAD(&htim2);
    uint32_t value = (period * percent) / 100;
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, value);
}


