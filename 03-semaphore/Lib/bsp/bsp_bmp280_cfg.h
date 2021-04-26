
#ifndef __BSP_BMP280_CFG_H__
#define __BSP_BMP280_CFG_H__

#include <stdio.h>
#include <i2c.h>
#include "bsp_bmp280.h"

/*! CPP guard */
#ifdef __cplusplus
extern "C" {
#endif

extern struct bmp280_dev bmp;
extern struct bmp280_config conf;
extern struct bmp280_uncomp_data ucomp_data;
extern int32_t temp32;
extern double temp;

void BMP280_Read(void);
void Delay_ms(uint32_t period_ms);
int8_t I2C_Reg_Write(uint8_t i2c_addr, uint8_t reg_addr, uint8_t *reg_data, uint16_t length);
int8_t I2C_Reg_Read(uint8_t i2c_addr, uint8_t reg_addr, uint8_t *reg_data, uint16_t length);
int8_t SPI_Reg_Write(uint8_t cs, uint8_t reg_addr, uint8_t *reg_data, uint16_t length);
int8_t SPI_Reg_Read(uint8_t cs, uint8_t reg_addr, uint8_t *reg_data, uint16_t length);
void print_rslt(const char api_name[], int8_t rslt);

#ifdef __cplusplus
}
#endif /* End of CPP guard */

#endif /* _BSP_BMP280_PORT_H_ */
