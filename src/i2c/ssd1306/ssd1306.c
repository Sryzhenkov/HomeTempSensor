#include "..\..\GlobalSettings.h"

LOG_MODULE_REGISTER(ssd1306);
/*
static uint8_t ssd1306InitArray[] = {
										SSD1306_COMMAND_BYTE, SSD1306_SET_MUX_RATIO, 			0x3F,
										SSD1306_COMMAND_BYTE, SSD1306_SET_DISPLAY_OFFSET, 		0x00,
										SSD1306_COMMAND_BYTE, SSD1306_SET_DISPLAY_START_LINE,	0xFF,	// 6
										SSD1306_COMMAND_BYTE, SSD1306_SET_SEG_RE_MAP_127_0, 	0xFF,	// 9
										SSD1306_COMMAND_BYTE, SSD1306_SET_COM_OUTPUT_RE_MAP, 	0xFF,	// 12
										SSD1306_COMMAND_BYTE, SSD1306_SET_COM_PINS, 			0x12,
										SSD1306_COMMAND_BYTE, SSD1306_SET_CONTRAST_CONTROL, 	0x7F,
										SSD1306_COMMAND_BYTE, SSD1306_ENT_DISPLAY_RES_TO_RAM, 	0xFF,	// 21
										SSD1306_COMMAND_BYTE, SSD1306_SET_NORMAL_DISPLAY, 		0xFF,	// 24
										SSD1306_COMMAND_BYTE, SSD1306_SET_DISPLAY_CLOCK, 		0x80,
										SSD1306_COMMAND_BYTE, SSD1306_CHARGE_PUMP_SETTING, 		0x14,
										SSD1306_COMMAND_BYTE, SSD1306_SET_DISPLAY_ON, 			0xFF,	// 33
										SSD1306_COMMAND_BYTE, SSD1306_SET_MEM_ADDR_MODE, 		0x10
									};
*/

