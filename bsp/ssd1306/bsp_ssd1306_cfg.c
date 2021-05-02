/**
 * @file bsp_ssd1306_cfg.c
 * @brief contains functions that should be modified when porting to differrent
 * target devices
 */

#include <bsp_ssd1306_cfg.h>

int8_t SSD1306_WriteCommand(uint8_t cmd)
{
    int8_t err;
    HAL_GPIO_WritePin(SSD1306_CS_PORT, SSD1306_CS_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SSD1306_DC_PORT, SSD1306_DC_PIN, GPIO_PIN_RESET);
    err = HAL_SPI_Transmit(SSD1306_SPI_HANDLER, &cmd, 1, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(SSD1306_CS_PORT, SSD1306_CS_PIN, GPIO_PIN_SET);
    if (err == HAL_OK)
        return SSD1306_OK;
    else
        return SSD1306_WRITECMD_FAILED;
}

int8_t SSD1306_WriteData(uint8_t *data, uint8_t length)
{
    int8_t err;
    HAL_GPIO_WritePin(SSD1306_CS_PORT, SSD1306_CS_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SSD1306_DC_PORT, SSD1306_DC_PIN, GPIO_PIN_SET);
    err = HAL_SPI_Transmit(SSD1306_SPI_HANDLER, data, length, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(SSD1306_CS_PORT, SSD1306_CS_PIN, GPIO_PIN_SET);
    if (err == HAL_OK)
        return SSD1306_OK;
    else
        return SSD1306_WRITEDATA_FAILED;
}

void SSD1306_Delay(uint32_t ms) { HAL_Delay(ms); }

void SSD1306_CSPinOff(void)
{
    HAL_GPIO_WritePin(SSD1306_CS_PORT, SSD1306_CS_PIN, GPIO_PIN_RESET);
}

void SSD1306_CSPinOn(void)
{
    HAL_GPIO_WritePin(SSD1306_DC_PORT, SSD1306_DC_PIN, GPIO_PIN_SET);
}

void SSD1306_DCPinOff(void)
{
    HAL_GPIO_WritePin(SSD1306_DC_PORT, SSD1306_DC_PIN, GPIO_PIN_RESET);
}

void SSD1306_DCPinOn(void)
{
    HAL_GPIO_WritePin(SSD1306_DC_PORT, SSD1306_DC_PIN, GPIO_PIN_SET);
}

void SSD1306_ResetPinOff(void)
{
    HAL_GPIO_WritePin(SSD1306_RESET_PORT, SSD1306_RESET_PIN, GPIO_PIN_RESET);
}
void SSD1306_ResetPinOn(void)
{
    HAL_GPIO_WritePin(SSD1306_RESET_PORT, SSD1306_RESET_PIN, GPIO_PIN_SET);
}
