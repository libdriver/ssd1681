/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      driver_ssd1681.h
 * @brief     driver ssd1681 header file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2022-08-30
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2022/08/30  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#ifndef DRIVER_SSD1681_H
#define DRIVER_SSD1681_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup ssd1681_driver ssd1681 driver function
 * @brief    ssd1681 driver modules
 * @{
 */

/**
 * @addtogroup ssd1681_base_driver
 * @{
 */

/**
 * @brief ssd1681 busy max delay definition
 */
#ifndef SSD1681_BUSY_MAX_DELAY_MS
    #define SSD1681_BUSY_MAX_DELAY_MS        10        /**< 10ms */
#endif

/**
 * @brief ssd1681 busy max retry times definition
 */
#ifndef SSD1681_BUSY_MAX_RETRY_TIMES
    #define SSD1681_BUSY_MAX_RETRY_TIMES     2000      /**< 2000 times */
#endif

/**
 * @brief ssd1681 bool enumeration definition
 */
typedef enum
{
    SSD1681_BOOL_FALSE = 0x00,        /**< false */
    SSD1681_BOOL_TRUE  = 0x01,        /**< true */
} ssd1681_bool_t;

/**
 * @brief ssd1681 gate driving voltage enumeration definition
 */
typedef enum  
{
    SSD1681_GATE_DRIVING_VOLTAGE_10V   = 0x03,        /**< 10V */
    SSD1681_GATE_DRIVING_VOLTAGE_10P5V = 0x04,        /**< 10.5V */
    SSD1681_GATE_DRIVING_VOLTAGE_11V   = 0x05,        /**< 11V */
    SSD1681_GATE_DRIVING_VOLTAGE_11P5V = 0x06,        /**< 11.5V */
    SSD1681_GATE_DRIVING_VOLTAGE_12V   = 0x07,        /**< 12V */
    SSD1681_GATE_DRIVING_VOLTAGE_12P5V = 0x08,        /**< 12.5V */
    SSD1681_GATE_DRIVING_VOLTAGE_13V   = 0x09,        /**< 13V */
    SSD1681_GATE_DRIVING_VOLTAGE_13P5V = 0x0A,        /**< 13.5V */
    SSD1681_GATE_DRIVING_VOLTAGE_14V   = 0x0B,        /**< 14V */
    SSD1681_GATE_DRIVING_VOLTAGE_14P5V = 0x0C,        /**< 14.5V */
    SSD1681_GATE_DRIVING_VOLTAGE_15V   = 0x0D,        /**< 15V */
    SSD1681_GATE_DRIVING_VOLTAGE_15P5V = 0x0E,        /**< 15.5V */
    SSD1681_GATE_DRIVING_VOLTAGE_16V   = 0x0F,        /**< 16V */
    SSD1681_GATE_DRIVING_VOLTAGE_16P5V = 0x10,        /**< 16.5V */
    SSD1681_GATE_DRIVING_VOLTAGE_17V   = 0x11,        /**< 17V */
    SSD1681_GATE_DRIVING_VOLTAGE_17P5V = 0x12,        /**< 17.5V */
    SSD1681_GATE_DRIVING_VOLTAGE_18V   = 0x13,        /**< 18V */
    SSD1681_GATE_DRIVING_VOLTAGE_18P5V = 0x14,        /**< 18.5V */
    SSD1681_GATE_DRIVING_VOLTAGE_19V   = 0x15,        /**< 19V */
    SSD1681_GATE_DRIVING_VOLTAGE_19P5V = 0x16,        /**< 19.5V */
    SSD1681_GATE_DRIVING_VOLTAGE_20V   = 0x17,        /**< 20V */
} ssd1681_gate_driving_voltage_t;

/**
 * @brief ssd1681 vsh enumeration definition
 */
typedef enum  
{
    SSD1681_VSH_2P4V  = 0x8E,        /**< 2.4V */
    SSD1681_VSH_2P5V  = 0x8F,        /**< 2.5V */
    SSD1681_VSH_2P6V  = 0x90,        /**< 2.6V */
    SSD1681_VSH_2P7V  = 0x91,        /**< 2.7V */
    SSD1681_VSH_2P8V  = 0x92,        /**< 2.8V */
    SSD1681_VSH_2P9V  = 0x93,        /**< 2.9V */
    SSD1681_VSH_3V    = 0x94,        /**< 3V */
    SSD1681_VSH_3P1V  = 0x95,        /**< 3.1V */
    SSD1681_VSH_3P2V  = 0x96,        /**< 3.2V */
    SSD1681_VSH_3P3V  = 0x97,        /**< 3.3V */
    SSD1681_VSH_3P4V  = 0x98,        /**< 3.4V */
    SSD1681_VSH_3P5V  = 0x99,        /**< 3.5V */
    SSD1681_VSH_3P6V  = 0x9A,        /**< 3.6V */
    SSD1681_VSH_3P7V  = 0x9B,        /**< 3.7V */
    SSD1681_VSH_3P8V  = 0x9C,        /**< 3.8V */
    SSD1681_VSH_3P9V  = 0x9D,        /**< 3.9V */
    SSD1681_VSH_4V    = 0x9E,        /**< 4V */
    SSD1681_VSH_4P1V  = 0x9F,        /**< 4.1V */
    SSD1681_VSH_4P2V  = 0xA0,        /**< 4.2V */
    SSD1681_VSH_4P3V  = 0xA1,        /**< 4.3V */
    SSD1681_VSH_4P4V  = 0xA2,        /**< 4.4V */
    SSD1681_VSH_4P5V  = 0xA3,        /**< 4.5V */
    SSD1681_VSH_4P6V  = 0xA4,        /**< 4.6V */
    SSD1681_VSH_4P7V  = 0xA5,        /**< 4.7V */
    SSD1681_VSH_4P8V  = 0xA6,        /**< 4.8V */
    SSD1681_VSH_4P9V  = 0xA7,        /**< 4.9V */
    SSD1681_VSH_5V    = 0xA8,        /**< 5V */
    SSD1681_VSH_5P1V  = 0xA9,        /**< 5.1V */
    SSD1681_VSH_5P2V  = 0xAA,        /**< 5.2V */
    SSD1681_VSH_5P3V  = 0xAB,        /**< 5.3V */
    SSD1681_VSH_5P4V  = 0xAC,        /**< 5.4V */
    SSD1681_VSH_5P5V  = 0xAD,        /**< 5.5V */
    SSD1681_VSH_5P6V  = 0xAE,        /**< 5.6V */
    SSD1681_VSH_5P7V  = 0xAF,        /**< 5.7V */
    SSD1681_VSH_5P8V  = 0xB0,        /**< 5.8V */
    SSD1681_VSH_5P9V  = 0xB1,        /**< 5.9V */
    SSD1681_VSH_6V    = 0xB2,        /**< 6V */
    SSD1681_VSH_6P1V  = 0xB3,        /**< 6.1V */
    SSD1681_VSH_6P2V  = 0xB4,        /**< 6.2V */
    SSD1681_VSH_6P3V  = 0xB5,        /**< 6.3V */
    SSD1681_VSH_6P4V  = 0xB6,        /**< 6.4V */
    SSD1681_VSH_6P5V  = 0xB7,        /**< 6.5V */
    SSD1681_VSH_6P6V  = 0xB8,        /**< 6.6V */
    SSD1681_VSH_6P7V  = 0xB9,        /**< 6.7V */
    SSD1681_VSH_6P8V  = 0xBA,        /**< 6.8V */
    SSD1681_VSH_6P9V  = 0xBB,        /**< 6.9V */
    SSD1681_VSH_7V    = 0xBC,        /**< 7V */
    SSD1681_VSH_7P1V  = 0xBD,        /**< 7.1V */
    SSD1681_VSH_7P2V  = 0xBE,        /**< 7.2V */
    SSD1681_VSH_7P3V  = 0xBF,        /**< 7.3V */
    SSD1681_VSH_7P4V  = 0xC0,        /**< 7.4V */
    SSD1681_VSH_7P5V  = 0xC1,        /**< 7.5V */
    SSD1681_VSH_7P6V  = 0xC2,        /**< 7.6V */
    SSD1681_VSH_7P7V  = 0xC3,        /**< 7.7V */
    SSD1681_VSH_7P8V  = 0xC4,        /**< 7.8V */
    SSD1681_VSH_7P9V  = 0xC5,        /**< 7.9V */
    SSD1681_VSH_8V    = 0xC6,        /**< 8V */
    SSD1681_VSH_8P1V  = 0xC7,        /**< 8.1V */
    SSD1681_VSH_8P2V  = 0xC8,        /**< 8.2V */
    SSD1681_VSH_8P3V  = 0xC9,        /**< 8.3V */
    SSD1681_VSH_8P4V  = 0xCA,        /**< 8.4V */
    SSD1681_VSH_8P5V  = 0xCB,        /**< 8.5V */
    SSD1681_VSH_8P6V  = 0xCC,        /**< 8.6V */
    SSD1681_VSH_8P7V  = 0xCD,        /**< 8.7V */
    SSD1681_VSH_8P8V  = 0xCE,        /**< 8.8V */
    SSD1681_VSH_9V    = 0x23,        /**< 9V */
    SSD1681_VSH_9P2V  = 0x24,        /**< 9.2V */
    SSD1681_VSH_9P4V  = 0x25,        /**< 9.4V */
    SSD1681_VSH_9P6V  = 0x26,        /**< 9.6V */
    SSD1681_VSH_9P8V  = 0x27,        /**< 9.8V */
    SSD1681_VSH_10V   = 0x28,        /**< 10V */
    SSD1681_VSH_10P2V = 0x29,        /**< 10.2V */
    SSD1681_VSH_10P4V = 0x2A,        /**< 10.4V */
    SSD1681_VSH_10P6V = 0x2B,        /**< 10.6V */
    SSD1681_VSH_10P8V = 0x2C,        /**< 10.8V */
    SSD1681_VSH_11V   = 0x2D,        /**< 11V */
    SSD1681_VSH_11P2V = 0x2E,        /**< 11.2V */
    SSD1681_VSH_11P4V = 0x2F,        /**< 11.4V */
    SSD1681_VSH_11P6V = 0x30,        /**< 11.6V */
    SSD1681_VSH_11P8V = 0x31,        /**< 11.8V */
    SSD1681_VSH_12V   = 0x32,        /**< 12V */
    SSD1681_VSH_12P2V = 0x33,        /**< 12.2V */
    SSD1681_VSH_12P4V = 0x34,        /**< 12.4V */
    SSD1681_VSH_12P6V = 0x35,        /**< 12.6V */
    SSD1681_VSH_12P8V = 0x36,        /**< 12.8V */
    SSD1681_VSH_13V   = 0x37,        /**< 13V */
    SSD1681_VSH_13P2V = 0x38,        /**< 13.2V */
    SSD1681_VSH_13P4V = 0x39,        /**< 13.4V */
    SSD1681_VSH_13P6V = 0x3A,        /**< 13.6V */
    SSD1681_VSH_13P8V = 0x3B,        /**< 13.8V */
    SSD1681_VSH_14V   = 0x3C,        /**< 14V */
    SSD1681_VSH_14P2V = 0x3D,        /**< 14.2V */
    SSD1681_VSH_14P4V = 0x3E,        /**< 14.4V */
    SSD1681_VSH_14P6V = 0x3F,        /**< 14.6V */
    SSD1681_VSH_14P8V = 0x40,        /**< 14.8V */
    SSD1681_VSH_15V   = 0x41,        /**< 15V */
    SSD1681_VSH_15P2V = 0x42,        /**< 15.2V */
    SSD1681_VSH_15P4V = 0x43,        /**< 15.4V */
    SSD1681_VSH_15P6V = 0x44,        /**< 15.6V */
    SSD1681_VSH_15P8V = 0x45,        /**< 15.8V */
    SSD1681_VSH_16V   = 0x46,        /**< 16V */
    SSD1681_VSH_16P2V = 0x47,        /**< 16.2V */
    SSD1681_VSH_16P4V = 0x48,        /**< 16.4V */
    SSD1681_VSH_16P6V = 0x49,        /**< 16.6V */
    SSD1681_VSH_16P8V = 0x4A,        /**< 16.8V */
    SSD1681_VSH_17V   = 0x4B,        /**< 17V */
} ssd1681_vsh_t;

/**
 * @brief ssd1681 vsl enumeration definition
 */
typedef enum  
{
    SSD1681_VSL_NEGATIVE_5    = 0x0A,        /**< -5 */
    SSD1681_VSL_NEGATIVE_5P5  = 0x0C,        /**< -5.5 */
    SSD1681_VSL_NEGATIVE_6    = 0x0E,        /**< -6 */
    SSD1681_VSL_NEGATIVE_6P5  = 0x10,        /**< -6.5 */
    SSD1681_VSL_NEGATIVE_7    = 0x12,        /**< -7 */
    SSD1681_VSL_NEGATIVE_7P5  = 0x14,        /**< -7.5 */
    SSD1681_VSL_NEGATIVE_8    = 0x16,        /**< -8 */
    SSD1681_VSL_NEGATIVE_8P5  = 0x18,        /**< -8.5 */
    SSD1681_VSL_NEGATIVE_9    = 0x1A,        /**< -9 */
    SSD1681_VSL_NEGATIVE_9P5  = 0x1C,        /**< -9.5 */
    SSD1681_VSL_NEGATIVE_10   = 0x1E,        /**< -10 */
    SSD1681_VSL_NEGATIVE_10P5 = 0x20,        /**< -10.5 */
    SSD1681_VSL_NEGATIVE_11   = 0x22,        /**< -11 */
    SSD1681_VSL_NEGATIVE_11P5 = 0x24,        /**< -11.5 */
    SSD1681_VSL_NEGATIVE_12   = 0x26,        /**< -12 */
    SSD1681_VSL_NEGATIVE_12P5 = 0x28,        /**< -12.5 */
    SSD1681_VSL_NEGATIVE_13   = 0x2A,        /**< -13 */
    SSD1681_VSL_NEGATIVE_13P5 = 0x2C,        /**< -13.5 */
    SSD1681_VSL_NEGATIVE_14   = 0x2E,        /**< -14 */
    SSD1681_VSL_NEGATIVE_14P5 = 0x30,        /**< -14.5 */
    SSD1681_VSL_NEGATIVE_15   = 0x32,        /**< -15 */
    SSD1681_VSL_NEGATIVE_15P5 = 0x34,        /**< -15.5 */
    SSD1681_VSL_NEGATIVE_16   = 0x36,        /**< -16 */
    SSD1681_VSL_NEGATIVE_16P5 = 0x38,        /**< -16.5 */
    SSD1681_VSL_NEGATIVE_17   = 0x3A,        /**< -17 */
} ssd1681_vsl_t;

/**
 * @brief ssd1681 driving strength enumeration definition
 */
typedef enum  
{
    SSD1681_DRIVING_STRENGTH_1 = (0 << 4),        /**< strength 1 */
    SSD1681_DRIVING_STRENGTH_2 = (1 << 4),        /**< strength 2 */
    SSD1681_DRIVING_STRENGTH_3 = (2 << 4),        /**< strength 3 */
    SSD1681_DRIVING_STRENGTH_4 = (3 << 4),        /**< strength 4 */
    SSD1681_DRIVING_STRENGTH_5 = (4 << 4),        /**< strength 5 */
    SSD1681_DRIVING_STRENGTH_6 = (5 << 4),        /**< strength 6 */
    SSD1681_DRIVING_STRENGTH_7 = (6 << 4),        /**< strength 7 */
    SSD1681_DRIVING_STRENGTH_8 = (7 << 4),        /**< strength 8 */
} ssd1681_driving_strength_t;

/**
 * @brief ssd1681 min off time enumeration definition
 */
typedef enum  
{
    SSD1681_MIN_OFF_TIME_2P6  = (4 << 0),         /**< 2.6 time unit */
    SSD1681_MIN_OFF_TIME_3P2  = (5 << 0),         /**< 3.2 time unit */
    SSD1681_MIN_OFF_TIME_3P9  = (6 << 0),         /**< 3.9 time unit */
    SSD1681_MIN_OFF_TIME_4P6  = (7 << 0),         /**< 4.6 time unit */
    SSD1681_MIN_OFF_TIME_5P4  = (8 << 0),         /**< 5.4 time unit */
    SSD1681_MIN_OFF_TIME_6P3  = (9 << 0),         /**< 6.3 time unit */
    SSD1681_MIN_OFF_TIME_7P3  = (10 << 0),        /**< 7.3 time unit */
    SSD1681_MIN_OFF_TIME_8P4  = (11 << 0),        /**< 8.4 time unit */
    SSD1681_MIN_OFF_TIME_9P8  = (12 << 0),        /**< 9.8 time unit */
    SSD1681_MIN_OFF_TIME_11P5 = (13 << 0),        /**< 11.5 time unit */
    SSD1681_MIN_OFF_TIME_13P8 = (14 << 0),        /**< 13.8 time unit */
    SSD1681_MIN_OFF_TIME_16P5 = (15 << 0),        /**< 16.5 time unit */
} ssd1681_min_off_time_t;

/**
 * @brief ssd1681 phase duration enumeration definition
 */
typedef enum  
{
    SSD1681_PHASE_DURATION_10MS = 0x00,        /**< 10ms */
    SSD1681_PHASE_DURATION_20MS = 0x01,        /**< 20ms */
    SSD1681_PHASE_DURATION_30MS = 0x02,        /**< 30ms */
    SSD1681_PHASE_DURATION_40MS = 0x03,        /**< 40ms */
} ssd1681_phase_duration_t;

/**
 * @brief ssd1681 mode enumeration definition
 */
typedef enum  
{
    SSD1681_MODE_NORMAL       = 0x00,        /**< normal mode */
    SSD1681_MODE_DEEP_SLEEP_1 = 0x01,        /**< enter deep sleep mode 1 */
    SSD1681_MODE_DEEP_SLEEP_2 = 0x03,        /**< enter deep sleep mode 2 */
} ssd1681_mode_t;

/**
 * @brief ssd1681 address mode enumeration definition
 */
typedef enum  
{
    SSD1681_ADDRESS_MODE_Y_DECREMENT_X_DECREMENT = 0x00,        /**< y decrement, x decrement */
    SSD1681_ADDRESS_MODE_Y_DECREMENT_X_INCREMENT = 0x01,        /**< y decrement, x increment */
    SSD1681_ADDRESS_MODE_Y_INCREMENT_X_DECREMENT = 0x02,        /**< y increment, x decrement */
    SSD1681_ADDRESS_MODE_Y_INCREMENT_X_INCREMENT = 0x03,        /**< y increment, x increment */
} ssd1681_address_mode_t;

/**
 * @brief ssd1681 address direction enumeration definition
 */
typedef enum  
{
    SSD1681_ADDRESS_DIRECTION_UPDATED_X = 0x00,        /**< the address counter is updated in the x direction */
    SSD1681_ADDRESS_DIRECTION_UPDATED_Y = 0x01,        /**< the address counter is updated in the y direction */
} ssd1681_address_direction_t;

/**
 * @brief ssd1681 vci level enumeration definition
 */
typedef enum  
{
    SSD1681_VCI_LEVEL_2P2V = 0x3,        /**< 2.2V */
    SSD1681_VCI_LEVEL_2P3V = 0x4,        /**< 2.3V */
    SSD1681_VCI_LEVEL_2P4V = 0x5,        /**< 2.4V */
    SSD1681_VCI_LEVEL_2P5V = 0x6,        /**< 2.5V */
    SSD1681_VCI_LEVEL_2P6V = 0x7,        /**< 2.6V */
} ssd1681_vci_level_t;

/**
 * @brief ssd1681 temperature sensor enumeration definition
 */
typedef enum  
{
    SSD1681_TEMPERATURE_SENSOR_EXTERNAL = 0x48,        /**< external temperature sensor */
    SSD1681_TEMPERATURE_SENSOR_INTERNAL = 0x80,        /**< internal temperature sensor */
} ssd1681_temperature_sensor_t;

/**
 * @brief ssd1681 display control enumeration definition
 */
typedef enum  
{
    SSD1681_DISPLAY_CONTROL_NORMAL  = 0x00,        /**< normal */
    SSD1681_DISPLAY_CONTROL_BYPASS  = 0x04,        /**< bypass ram content as 0 */
    SSD1681_DISPLAY_CONTROL_INVERSE = 0x08,        /**< inverse ram content */
} ssd1681_display_control_t;

/**
 * @brief ssd1681 display sequence enumeration definition
 */
typedef enum  
{
    SSD1681_DISPLAY_SEQUENCE_0  = 0x80,        /**< enable clock signal */
    SSD1681_DISPLAY_SEQUENCE_1  = 0x01,        /**< disable clock signal */
    SSD1681_DISPLAY_SEQUENCE_2  = 0xC0,        /**< enable clock signal, enable analog */
    SSD1681_DISPLAY_SEQUENCE_3  = 0x03,        /**< disable analog, disable clock signal */
    SSD1681_DISPLAY_SEQUENCE_4  = 0x91,        /**< enable clock signal, load lut with display mode 1, disable clock signal */
    SSD1681_DISPLAY_SEQUENCE_5  = 0x99,        /**< enable clock signal, load lut with display mode 2, disable clock signal */
    SSD1681_DISPLAY_SEQUENCE_6  = 0xB1,        /**< enable clock signal, load temperature value, load lut with display mode 1, disable clock signal */
    SSD1681_DISPLAY_SEQUENCE_7  = 0xB9,        /**< enable clock signal, load temperature value, load lut with display mode 2, disable clock signal */
    SSD1681_DISPLAY_SEQUENCE_8  = 0xC7,        /**< enable clock signal, enable analog, display with display mode 1, disable analog, disable osc */
    SSD1681_DISPLAY_SEQUENCE_9  = 0xCF,        /**< enable clock signal, enable analog, display with display mode 2, disable analog, disable osc */
    SSD1681_DISPLAY_SEQUENCE_10 = 0xF7,        /**< enable clock signal, enable analog, load temperature value, display with display mode 1, disable analog, disable osc */
    SSD1681_DISPLAY_SEQUENCE_11 = 0xFF,        /**< enable clock signal, enable analog, load temperature value, display with display mode 2, disable analog, disable osc */
} ssd1681_display_sequence_t;

/**
 * @brief ssd1681 vcom enumeration definition
 */
typedef enum  
{
    SSD1681_VCOM_NEGATIVE_0P2 = 0x08,        /**< -0.2 */
    SSD1681_VCOM_NEGATIVE_0P3 = 0x0C,        /**< -0.3 */
    SSD1681_VCOM_NEGATIVE_0P4 = 0x10,        /**< -0.4 */
    SSD1681_VCOM_NEGATIVE_0P5 = 0x14,        /**< -0.5 */
    SSD1681_VCOM_NEGATIVE_0P6 = 0x18,        /**< -0.6 */
    SSD1681_VCOM_NEGATIVE_0P7 = 0x1C,        /**< -0.7 */
    SSD1681_VCOM_NEGATIVE_0P8 = 0x20,        /**< -0.8 */
    SSD1681_VCOM_NEGATIVE_0P9 = 0x24,        /**< -0.9 */
    SSD1681_VCOM_NEGATIVE_1P0 = 0x28,        /**< -1.0 */
    SSD1681_VCOM_NEGATIVE_1P1 = 0x2C,        /**< -1.1 */
    SSD1681_VCOM_NEGATIVE_1P2 = 0x30,        /**< -1.2 */
    SSD1681_VCOM_NEGATIVE_1P3 = 0x34,        /**< -1.3 */
    SSD1681_VCOM_NEGATIVE_1P4 = 0x38,        /**< -1.4 */
    SSD1681_VCOM_NEGATIVE_1P5 = 0x3C,        /**< -1.5 */
    SSD1681_VCOM_NEGATIVE_1P6 = 0x40,        /**< -1.6 */
    SSD1681_VCOM_NEGATIVE_1P7 = 0x44,        /**< -1.7 */
    SSD1681_VCOM_NEGATIVE_1P8 = 0x48,        /**< -1.8 */
    SSD1681_VCOM_NEGATIVE_1P9 = 0x4C,        /**< -1.9 */
    SSD1681_VCOM_NEGATIVE_2P0 = 0x50,        /**< -2.0 */
    SSD1681_VCOM_NEGATIVE_2P1 = 0x54,        /**< -2.1 */
    SSD1681_VCOM_NEGATIVE_2P2 = 0x58,        /**< -2.2 */
    SSD1681_VCOM_NEGATIVE_2P3 = 0x5C,        /**< -2.3 */
    SSD1681_VCOM_NEGATIVE_2P4 = 0x60,        /**< -2.4 */
    SSD1681_VCOM_NEGATIVE_2P5 = 0x64,        /**< -2.5 */
    SSD1681_VCOM_NEGATIVE_2P6 = 0x68,        /**< -2.6 */
    SSD1681_VCOM_NEGATIVE_2P7 = 0x6C,        /**< -2.7 */
    SSD1681_VCOM_NEGATIVE_2P8 = 0x70,        /**< -2.8 */
    SSD1681_VCOM_NEGATIVE_2P9 = 0x74,        /**< -2.9 */
    SSD1681_VCOM_NEGATIVE_3P0 = 0x78,        /**< -3.0 */
} ssd1681_vcom_t;

/**
 * @brief ssd1681 otp mode enumeration definition
 */
typedef enum  
{
    SSD1681_OTP_MODE_NORMAL   = 0x0,        /**< normal mode */
    SSD1681_OTP_MODE_INTERNAL = 0x3,        /**< internal generated otp programming voltage */
} ssd1681_otp_mode_t;

/**
 * @brief ssd1681 vbd enumeration definition
 */
typedef enum  
{
    SSD1681_VBD_GS_TRANSITION = 0x0,        /**< gs transition */
    SSD1681_VBD_FIX_LEVEL     = 0x1,        /**< fix level, */
    SSD1681_VBD_VCOM          = 0x2,        /**< vcom */
    SSD1681_VBD_HIZ           = 0x3,        /**< hiz */
} ssd1681_vbd_t;

/**
 * @brief ssd1681 vbd fix level enumeration definition
 */
typedef enum  
{
    SSD1681_VBD_FIX_LEVEL_VSS  = 0x0,        /**< vss */
    SSD1681_VBD_FIX_LEVEL_VSH1 = 0x1,        /**< vsh1 */
    SSD1681_VBD_FIX_LEVEL_VSL  = 0x2,        /**< vsl */
    SSD1681_VBD_FIX_LEVEL_VSH2 = 0x3,        /**< vsh2 */
} ssd1681_vbd_fix_level_t;

/**
 * @brief ssd1681 gs transition enumeration definition
 */
typedef enum  
{
    SSD1681_GS_TRANSITION_FOLLOW_LUT_RED = 0x0,        /**< follow lut red */
    SSD1681_GS_TRANSITION_FOLLOW_LUT     = 0x1,        /**< follow lut */
} ssd1681_gs_transition_t;

/**
 * @brief ssd1681 vbd transition enumeration definition
 */
typedef enum  
{
    SSD1681_VBD_TRANSITION_LUT0 = 0x0,        /**< lut0 */
    SSD1681_VBD_TRANSITION_LUT1 = 0x1,        /**< lut1 */
    SSD1681_VBD_TRANSITION_LUT2 = 0x2,        /**< lut2 */
    SSD1681_VBD_TRANSITION_LUT3 = 0x3,        /**< lut3 */
} ssd1681_vbd_transition_t;

/**
 * @brief ssd1681 end opt enumeration definition
 */
typedef enum  
{
    SSD1681_END_OPT_NORMAL             = 0x22,        /**< normal */
    SSD1681_END_OPT_KEEP_BEFORE_OUTPUT = 0x07,        /**< source output level keep previous output before power off */
} ssd1681_end_opt_t;

/**
 * @brief ssd1681 read ram enumeration definition
 */
typedef enum  
{
    SSD1681_READ_RAM_BLACK = 0x0,        /**< black */
    SSD1681_READ_RAM_RED   = 0x1,        /**< red */
} ssd1681_read_ram_t;

/**
 * @brief ssd1681 step height enumeration definition
 */
typedef enum  
{
    SSD1681_STEP_HEIGHT_8   = 0x0,        /**< height 8 */
    SSD1681_STEP_HEIGHT_16  = 0x1,        /**< height 16 */
    SSD1681_STEP_HEIGHT_32  = 0x2,        /**< height 32 */
    SSD1681_STEP_HEIGHT_64  = 0x3,        /**< height 64 */
    SSD1681_STEP_HEIGHT_128 = 0x4,        /**< height 128 */
    SSD1681_STEP_HEIGHT_200 = 0x5,        /**< height 200 */
} ssd1681_step_height_t;

/**
 * @brief ssd1681 step width enumeration definition
 */
typedef enum  
{
    SSD1681_STEP_WIDTH_8   = 0x0,        /**< width 8 */
    SSD1681_STEP_WIDTH_16  = 0x1,        /**< width 16 */
    SSD1681_STEP_WIDTH_32  = 0x2,        /**< width 32 */
    SSD1681_STEP_WIDTH_64  = 0x3,        /**< width 64 */
    SSD1681_STEP_WIDTH_128 = 0x4,        /**< width 128 */
    SSD1681_STEP_WIDTH_200 = 0x5,        /**< width 200 */
} ssd1681_step_width_t;

/**
 * @brief ssd1681 color enumeration definition
 */
typedef enum  
{
    SSD1681_COLOR_BLACK = 0x0,        /**< black color */
    SSD1681_COLOR_RED   = 0x1,        /**< red color */
} ssd1681_color_t;

/**
 * @brief ssd1681 font enumeration definition
 */
typedef enum  
{
    SSD1681_FONT_12 = 0x0C,        /**< font 12 */
    SSD1681_FONT_16 = 0x10,        /**< font 16 */
    SSD1681_FONT_24 = 0x18,        /**< font 24 */
} ssd1681_font_t;

/**
 * @brief ssd1681 handle structure definition
 */
typedef struct ssd1681_handle_s
{
    uint8_t (*spi_init)(void);                                   /**< point to a spi_init function address */
    uint8_t (*spi_deinit)(void);                                 /**< point to a spi_deinit function address */
    uint8_t (*spi_write_cmd)(uint8_t *buf, uint16_t len);        /**< point to a spi_write_cmd function address */
    uint8_t (*spi_read_cmd)(uint8_t *buf, uint16_t len);         /**< point to a spi_read_cmd function address */
    uint8_t (*spi_cmd_data_gpio_init)(void);                     /**< point to a spi_cmd_data_gpio_init function address */
    uint8_t (*spi_cmd_data_gpio_deinit)(void);                   /**< point to a spi_cmd_data_gpio_deinit function address */
    uint8_t (*spi_cmd_data_gpio_write)(uint8_t value);           /**< point to a spi_cmd_data_gpio_write function address */
    uint8_t (*reset_gpio_init)(void);                            /**< point to a reset_gpio_init function address */
    uint8_t (*reset_gpio_deinit)(void);                          /**< point to a reset_gpio_deinit function address */
    uint8_t (*reset_gpio_write)(uint8_t value);                  /**< point to a reset_gpio_write function address */
    uint8_t (*busy_gpio_init)(void);                             /**< point to a busy_gpio_init function address */
    uint8_t (*busy_gpio_deinit)(void);                           /**< point to a busy_gpio_deinit function address */
    uint8_t (*busy_gpio_read)(uint8_t *value);                   /**< point to a busy_gpio_read function address */
    void (*debug_print)(const char *const fmt, ...);             /**< point to a debug_print function address */
    void (*delay_ms)(uint32_t ms);                               /**< point to a delay_ms function address */
    uint8_t inited;                                              /**< inited flag */
    uint8_t black_gram[200][25];                                 /**< black gram buffer */
    uint8_t red_gram[200][25];                                   /**< red gram buffer */
} ssd1681_handle_t;

/**
 * @brief ssd1681 information structure definition
 */
typedef struct ssd1681_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} ssd1681_info_t;

