/*!
 * @file bsp_ssd1306.h
 */
#ifndef __BSP_SSD1306_H__
#define __BSP_SSD1306_H__

#ifdef __cplusplus
extern "C"
{
#endif

/* Belong to bsp_ssd1306_cfg.h */
#include <gpio.h>
#include <spi.h>
/* End of cfg */

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define SSD1306_WIDTH 128u
#define SSD1306_HEIGHT 64u

#define SSD1306_MUX_RATIO 63u

#define SSD1306_DUMMY_BYTE_OFF 0x00
#define SSD1306_DUMMY_BYTE_ON 0xFF

#define SSD1306_SEG_SIZE 0x08

uint8_t SSD1306_Buffer[SSD1306_HEIGHT / 8][SSD1306_WIDTH];

static const uint8_t Font[] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // sp
0x00, 0x00, 0xfa, 0x00, 0x00, 0x00,  // !
0x00, 0xe0, 0x00, 0xe0, 0x00, 0x00,  // "
0x28, 0xfe, 0x28, 0xfe, 0x28, 0x00,  // #
0x74, 0x54, 0xfe, 0x54, 0x5c, 0x00,  // $
0x02, 0x4c, 0x10, 0x64, 0x80, 0x00,  // %
0x6c, 0x92, 0xaa, 0x44, 0x0a, 0x00,  // &
0x00, 0x00, 0xe0, 0x00, 0x00, 0x00,  // '
0x00, 0x38, 0x44, 0x82, 0x00, 0x00,  // (
0x00, 0x82, 0x44, 0x38, 0x00, 0x00,  // )
0x28, 0x10, 0x7c, 0x10, 0x28, 0x00,  // *
0x10, 0x10, 0x7c, 0x10, 0x10, 0x00,  // +
0x00, 0x0a, 0x0c, 0x00, 0x00, 0x00,  // ,
0x10, 0x10, 0x10, 0x10, 0x10, 0x10,  // -
0x00, 0x06, 0x06, 0x00, 0x00, 0x00,  // .
0x04, 0x08, 0x10, 0x20, 0x40, 0x00,  // /
0x7c, 0x8a, 0x92, 0xa2, 0x7c, 0x00,  // 0
0x22, 0x62, 0xfe, 0x02, 0x02, 0x00,  // 1
0x42, 0x86, 0x8a, 0x92, 0x62, 0x00,  // 2
0x84, 0x82, 0xa2, 0xd2, 0x8c, 0x00,  // 3
0x18, 0x28, 0x48, 0xfe, 0x08, 0x00,  // 4
0xe2, 0xa2, 0xa2, 0xa2, 0x9c, 0x00,  // 5
0x3c, 0x52, 0x92, 0x92, 0x0c, 0x00,  // 6
0x86, 0x88, 0x90, 0xa0, 0xc0, 0x00,  // 7
0x6c, 0x92, 0x92, 0x92, 0x6c, 0x00,  // 8
0x60, 0x92, 0x92, 0x94, 0x78, 0x00,  // 9
0x00, 0x6c, 0x6c, 0x00, 0x00, 0x00,  // :
0x00, 0x6a, 0x6c, 0x00, 0x00, 0x00,  // ;
0x10, 0x28, 0x44, 0x82, 0x00, 0x00,  // <
0x28, 0x28, 0x28, 0x28, 0x28, 0x00,  // =
0x00, 0x82, 0x44, 0x28, 0x10, 0x00,  // >
0x40, 0x80, 0x8a, 0x90, 0x60, 0x00,  // ?
0x7c, 0x82, 0xba, 0xaa, 0x7a, 0x00,  // @
0x7e, 0x88, 0x88, 0x88, 0x7e, 0x00,  // A
0xfe, 0x92, 0x92, 0x92, 0x6c, 0x00,  // B
0x7c, 0x82, 0x82, 0x82, 0x44, 0x00,  // C
0xfe, 0x82, 0x82, 0x82, 0x7c, 0x00,  // D
0xfe, 0x92, 0x92, 0x92, 0x82, 0x00,  // E
0xfe, 0x90, 0x90, 0x90, 0x80, 0x00,  // F
0x7c, 0x82, 0x92, 0x92, 0x5e, 0x00,  // G
0xfe, 0x10, 0x10, 0x10, 0xfe, 0x00,  // H
0x82, 0x82, 0xfe, 0x82, 0x82, 0x00,  // I
0x04, 0x02, 0x82, 0xfc, 0x80, 0x00,  // J
0xfe, 0x10, 0x28, 0x44, 0x82, 0x00,  // K
0xfe, 0x02, 0x02, 0x02, 0x02, 0x00,  // L
0xfe, 0x40, 0x20, 0x40, 0xfe, 0x00,  // M
0xfe, 0x20, 0x10, 0x08, 0xfe, 0x00,  // N
0x7c, 0x82, 0x82, 0x82, 0x7c, 0x00,  // O
0xfe, 0x90, 0x90, 0x90, 0x60, 0x00,  // P
0x7c, 0x82, 0x8a, 0x84, 0x7a, 0x00,  // Q
0xfe, 0x90, 0x98, 0x94, 0x62, 0x00,  // R
0x64, 0x92, 0x92, 0x92, 0x4c, 0x00,  // S
0x80, 0x80, 0xfe, 0x80, 0x80, 0x00,  // T
0xfc, 0x02, 0x02, 0x02, 0xfc, 0x00,  // U
0xf8, 0x04, 0x02, 0x04, 0xf8, 0x00,  // V
0xfc, 0x02, 0x1c, 0x02, 0xfc, 0x00,  // W
0xc6, 0x28, 0x10, 0x28, 0xc6, 0x00,  // X
0xe0, 0x10, 0x0e, 0x10, 0xe0, 0x00,  // Y
0x86, 0x8a, 0x92, 0xa2, 0xc2, 0x00,  // Z
0x00, 0xfe, 0x82, 0x82, 0x00, 0x00,  // [
0x40, 0x20, 0x10, 0x08, 0x04, 0x00,  /* \ */
0x00, 0x82, 0x82, 0xfe, 0x00, 0x00,  // ]
0x20, 0x40, 0x80, 0x40, 0x20, 0x00,  // ^
0x02, 0x02, 0x02, 0x02, 0x02, 0x00,  // _
0x00, 0x80, 0x40, 0x20, 0x00, 0x00,  // `
0x2e, 0x2a, 0x2a, 0x2a, 0x1e, 0x00,  // a
0xfe, 0x12, 0x22, 0x22, 0x1c, 0x00,  // b
0x1c, 0x22, 0x22, 0x22, 0x04, 0x00,  // c
0x1c, 0x22, 0x22, 0x12, 0xfe, 0x00,  // d
0x1c, 0x2a, 0x2a, 0x2a, 0x18, 0x00,  // e
0x10, 0x7e, 0x90, 0x80, 0x40, 0x00,  // f
0x30, 0x4a, 0x4a, 0x4a, 0x7c, 0x00,  // g
0xfe, 0x10, 0x20, 0x20, 0x1e, 0x00,  // h
0x00, 0x22, 0xbe, 0x02, 0x00, 0x00,  // i
0x04, 0x02, 0x02, 0xbc, 0x00, 0x00,  // j
0xfe, 0x08, 0x14, 0x22, 0x00, 0x00,  // k
0x00, 0x82, 0xfe, 0x02, 0x00, 0x00,  // l
0x3e, 0x20, 0x18, 0x20, 0x1e, 0x00,  // m
0x3e, 0x10, 0x20, 0x20, 0x1e, 0x00,  // n
0x1c, 0x22, 0x22, 0x22, 0x1c, 0x00,  // o
0x3e, 0x28, 0x28, 0x28, 0x10, 0x00,  // p
0x10, 0x28, 0x28, 0x28, 0x3e, 0x00,  // q
0x3e, 0x10, 0x20, 0x20, 0x10, 0x00,  // r
0x12, 0x2a, 0x2a, 0x2a, 0x04, 0x00,  // s
0x20, 0xfc, 0x22, 0x02, 0x04, 0x00,  // t
0x3c, 0x02, 0x02, 0x04, 0x3e, 0x00,  // u
0x38, 0x04, 0x02, 0x04, 0x38, 0x00,  // v
0x3c, 0x02, 0x0c, 0x02, 0x3c, 0x00,  // w
0x22, 0x14, 0x08, 0x14, 0x22, 0x00,  // x
0x30, 0x0a, 0x0a, 0x0a, 0x3c, 0x00,  // y
0x22, 0x26, 0x2a, 0x32, 0x22, 0x00,  // z
0x00, 0x10, 0x6c, 0x82, 0x00, 0x00,  // {
0x00, 0x00, 0xfe, 0x00, 0x00, 0x00,  // |
0x00, 0x82, 0x6c, 0x10, 0x00, 0x00,  // }
0x18, 0x20, 0x10, 0x08, 0x30, 0x00,  // ~
};

