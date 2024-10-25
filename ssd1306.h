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
#else
#endif

#ifndef SSD1306_I2C_ADDR
#define SSD1306_I2C_ADDR        (0x3C << 1) //Either “0111100” or “0111101”, 
                                            //can be selected as the slave address 
                                            //of SSD1306. sec. 8.1.5 pg 19
                                            //Shifted for 7-bit addr
#endif

#ifndef SSD1306_I2C_PORT
#define SSD1306_I2C_PORT        hi2c1
#endif


#endif // __SSD1306_H__