/**
 * @}
 */

/**
 * @defgroup ssd1681_link_driver ssd1681 link driver function
 * @brief    ssd1681 link driver modules
 * @ingroup  ssd1681_driver
 * @{
 */

/**
 * @brief     initialize ssd1681_handle_t structure
 * @param[in] HANDLE pointer to an ssd1681 handle structure
 * @param[in] STRUCTURE ssd1681_handle_t
 * @note      none
 */
#define DRIVER_SSD1681_LINK_INIT(HANDLE, STRUCTURE)                     memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link spi_init function
 * @param[in] HANDLE pointer to an ssd1681 handle structure
 * @param[in] FUC pointer to a spi_init function address
 * @note      none
 */
#define DRIVER_SSD1681_LINK_SPI_INIT(HANDLE, FUC)                      (HANDLE)->spi_init = FUC

/**
 * @brief     link spi_deinit function
 * @param[in] HANDLE pointer to an ssd1681 handle structure
 * @param[in] FUC pointer to a spi_deinit function address
 * @note      none
 */
#define DRIVER_SSD1681_LINK_SPI_DEINIT(HANDLE, FUC)                    (HANDLE)->spi_deinit = FUC

/**
 * @brief     link spi_write_cmd function
 * @param[in] HANDLE pointer to an ssd1681 handle structure
 * @param[in] FUC pointer to a spi_write_cmd function address
 * @note      none
 */