typedef enum
{
    SSD1306_MEM_ADDR_HORIZONTAL_MODE,
    SSD1306_MEM_ADDR_VERTICAL_MODE,
    SSD1306_MEM_ADDR_PAGE_MODE
} SSD1306_MemAddrMode_t;

typedef enum
{
    SSD1306_PAGE_ADDR_0,
    SSD1306_PAGE_ADDR_1,
    SSD1306_PAGE_ADDR_2,
    SSD1306_PAGE_ADDR_3,
    SSD1306_PAGE_ADDR_4,
    SSD1306_PAGE_ADDR_5,
    SSD1306_PAGE_ADDR_6,
    SSD1306_PAGE_ADDR_7
} SSD1306_PageAddr_t;

typedef enum
{
    SSD1306_SCROLL_STEP_5_FRAME,
    SSD1306_SCROLL_STEP_64_FRAME,
    SSD1306_SCROLL_STEP_128_FRAME,
    SSD1306_SCROLL_STEP_256_FRAME,
    SSD1306_SCROLL_STEP_3_FRAME,
    SSD1306_SCROLL_STEP_4_FRAME,
    SSD1306_SCROLL_STEP_25_FRAME,
    SSD1306_SCROLL_STEP_2_FRAME
} SSD1306_ScrollStep_t;

