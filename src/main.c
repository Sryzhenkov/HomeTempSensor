#include "GlobalSettings.h"

#define LED_RED_NODE	DT_ALIAS(led1_red)
#define LED_GREEN_NODE	DT_ALIAS(led1_green)

LOG_MODULE_REGISTER(main);

static const struct gpio_dt_spec ledRed = GPIO_DT_SPEC_GET(LED_RED_NODE, gpios);
static const struct gpio_dt_spec ledGreen = GPIO_DT_SPEC_GET(LED_GREEN_NODE, gpios);

int LedInit(const struct gpio_dt_spec*, gpio_flags_t);

Global_Info_t globalInfo_s = {
								.bmp280  = I2C_DT_SPEC_GET(BMP280_NODE),
								.ssd1306 = I2C_DT_SPEC_GET(SSD1306_NODE),
}; 

void main(void)
{	
	//LedInit(&ledRed,GPIO_OUTPUT_ACTIVE);
	LedInit(&ledGreen,GPIO_OUTPUT_ACTIVE);

	//gpio_pin_set_dt(&ledRed, 0);
	gpio_pin_set_dt(&ledGreen, 1);

	//BMP280_Init();
	SSD1306_Init();

	while(1)
		{		
			k_msleep(1000);	
			//BMP280_ReadTemp();	
		}
}

/*#define STACKSIZE 1024

#define THREAD0_PRIORITY 7
#define THREAD1_PRIORITY 7

void thread0(void)
{
	while (1) {
		  LOG_INF("Hello, I am 000\n");
          //k_yield();
		  k_msleep(1000);
	}
}

void thread1(void)
{
	while (1) {
          LOG_INF("Hello, I am 111\n");		  
		  //k_yield();		  
		  k_msleep(1000);
	}
}

K_THREAD_DEFINE(thread0_id, STACKSIZE, thread0, NULL, NULL, NULL, THREAD0_PRIORITY, 0, 0);
K_THREAD_DEFINE(thread1_id, STACKSIZE, thread1, NULL, NULL, NULL, THREAD1_PRIORITY, 0, 0);
*/