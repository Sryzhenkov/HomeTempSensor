#ifndef LED_H
#define LED_H

#include <zephyr/drivers/gpio.h>

int LedInit(const struct gpio_dt_spec* led, gpio_flags_t cfg);

#endif