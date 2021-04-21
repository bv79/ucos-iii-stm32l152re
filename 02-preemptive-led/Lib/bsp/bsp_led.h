#ifndef __BSP_LED_H
#define __BSP_LED_H

#ifdef __cplusplus
extern "C"
{
#endif

#define BSP_LED_GREEN_PIN DEF_BIT_10
#define BSP_LED_GREEN_PORT GPIOA
#define BSP_LED_RED_PIN DEF_BIT_05
#define BSP_LED_RED_PORT GPIOB

#define BSP_LED_GREEN_On()      \
    HAL_GPIO_WritePin(BSP_LED_GREEN_PORT, BSP_LED_GREEN_PIN, GPIO_PIN_RESET);
#define BSP_LED_GREEN_Off()     \
    HAL_GPIO_WritePin(BSP_LED_GREEN_PORT, BSP_LED_GREEN_PIN, GPIO_PIN_SET);
#define BSP_LED_GREEN_Toggle()  \
    HAL_GPIO_TogglePin(BSP_LED_GREEN_PORT, BSP_LED_GREEN_PIN);
#define BSP_LED_RED_On()        \
    HAL_GPIO_WritePin(BSP_LED_RED_PORT, BSP_LED_RED_PIN, GPIO_PIN_RESET);
#define BSP_LED_RED_Off()       \
    HAL_GPIO_WritePin(BSP_LED_RED_PORT, BSP_LED_RED_PIN, GPIO_PIN_SET);
#define BSP_LED_RED_Toggle()    \
    HAL_GPIO_TogglePin(BSP_LED_RED_PORT, BSP_LED_RED_PIN);

    void BSP_LED_Init(void);

#ifdef __cplusplus
}
#endif

#endif