#define DRIVER_SSD1681_LINK_SPI_WRITE_CMD(HANDLE, FUC)                 (HANDLE)->spi_write_cmd = FUC

/**
 * @brief     link spi_read_cmd function
 * @param[in] HANDLE pointer to an ssd1681 handle structure
 * @param[in] FUC pointer to a spi_read_cmd function address
 * @note      none
 */
#define DRIVER_SSD1681_LINK_SPI_READ_CMD(HANDLE, FUC)                  (HANDLE)->spi_read_cmd = FUC

/**
 * @brief     link spi_cmd_data_gpio_init function
 * @param[in] HANDLE pointer to an ssd1681 handle structure
 * @param[in] FUC pointer to a spi_cmd_data_gpio_init function address
 * @note      none
 */
#define DRIVER_SSD1681_LINK_SPI_CMD_DATA_GPIO_INIT(HANDLE, FUC)        (HANDLE)->spi_cmd_data_gpio_init = FUC

/**
 * @brief     link spi_cmd_data_gpio_deinit function
 * @param[in] HANDLE pointer to an ssd1681 handle structure
 * @param[in] FUC pointer to a spi_cmd_data_gpio_deinit function address
 * @note      none
 */
#define DRIVER_SSD1681_LINK_SPI_CMD_DATA_GPIO_DEINIT(HANDLE, FUC)      (HANDLE)->spi_cmd_data_gpio_deinit = FUC