static uint8_t ssd1306InitArray[] = {
										SSD1306_COMMAND_BYTE, 0xAE, SSD1306_NOP_BYTE,
										SSD1306_COMMAND_BYTE, 0x20, 0x10,
										SSD1306_COMMAND_BYTE, 0xB0, SSD1306_NOP_BYTE,
										SSD1306_COMMAND_BYTE, 0xC8, SSD1306_NOP_BYTE,
										SSD1306_COMMAND_BYTE, 0x00, SSD1306_NOP_BYTE,
										SSD1306_COMMAND_BYTE, 0x10, SSD1306_NOP_BYTE,
										SSD1306_COMMAND_BYTE, 0x40, SSD1306_NOP_BYTE,
										SSD1306_COMMAND_BYTE, 0x81, 0xFF,
										SSD1306_COMMAND_BYTE, 0xA1, SSD1306_NOP_BYTE,
										SSD1306_COMMAND_BYTE, 0xA6, SSD1306_NOP_BYTE,
										SSD1306_COMMAND_BYTE, 0xA8, 0x3F,
										SSD1306_COMMAND_BYTE, 0xA4, SSD1306_NOP_BYTE,
										SSD1306_COMMAND_BYTE, 0xD3, 0x00,
										SSD1306_COMMAND_BYTE, 0xD5, 0xF0,
										SSD1306_COMMAND_BYTE, 0xD9, 0x22,
										SSD1306_COMMAND_BYTE, 0xDA, 0x12,
										SSD1306_COMMAND_BYTE, 0xDB, 0x20,
										SSD1306_COMMAND_BYTE, 0x8D, 0x14,
										SSD1306_COMMAND_BYTE, 0xAF, SSD1306_NOP_BYTE,
									};


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

	
	
	i2c_write_dt(&(p_globalInfo->ssd1306), (ssd1306InitArray+0), 2);
	i2c_write_dt(&(p_globalInfo->ssd1306), (ssd1306InitArray+3), 3);
	i2c_write_dt(&(p_globalInfo->ssd1306), (ssd1306InitArray+6), 2);
	i2c_write_dt(&(p_globalInfo->ssd1306), (ssd1306InitArray+9), 2);
	i2c_write_dt(&(p_globalInfo->ssd1306), (ssd1306InitArray+12), 2);
	i2c_write_dt(&(p_globalInfo->ssd1306), (ssd1306InitArray+15), 2);
	i2c_write_dt(&(p_globalInfo->ssd1306), (ssd1306InitArray+18), 2);
	i2c_write_dt(&(p_globalInfo->ssd1306), (ssd1306InitArray+21), 3);
	i2c_write_dt(&(p_globalInfo->ssd1306), (ssd1306InitArray+24), 2);
	i2c_write_dt(&(p_globalInfo->ssd1306), (ssd1306InitArray+27), 2);
	i2c_write_dt(&(p_globalInfo->ssd1306), (ssd1306InitArray+30), 3);
	i2c_write_dt(&(p_globalInfo->ssd1306), (ssd1306InitArray+33), 2);
	i2c_write_dt(&(p_globalInfo->ssd1306), (ssd1306InitArray+36), 3);
	i2c_write_dt(&(p_globalInfo->ssd1306), (ssd1306InitArray+39), 3);
	i2c_write_dt(&(p_globalInfo->ssd1306), (ssd1306InitArray+42), 3);
	i2c_write_dt(&(p_globalInfo->ssd1306), (ssd1306InitArray+45), 3);
	i2c_write_dt(&(p_globalInfo->ssd1306), (ssd1306InitArray+48), 3);
	i2c_write_dt(&(p_globalInfo->ssd1306), (ssd1306InitArray+51), 3);
	i2c_write_dt(&(p_globalInfo->ssd1306), (ssd1306InitArray+54), 2);

	uint8_t pos[] = {
						SSD1306_COMMAND_BYTE,0x00, 
						SSD1306_COMMAND_BYTE,0x10, 
						SSD1306_COMMAND_BYTE,0xB0
					};

	uint8_t clear[] = {0x40,0x00};


	for(uint8_t i=0;i<8;i++)
		{
			pos[5] = 0xB0 + i;
			for(uint8_t i = 0; i < 3; i++) 
				{
					i2c_write_dt(&(p_globalInfo->ssd1306), pos+(i*2), 2);
				}

			for(uint8_t j=0;j<128;j++)
				{
					i2c_write_dt(&(p_globalInfo->ssd1306), clear, 2);
				}
		}

	uint8_t bt_logo[] = {0x40,0x00,0x28,0x10,0xFE,0x54,0x28,0x00,0x00};

	i2c_write_dt(&(p_globalInfo->ssd1306), bt_logo, 9);

	oled_print("Hello World");

/*
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

	uint8_t pos[] = {SSD1306_COMMAND_BYTE,0x00+( 0x0F & 0), SSD1306_COMMAND_BYTE,0x10+( 0x0F & (0 >> 4)), SSD1306_COMMAND_BYTE,0xB0 + 0};

	i2c_write_dt(&(p_globalInfo->ssd1306), pos, 2);
	i2c_write_dt(&(p_globalInfo->ssd1306), pos+2, 2);
	i2c_write_dt(&(p_globalInfo->ssd1306), pos+4, 2);

	int i,j;

	uint8_t clear[] = {0x40,0x00};

	for(i=0;i<1;i++)
	{
		for(j=0;j<128;j++)
		{
			i2c_write_dt(&(p_globalInfo->ssd1306), clear, 2);
		}
	}

//	uint8_t pos2[] = {0x40,0x00+( 0x0F & 30), 0x40,0x10+( 0x0F & (30 >> 4)), 0x40,0xB0 + 3};

	i2c_write_dt(&(p_globalInfo->ssd1306), pos, 2);
	i2c_write_dt(&(p_globalInfo->ssd1306), pos+2, 2);
	i2c_write_dt(&(p_globalInfo->ssd1306), pos+4, 2);

	oled_print("Hello World");
*/
	LOG_INF("Init Ok\r");

	return DEVICE_ALL_OK;
}

void clearFullScreen(const struct i2c_dt_spec* dev)
{
	uint8_t pos[] = {
						SSD1306_COMMAND_BYTE,0x00, 
						SSD1306_COMMAND_BYTE,0x10, 
						SSD1306_COMMAND_BYTE,0xB0
					};
	
	for(uint8_t i = 0; i < 3; i++) 
		{
			i2c_write_dt(dev, pos+(i*2), 2);
		}
	
	for(uint32_t i = 0; i < (128*8); i++)
		{

		}
}