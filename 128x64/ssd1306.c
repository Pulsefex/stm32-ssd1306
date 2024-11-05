/**
 ******************************************************************************
 * @file           : ssd1306.c
 * @brief          : SSD1306 OLED Display Driver Implementation
 *
 * This file implements functions for controlling an SSD1306 OLED display over
 * the I2C protocol. It includes initialization, basic drawing routines, 
 * and character rendering using custom font data.
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

#include "ssd1306.h"
#include <string.h>

#define STM32WB

static uint8_t SSD1306_Buffer[SSD1306_BUFFER_SIZE];
static DisplayControl_t SSD1306;

void ssd1306_WriteCommand(uint8_t cmd) {
    HAL_I2C_Mem_Write(&SSD1306_I2C_PORT, SSD1306_I2C_ADDR, 0x00, I2C_MEMADD_SIZE_8BIT, &cmd, 1, HAL_MAX_DELAY);
}
void ssd1306_WriteData(uint8_t* data, size_t size) {
    HAL_I2C_Mem_Write(&SSD1306_I2C_PORT, SSD1306_I2C_ADDR, 0x40, 1, data, size, HAL_MAX_DELAY);
}

void ssd1306_Init(void) {

    //<Boot up process!>//
    //<Order matters!>//

	if (HAL_I2C_IsDeviceReady(&SSD1306_I2C_PORT, SSD1306_I2C_ADDR, 5, 1000) != HAL_OK)
	{
		SSD1306.IsInitialized = 0;
		return 0;
	}

    HAL_Delay(100);

    //init sequence from https://cdn-shop.adafruit.com/datasheets/SSD1306.pdf, modified according to convention
    ssd1306_WriteCommand(SET_DISPLAY_OFF);
    ssd1306_WriteCommand(SET_MUX_RATIO);
    ssd1306_WriteCommand(0x3F);
    ssd1306_WriteCommand(SET_DISPLAY_OFFSET);
    ssd1306_WriteCommand(0x00);
    ssd1306_WriteCommand(SET_START_LINE);
    ssd1306_WriteCommand(SET_SEGMENT_REMAP);
    ssd1306_WriteCommand(SET_COM_SCAN_DIR_DEC);
    ssd1306_WriteCommand(SET_COM_PINS);
    ssd1306_WriteCommand(0x02); //gpt says this should be 0x12
    ssd1306_WriteCommand(SET_CONTRAST_CONTROL);
    ssd1306_WriteCommand(0xFF);
    ssd1306_WriteCommand(SET_NORMAL_DISPLAY);
    ssd1306_WriteCommand(SET_DISPLAY_CLOCK_DIVIDE_RATIO);
    ssd1306_WriteCommand(OSCILLATOR_FREQUENCY);
    ssd1306_WriteCommand(SET_PRE_CHARGE_PERIOD);
    ssd1306_WriteCommand(0xF1);
    ssd1306_WriteCommand(0x8D); //some shit about charge pumps? idk
    ssd1306_WriteCommand(0x14);
    ssd1306_WriteCommand(SET_VCOMH_DESELECT_LEVEL);
    ssd1306_WriteCommand(0x40);
    ssd1306_WriteCommand(ENTIRE_DISPLAY_ON);
    ssd1306_WriteCommand(SET_DISPLAY_ON);

    SSD1306.CursorXPos = 0;
	SSD1306.CursorYPos = 0;
	ssd1306_Clear();

	// Flush buffer to screen
	ssd1306_UpdateScreen();

	SSD1306.isInitialized = 1;
	return 1;

}
