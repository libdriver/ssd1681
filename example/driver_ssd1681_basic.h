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
 * @file      driver_ssd1681_basic.h
 * @brief     driver ssd1681 basic header file
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

#ifndef DRIVER_SSD1681_BASIC_H
#define DRIVER_SSD1681_BASIC_H

#include "driver_ssd1681_interface.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup ssd1681_example_driver ssd1681 example driver function
 * @brief    ssd1681 example driver modules
 * @ingroup  ssd1681_driver
 * @{
 */

/**
 * @brief ssd1681 basic example default definition
 */
#define SSD1681_BASIC_DEFAULT_DRIVER_OUTPUT_MUX             0xC7                                                           /**< 200 - 1*/
#define SSD1681_BASIC_DEFAULT_DRIVER_OUTPUT_GD              SSD1681_BOOL_FALSE                                             /**< disable gd */
#define SSD1681_BASIC_DEFAULT_DRIVER_OUTPUT_SM              SSD1681_BOOL_FALSE                                             /**< disable sm */
#define SSD1681_BASIC_DEFAULT_DRIVER_OUTPUT_TB              SSD1681_BOOL_FALSE                                             /**< disable tb */
#define SSD1681_BASIC_DEFAULT_ADDRESS_MODE                  SSD1681_ADDRESS_MODE_Y_DECREMENT_X_INCREMENT                   /**< y decrement and x increment */
#define SSD1681_BASIC_DEFAULT_ADDRESS_DIRECTION             SSD1681_ADDRESS_DIRECTION_UPDATED_X                            /**< update x */
#define SSD1681_BASIC_DEFAULT_TEMPERATURE_SENSOR            SSD1681_TEMPERATURE_SENSOR_INTERNAL                            /**< internal sensor */
#define SSD1681_BASIC_DEFAULT_VBD                           SSD1681_VBD_GS_TRANSITION                                      /**< vbd gs transition */
#define SSD1681_BASIC_DEFAULT_VBD_FIX_LEVEL                 SSD1681_VBD_FIX_LEVEL_VSS                                      /**< vbd fix level vss */
#define SSD1681_BASIC_DEFAULT_GS_TRANSITION                 SSD1681_GS_TRANSITION_FOLLOW_LUT                               /**< gs transition follow lut */
#define SSD1681_BASIC_DEFAULT_VBD_TRANSITION                SSD1681_VBD_TRANSITION_LUT1                                    /**< vbd transition lut1 */
#define SSD1681_BASIC_DEFAULT_RAM_X_START                   0x00                                                           /**< 0 */
#define SSD1681_BASIC_DEFAULT_RAM_X_END                     0x18                                                           /**< 200 / 8 */
#define SSD1681_BASIC_DEFAULT_RAM_Y_START                   0xC7                                                           /**< 200 - 1 */
#define SSD1681_BASIC_DEFAULT_RAM_Y_END                     0x00                                                           /**< 0 */
#define SSD1681_BASIC_DEFAULT_RAM_X_ADDRESS_COUNTER         0x00                                                           /**< 0 */
#define SSD1681_BASIC_DEFAULT_RAM_Y_ADDRESS_COUNTER         0xC7                                                           /**< 200 - 1 */
#define SSD1681_BASIC_DEFAULT_DISPLAY_CONTROL_RED           SSD1681_DISPLAY_CONTROL_NORMAL                                 /**< normal mode */
#define SSD1681_BASIC_DEFAULT_DISPLAY_CONTROL_BLACK         SSD1681_DISPLAY_CONTROL_NORMAL                                 /**< normal mode */
#define SSD1681_BASIC_DEFAULT_DISPLAY_SEQUENCE              SSD1681_DISPLAY_SEQUENCE_0                                     /**< sequence0 */
#define SSD1681_BASIC_DEFAULT_VCOM_SENSE_DURATION           0x00                                                           /**< 0x00 */
#define SSD1681_BASIC_DEFAULT_END_OPT                       SSD1681_END_OPT_NORMAL                                         /**< normal mode */
#define SSD1681_BASIC_DEFAULT_GATE_DRIVING_VOLTAGE          SSD1681_GATE_DRIVING_VOLTAGE_20V                               /**< 20V */
#define SSD1681_BASIC_DEFAULT_VSH1                          SSD1681_VSH_15V                                                /**< 15V */
#define SSD1681_BASIC_DEFAULT_VSH2                          SSD1681_VSH_5V                                                 /**< 5V */
#define SSD1681_BASIC_DEFAULT_VSL                           SSD1681_VSL_NEGATIVE_15                                        /**< -15V */
#define SSD1681_BASIC_DEFAULT_VCOM                          SSD1681_VCOM_NEGATIVE_0P8                                      /**< -0.8V */
#define SSD1681_BASIC_DEFAULT_AUTO_RED_STEP_HEIGHT          SSD1681_STEP_HEIGHT_200                                        /**< 200 */
#define SSD1681_BASIC_DEFAULT_AUTO_RED_STEP_WIDTH           SSD1681_STEP_WIDTH_200                                         /**< 200 */
#define SSD1681_BASIC_DEFAULT_AUTO_BLACK_STEP_HEIGHT        SSD1681_STEP_HEIGHT_200                                        /**< 200 */
#define SSD1681_BASIC_DEFAULT_AUTO_BLACK_STEP_WIDTH         SSD1681_STEP_WIDTH_200                                         /**< 200 */
#define SSD1681_BASIC_DEFAULT_COOL_DOWN_DURATION            0x00                                                           /**< 0x00 */
#define SSD1681_BASIC_DEFAULT_COOL_DOWN_LOOP_NUM            0x00                                                           /**< 0x00 */
#define SSD1681_BASIC_DEFAULT_VCI                           SSD1681_VCI_LEVEL_2P3V                                         /**< 2.3V */
#define SSD1681_BASIC_DEFAULT_PHASE1                        (SSD1681_DRIVING_STRENGTH_1 | SSD1681_MIN_OFF_TIME_8P4)        /**< strength1 && mini off 8.4 */
#define SSD1681_BASIC_DEFAULT_PHASE2                        (SSD1681_DRIVING_STRENGTH_2 | SSD1681_MIN_OFF_TIME_9P8)        /**< strength2 && mini off 9.8 */
#define SSD1681_BASIC_DEFAULT_PHASE3                        (SSD1681_DRIVING_STRENGTH_2 | SSD1681_MIN_OFF_TIME_3P9)        /**< strength2 && mini off 3.9 */
#define SSD1681_BASIC_DEFAULT_DURATION                      ((SSD1681_PHASE_DURATION_10MS << 4) \
                                                              | (SSD1681_PHASE_DURATION_40MS << 2) \
                                                              | (SSD1681_PHASE_DURATION_40MS << 0))                        /**< 10ms && 40ms && 40ms */
