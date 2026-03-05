

#ifndef SENSORS_SENSORS_H_
#define SENSORS_SENSORS_H_

#include "main.h"

/* ----- Sensor Data Structure ----- */

typedef struct
{
    float bus_v;        // Volts
    float current;      // Amps
    float pressure;     // MPa
    float level;        // %
    float mos_temp;     // °C
    float mot_temp;     // °C
} sensor_data_t;

/* ----- API ----- */

void sensors_init(void);
void sensors_update(void);
sensor_data_t sensors_get(void);


#endif /* SENSORS_SENSORS_H_ */
