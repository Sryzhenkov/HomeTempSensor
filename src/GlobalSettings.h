#ifndef GLOBALSETTINGS_H
#define GLOBALSETTINGS_H

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include "led/led.h"
#include "i2c/bmp280/bmp280.h"
#include "i2c/ssd1306/ssd1306.h"

enum error_code{
    DEVICE_ALL_OK = 0,
    DEVICE_NOT_READY = -1,
    DEVICE_ID_INCORRECR = -2,
};

typedef struct {
    struct i2c_dt_spec bmp280;
    struct i2c_dt_spec ssd1306;
}Global_Info_t;

extern Global_Info_t globalInfo_s;

#endif