
#include "log.h"
#include "usart.h"
#include <stdio.h>
#include <string.h>

void log_printf(const char *fmt, ...)
{
    char buf[128];

    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);

    HAL_UART_Transmit(&huart1,
                      (uint8_t*)buf,
                      strlen(buf),
                      100);
}


