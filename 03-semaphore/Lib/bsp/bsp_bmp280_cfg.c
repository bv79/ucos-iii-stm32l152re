#include <bsp_bmp280_cfg.h>

struct bmp280_dev bmp;
struct bmp280_config conf;
struct bmp280_uncomp_data ucomp_data;
int32_t temp32;
double temp;

/*!
 *  @brief Function that reads data (temp, humidity and pressure)
 *
 *  @return void.
 *
 */
void BMP280_Read(void)
{
    bmp280_get_uncomp_data(&ucomp_data, &bmp);
    bmp280_get_comp_temp_32bit(&temp32, ucomp_data.uncomp_temp, &bmp);
    bmp280_get_comp_temp_double(&temp, ucomp_data.uncomp_temp, &bmp);
}

/*!
 *  @brief Function that creates a mandatory delay required in some of the APIs such as "bmg250_soft_reset",
 *      "bmg250_set_foc", "bmg250_perform_self_test"  and so on.
 *
 *  @param[in] period_ms  : the required wait time in milliseconds.
 *  @return void.
 *
 */
void Delay_ms(uint32_t period_ms)
{
    OS_ERR os_err;
    /* Implement the delay routine according to the target machine */
    if (period_ms < 1000){
        OSTimeDlyHMSM(0, 0, 0, period_ms, OS_OPT_TIME_HMSM_STRICT, &os_err);
    }
    else if (period_ms < 59000) 
    {
        OSTimeDlyHMSM(0, 0, period_ms/1000u,period_ms%1000u, OS_OPT_TIME_HMSM_STRICT, &os_err);
    }
}

/*!
 *  @brief Function for writing the sensor's registers through I2C bus.
 *
 *  @param[in] i2c_addr : sensor I2C address.
 *  @param[in] reg_addr : Register address.
 *  @param[in] reg_data : Pointer to the data buffer whose value is to be written.
 *  @param[in] length   : No of bytes to write.
 *
 *  @return Status of execution
 *  @retval 0 -> Success
 *  @retval >0 -> Failure Info
 *
 */
int8_t I2C_Reg_Write(uint8_t i2c_addr, uint8_t reg_addr, uint8_t *reg_data, uint16_t length)
{

	uint16_t bmp280_addr = (bmp.dev_id << 1);
	if (HAL_I2C_Mem_Write(&hi2c1,
						  bmp280_addr,
						  reg_addr,
						  1,
						  reg_data, length, 500) == HAL_OK)
		return 0;
	else
    return -1;
}

/*!
 *  @brief Function for reading the sensor's registers through I2C bus.
 *
 *  @param[in] i2c_addr : Sensor I2C address.
 *  @param[in] reg_addr : Register address.
 *  @param[out] reg_data    : Pointer to the data buffer to store the read data.
 *  @param[in] length   : No of bytes to read.
 *
 *  @return Status of execution
 *  @retval 0 -> Success
 *  @retval >0 -> Failure Info
 *
 */
int8_t I2C_Reg_Read(uint8_t i2c_addr, uint8_t reg_addr, uint8_t *reg_data, uint16_t length)
{

	uint16_t bmp280_addr;
	bmp280_addr = (bmp.dev_id << 1);

	if (HAL_I2C_Mem_Read(&hi2c1,
						 bmp280_addr,
                         reg_addr,
						 1,
						 reg_data, length, 500) == HAL_OK)
	{
		return 0;
	}
	else
    return -1;
}

/*!
 *  @brief Function for writing the sensor's registers through SPI bus.
 *
 *  @param[in] cs           : Chip select to enable the sensor.
 *  @param[in] reg_addr     : Register address.
 *  @param[in] reg_data : Pointer to the data buffer whose data has to be written.
 *  @param[in] length       : No of bytes to write.
 *
 *  @return Status of execution
 *  @retval 0 -> Success
 *  @retval >0 -> Failure Info
 *
 */
int8_t SPI_Reg_Write(uint8_t cs, uint8_t reg_addr, uint8_t *reg_data, uint16_t length)
{

    return -1;
}

/*!
 *  @brief Function for reading the sensor's registers through SPI bus.
 *
 *  @param[in] cs       : Chip select to enable the sensor.
 *  @param[in] reg_addr : Register address.
 *  @param[out] reg_data    : Pointer to the data buffer to store the read data.
 *  @param[in] length   : No of bytes to read.
 *
 *  @return Status of execution
 *  @retval 0 -> Success
 *  @retval >0 -> Failure Info
 *
 */
int8_t SPI_Reg_Read(uint8_t cs, uint8_t reg_addr, uint8_t *reg_data, uint16_t length)
{

    return -1;
}