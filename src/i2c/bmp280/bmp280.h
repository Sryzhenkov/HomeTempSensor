#ifndef BMP280_H
#define BMP280_H

#include <zephyr/drivers/i2c.h>
#include <zephyr/logging/log.h>

#define BMP280_NODE DT_NODELABEL(bmp280)

#define BMP280_VALUE_ID         0x58

#define BMP280_REG_READ_ID      0xD0
#define BMP280_REG_RESET        0xE0
#define BMP280_REG_STATUS       0xF3
#define BMP280_REG_CTRL_MEAS    0xF4
#define BMP280_REG_CONFIG       0xF5

#define BMP280_REG_PRESS_MSB    0xF7
#define BMP280_REG_PRESS_LSB    0xF8
#define BMP280_REG_PRESS_XLSB   0xF9

#define BMP280_REG_TEMP_MSB     0xFA
#define BMP280_REG_TEMP_LSB     0xFB
#define BMP280_REG_TEMP_XLSB    0xFC

#define BMP280_REG_DT1_LOW      0x88
#define BMP280_REG_DT1_HIGH     0x89
#define BMP280_REG_DT2_LOW      0x8A
#define BMP280_REG_DT2_HIGH     0x8B
#define BMP280_REG_DT3_LOW      0x8C
#define BMP280_REG_DT3_HIGH     0x8D

#define BMP280_REG_DP1_LOW      0x8E
#define BMP280_REG_DP1_HIGH     0x8F
#define BMP280_REG_DP2_LOW      0x90
#define BMP280_REG_DP2_HIGH     0x91
#define BMP280_REG_DP3_LOW      0x92
#define BMP280_REG_DP3_HIGH     0x93
#define BMP280_REG_DP4_LOW      0x94
#define BMP280_REG_DP4_HIGH     0x95
#define BMP280_REG_DP5_LOW      0x96
#define BMP280_REG_DP5_HIGH     0x97
#define BMP280_REG_DP6_LOW      0x98
#define BMP280_REG_DP6_HIGH     0x99
#define BMP280_REG_DP7_LOW      0x9A
#define BMP280_REG_DP7_HIGH     0x9B
#define BMP280_REG_DP8_LOW      0x9C
#define BMP280_REG_DP8_HIGH     0x9D
#define BMP280_REG_DP9_LOW      0x9E
#define BMP280_REG_DP9_HIGH     0x9F

enum BMP280_error_code{
    DEVICE_ALL_OK = 0,
    DEVICE_NOT_READY = -1,
    DEVICE_ID_INCORRECR = -2,
};

typedef struct
{
    uint16_t DT1;
     int16_t DT2;
     int16_t DT3;
/*  
    uint16_t DP1;
     int16_t DP2;
     int16_t DP3;
     int16_t DP4;
     int16_t DP5;
     int16_t DP6;
     int16_t DP7;
     int16_t DP8;
     int16_t DP9;
*/
}bmp280_CalibValue_t;

extern int32_t BMP280_Init();
extern int32_t BMP280_ReadTemp(void);

#endif