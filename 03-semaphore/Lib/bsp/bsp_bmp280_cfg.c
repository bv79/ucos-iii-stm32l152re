#include <bsp_bmp280_cfg.h>

SPI_HandleTypeDef *bmp280_spi_handler;
I2C_HandleTypeDef *bmp280_i2c_handler;

struct bmp280_dev bmp;
struct bmp280_config conf;
struct bmp280_uncomp_data ucomp_data;

int32_t temp32;
double temp;

uint32_t pres32;
double pres;

/*!
 *  @brief Function that reads and computes data (temp, humidity and pressure)
 *
 *  @return void.
 *
 */
void BMP280_Read(void)
{
	bmp280_get_uncomp_data(&ucomp_data, &bmp);

	bmp280_get_comp_temp_32bit(&temp32, ucomp_data.uncomp_temp, &bmp);
	bmp280_get_comp_pres_32bit(&pres32, ucomp_data.uncomp_press, &bmp);

	bmp280_get_comp_temp_double(&temp, ucomp_data.uncomp_temp, &bmp);
	bmp280_get_comp_pres_double(&pres, ucomp_data.uncomp_press, &bmp);
}

/*!
 *  @brief Function that initializes and configurates BMP280.
 *			Call BMP280_Setup() before BMP280_Read()
 *
 *  @return void.
 *
 */
void BMP280_Setup(void)
{
	/* Assign address*/
	bmp.dev_id = BMP280_I2C_ADDR_PRIM;

	/* Map functions */
	bmp.delay_ms = Delay_ms;
	#ifdef BMP280_SPI
		bmp280_spi_handler = &hspi1;
		bmp.read = SPI_Reg_Read;
		bmp.write = SPI_Reg_Write;
		bmp.intf = BMP280_SPI_INTF;
	#endif
	#ifdef BMP280_I2C
		bmp280_i2c_handler = &hi2c1;
		bmp.read = I2C_Reg_Read;
		bmp.write = I2C_Reg_Write;
		bmp.intf = BMP280_I2C_INTF;
	#endif
	
	conf.filter = BMP280_FILTER_COEFF_2;
	conf.os_temp = BMP280_OS_4X;
	conf.os_pres = BMP280_OS_NONE;
	conf.odr = BMP280_ODR_1000_MS;
	bmp280_init(&bmp);
	bmp280_set_config(&conf, &bmp);
	bmp280_set_power_mode(BMP280_NORMAL_MODE, &bmp);
}
/*!
 *  @brief Function that creates a mandatory delay required in some of the APIs such as "bmg250_soft_reset",
 *      "bmg250_set_foc", "bmg250_perform_self_test"  and so on.
 *
 *  @param[in] period_ms  : the required wait time in milliseconds. (< 60000ms)
 *  @return void.
 *
 */
void Delay_ms(uint32_t period_ms)
{
	OS_ERR os_err;
	/* Implement the delay routine according to the target machine */
	if (period_ms < 1000)
	{
		OSTimeDlyHMSM(0, 0, 0, period_ms, OS_OPT_TIME_HMSM_STRICT, &os_err);
	}
	else if (period_ms < 60000)
	{
		OSTimeDlyHMSM(0, 0, period_ms / 1000u, period_ms % 1000u, OS_OPT_TIME_HMSM_STRICT, &os_err);
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
 *  @retval -1 -> Failed
 *
 */
int8_t I2C_Reg_Write(uint8_t i2c_addr, uint8_t reg_addr, uint8_t *reg_data, uint16_t length)
{

	uint16_t bmp280_addr = (bmp.dev_id << 1);
	if (HAL_I2C_Mem_Write(bmp280_i2c_handler,
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
 *  @retval -1 -> Failed
 *
 */
int8_t I2C_Reg_Read(uint8_t i2c_addr, uint8_t reg_addr, uint8_t *reg_data, uint16_t length)
{

	uint16_t bmp280_addr;
	bmp280_addr = (bmp.dev_id << 1);

	if (HAL_I2C_Mem_Read(bmp280_i2c_handler,
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
 *  @param[in] cs           : NOT USE
 *  @param[in] reg_addr     : NOT USE
 *  @param[in] reg_data 	: Pointer to the data buffer whose data has to be written.
 *  @param[in] length       : Number of bytes to write.
 *
 *  @return Status of execution
 *  @retval 0 -> Success
 *  @retval -1 -> Failed
 *
 */
int8_t SPI_Reg_Write(uint8_t cs, uint8_t reg_addr, uint8_t *reg_data, uint16_t length)
{
	HAL_GPIO_WritePin(BMP280_SPI_CS_PORT, BMP280_SPI_CS_PIN, GPIO_PIN_RESET);
	if (HAL_SPI_Transmit(bmp280_spi_handler, reg_data, length, 100) == HAL_OK)
	{
		HAL_GPIO_WritePin(BMP280_SPI_CS_PORT, BMP280_SPI_CS_PIN, GPIO_PIN_SET);
		return 0;
	}
	else
		return -1;
}

/*!
 *  @brief Function for reading the sensor's registers through SPI bus.
 *
 *  @param[in] cs       	: NOT USE
 *  @param[in] reg_addr 	: Register command
 *  @param[out] reg_data    : Pointer to the data buffer to store the read data.
 *  @param[in] length   	: Number of bytes to read.
 *
 *  @return Status of execution
 *  @retval 0 -> Success
 *  @retval 1 -> Failed
 *
 */
int8_t SPI_Reg_Read(uint8_t cs, uint8_t reg_addr, uint8_t *reg_data, uint16_t length)
{

	HAL_GPIO_WritePin(BMP280_SPI_CS_PORT, BMP280_SPI_CS_PIN, GPIO_PIN_RESET);
	if (HAL_SPI_Transmit(bmp280_spi_handler, &reg_addr, 1, 100) == HAL_OK && HAL_SPI_Receive(bmp280_spi_handler, reg_data, length, 100) == HAL_OK)
	{
		HAL_GPIO_WritePin(BMP280_SPI_CS_PORT, BMP280_SPI_CS_PIN, GPIO_PIN_SET);
		return 0;
	}
	else
		return -1;
}