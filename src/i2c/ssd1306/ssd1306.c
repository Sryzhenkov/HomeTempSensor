#include "..\..\GlobalSettings.h"

LOG_MODULE_REGISTER(ssd1306);

static uint8_t ssd1306InitArray[] = {
										0x00, 0xA8, 0x3F,
										0x00, 0xD3, 0x00,
										0x00, 0x40, 0xFF,	// 6
										0x00, 0xA1, 0xFF,	// 9
										0x00, 0xC8, 0xFF,	// 12
										0x00, 0xDA, 0x12,
										0x00, 0x81, 0x7F,
										0x00, 0xA4, 0xFF,	// 21
										0x00, 0xA6, 0xFF,	// 24
										0x00, 0xD5, 0x80,
										0x00, 0x8D, 0x14,
										0x00, 0xAF, 0xFF,	// 33
										0x00, 0x20, 0x10,
										0x00, 0xAE
};

/*static uint8_t ssd1306InitArray[] = {
										0xA8, 0x3F,
										0xD3, 0x00,
										0x40, 0xFF,	// 4
										0xA1, 0xFF,	// 6
										0xC8, 0xFF,	// 8
										0xDA, 0x12,
										0x81, 0x7F,
										0xA4, 0xFF,	// 14
										0xA6, 0xFF,	// 16
										0xD5, 0x80,
										0x8D, 0x14,
										0xAF, 0xFF,	// 22
										0x20, 0x10,
										0xAE
};*/


void oled_print(char str[])
{
	int i,j;
	i=0;

	Global_Info_t* p_globalInfo = &globalInfo_s;

	uint8_t data[] = {0x40,0x00};

	while(str[i])
	{
		for(j=0;j<5;j++)
		{
			data[1] = ASCII[(str[i]-32)][j];
			i2c_write_dt(&(p_globalInfo->ssd1306), data, 2);
		}
		i++;
	}
}

int32_t SSD1306_Init()
{
    Global_Info_t* p_globalInfo = &globalInfo_s;

	if (!device_is_ready(p_globalInfo->ssd1306.bus)) return DEVICE_NOT_READY;

	i2c_write_dt(&(p_globalInfo->ssd1306), (ssd1306InitArray+39), 2);

	i2c_write_dt(&(p_globalInfo->ssd1306), (ssd1306InitArray+0), 3);
	i2c_write_dt(&(p_globalInfo->ssd1306), (ssd1306InitArray+3), 3);

	i2c_write_dt(&(p_globalInfo->ssd1306), (ssd1306InitArray+6), 2);
	i2c_write_dt(&(p_globalInfo->ssd1306), (ssd1306InitArray+9), 2);
	i2c_write_dt(&(p_globalInfo->ssd1306), (ssd1306InitArray+12), 2);

	i2c_write_dt(&(p_globalInfo->ssd1306), (ssd1306InitArray+15), 3);
	i2c_write_dt(&(p_globalInfo->ssd1306), (ssd1306InitArray+18), 3);

	i2c_write_dt(&(p_globalInfo->ssd1306), (ssd1306InitArray+21), 2);
	i2c_write_dt(&(p_globalInfo->ssd1306), (ssd1306InitArray+24), 2);

	i2c_write_dt(&(p_globalInfo->ssd1306), (ssd1306InitArray+27), 3);
	i2c_write_dt(&(p_globalInfo->ssd1306), (ssd1306InitArray+30), 3);

	i2c_write_dt(&(p_globalInfo->ssd1306), (ssd1306InitArray+33), 2);

	i2c_write_dt(&(p_globalInfo->ssd1306), (ssd1306InitArray+36), 3);

	uint8_t pos[] = {0x40,0x00+( 0x0F & 0), 0x40,0x10+( 0x0F & (0 >> 4)), 0x40,0xB0 + 0};

	i2c_write_dt(&(p_globalInfo->ssd1306), pos, 2);
	i2c_write_dt(&(p_globalInfo->ssd1306), pos+2, 2);
	i2c_write_dt(&(p_globalInfo->ssd1306), pos+4, 2);

	int i,j;

	uint8_t clear[] = {0x40,0xFF};

	for(i=0;i<8;i++)
	{
		for(j=0;j<128;j++)
		{
			i2c_write_dt(&(p_globalInfo->ssd1306), clear, 2);
		}
	}

	uint8_t pos2[] = {0x40,0x00+( 0x0F & 30), 0x40,0x10+( 0x0F & (30 >> 4)), 0x40,0xB0 + 3};
/*
	i2c_write_dt(&(p_globalInfo->ssd1306), pos, 2);
	i2c_write_dt(&(p_globalInfo->ssd1306), pos+2, 2);
	i2c_write_dt(&(p_globalInfo->ssd1306), pos+4, 2);
*/
//	oled_print("Hello World");

/*
	//############ READ_ID ############//

	i2c_write_read_dt(&(p_globalInfo->bmp280), bmp280InitArray, 1, (bmp280InitArray+1), 1);

	if(*(bmp280InitArray+1) != BMP280_VALUE_ID)	return DEVICE_ID_INCORRECR;

	LOG_INF("CheckID - OK\r");

	//############  RESET  ############//
	i2c_write_dt(&(p_globalInfo->bmp280), (bmp280InitArray+2), 2);

	uint8_t countTry = 0;

	while(BMP280_Status(&(p_globalInfo->bmp280)))
		{
			LOG_INF("reset try %u\r",countTry);

			if(!(countTry++ <= 10))	break;
		}
	//############  CONFIG ############//
	i2c_write_dt(&(p_globalInfo->bmp280), (bmp280InitArray+4), 2);
	//############   MODE  ############//
	i2c_write_dt(&(p_globalInfo->bmp280), (bmp280InitArray+6), 2);
*/
	LOG_INF("Init Ok\r");

	return DEVICE_ALL_OK;
}