/**
 * @brief     link spi_cmd_data_gpio_write function
 * @param[in] HANDLE pointer to an ssd1681 handle structure
 * @param[in] FUC pointer to a spi_cmd_data_gpio_write function address
 * @note      none
 */
#define DRIVER_SSD1681_LINK_SPI_CMD_DATA_GPIO_WRITE(HANDLE, FUC)       (HANDLE)->spi_cmd_data_gpio_write = FUC

/**
 * @brief     link reset_gpio_init function
 * @param[in] HANDLE pointer to an ssd1681 handle structure
 * @param[in] FUC pointer to a reset_gpio_init function address
 * @note      none
 */
#define DRIVER_SSD1681_LINK_RESET_GPIO_INIT(HANDLE, FUC)               (HANDLE)->reset_gpio_init = FUC

/**
 * @brief     link reset_gpio_deinit function
 * @param[in] HANDLE pointer to an ssd1681 handle structure
 * @param[in] FUC pointer to a reset_gpio_deinit function address
 * @note      none
 */
#define DRIVER_SSD1681_LINK_RESET_GPIO_DEINIT(HANDLE, FUC)             (HANDLE)->reset_gpio_deinit = FUC

/**
 * @brief     link reset_gpio_write function
 * @param[in] HANDLE pointer to an ssd1681 handle structure
 * @param[in] FUC pointer to a reset_gpio_write function address
 * @note      none
 */
