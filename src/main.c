#include "GlobalSettings.h"

#define LED_RED_NODE	DT_ALIAS(led1_red)
#define LED_GREEN_NODE	DT_ALIAS(led1_green)

LOG_MODULE_REGISTER(main);

static const struct gpio_dt_spec ledRed = GPIO_DT_SPEC_GET(LED_RED_NODE, gpios);
static const struct gpio_dt_spec ledGreen = GPIO_DT_SPEC_GET(LED_GREEN_NODE, gpios);

int LedInit(const struct gpio_dt_spec*, gpio_flags_t);

Global_Info_t globalInfo_s = {
								.bmp280 = I2C_DT_SPEC_GET(BMP280_NODE),
}; 

void main(void)
{	
	//LedInit(&ledRed,GPIO_OUTPUT_ACTIVE);
	LedInit(&ledGreen,GPIO_OUTPUT_ACTIVE);

	//gpio_pin_set_dt(&ledRed, 0);
	gpio_pin_set_dt(&ledGreen, 1);

	BMP280_Init();

	while(1)
		{		
			k_msleep(1000);	
			BMP280_ReadTemp();	
		}
}
