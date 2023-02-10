#include "..\..\GlobalSettings.h"

LOG_MODULE_REGISTER(BMP280);

bmp280_CalibValue_t bmp280_CValue_s = {
											.DT1 = 0x69A7,
											.DT2 = 0x63BC,
											.DT3 = 0x0032
};


static uint8_t bmp280InitArray[] = {
										BMP280_REG_READ_ID, 0x00,
										BMP280_REG_RESET, 0xB6,
										BMP280_REG_CONFIG, 0x28,
										BMP280_REG_CTRL_MEAS, 0x43,
};

static uint8_t BMP280_Status(const struct i2c_dt_spec* dev)
{
	uint8_t wVal = BMP280_REG_STATUS; 
	uint8_t status = 0;

	i2c_write_read_dt(dev, &wVal, 1, &status, 1);

	return (status & 0x01);
}

int32_t BMP280_ReadTemp(void)
{
	static const struct i2c_dt_spec devBMP280 = I2C_DT_SPEC_GET(BMP280_NODE);

	uint8_t wVal[3]= {BMP280_REG_TEMP_MSB, BMP280_REG_TEMP_LSB, BMP280_REG_TEMP_XLSB};
	uint8_t rVal[3] = {0};

	if(i2c_burst_read_dt(&devBMP280, *(wVal+0), rVal, 3) != 0) return -2;

	int32_t temper_int;
	uint32_t temper_raw = ((rVal[0] << 16) | (rVal[1] << 8) | (rVal[2])) >> 4;

	int32_t var1, var2, T;

	var1 = ((((temper_raw>>3) - (bmp280_CValue_s.DT1<<1))) * (bmp280_CValue_s.DT2)) >> 11;
	var2 = (((((temper_raw>>4) - (bmp280_CValue_s.DT1)) * ((temper_raw>>4) - (bmp280_CValue_s.DT1))) >> 12) * (bmp280_CValue_s.DT3)) >> 14;
	temper_int = var1 + var2;
	T = (temper_int * 5 + 128) >> 8;

	LOG_INF("%u.%u C\r",T/100, T%100);

	return 0;
}

int32_t BMP280_Init()
{
    Global_Info_t* p_globalInfo = &globalInfo_s;

	if (!device_is_ready(p_globalInfo->bmp280.bus)) return DEVICE_NOT_READY;

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

	LOG_INF("Init Ok\r");

	return DEVICE_ALL_OK;
}