typedef enum
{
    SSD1306_VCOMH_065_VCC = 0x00,
    SSD1306_VCOMH_077_VCC = 0x20,
    SSD1306_VCOMH_083_VCC = 0x30
} SSD1306_VCOMHDeselectLevel_t;

typedef enum
{
    SSD1306_NORMAL_DISP,
    SSD1306_INVERSE_DISP
} SSD1306_Inverse_t;

typedef enum
{
    SSD1306_DISP_OFF,
    SSD1306_DISP_ON
} SSD1306_DispState_t;

typedef enum
{
    SSD1306_RIGHT_SCROLL = 0x01,
    SSD1306_LEFT_SCROLL
} SSD1306_HorizontalScrollDirection_t;

typedef enum
{
    SSD1306_SEG_REMAP_NORM,
    SSD1306_SEG_REMAP_INVERSE
} SSD1306_SegmentRemapDirection_t;

typedef enum
{
    SSD1306_FLIP_OFF = 0x00,
    SSD1306_FLIP_ON = 0x08
} SSD1306_COMOutputScanDirection_t; /* COM Output Scan Direction */

typedef enum
{
    SSD1306_PIN_CFG_SEQUENT = 0x02,
    SSD1306_PIN_CFG_ALTER = 0x12
} SSD1306_PinConfig_t;

typedef enum
{
    SSD1306_COM_REMAP_DISABLE = 0x02,
    SSD1306_COM_REMAP_ENABLE = 0x22
} SSD1306_COMRemap_t;

typedef enum
{
    SSD1306_CHARGE_BUMP_DISABLE = 0x10,
    SSD1306_CHARGE_BUMP_ENABLE = 0x14
} SSD1306_ChargeBumpState_t;

typedef enum
{
    SSD1306_PIXEL_OFF,
    SSD1306_PIXEL_ON
} SSD1306_PixelState_t;