#define DRIVER_SSD1681_LINK_RESET_GPIO_WRITE(HANDLE, FUC)              (HANDLE)->reset_gpio_write = FUC

/**
 * @brief     link busy_gpio_init function
 * @param[in] HANDLE pointer to an ssd1681 handle structure
 * @param[in] FUC pointer to a busy_gpio_init function address
 * @note      none
 */
#define DRIVER_SSD1681_LINK_BUSY_GPIO_INIT(HANDLE, FUC)                (HANDLE)->busy_gpio_init = FUC

/**
 * @brief     link busy_gpio_deinit function
 * @param[in] HANDLE pointer to an ssd1681 handle structure
 * @param[in] FUC pointer to a busy_gpio_init function address
 * @note      none
 */
#define DRIVER_SSD1681_LINK_BUSY_GPIO_DEINIT(HANDLE, FUC)              (HANDLE)->busy_gpio_deinit = FUC

/**
 * @brief     link busy_gpio_read function
 * @param[in] HANDLE pointer to an ssd1681 handle structure
 * @param[in] FUC pointer to a busy_gpio_read function address
 * @note      none
 */
#define DRIVER_SSD1681_LINK_BUSY_GPIO_READ(HANDLE, FUC)                (HANDLE)->busy_gpio_read = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE pointer to an ssd1681 handle structure
 * @param[in] FUC pointer to a delay_ms function address
 * @note      none
 */
