#include "app.h"

#include "sensors.h"
#include "inputs.h"
#include "hydraulic_sm.h"
#include "can_if.h"
#include "gpio.h"
#include "log.h"

/* ----- Timing Control ----- */

#define APP_INPUT_PERIOD_MS     10
#define APP_CAN_TX_PERIOD_MS    100

static uint32_t input_tick = 0;
static uint32_t can_tx_tick = 0;
static uint32_t log_tick = 0;

/* ----- Private Functions ----- */

static void app_led_service(void);

/* ----- Public Functions ----- */

void app_init(void)
{
    sensors_init();
    can_if_init();

    input_tick = HAL_GetTick();
    can_tx_tick = HAL_GetTick();
    log_tick = HAL_GetTick();
}

void app_run(void)
{
    uint32_t now = HAL_GetTick();

    /* ----- Sensor Update (fast loop) ----- */
    sensors_update();

    /* ----- Inputs Update (10 ms debounce task) ----- */
    if(now - input_tick >= APP_INPUT_PERIOD_MS)
    {
        input_tick = now;
        inputs_update();
    }

    /* ----- Hydraulic State Machine ----- */
    hydraulic_sm_update();

    /* ----- CAN periodic status TX ----- */
    if(now - can_tx_tick >= APP_CAN_TX_PERIOD_MS)
    {
        can_tx_tick = now;
        can_if_periodic_tx();
    }

    /* ----- LED timing service ----- */
    app_led_service();

    /* ----- Logs ----- */
    sensor_data_t s = sensors_get();

	log_printf(
	  "V=%.1fV I=%.1fA P=%.1fMPa L=%.0f%% State=%d Err=%02X\r\n",
	  s.bus_v,
	  s.current,
	  s.pressure,
	  s.level,
	  hydraulic_sm_get_state(),
	  hydraulic_sm_get_error_flags()
	);
}

/* ----- LED Service ----- */

extern uint32_t data_led_timer;

static void app_led_service(void)
{
    if(data_led_timer != 0)
    {
        if(HAL_GetTick() >= data_led_timer)
        {
            HAL_GPIO_WritePin(DATA_LED_GPIO_Port,
                              DATA_LED_Pin,
                              GPIO_PIN_RESET);
            data_led_timer = 0;
        }
    }
}