#define SSD1306_CONSTRAST

typedef enum
{
    SSD1306_COL_0,
    SSD1306_COL_1,
    SSD1306_COL_2,
    SSD1306_COL_3,
    SSD1306_COL_4,
    SSD1306_COL_5,
    SSD1306_COL_6,
    SSD1306_COL_7,
    SSD1306_COL_8,
    SSD1306_COL_9,
    SSD1306_COL_10,
    SSD1306_COL_11,
    SSD1306_COL_12,
    SSD1306_COL_13,
    SSD1306_COL_14,
    SSD1306_COL_15,
    SSD1306_COL_16,
    SSD1306_COL_17,
    SSD1306_COL_18,
    SSD1306_COL_19,
    SSD1306_COL_20,
    SSD1306_COL_21,
    SSD1306_COL_22,
    SSD1306_COL_23,
    SSD1306_COL_24,
    SSD1306_COL_25,
    SSD1306_COL_26,
    SSD1306_COL_27,
    SSD1306_COL_28,
    SSD1306_COL_29,
    SSD1306_COL_30,
    SSD1306_COL_31,
    SSD1306_COL_32,
    SSD1306_COL_33,
    SSD1306_COL_34,
    SSD1306_COL_35,
    SSD1306_COL_36,
    SSD1306_COL_37,
    SSD1306_COL_38,
    SSD1306_COL_39,
    SSD1306_COL_40,
    SSD1306_COL_41,
    SSD1306_COL_42,
    SSD1306_COL_43,
    SSD1306_COL_44,
    SSD1306_COL_45,
    SSD1306_COL_46,
    SSD1306_COL_47,
    SSD1306_COL_48,
    SSD1306_COL_49,
    SSD1306_COL_50,
    SSD1306_COL_51,
    SSD1306_COL_52,
    SSD1306_COL_53,
    SSD1306_COL_54,
    SSD1306_COL_55,
    SSD1306_COL_56,
    SSD1306_COL_57,
    SSD1306_COL_58,
    SSD1306_COL_59,
    SSD1306_COL_60,
    SSD1306_COL_61,
    SSD1306_COL_62,
    SSD1306_COL_63,
    SSD1306_COL_64,
    SSD1306_COL_65,
    SSD1306_COL_66,
    SSD1306_COL_67,
    SSD1306_COL_68,
    SSD1306_COL_69,
    SSD1306_COL_70,
    SSD1306_COL_71,
    SSD1306_COL_72,
    SSD1306_COL_73,
    SSD1306_COL_74,
    SSD1306_COL_75,
    SSD1306_COL_76,
    SSD1306_COL_77,
    SSD1306_COL_78,
    SSD1306_COL_79,
    SSD1306_COL_80,
    SSD1306_COL_81,
    SSD1306_COL_82,
    SSD1306_COL_83,
    SSD1306_COL_84,
    SSD1306_COL_85,
    SSD1306_COL_86,
    SSD1306_COL_87,
    SSD1306_COL_88,
    SSD1306_COL_89,
    SSD1306_COL_90,
    SSD1306_COL_91,
    SSD1306_COL_92,
    SSD1306_COL_93,
    SSD1306_COL_94,
    SSD1306_COL_95,
    SSD1306_COL_96,
    SSD1306_COL_97,
    SSD1306_COL_98,
    SSD1306_COL_99,
    SSD1306_COL_100,
    SSD1306_COL_101,
    SSD1306_COL_102,
    SSD1306_COL_103,
    SSD1306_COL_104,
    SSD1306_COL_105,
    SSD1306_COL_106,
    SSD1306_COL_107,
    SSD1306_COL_108,
    SSD1306_COL_109,
    SSD1306_COL_110,
    SSD1306_COL_111,
    SSD1306_COL_112,
    SSD1306_COL_113,
    SSD1306_COL_114,
    SSD1306_COL_115,
    SSD1306_COL_116,
    SSD1306_COL_117,
    SSD1306_COL_118,
    SSD1306_COL_119,
    SSD1306_COL_120,
    SSD1306_COL_121,
    SSD1306_COL_122,
    SSD1306_COL_123,
    SSD1306_COL_124,
    SSD1306_COL_125,
    SSD1306_COL_126,
    SSD1306_COL_127,
} SSD1306_Col_t;