#define DRIVER_SSD1681_LINK_DELAY_MS(HANDLE, FUC)                      (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE pointer to an ssd1681 handle structure
 * @param[in] FUC pointer to a debug_print function address
 * @note      none
 */
#define DRIVER_SSD1681_LINK_DEBUG_PRINT(HANDLE, FUC)                   (HANDLE)->debug_print = FUC

/**
 * @}
 */

/**
 * @defgroup ssd1681_base_driver ssd1681 base driver function
 * @brief    ssd1681 base driver modules
 * @ingroup  ssd1681_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info pointer to an ssd1681 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t ssd1681_info(ssd1681_info_t *info);

/**
 * @brief     initialize the chip
 * @param[in] *handle pointer to an ssd1681 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 spi initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 *            - 4 reset failed
 *            - 5 gpio init failed
 * @note      none
 */
uint8_t ssd1681_init(ssd1681_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle pointer to an ssd1681 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 spi deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 power down failed
 *            - 5 reset gpio deinit failed
 *            - 6 command && data deinit failed
 *            - 7 busy gpio deinit failed
 * @note      none
 */
uint8_t ssd1681_deinit(ssd1681_handle_t *handle);

/**
 * @brief     clear the screen
 * @param[in] *handle pointer to an ssd1681 handle structure
 * @param[in] color color type
 * @return    status code
 *            - 0 success
 *            - 1 clear failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ssd1681_clear(ssd1681_handle_t *handle, ssd1681_color_t color);

/**
 * @brief     update the gram data
 * @param[in] *handle pointer to an ssd1681 handle structure
 * @param[in] color color type
 * @return    status code
 *            - 0 success
 *            - 1 gram update failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ssd1681_gram_update(ssd1681_handle_t *handle, ssd1681_color_t color);

/**
 * @brief     clear the screen in the gram
 * @param[in] *handle pointer to an ssd1681 handle structure
 * @param[in] color color type
 * @return    status code
 *            - 0 success
 *            - 1 clear failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ssd1681_gram_clear(ssd1681_handle_t *handle, ssd1681_color_t color);

/**
 * @brief     write a point in the gram
 * @param[in] *handle pointer to an ssd1681 handle structure
 * @param[in] color color type
 * @param[in] x coordinate x
 * @param[in] y coordinate y
 * @param[in] data written data
 * @return    status code
 *            - 0 success
 *            - 1 gram write point failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 x or y is invalid
 * @note      none
 */
uint8_t ssd1681_gram_write_point(ssd1681_handle_t *handle, ssd1681_color_t color, uint8_t x, uint8_t y, uint8_t data);

/**
 * @brief      read a point from the gram
 * @param[in]  *handle pointer to an ssd1681 handle structure
 * @param[in]  color color type
 * @param[in]  x coordinate x
 * @param[in]  y coordinate y
 * @param[out] *data pointer to a data buffer
 * @return     status code
 *             - 0 success
 *             - 1 gram read point failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 x or y is invalid
 * @note       none
 */
uint8_t ssd1681_gram_read_point(ssd1681_handle_t *handle, ssd1681_color_t color, uint8_t x, uint8_t y, uint8_t *data);

/**
 * @brief     draw a string in the gram
 * @param[in] *handle pointer to an ssd1681 handle structure
 * @param[in] color color type
 * @param[in] x coordinate x
 * @param[in] y coordinate y
 * @param[in] *str pointer to a write string address
 * @param[in] len length of the string
 * @param[in] data display color
 * @param[in] font display font size
 * @return    status code
 *            - 0 success
 *            - 1 gram write string failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 x or y is invalid
 * @note      none
 */
uint8_t ssd1681_gram_write_string(ssd1681_handle_t *handle, ssd1681_color_t color, uint8_t x, uint8_t y, char *str, uint16_t len, uint8_t data, ssd1681_font_t font);

/**
 * @brief     fill a rectangle in the gram
 * @param[in] *handle pointer to an ssd1681 handle structure
 * @param[in] color color type
 * @param[in] left left coordinate x
 * @param[in] top top coordinate y
 * @param[in] right right coordinate x
 * @param[in] bottom bottom coordinate y
 * @param[in] data display color
 * @return    status code
 *            - 0 success
 *            - 1 gram fill rect failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 left or top is invalid
 *            - 5 right or bottom is invalid
 *            - 6 left > right or top > bottom
 * @note      none
 */
uint8_t ssd1681_gram_fill_rect(ssd1681_handle_t *handle, ssd1681_color_t color, uint8_t left, uint8_t top, uint8_t right, uint8_t bottom, uint8_t data);

/**
 * @brief     draw a picture in the gram
 * @param[in] *handle pointer to an ssd1681 handle structure
 * @param[in] color color type
 * @param[in] left left coordinate x
 * @param[in] top top coordinate y
 * @param[in] right right coordinate x
 * @param[in] bottom bottom coordinate y
 * @param[in] *img pointer to an image buffer
 * @return    status code
 *            - 0 success
 *            - 1 gram draw picture failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 left or top is invalid
 *            - 5 right or bottom is invalid
 *            - 6 left > right or top > bottom
 * @note      none
 */
uint8_t ssd1681_gram_draw_picture(ssd1681_handle_t *handle, ssd1681_color_t color, uint8_t left, uint8_t top, uint8_t right, uint8_t bottom, uint8_t *img);

/**
 * @brief     set the driver output
 * @param[in] *handle pointer to an ssd1681 handle structure
 * @param[in] mux set mux
 * @param[in] gd bool value
 * @param[in] sm bool value
 * @param[in] tb bool value
 * @return    status code
 *            - 0 success
 *            - 1 set driver output failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 mux is invalid
 * @note      mux can't be over 0x1FF
 */
uint8_t ssd1681_set_driver_output(ssd1681_handle_t *handle, uint16_t mux, ssd1681_bool_t gd, ssd1681_bool_t sm, ssd1681_bool_t tb);

/**
 * @brief     set the gate driving voltage
 * @param[in] *handle pointer to an ssd1681 handle structure
 * @param[in] voltage gate driving voltage
 * @return    status code
 *            - 0 success
 *            - 1 set gate driving voltage failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ssd1681_set_gate_driving_voltage(ssd1681_handle_t *handle, ssd1681_gate_driving_voltage_t voltage);

/**
 * @brief     set the source driving voltage
 * @param[in] *handle pointer to an ssd1681 handle structure
 * @param[in] vsh1 set vsh1
 * @param[in] vsh2 set vsh2
 * @param[in] vsl set vsl
 * @return    status code
 *            - 0 success
 *            - 1 set source driving voltage failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      vsh1 >= vsh2
 */
uint8_t ssd1681_set_source_driving_voltage(ssd1681_handle_t *handle, ssd1681_vsh_t vsh1, ssd1681_vsh_t vsh2, ssd1681_vsl_t vsl);

/**
 * @brief     initial code setting otp program
 * @param[in] *handle pointer to an ssd1681 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 otp initial failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ssd1681_otp_initial(ssd1681_handle_t *handle);

/**
 * @brief     write register for initial code setting
 * @param[in] *handle pointer to an ssd1681 handle structure
 * @param[in] *param pointer to a param buffer
 * @return    status code
 *            - 0 success
 *            - 1 otp initial write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ssd1681_otp_initial_write(ssd1681_handle_t *handle, uint8_t param[4]);

/**
 * @brief     read register for initial code setting
 * @param[in] *handle pointer to an ssd1681 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 otp initial read failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ssd1681_otp_initial_read(ssd1681_handle_t *handle);

/**
 * @brief     program vcom otp
 * @param[in] *handle pointer to an ssd1681 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 otp program vcom failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ssd1681_otp_program_vcom(ssd1681_handle_t *handle);

/**
 * @brief      otp register read for display option
 * @param[in]  *handle pointer to an ssd1681 handle structure
 * @param[out] *param pointer to a param buffer
 * @return     status code
 *             - 0 success
 *             - 1 otp read register failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ssd1681_otp_read_register(ssd1681_handle_t *handle, uint8_t param[11]);

/**
 * @brief     program otp of waveform setting
 * @param[in] *handle pointer to an ssd1681 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 otp program waveform failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ssd1681_otp_program_waveform(ssd1681_handle_t *handle);

/**
 * @brief     load otp of waveform setting
 * @param[in] *handle pointer to an ssd1681 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 otp load waveform failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note       none
 */
uint8_t ssd1681_otp_load_waveform(ssd1681_handle_t *handle);

/**
 * @brief     program otp selection
 * @param[in] *handle pointer to an ssd1681 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 otp program selection failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ssd1681_otp_program_selection(ssd1681_handle_t *handle);

/**
 * @brief     otp write register for display option
 * @param[in] *handle pointer to an ssd1681 handle structure
 * @param[in] *param pointer to a param buffer
 * @return    status code
 *            - 0 success
 *            - 1 otp write register failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ssd1681_otp_write_register(ssd1681_handle_t *handle, uint8_t param[11]);

/**
 * @brief     set the otp program mode
 * @param[in] *handle pointer to an ssd1681 handle structure
 * @param[in] mode otp mode
 * @return    status code
 *            - 0 success
 *            - 1 otp program mode failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ssd1681_otp_program_mode(ssd1681_handle_t *handle, ssd1681_otp_mode_t mode);

/**
 * @brief     set the booster soft start
 * @param[in] *handle pointer to an ssd1681 handle structure
 * @param[in] phase1 phase 1
 * @param[in] phase2 phase 2
 * @param[in] phase3 phase 3
 * @param[in] duration phase duration
 * @return    status code
 *            - 0 success
 *            - 1 set booster soft start failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ssd1681_set_booster_soft_start(ssd1681_handle_t *handle, 
                                       uint8_t phase1, uint8_t phase2,
                                       uint8_t phase3, uint8_t duration);

/**
 * @brief     set the mode
 * @param[in] *handle pointer to an ssd1681 handle structure
 * @param[in] mode set mode
 * @return    status code
 *            - 0 success
 *            - 1 set mode failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ssd1681_set_mode(ssd1681_handle_t *handle, ssd1681_mode_t mode);

/**
 * @brief     set the data entry mode
 * @param[in] *handle pointer to an ssd1681 handle structure
 * @param[in] mode address mode
 * @param[in] direction address direction
 * @return    status code
 *            - 0 success
 *            - 1 set data entry mode failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ssd1681_set_data_entry_mode(ssd1681_handle_t *handle, ssd1681_address_mode_t mode, ssd1681_address_direction_t direction);

/**
 * @brief     software reset
 * @param[in] *handle pointer to an ssd1681 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 software reset failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ssd1681_software_reset(ssd1681_handle_t *handle);

/**
 * @brief     set the hv ready detection
 * @param[in] *handle pointer to an ssd1681 handle structure
 * @param[in] cool_down_duration cool down duration 
 * @param[in] cool_down_loop_num cool down loop num
 * @return    status code
 *            - 0 success
 *            - 1 set hv ready detection failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 cool_down_duration is over 7
 *            - 5 cool_down_loop_num is over 7
 * @note      cool_down_duration <= 7
 *            cool_down_loop_num <= 7
 *            duration = 10ms x (cool_down_duration + 1)
 */
uint8_t ssd1681_set_hv_ready_detection(ssd1681_handle_t *handle, uint8_t cool_down_duration, uint8_t cool_down_loop_num);

/**
 * @brief     set the vci detection
 * @param[in] *handle pointer to an ssd1681 handle structure
 * @param[in] level vci level
 * @return    status code
 *            - 0 success
 *            - 1 set vci detection failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ssd1681_set_vci_detection(ssd1681_handle_t *handle, ssd1681_vci_level_t level);

/**
 * @brief     set the temperature sensor
 * @param[in] *handle pointer to an ssd1681 handle structure
 * @param[in] sensor temperature sensor
 * @return    status code
 *            - 0 success
 *            - 1 set temperature sensor failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ssd1681_set_temperature_sensor(ssd1681_handle_t *handle, ssd1681_temperature_sensor_t sensor);

/**
 * @brief     write the temperature sensor
 * @param[in] *handle pointer to an ssd1681 handle structure
 * @param[in] control set control
 * @return    status code
 *            - 0 success
 *            - 1 write temperature sensor failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 control is over 0xFFF
 * @note      none
 */
uint8_t ssd1681_write_temperature_sensor(ssd1681_handle_t *handle, uint16_t control);

/**
 * @brief      read the temperature sensor
 * @param[in]  *handle pointer to an ssd1681 handle structure
 * @param[out] *control pointer to a control buffer
 * @return     status code
 *             - 0 success
 *             - 1 read temperature sensor failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ssd1681_read_temperature_sensor(ssd1681_handle_t *handle, uint16_t *control);

/**
 * @brief     write command to external temperature sensor
 * @param[in] *handle pointer to an ssd1681 handle structure
 * @param[in] *param pointer to a param buffer
 * @return    status code
 *            - 0 success
 *            - 1 write temperature sensor ext failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ssd1681_write_temperature_sensor_ext(ssd1681_handle_t *handle, uint8_t param[3]);

/**
 * @brief     master activate
 * @param[in] *handle pointer to an ssd1681 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 set master activate failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ssd1681_set_master_activate(ssd1681_handle_t *handle);

/**
 * @brief     set the display update control
 * @param[in] *handle pointer to an ssd1681 handle structure
 * @param[in] red_control red control
 * @param[in] black_control black control
 * @return    status code
 *            - 0 success
 *            - 1 set display update control failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ssd1681_set_display_update_control(ssd1681_handle_t *handle, ssd1681_display_control_t red_control, ssd1681_display_control_t black_control);

/**
 * @brief     set the display sequence
 * @param[in] *handle pointer to an ssd1681 handle structure
 * @param[in] sequence display sequence
 * @return    status code
 *            - 0 success
 *            - 1 set display sequence failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ssd1681_set_display_sequence(ssd1681_handle_t *handle, ssd1681_display_sequence_t sequence);

/**
 * @brief     set the black ram
 * @param[in] *handle pointer to an ssd1681 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 set black ram failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ssd1681_set_black_ram(ssd1681_handle_t *handle);

/**
 * @brief     set the red ram
 * @param[in] *handle pointer to an ssd1681 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 set red ram failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ssd1681_set_red_ram(ssd1681_handle_t *handle);

/**
 * @brief     get the ram
 * @param[in] *handle pointer to an ssd1681 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 get ram failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ssd1681_get_ram(ssd1681_handle_t *handle);

/**
 * @brief     set enter vcom sense
 * @param[in] *handle pointer to an ssd1681 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 set enter vcom sense failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ssd1681_set_enter_vcom_sense(ssd1681_handle_t *handle);

/**
 * @brief     set the vcom sense duration
 * @param[in] *handle pointer to an ssd1681 handle structure
 * @param[in] duration vcom sense duration
 * @return    status code
 *            - 0 success
 *            - 1 set vcom sense duration failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      vcom sense duration = (duration + 1) sec
 */
uint8_t ssd1681_set_vcom_sense_duration(ssd1681_handle_t *handle, uint8_t duration);

/**
 * @brief     write register for vcom control
 * @param[in] *handle pointer to an ssd1681 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 set vcom control reg failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ssd1681_set_vcom_control_reg(ssd1681_handle_t *handle);

/**
 * @brief     write vcom register
 * @param[in] *handle pointer to an ssd1681 handle structure
 * @param[in] vcom set vcom
 * @return    status code
 *            - 0 success
 *            - 1 set vcom register failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ssd1681_set_vcom_register(ssd1681_handle_t *handle, ssd1681_vcom_t vcom);

/**
 * @brief      get the user id
 * @param[in]  *handle pointer to an ssd1681 handle structure
 * @param[out] *id pointer to an id buffer
 * @return     status code
 *             - 0 success
 *             - 1 get user id failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ssd1681_get_user_id(ssd1681_handle_t *handle, uint8_t id[10]);

/**
 * @brief      get the status
 * @param[in]  *handle pointer to an ssd1681 handle structure
 * @param[out] *status pointer to a status buffer
 * @return     status code
 *             - 0 success
 *             - 1 get status failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ssd1681_get_status(ssd1681_handle_t *handle, uint8_t *status);

/**
 * @brief     set the lut register
 * @param[in] *handle pointer to an ssd1681 handle structure
 * @param[in] *reg pointer to a register buffer
 * @param[in] len register length
 * @return    status code
 *            - 0 success
 *            - 1 set lut register failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ssd1681_set_lut_register(ssd1681_handle_t *handle, uint8_t *reg, uint16_t len);

/**
 * @brief     set the crc calculation
 * @param[in] *handle pointer to an ssd1681 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 set crc calculation failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ssd1681_set_crc_calculation(ssd1681_handle_t *handle);

/**
 * @brief      get the crc status
 * @param[in]  *handle pointer to an ssd1681 handle structure
 * @param[out] *status pointer to a status buffer
 * @return     status code
 *             - 0 success
 *             - 1 get crc status failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ssd1681_get_crc_status(ssd1681_handle_t *handle, uint16_t *status);

/**
 * @brief     set the user id
 * @param[in] *handle pointer to an ssd1681 handle structure
 * @param[in] *id pointer to an id buffer
 * @return    status code
 *            - 0 success
 *            - 1 set user id failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ssd1681_set_user_id(ssd1681_handle_t *handle, uint8_t id[10]);

/**
 * @brief     set the border waveform
 * @param[in] *handle pointer to an ssd1681 handle structure
 * @param[in] vbd select vbd option
 * @param[in] level fix level setting for vbd
 * @param[in] gs_tran gs transition control
 * @param[in] vbd_tran gs transition setting for vbd
 * @return    status code
 *            - 0 success
 *            - 1 set border waveform failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ssd1681_set_border_waveform(ssd1681_handle_t *handle, ssd1681_vbd_t vbd, ssd1681_vbd_fix_level_t level,
                                    ssd1681_gs_transition_t gs_tran, ssd1681_vbd_transition_t vbd_tran);

/**
 * @brief     end option
 * @param[in] *handle pointer to an ssd1681 handle structure
 * @param[in] opt end option
 * @return    status code
 *            - 0 success
 *            - 1 set end option failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ssd1681_set_end_option(ssd1681_handle_t *handle, ssd1681_end_opt_t opt);

/**
 * @brief     set the read ram
 * @param[in] *handle pointer to an ssd1681 handle structure
 * @param[in] ram read ram option
 * @return    status code
 *            - 0 success
 *            - 1 set read ram failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ssd1681_set_read_ram(ssd1681_handle_t *handle, ssd1681_read_ram_t ram);

/**
 * @brief     set the ram x range
 * @param[in] *handle pointer to an ssd1681 handle structure
 * @param[in] start start address
 * @param[in] end end address
 * @return    status code
 *            - 0 success
 *            - 1 set ram x failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 start > 0x3F
 *            - 5 end > 0x3F
 * @note      none
 */
uint8_t ssd1681_set_ram_x(ssd1681_handle_t *handle, uint8_t start, uint8_t end);

/**
 * @brief     set the ram y range
 * @param[in] *handle pointer to an ssd1681 handle structure
 * @param[in] start start address
 * @param[in] end end address
 * @return    status code
 *            - 0 success
 *            - 1 set ram y failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ssd1681_set_ram_y(ssd1681_handle_t *handle, uint16_t start, uint16_t end);

/**
 * @brief     set the auto write red ram
 * @param[in] *handle pointer to an ssd1681 handle structure
 * @param[in] height step height
 * @param[in] width step width
 * @return    status code
 *            - 0 success
 *            - 1 set auto write red ram failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ssd1681_set_auto_write_red_ram(ssd1681_handle_t *handle, ssd1681_step_height_t height, ssd1681_step_width_t width);

/**
 * @brief     set the auto write black ram
 * @param[in] *handle pointer to an ssd1681 handle structure
 * @param[in] height step height
 * @param[in] width step width
 * @return    status code
 *            - 0 success
 *            - 1 set auto write black ram failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ssd1681_set_auto_write_black_ram(ssd1681_handle_t *handle, ssd1681_step_height_t height, ssd1681_step_width_t width);

/**
 * @brief     set the ram x address counter
 * @param[in] *handle pointer to an ssd1681 handle structure
 * @param[in] cnt address counter
 * @return    status code
 *            - 0 success
 *            - 1 set ram x address counter failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 cnt > 0x3F
 * @note      none
 */
uint8_t ssd1681_set_ram_x_address_counter(ssd1681_handle_t *handle, uint8_t cnt);

/**
 * @brief     set the ram y address counter
 * @param[in] *handle pointer to an ssd1681 handle structure
 * @param[in] cnt address counter
 * @return    status code
 *            - 0 success
 *            - 1 set ram y address counter failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 cnt > 0x1FF
 * @note      none
 */
uint8_t ssd1681_set_ram_y_address_counter(ssd1681_handle_t *handle, uint16_t cnt);

/**
 * @brief     nop command
 * @param[in] *handle pointer to an ssd1681 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 nop failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ssd1681_nop(ssd1681_handle_t *handle);

/**
 * @}
 */

/**
 * @defgroup ssd1681_extend_driver ssd1681 extend driver function
 * @brief    ssd1681 extend driver modules
 * @ingroup  ssd1681_driver
 * @{
 */

/**
 * @brief     write the register command
 * @param[in] *handle pointer to an ssd1681 handle structure
 * @param[in] *buf pointer to a data buffer
 * @param[in] len data length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ssd1681_write_cmd(ssd1681_handle_t *handle, uint8_t *buf, uint8_t len);

/**
 * @brief     write the register data
 * @param[in] *handle pointer to an ssd1681 handle structure
 * @param[in] *buf pointer to a data buffer
 * @param[in] len data length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ssd1681_write_data(ssd1681_handle_t *handle, uint8_t *buf, uint8_t len);

/**
 * @brief      read the register data
 * @param[in]  *handle pointer to an ssd1681 handle structure
 * @param[out] *buf pointer to a data buffer
 * @param[in]  len data length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ssd1681_read_data(ssd1681_handle_t *handle, uint8_t *buf, uint8_t len);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
