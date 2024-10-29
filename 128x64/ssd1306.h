/**
 ******************************************************************************
 * @file           : ssd1306.h
 * @brief          : SSD1306 OLED Display Driver Header
 *
 * This file provides function prototypes, data structures, and macros
 * for controlling an SSD1306 OLED display over I2C. It supports basic
 * operations such as initializing the display, drawing pixels, and rendering
 * characters from custom font data.
 *
 ******************************************************************************
 * @attention
 *
 * This library is tailored for STM32 microcontrollers and is intended for use
 * with the HAL library. It supports custom fonts sourced from the afiskon
 * STM32 SSD1306 library on GitHub (https://github.com/afiskon/stm32-ssd1306),
 * under the MIT License.
 *
 ******************************************************************************
 * @authors
 *
 * - Leroy Musa        (219198761)
 * - Mame Mor Mbacke   (218666206)
 * - Justin Chiu       (219589076)
 * - Nicole Xiong      (219574334)
 * - Connor Chan       (218993089)
 *
 ******************************************************************************
 * @repository
 *
 * https://github.com/pulsefex/ssd1306
 *
 ******************************************************************************
 */

#ifndef __SSD1306_H__
#define __SSD1306_H__

#if defined(STM32WB) //we use the NUCLEO-WB55RG board
#include "stm32wbxx_hal.h"
#include "stm32wbxx_hal_i2c.h"
#else
#endif

#ifndef SSD1306_I2C_ADDR
#define SSD1306_I2C_ADDR        (0x3C << 1)     //Either “0111100” or “0111101” can be selected as the slave address of SSD1306. sec. 8.1.5 pg 19
                                                //Shifted for 7-bit addr
#endif

#ifndef SSD1306_I2C_PORT
#define SSD1306_I2C_PORT        hi2c1
#endif


/***********************************************COMMANDS***************************************************/
/******************************************************************************************************** */

//Command tables are from pg 28-32

/***********Fundamental Command Table***********/
#define SET_CONTRAST_CONTROL    0x81
#define ENTIRE_DISPLAY_ON       0xA5
#define SET_NORMAL_DISPLAY      0xA6
#define SET_INVERSE_DISPLAY     0xA7
#define SET_DISPLAY_ON          0xAF
#define SET_DISPLAY_OFF         0xAE

/***********Scrolling Command Table*************/
#define SET_RIGHT_HORZONTAL_SCROLL               0x26
#define SET_LEFT_HORZONTAL_SCROLL                0x27
#define SET_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29
#define SET_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL  0x2A
#define DEACTIVATE_SCROLL                        0x2E
#define ACTIVATE_SCROLL                          0x2F
#define SET_VERTICAL_SCROLL_AREA                 0xA3

/**********Addressing Setting Command Table**********/
#define SET_LOW_COLUMN       0x00
#define SET_HIGH_COLUMN      0x10
#define SET_MEMORY_MODE      0x20
#define SET_COLUMN_ADDR      0x21
#define SET_PAGE_ADDR        0x22

/********Hardware Configuration (Panel resolution & layout related) Command Table**********/
#define SET_START_LINE            0x40
#define SET_SEGMENT_REMAP         0xA1
#define SET_MUX_RATIO             0xA8
#define SET_COM_SCAN_DIR_INC      0xC0
#define SET_COM_SCAN_DIR_DEC      0xC8
#define SET_DISPLAY_OFFSET        0xD3
#define SET_COM_PINS              0xDA

/************Timing & Driving Scheme Setting Command Table************/
#define SET_DISPLAY_CLOCK_DIVIDE_RATIO    0xD5
#define OSCILLATOR_FREQUENCY              0xD5
#define SET_PRE_CHARGE_PERIOD             0XD9
#define SET_VCOMH_DESELECT_LEVEL          0xDB
#define NOP                               0xE3



// <Buffer> //
#ifndef SSD1306_HEIGHT
#define SSD1306_HEIGHT          64
#endif

#ifndef SSD1306_WIDTH
#define SSD1306_WIDTH           128
#endif

#ifndef SSD1306_BUFFER_SIZE
#define SSD1306_BUFFER_SIZE   SSD1306_WIDTH * SSD1306_HEIGHT / 8
#endif


/** Font */
typedef struct {
	const uint8_t width;                /**< Font width in pixels */
	const uint8_t height;               /**< Font height in pixels */
	const uint16_t *const data;         /**< Pointer to font data array */
    const uint8_t *const char_width;    /**< Proportional character width in pixels (NULL for monospaced) */
} SSD1306_Font_t;


typedef enum {
    Black = 0x00,
    White = 0x01
} DisplayColor;


typedef enum {
    OK = 0x00,
    ERROR = 0x01
} DisplayStatus;


typedef struct {
    uint16_t CursorXPos;
    uint16_t CursorYPos;
    uint8_t IsInitialized;
    uint8_t IsPoweredOn;
} DisplayControl_t;


typedef struct {
    uint8_t PosX;
    uint8_t PosY;
} VertexPosition_t;




/****************************************Function Prototypes*******************************************/
void ssd1306_Init(void);
void ssd1306_SetContrast(uint8_t value);
void ssd1306_SetDisplayOn(uint8_t on);
uint8_t ssd1306_GetDisplayOn(void);
void ssd1306_Fill(DisplayControl_t color);
void ssd1306_UpdateScreen(void);
void ssd1306_DrawPixel(uint8_t x, uint8_t y, DisplayControl_t color);
void ssd1306_DrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1)
char ssd1306_WriteChar(char ch,SSD1306_Font_t Font, DisplayColor color);
char ssd1306_WriteString(char* str, SSD1306_Font_t Font, DisplayColor color);
void ssd1306_SetCursor(uint8_t x, uint8_t y);
void ssd1306_WriteCommand(uint8_t cmd);
void ssd1306_WriteData(uint8_t* data, size_t size);
/****************************************Function Prototypes*******************************************/

#endif // __SSD1306_H__