typedef enum
{
    SSD1306_ROW_0,
    SSD1306_ROW_1,
    SSD1306_ROW_2,
    SSD1306_ROW_3,
    SSD1306_ROW_4,
    SSD1306_ROW_5,
    SSD1306_ROW_6,
    SSD1306_ROW_7,
    SSD1306_ROW_8,
    SSD1306_ROW_9,
    SSD1306_ROW_10,
    SSD1306_ROW_11,
    SSD1306_ROW_12,
    SSD1306_ROW_13,
    SSD1306_ROW_14,
    SSD1306_ROW_15,
    SSD1306_ROW_16,
    SSD1306_ROW_17,
    SSD1306_ROW_18,
    SSD1306_ROW_19,
    SSD1306_ROW_20,
    SSD1306_ROW_21,
    SSD1306_ROW_22,
    SSD1306_ROW_23,
    SSD1306_ROW_24,
    SSD1306_ROW_25,
    SSD1306_ROW_26,
    SSD1306_ROW_27,
    SSD1306_ROW_28,
    SSD1306_ROW_29,
    SSD1306_ROW_30,
    SSD1306_ROW_31,
    SSD1306_ROW_32,
    SSD1306_ROW_33,
    SSD1306_ROW_34,
    SSD1306_ROW_35,
    SSD1306_ROW_36,
    SSD1306_ROW_37,
    SSD1306_ROW_38,
    SSD1306_ROW_39,
    SSD1306_ROW_40,
    SSD1306_ROW_41,
    SSD1306_ROW_42,
    SSD1306_ROW_43,
    SSD1306_ROW_44,
    SSD1306_ROW_45,
    SSD1306_ROW_46,
    SSD1306_ROW_47,
    SSD1306_ROW_48,
    SSD1306_ROW_49,
    SSD1306_ROW_50,
    SSD1306_ROW_51,
    SSD1306_ROW_52,
    SSD1306_ROW_53,
    SSD1306_ROW_54,
    SSD1306_ROW_55,
    SSD1306_ROW_56,
    SSD1306_ROW_57,
    SSD1306_ROW_58,
    SSD1306_ROW_59,
    SSD1306_ROW_60,
    SSD1306_ROW_61,
    SSD1306_ROW_62,
    SSD1306_ROW_63,
} SSD1306_Row_t;

typedef enum
{
    SSD1306_MUX_RATIO_15,
    SSD1306_MUX_RATIO_16,
    SSD1306_MUX_RATIO_17,
    SSD1306_MUX_RATIO_18,
    SSD1306_MUX_RATIO_19,
    SSD1306_MUX_RATIO_20,
    SSD1306_MUX_RATIO_21,
    SSD1306_MUX_RATIO_22,
    SSD1306_MUX_RATIO_23,
    SSD1306_MUX_RATIO_24,
    SSD1306_MUX_RATIO_25,
    SSD1306_MUX_RATIO_26,
    SSD1306_MUX_RATIO_27,
    SSD1306_MUX_RATIO_28,
    SSD1306_MUX_RATIO_29,
    SSD1306_MUX_RATIO_30,
    SSD1306_MUX_RATIO_31,
    SSD1306_MUX_RATIO_32,
    SSD1306_MUX_RATIO_33,
    SSD1306_MUX_RATIO_34,
    SSD1306_MUX_RATIO_35,
    SSD1306_MUX_RATIO_36,
    SSD1306_MUX_RATIO_37,
    SSD1306_MUX_RATIO_38,
    SSD1306_MUX_RATIO_39,
    SSD1306_MUX_RATIO_40,
    SSD1306_MUX_RATIO_41,
    SSD1306_MUX_RATIO_42,
    SSD1306_MUX_RATIO_43,
    SSD1306_MUX_RATIO_44,
    SSD1306_MUX_RATIO_45,
    SSD1306_MUX_RATIO_46,
    SSD1306_MUX_RATIO_47,
    SSD1306_MUX_RATIO_48,
    SSD1306_MUX_RATIO_49,
    SSD1306_MUX_RATIO_50,
    SSD1306_MUX_RATIO_51,
    SSD1306_MUX_RATIO_52,
    SSD1306_MUX_RATIO_53,
    SSD1306_MUX_RATIO_54,
    SSD1306_MUX_RATIO_55,
    SSD1306_MUX_RATIO_56,
    SSD1306_MUX_RATIO_57,
    SSD1306_MUX_RATIO_58,
    SSD1306_MUX_RATIO_59,
    SSD1306_MUX_RATIO_60,
    SSD1306_MUX_RATIO_61,
    SSD1306_MUX_RATIO_62,
    SSD1306_MUX_RATIO_63,
} SSD1306_MUXRatio_t;

