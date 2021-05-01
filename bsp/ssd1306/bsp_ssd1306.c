/*!
 * @file bsp_ssd1306.c
 */

#include <bsp_ssd1306.h>

/* Belong to bsp_ssd1306_cfg.h */
int8_t SSD1306_WriteCommand(uint8_t cmd)
{
    HAL_GPIO_WritePin(SSD1306_CS_PORT, SSD1306_CS_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SSD1306_DC_PORT, SSD1306_DC_PIN, GPIO_PIN_RESET);
    HAL_SPI_Transmit(SSD1306_SPI_HANDLER, &cmd, 1, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(SSD1306_CS_PORT, SSD1306_CS_PIN, GPIO_PIN_SET);
    return 0;
}

int8_t SSD1306_WriteData(uint8_t *data, uint8_t size)
{
    HAL_GPIO_WritePin(SSD1306_CS_PORT, SSD1306_CS_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SSD1306_DC_PORT, SSD1306_DC_PIN, GPIO_PIN_SET);
    HAL_SPI_Transmit(SSD1306_SPI_HANDLER, data, size, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(SSD1306_CS_PORT, SSD1306_CS_PIN, GPIO_PIN_SET);
    return 0;
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

/* End of bsp_ssd1306_cfg.h */

int8_t SSD1306_SetConstrast(uint8_t constrast)
{
    SSD1306_WriteCommand(0x81);
    SSD1306_WriteCommand(constrast);
    return 0;
}

int8_t SSD1306_EntireDispOnSoft(void)
{
    SSD1306_WriteCommand(0xA4);
    return 0;
}

int8_t SSD1306_EntireDispOnHard(void)
{
    SSD1306_WriteCommand(0xA5);
    return 0;
}

int8_t SSD1306_InverseDisp(SSD1306_Inverse_t state)
{
    SSD1306_WriteCommand(0xA6 | state);
    return 0;
}

int8_t SSD1306_DispOnOff(SSD1306_DispState_t state)
{
    SSD1306_WriteCommand(0xAE | state);
    if (state == 0x01)      /* ON */
        SSD1306_Delay(100); /* SEG/COM will be ON after 100ms */
    return 0;
}

int8_t SSD1306_SetupContHorizontalScroll(
    SSD1306_HorizontalScrollDirection_t direct, SSD1306_PageAddr_t start_page,
    SSD1306_ScrollStep_t step, SSD1306_PageAddr_t end_page)
{
    SSD1306_WriteCommand(0x26 | direct);
    SSD1306_WriteCommand(SSD1306_DUMMY_BYTE_OFF);
    SSD1306_WriteCommand(start_page);
    SSD1306_WriteCommand(step);
    SSD1306_WriteCommand(end_page);
    SSD1306_WriteCommand(SSD1306_DUMMY_BYTE_OFF);
    SSD1306_WriteCommand(SSD1306_DUMMY_BYTE_ON);
    return 0;
}

int8_t SSD1306_SetupContHorizontalVerticalScroll(
    SSD1306_HorizontalScrollDirection_t direct, SSD1306_PageAddr_t start_page,
    SSD1306_ScrollStep_t step, SSD1306_PageAddr_t end_page,
    SSD1306_Row_t offset)
{
    SSD1306_WriteCommand(0x29 | direct);
    SSD1306_WriteCommand(SSD1306_DUMMY_BYTE_OFF);
    SSD1306_WriteCommand(start_page);
    SSD1306_WriteCommand(step);
    SSD1306_WriteCommand(end_page);
    SSD1306_WriteCommand(offset);
    return 0;
}

int8_t SSD1306_DeactiveScroll(void)
{
    SSD1306_WriteCommand(0x2E);
    return 0;
}

int8_t SSD1306_ActiveScroll(void)
{
    SSD1306_WriteCommand(0x2F);
    return 0;
}

int8_t SSD1306_SetVerticalScrollArea(SSD1306_Row_t n_fixed_row,
                                     SSD1306_Row_t n_scroll_row)
{
    if (((n_fixed_row + n_scroll_row) <= SSD1306_MUX_RATIO) &&
        (n_scroll_row <= SSD1306_MUX_RATIO))
    {
        SSD1306_WriteCommand(0xA3);
        SSD1306_WriteCommand(n_fixed_row);
        SSD1306_WriteCommand(n_scroll_row);
    }

    return 0;
}

int8_t SSD1306_SetLowerColStartAddr(SSD1306_Col_t addr)
{
    if (addr < SSD1306_HEIGHT / SSD1306_SEG_SIZE)
        SSD1306_WriteCommand(0x00 | addr);
    return 0;
}

int8_t SSD1306_SetHigherColStartAddr(SSD1306_Col_t addr)
{
    if (addr < SSD1306_HEIGHT / SSD1306_SEG_SIZE)
        SSD1306_WriteCommand(0x10 | addr);
    return 0;
}

int8_t SSD1306_SetMemAddrMode(SSD1306_MemAddrMode_t mode)
{
    SSD1306_WriteCommand(0x20);
    SSD1306_WriteCommand(mode);
    return 0;
}

int8_t SSD1306_SetColAddr(SSD1306_Col_t col_start, SSD1306_Col_t col_end)
{
    SSD1306_WriteCommand(0x21);
    SSD1306_WriteCommand(col_start);
    SSD1306_WriteCommand(col_end);
    return 0;
}

int8_t SSD1306_SetPageAddr(SSD1306_PageAddr_t start_page,
                           SSD1306_PageAddr_t end_page)
{
    SSD1306_WriteCommand(0x22);
    SSD1306_WriteCommand(start_page);
    SSD1306_WriteCommand(end_page);
    return 0;
}

int8_t SSD1306_SetPageStartAddr(SSD1306_PageAddr_t start_page)
{
    SSD1306_WriteCommand(0xB0 | start_page);
    return 0;
}

int8_t SSD1306_SetDispStartLine(SSD1306_Row_t start_line)
{
    SSD1306_WriteCommand(0x40 | start_line);
    return 0;
}

int8_t SSD1306_SetSegRemap(SSD1306_SegmentRemapDirection_t direction)
{
    SSD1306_WriteCommand(0xA0 | direction);
    return 0;
}

int8_t SSD1306_SetMultiplexRatio(SSD1306_MUXRatio_t ratio)
{
    SSD1306_WriteCommand(0xA8);
    SSD1306_WriteCommand(ratio);
    return 0;
}

int8_t SSD1306_SetCOMOutPutScanDirection(SSD1306_COMOutputScanDirection_t state)
{
    SSD1306_WriteCommand(0xC0 | state);
    return 0;
}

int8_t SSD1306_SetDispOffet(SSD1306_Row_t offset)
{
    SSD1306_WriteCommand(0xD3);
    SSD1306_WriteCommand(offset);
    return 0;
}

int8_t SSD1306_SetHardwareCfg(SSD1306_PinConfig_t cfg, SSD1306_COMRemap_t remap)
{
    SSD1306_WriteCommand(0xDA);
    SSD1306_WriteCommand(cfg | remap);
    return 0;
}

int8_t SSD1306_ClkCfg(SSD1306_ClkRatio_t ratio, SSD1306_ClkFrq_t frq)
{
    SSD1306_WriteCommand(0xD5);
    SSD1306_WriteCommand(ratio | (frq << 4));
    return 0;
}

int8_t SSD1306_SetPrechargePeriod(SSD1306_Phase_t phase1_period,
                                  SSD1306_Phase_t phase2_period)
{
    SSD1306_WriteCommand(0xD9);
    SSD1306_WriteCommand(phase1_period | (phase2_period << 4));
    return 0;
}

int8_t SSD1306_SetVCOMHDeselectLevel(SSD1306_VCOMHDeselectLevel_t level)
{
    SSD1306_WriteCommand(0xDB);
    SSD1306_WriteCommand(level);
    return 0;
}

int8_t SSD1306_SetChargeBumpSetting(SSD1306_ChargeBumpState_t state)
{
    SSD1306_WriteCommand(0x8D);
    SSD1306_WriteCommand(state);
    return 0;
}

void SSD1306_Init(void)
{
    SSD1306_Delay(100); /* Wait until Vcc is statble */
    SSD1306_Reset();

    SSD1306_SetSegRemap(SSD1306_SEG_REMAP_INVERSE);
    SSD1306_SetChargeBumpSetting(SSD1306_CHARGE_BUMP_ENABLE);
    SSD1306_DispOnOff(SSD1306_DISP_ON);
    SSD1306_Delay(100);
    SSD1306_FillBuffer(SSD1306_PIXEL_OFF);
    SSD1306_Board_Initialize();
    SSD1306_Board_PrintChar(5, 3, 'A');
    SSD1306_UpdateDisp();
}

void SSD1306_Reset(void)
{
    SSD1306_ResetPinOff();
    SSD1306_Delay(5); /* at least 3us */
    SSD1306_ResetPinOn();
}

void SSD1306_UpdateDisp(void)
{
    for (uint8_t i = 0; i < SSD1306_HEIGHT / SSD1306_SEG_SIZE; i++)
    {
        SSD1306_WriteCommand(0xB0 + i);
        SSD1306_WriteCommand(0x00);
        SSD1306_WriteCommand(0x10);
        for (uint8_t j = 0; j < SSD1306_WIDTH; j++)
        {
            SSD1306_WriteData(&SSD1306_Buffer[i][j], 1);
        }
    }
}

void SSD1306_FillBuffer(SSD1306_PixelState_t state)
{
    uint8_t byte = 0x00;
    if (state)
        byte = 0xFF;
    for (int8_t i = 0; i < SSD1306_HEIGHT / SSD1306_SEG_SIZE; i++)
    {
        for (int8_t j = 0; j < SSD1306_WIDTH; j++)
        {
            SSD1306_Buffer[i][j] = byte;
        }
    }
}

void SSD1306_DrawPixel(uint8_t x, uint8_t y, SSD1306_PixelState_t state)
{
    if (state)
        SSD1306_Buffer[y / SSD1306_SEG_SIZE][x] |= 1u << (y % SSD1306_SEG_SIZE);
    else
        SSD1306_Buffer[y / SSD1306_SEG_SIZE][x] &=
            ~(1u << (y % SSD1306_SEG_SIZE));
}

void SSD1306_Board_Initialize(void)
{
    for (uint8_t y = 0; y <= SSD1306_BOARD_HEIGHT; y++)
    {
        for (uint8_t x = 0; x <= SSD1306_BOARD_WIDTH; x++)
        {
            if (y == 0 || y % 10 == 0)
            {
                SSD1306_DrawPixel(x + SSD1306_BOARD_X_OFFSET,
                                  y + SSD1306_BOARD_Y_OFFSET, SSD1306_PIXEL_ON);
            }
            if (x == 0 || x % 8 == 0)
            {
                SSD1306_DrawPixel(x + SSD1306_BOARD_X_OFFSET,
                                  y + SSD1306_BOARD_Y_OFFSET, SSD1306_PIXEL_ON);
            }
        }
    }
}

void SSD1306_Board_PrintChar(uint8_t board_col, uint8_t board_row, char c)
{
    if (board_col <= SSD1306_BOARD_WIDTH / SSD1306_BOARD_CELL_WIDTH &&
        board_row <= SSD1306_BOARD_HEIGHT / SSD1306_BOARD_CELL_HEIGHT)
    {
        for (uint8_t j = 0; j < SSD1306_FONT_WIDTH; j++)
        {
            for (uint8_t i = 0; i < SSD1306_FONT_HEIGHT; i++)
            {
                SSD1306_DrawPixel(
                    board_col * SSD1306_BOARD_CELL_WIDTH + SSD1306_BOARD_X0 +
                        SSD1306_BOARD_X_OFFSET + j,
                    board_row * SSD1306_BOARD_CELL_HEIGHT + SSd1306_BOARD_Y0 +
                        SSD1306_BOARD_Y_OFFSET + i,
                    Font[(c - 32) * SSD1306_FONT_WIDTH + j] & (1 << i));
            }
        }
    }
}