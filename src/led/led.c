#include "..\GlobalSettings.h"

int LedInit(const struct gpio_dt_spec* led, gpio_flags_t cfg)
{
	if(device_is_ready(led->port))
		{
			return gpio_pin_configure_dt(led,cfg);
		}
	
	return -1;
}