typedef enum
{
    SSD1306_CLK_RATIO_0,
    SSD1306_CLK_RATIO_1,
    SSD1306_CLK_RATIO_2,
    SSD1306_CLK_RATIO_3,
    SSD1306_CLK_RATIO_4,
    SSD1306_CLK_RATIO_5,
    SSD1306_CLK_RATIO_6,
    SSD1306_CLK_RATIO_7,
    SSD1306_CLK_RATIO_8,
    SSD1306_CLK_RATIO_9,
    SSD1306_CLK_RATIO_10,
    SSD1306_CLK_RATIO_11,
    SSD1306_CLK_RATIO_12,
    SSD1306_CLK_RATIO_13,
    SSD1306_CLK_RATIO_14,
    SSD1306_CLK_RATIO_15,
} SSD1306_ClkRatio_t;

typedef enum
{
    SSD1306_CLK_FRQ_0,
    SSD1306_CLK_FRQ_1,
    SSD1306_CLK_FRQ_2,
    SSD1306_CLK_FRQ_3,
    SSD1306_CLK_FRQ_4,
    SSD1306_CLK_FRQ_5,
    SSD1306_CLK_FRQ_6,
    SSD1306_CLK_FRQ_7,
    SSD1306_CLK_FRQ_8,
    SSD1306_CLK_FRQ_9,
    SSD1306_CLK_FRQ_10,
    SSD1306_CLK_FRQ_11,
    SSD1306_CLK_FRQ_12,
    SSD1306_CLK_FRQ_13,
    SSD1306_CLK_FRQ_14,
    SSD1306_CLK_FRQ_15,
} SSD1306_ClkFrq_t;

typedef enum
{
    SSD1306_PHASE_1 = 1,
    SSD1306_PHASE_2,
    SSD1306_PHASE_3,
    SSD1306_PHASE_4,
    SSD1306_PHASE_5,
    SSD1306_PHASE_6,
    SSD1306_PHASE_7,
    SSD1306_PHASE_8,
    SSD1306_PHASE_9,
    SSD1306_PHASE_10,
    SSD1306_PHASE_11,
    SSD1306_PHASE_12,
    SSD1306_PHASE_13,
    SSD1306_PHASE_14,
    SSD1306_PHASE_15,
} SSD1306_Phase_t;

int8_t SSD1306_SetConstrast(uint8_t constrast);
int8_t SSD1306_EntireDispOnSoft(void);
int8_t SSD1306_EntireDispOnHard(void);
int8_t SSD1306_InverseDisp(SSD1306_Inverse_t state);
int8_t SSD1306_DispOnOff(SSD1306_DispState_t state);
int8_t SSD1306_SetupContHorizontalScroll(SSD1306_HorizontalScrollDirection_t direct, SSD1306_PageAddr_t start_page, SSD1306_ScrollStep_t step, SSD1306_PageAddr_t end_page);

/* Setup Continuous Vertical and Horizontal Scroll */
int8_t SSD1306_SetupContHorizontalVerticalScroll(SSD1306_HorizontalScrollDirection_t direct, SSD1306_PageAddr_t start_page, SSD1306_ScrollStep_t step, SSD1306_PageAddr_t end_page, SSD1306_Row_t offset);

