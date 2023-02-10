#ifndef GLOBALSETTINGS_H
#define GLOBALSETTINGS_H

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include "led/led.h"
#include "i2c/bmp280/bmp280.h"

typedef struct 
{
    struct i2c_dt_spec bmp280;
}Global_Info_t;

extern Global_Info_t globalInfo_s;

#endif