#define SSD1681_BASIC_DEFAULT_MODE                          SSD1681_MODE_NORMAL                                            /**< normal mode */

/**
 * @brief  basic example init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t ssd1681_basic_init(void);

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t ssd1681_basic_deinit(void);

/**
 * @brief     basic example clear
 * @param[in] color is the color type
 * @return    status code
 *            - 0 success
 *            - 1 clear failed
 * @note      none
 */
uint8_t ssd1681_basic_clear(ssd1681_color_t color);

/**
 * @brief     basic example write a point
 * @param[in] color is the color type
 * @param[in] x is the coordinate x
 * @param[in] y is the coordinate y
 * @param[in] data is the written data
 * @return    status code
 *            - 0 success
 *            - 1 write point failed
 * @note      none
 */
uint8_t ssd1681_basic_write_point(ssd1681_color_t color, uint8_t x, uint8_t y, uint8_t data);

/**
 * @brief      basic example read a point
 * @param[in]  color is the color type
 * @param[in]  x is the coordinate x
 * @param[in]  y is the coordinate y
 * @param[out] *data points to a data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read point failed
 * @note       none
 */
uint8_t ssd1681_basic_read_point(ssd1681_color_t color, uint8_t x, uint8_t y, uint8_t *data);

/**
 * @brief     basic example draw a string
 * @param[in] color is the color type
 * @param[in] x is the coordinate x
 * @param[in] y is the coordinate y
 * @param[in] *str points to a written string address
 * @param[in] len is the length of the string
 * @param[in] data is the display color
 * @param[in] font is the display font size
 * @return    status code
 *            - 0 success
 *            - 1 write string failed
 * @note      none
 */
uint8_t ssd1681_basic_string(ssd1681_color_t color, uint8_t x, uint8_t y, char *str, uint16_t len, uint8_t data, ssd1681_font_t font);

/**
 * @brief     basic example fill a rectangle
 * @param[in] color is the color type
 * @param[in] left is the left coordinate x
 * @param[in] top is the top coordinate y
 * @param[in] right is the right coordinate x
 * @param[in] bottom is the bottom coordinate y
 * @param[in] data is the display color
 * @return    status code
 *            - 0 success
 *            - 1 fill rect failed
 * @note      none
 */
uint8_t ssd1681_basic_rect(ssd1681_color_t color, uint8_t left, uint8_t top, uint8_t right, uint8_t bottom, uint8_t data);

/**
 * @brief     basic example draw a picture
 * @param[in] color is the color type
 * @param[in] left is the left coordinate x
 * @param[in] top is the top coordinate y
 * @param[in] right is the right coordinate x
 * @param[in] bottom is the bottom coordinate y
 * @param[in] *img points to a image buffer
 * @return    status code
 *            - 0 success
 *            - 1 draw picture failed
 * @note      none
 */
uint8_t ssd1681_basic_picture(ssd1681_color_t color, uint8_t left, uint8_t top, uint8_t right, uint8_t bottom, uint8_t *img);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
