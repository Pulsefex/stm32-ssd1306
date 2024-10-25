/**
 *
 * This SSD1306 Oled library was written by 
 * 
 * Leroy Musa (219198761)
 * Mame Mor Mbacke (218666206)
 * Justin Chiu (219589076)
 * Nicole Xiong (219574334)
 * Connor Chan (218993089)
 * 
 * https://github.com/pulsefex/ssd1306
 */

#ifndef __SSD1306_H__
#define __SSD1306_H__

#if defined(STM32WB) //we use the NUCLEO-WB55RG board
#include "stm32wbxx_hal.h"
#include "stm32wbxx_hal_i2c.h"
#else
#endif

#ifndef SSD1306_I2C_ADDR
#define SSD1306_I2C_ADDR        (0x3C << 1)     //Either “0111100” or “0111101”, 
                                                //can be selected as the slave address 
                                                //of SSD1306. sec. 8.1.5 pg 19
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

//TODO


/**********Addressing Setting Command Table**********/

//TODO

/********Hardware Configuration (Panel resolution & layout related) Command Table**********/

//TODO

/************Timing & Driving Scheme Setting Command Table************/

//TODO

#endif // __SSD1306_H__