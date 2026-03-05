
#include "can_if.h"

#include "can.h"
#include "sensors.h"
#include "hydraulic_sm.h"
#include "gpio.h"
#include "log.h"


/* ----- Protocol IDs ----- */

#define CAN_ID_CMD     0x100
#define CAN_ID_STATUS  0x101

/* ----- Private State ----- */

static uint8_t cmd_up = 0;
static uint8_t cmd_down = 0;

static CAN_TxHeaderTypeDef txHeader;
static uint8_t txData[8];
static uint32_t txMailbox;

/* LED hold timer (used by app layer) */
uint32_t data_led_timer = 0;

/* ----- Public ----- */

void can_if_init(void)
{
    /* ----- CAN filter accept all ----- */
    CAN_FilterTypeDef filter;

    filter.FilterActivation = ENABLE;
    filter.FilterBank = 0;
    filter.FilterFIFOAssignment = CAN_FILTER_FIFO0;
    filter.FilterIdHigh = 0;
    filter.FilterIdLow = 0;
    filter.FilterMaskIdHigh = 0;
    filter.FilterMaskIdLow = 0;
    filter.FilterMode = CAN_FILTERMODE_IDMASK;
    filter.FilterScale = CAN_FILTERSCALE_32BIT;

    HAL_CAN_ConfigFilter(&hcan, &filter);

    /* ----- TX header ----- */

    txHeader.StdId = CAN_ID_STATUS;
    txHeader.IDE = CAN_ID_STD;
    txHeader.RTR = CAN_RTR_DATA;
    txHeader.DLC = 8;

    /* ----- enable RX interrupt ----- */

    HAL_CAN_ActivateNotification(&hcan,
        CAN_IT_RX_FIFO0_MSG_PENDING);
}

/* ----- RX Processing ----- */

void can_if_process_rx(CAN_RxHeaderTypeDef *hdr, uint8_t *data)
{
    /* ----- DATA LED ON + restart 50ms timer ----- */

    HAL_GPIO_WritePin(DATA_LED_GPIO_Port,
                      DATA_LED_Pin,
                      GPIO_PIN_SET);

    data_led_timer = HAL_GetTick() + 50;

    log_printf("CAN RX ID=0x%03X CMD=%02X\r\n",
                hdr->StdId,
                data[0]);

    /* ----- Command decode ----- */

    if(hdr->StdId != CAN_ID_CMD)
        return;

    switch(data[0])
    {
        case 0x01:
            cmd_up = 1;
            cmd_down = 0;
            break;

        case 0x02:
            cmd_down = 1;
            cmd_up = 0;
            break;

        default:
            cmd_up = 0;
            cmd_down = 0;
            break;
    }
}

/* ----- Periodic Status TX ----- */

void can_if_periodic_tx(void)
{
    sensor_data_t s = sensors_get();

    uint16_t v = (uint16_t)(s.bus_v * 10.0f);

    txData[0] = v >> 8;
    txData[1] = v & 0xFF;
    txData[2] = (uint8_t)s.current;
    txData[3] = (uint8_t)s.pressure;
    txData[4] = (uint8_t)s.level;
    txData[5] = (uint8_t)hydraulic_sm_get_state();
    txData[6] = hydraulic_sm_get_error_flags();
    txData[7] = 0;

    HAL_CAN_AddTxMessage(&hcan,
                         &txHeader,
                         txData,
                         &txMailbox);
}

/* ----- Command Accessors ----- */

uint8_t can_if_up_cmd(void)
{
    return cmd_up;
}

uint8_t can_if_down_cmd(void)
{
    return cmd_down;
}