int8_t SSD1306_DeactiveScroll(void);
int8_t SSD1306_ActiveScroll(void);
int8_t SSD1306_SetVerticalScrollArea(SSD1306_Row_t n_fixed_row, SSD1306_Row_t n_scroll_row);
int8_t SSD1306_SetLowerColStartAddr(SSD1306_Col_t addr);  /* ONLY use for Page Addressing Mode */
int8_t SSD1306_SetHigherColStartAddr(SSD1306_Col_t addr); /* ONLY use for Page Addressing Mode */
int8_t SSD1306_SetMemAddrMode(SSD1306_MemAddrMode_t mode);
int8_t SSD1306_SetColAddr(SSD1306_Col_t col_start, SSD1306_Col_t col_end);              /* ONLY use for Horizontal or Vertical Addressing Mode */
int8_t SSD1306_SetPageAddr(SSD1306_PageAddr_t start_page, SSD1306_PageAddr_t end_page); /* ONLY use for Horizontal or Vertical Addressing Mode */
int8_t SSD1306_SetPageStartAddr(SSD1306_PageAddr_t start_page);                         /* ONLY use for Page Addressing Mode */
int8_t SSD1306_SetDispStartLine(SSD1306_Row_t start_line);                              /* Documentation is UNCLEAR; 5-bit or 6-bit ??? */
int8_t SSD1306_SetSegRemap(SSD1306_SegmentRemapDirection_t direction);
int8_t SSD1306_SetMultiplexRatio(SSD1306_MUXRatio_t ratio);
int8_t SSD1306_SetCOMOutPutScanDirection(SSD1306_COMOutputScanDirection_t state); /* COM Output Scan Direction */
int8_t SSD1306_SetDispOffet(SSD1306_Row_t offset);
int8_t SSD1306_SetHardwareCfg(SSD1306_PinConfig_t cfg, SSD1306_COMRemap_t remap);
int8_t SSD1306_ClkCfg(SSD1306_ClkRatio_t ratio, SSD1306_ClkFrq_t frq); /* Set Display Clock Divide Ratio and Oscillator Freq */
int8_t SSD1306_SetPrechargePeriod(SSD1306_Phase_t phase1_period, SSD1306_Phase_t phase2_period);
int8_t SSD1306_SetVCOMHDeselectLevel(SSD1306_VCOMHDeselectLevel_t level);
int8_t SSD1306_SetChargeBumpSetting(SSD1306_ChargeBumpState_t state);

void SSD1306_Init(void);
void SSD1306_Reset(void);
void SSD1306_UpdateDisp(void);
void SSD1306_FillBuffer(SSD1306_PixelState_t state);
void SSD1306_DrawPixel(uint8_t x, uint8_t y, SSD1306_PixelState_t state);

/* Belong to bsp_ssd1306_cfg.h */

#define SSD1306_DC_PORT GPIOA
#define SSD1306_DC_PIN GPIO_PIN_8

/* RESET Pin is active LOW -> Keep this pin HIGH during normal operation */
#define SSD1306_RESET_PORT GPIOA
#define SSD1306_RESET_PIN GPIO_PIN_9

#define SSD1306_CS_PORT GPIOA
#define SSD1306_CS_PIN GPIO_PIN_10

#define SSD1306_SPI_HANDLER &hspi1


int8_t SSD1306_WriteCommand(uint8_t cmd);
int8_t SSD1306_WriteData(uint8_t *data, uint8_t size);
void SSD1306_Delay(uint32_t ms);
void SSD1306_CSPinOff(void);
void SSD1306_CSPinOn(void);
void SSD1306_DCPinOff(void);
void SSD1306_DCPinOn(void);
void SSD1306_ResetPinOff(void);
void SSD1306_ResetPinOn(void);

/* End of bsp_ssd1306_cfg.h */
#ifdef __cplusplus
}
#endif /* End of CPP guard */

#endif /* _BSP_BMP280_H_ */
