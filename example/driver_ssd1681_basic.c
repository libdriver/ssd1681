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
 * @file      driver_ssd1681_basic.c
 * @brief     driver ssd1681 basic source file
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

#include "driver_ssd1681_basic.h"

static ssd1681_handle_t gs_handle;        /**< ssd1681 handle */
static uint8_t gs_lut[153] = {            /**< lut */
    0x80, 0x48, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x40, 0x48, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x80, 0x48, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x40, 0x48, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0xA, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x8, 0x1, 0x0, 0x8, 0x1, 0x0, 0x2,
    0xA, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x0, 0x0, 0x0,
};

/**
 * @brief  basic example init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t ssd1681_basic_init(void)
{
    uint8_t res;

    /* link functions */
    DRIVER_SSD1681_LINK_INIT(&gs_handle, ssd1681_handle_t);
    DRIVER_SSD1681_LINK_SPI_INIT(&gs_handle, ssd1681_interface_spi_init);
    DRIVER_SSD1681_LINK_SPI_DEINIT(&gs_handle, ssd1681_interface_spi_deinit);
    DRIVER_SSD1681_LINK_SPI_WRITE_CMD(&gs_handle, ssd1681_interface_spi_write_cmd);
    DRIVER_SSD1681_LINK_SPI_READ_CMD(&gs_handle, ssd1681_interface_spi_read_cmd);
    DRIVER_SSD1681_LINK_SPI_CMD_DATA_GPIO_INIT(&gs_handle, ssd1681_interface_spi_cmd_data_gpio_init);
    DRIVER_SSD1681_LINK_SPI_CMD_DATA_GPIO_DEINIT(&gs_handle, ssd1681_interface_spi_cmd_data_gpio_deinit);
    DRIVER_SSD1681_LINK_SPI_CMD_DATA_GPIO_WRITE(&gs_handle, ssd1681_interface_spi_cmd_data_gpio_write);
    DRIVER_SSD1681_LINK_RESET_GPIO_INIT(&gs_handle, ssd1681_interface_reset_gpio_init);
    DRIVER_SSD1681_LINK_RESET_GPIO_DEINIT(&gs_handle, ssd1681_interface_reset_gpio_deinit);
    DRIVER_SSD1681_LINK_RESET_GPIO_WRITE(&gs_handle, ssd1681_interface_reset_gpio_write);
    DRIVER_SSD1681_LINK_BUSY_GPIO_INIT(&gs_handle, ssd1681_interface_busy_gpio_init);
    DRIVER_SSD1681_LINK_BUSY_GPIO_DEINIT(&gs_handle, ssd1681_interface_busy_gpio_deinit);
    DRIVER_SSD1681_LINK_BUSY_GPIO_READ(&gs_handle, ssd1681_interface_busy_gpio_read);
    DRIVER_SSD1681_LINK_DELAY_MS(&gs_handle, ssd1681_interface_delay_ms);
    DRIVER_SSD1681_LINK_DEBUG_PRINT(&gs_handle, ssd1681_interface_debug_print);

    /* init */
    res = ssd1681_init(&gs_handle);
    if (res != 0)
    {
        ssd1681_interface_debug_print("ssd1681: init failed.\n");

        return 1;
    }

    /* reset the chip */
    res = ssd1681_software_reset(&gs_handle);
    if (res != 0)
    {
        ssd1681_interface_debug_print("ssd1681: software reset failed.\n");
        (void)ssd1681_deinit(&gs_handle);

        return 1;
    }

    /* set the default driver output */
    res = ssd1681_set_driver_output(&gs_handle, SSD1681_BASIC_DEFAULT_DRIVER_OUTPUT_MUX,
                                    SSD1681_BASIC_DEFAULT_DRIVER_OUTPUT_GD,
                                    SSD1681_BASIC_DEFAULT_DRIVER_OUTPUT_SM,
                                    SSD1681_BASIC_DEFAULT_DRIVER_OUTPUT_TB);
    if (res != 0)
    {
        ssd1681_interface_debug_print("ssd1681: set the driver output failed.\n");
        (void)ssd1681_deinit(&gs_handle);

        return 1;
    }

    /* set the default data entry mode */
    res = ssd1681_set_data_entry_mode(&gs_handle, SSD1681_BASIC_DEFAULT_ADDRESS_MODE, SSD1681_BASIC_DEFAULT_ADDRESS_DIRECTION);
    if (res != 0)
    {
        ssd1681_interface_debug_print("ssd1681: set data entry mode failed.\n");
        (void)ssd1681_deinit(&gs_handle);

        return 1;
    }

    /* set the default temperature sensor */
    res = ssd1681_set_temperature_sensor(&gs_handle, SSD1681_BASIC_DEFAULT_TEMPERATURE_SENSOR);
    if (res != 0)
    {
        ssd1681_interface_debug_print("ssd1681: set temperature sensor failed.\n");
        (void)ssd1681_deinit(&gs_handle);

        return 1;
    }

    /* set the default border waveform */
    res = ssd1681_set_border_waveform(&gs_handle, SSD1681_BASIC_DEFAULT_VBD, SSD1681_BASIC_DEFAULT_VBD_FIX_LEVEL,
                                      SSD1681_BASIC_DEFAULT_GS_TRANSITION, SSD1681_BASIC_DEFAULT_VBD_TRANSITION);
    if (res != 0)
    {
        ssd1681_interface_debug_print("ssd1681: set border waveform failed.\n");
        (void)ssd1681_deinit(&gs_handle);

        return 1;
    }

    /* set the default x range */
    res = ssd1681_set_ram_x(&gs_handle, SSD1681_BASIC_DEFAULT_RAM_X_START, SSD1681_BASIC_DEFAULT_RAM_X_END);
    if (res != 0)
    {
        ssd1681_interface_debug_print("ssd1681: set ram x failed.\n");
        (void)ssd1681_deinit(&gs_handle);

        return 1;
    }

    /* set the default y range */
    res = ssd1681_set_ram_y(&gs_handle, SSD1681_BASIC_DEFAULT_RAM_Y_START, SSD1681_BASIC_DEFAULT_RAM_Y_END);
    if (res != 0)
    {
        ssd1681_interface_debug_print("ssd1681: set ram y failed.\n");
        (void)ssd1681_deinit(&gs_handle);

        return 1;
    }

    /* set the default ram x address counter */
    res = ssd1681_set_ram_x_address_counter(&gs_handle, SSD1681_BASIC_DEFAULT_RAM_X_ADDRESS_COUNTER);
    if (res != 0)
    {
        ssd1681_interface_debug_print("ssd1681: set ram x address counter failed.\n");
        (void)ssd1681_deinit(&gs_handle);

        return 1;
    }

    /* set the default ram y address counter */
    res = ssd1681_set_ram_y_address_counter(&gs_handle, SSD1681_BASIC_DEFAULT_RAM_Y_ADDRESS_COUNTER);
    if (res != 0)
    {
        ssd1681_interface_debug_print("ssd1681: set ram y address counter failed.\n");
        (void)ssd1681_deinit(&gs_handle);

        return 1;
    }

    /* set the default display update control mode */
    res = ssd1681_set_display_update_control(&gs_handle, SSD1681_BASIC_DEFAULT_DISPLAY_CONTROL_RED, SSD1681_BASIC_DEFAULT_DISPLAY_CONTROL_BLACK);
    if (res != 0)
    {
        ssd1681_interface_debug_print("ssd1681: set display update control failed.\n");
        (void)ssd1681_deinit(&gs_handle);

        return 1;
    }

    /* set the default sequence */
    res = ssd1681_set_display_sequence(&gs_handle, SSD1681_BASIC_DEFAULT_DISPLAY_SEQUENCE);
    if (res != 0)
    {
        ssd1681_interface_debug_print("ssd1681: set display sequence failed.\n");
        (void)ssd1681_deinit(&gs_handle);

        return 1;
    }

    /* set the default vcom sense duration */
    res = ssd1681_set_vcom_sense_duration(&gs_handle, SSD1681_BASIC_DEFAULT_VCOM_SENSE_DURATION);
    if (res != 0)
    {
        ssd1681_interface_debug_print("ssd1681: set vcom sense duration failed.\n");
        (void)ssd1681_deinit(&gs_handle);

        return 1;
    }

    /* enter the vcom sense */
    res = ssd1681_set_enter_vcom_sense(&gs_handle);
    if (res != 0)
    {
        ssd1681_interface_debug_print("ssd1681: set enter vcom sense failed.\n");
        (void)ssd1681_deinit(&gs_handle);

        return 1;
    }

    /* set the vcom control reg */
    res = ssd1681_set_vcom_control_reg(&gs_handle);
    if (res != 0)
    {
        ssd1681_interface_debug_print("ssd1681: set vcom control reg failed.\n");
        (void)ssd1681_deinit(&gs_handle);

        return 1;
    }

    /* set the lut register */
    res = ssd1681_set_lut_register(&gs_handle, gs_lut, 153);
    if (res != 0)
    {
        ssd1681_interface_debug_print("ssd1681: set lut register failed.\n");
        (void)ssd1681_deinit(&gs_handle);

        return 1;
    }

    /* set the default end option */
    res = ssd1681_set_end_option(&gs_handle, SSD1681_BASIC_DEFAULT_END_OPT);
    if (res != 0)
    {
        ssd1681_interface_debug_print("ssd1681: set end option failed.\n");
        (void)ssd1681_deinit(&gs_handle);

        return 1;
    }

    /* set the default gate driving voltage */
    res = ssd1681_set_gate_driving_voltage(&gs_handle, SSD1681_BASIC_DEFAULT_GATE_DRIVING_VOLTAGE);
    if (res != 0)
    {
        ssd1681_interface_debug_print("ssd1681: set gate driving voltage failed.\n");
        (void)ssd1681_deinit(&gs_handle);

        return 1;
    }

    /* set the default source driving voltage */
    res = ssd1681_set_source_driving_voltage(&gs_handle, SSD1681_BASIC_DEFAULT_VSH1, SSD1681_BASIC_DEFAULT_VSH2, SSD1681_BASIC_DEFAULT_VSL);
    if (res != 0)
    {
        ssd1681_interface_debug_print("ssd1681: set source driving voltage failed.\n");
        (void)ssd1681_deinit(&gs_handle);

        return 1;
    }

    /* set the default vcom */
    res = ssd1681_set_vcom_register(&gs_handle, SSD1681_VCOM_NEGATIVE_0P8);
    if (res != 0)
    {
        ssd1681_interface_debug_print("ssd1681: set vcom register failed.\n");
        (void)ssd1681_deinit(&gs_handle);

        return 1;
    }

    /* set the default auto write red ram */
    res = ssd1681_set_auto_write_red_ram(&gs_handle, SSD1681_BASIC_DEFAULT_AUTO_RED_STEP_HEIGHT, SSD1681_BASIC_DEFAULT_AUTO_RED_STEP_WIDTH);
    if (res != 0)
    {
        ssd1681_interface_debug_print("ssd1681: set auto write red ram failed.\n");
        (void)ssd1681_deinit(&gs_handle);

        return 1;
    }

    /* set the default auto write black ram */
    res = ssd1681_set_auto_write_black_ram(&gs_handle, SSD1681_BASIC_DEFAULT_AUTO_BLACK_STEP_HEIGHT, SSD1681_BASIC_DEFAULT_AUTO_BLACK_STEP_WIDTH);
    if (res != 0)
    {
        ssd1681_interface_debug_print("ssd1681: set auto write black ram failed.\n");
        (void)ssd1681_deinit(&gs_handle);

        return 1;
    }

    /* set the default hv ready detection */
    res = ssd1681_set_hv_ready_detection(&gs_handle, SSD1681_BASIC_DEFAULT_COOL_DOWN_DURATION, SSD1681_BASIC_DEFAULT_COOL_DOWN_LOOP_NUM);
    if (res != 0)
    {
        ssd1681_interface_debug_print("ssd1681: set hv ready detection failed.\n");
        (void)ssd1681_deinit(&gs_handle);

        return 1;
    }

    /* set the default vci detection */
    res = ssd1681_set_vci_detection(&gs_handle, SSD1681_BASIC_DEFAULT_VCI);
    if (res != 0)
    {
        ssd1681_interface_debug_print("ssd1681: set vci detection failed.\n");
        (void)ssd1681_deinit(&gs_handle);

        return 1;
    }

    /* set the default booster soft start param */
    res = ssd1681_set_booster_soft_start(&gs_handle,
                                        (uint8_t)(SSD1681_BASIC_DEFAULT_PHASE1),
                                        (uint8_t)(SSD1681_BASIC_DEFAULT_PHASE2),
                                        (uint8_t)(SSD1681_BASIC_DEFAULT_PHASE3),
                                        (uint8_t)(SSD1681_BASIC_DEFAULT_DURATION));
    if (res != 0)
    {
        ssd1681_interface_debug_print("ssd1681: set booster soft start failed.\n");
        (void)ssd1681_deinit(&gs_handle);

        return 1;
    }

    /* set the default mode */
    res = ssd1681_set_mode(&gs_handle, SSD1681_BASIC_DEFAULT_MODE);
    if (res != 0)
    {
        ssd1681_interface_debug_print("ssd1681: set mode failed.\n");
        (void)ssd1681_deinit(&gs_handle);

        return 1;
    }

    /* clear the black */
    res = ssd1681_gram_clear(&gs_handle, SSD1681_COLOR_BLACK);
    if (res != 0)
    {
        ssd1681_interface_debug_print("ssd1681: clear failed.\n");
        (void)ssd1681_deinit(&gs_handle);

        return 1;
    }

    /* clear the red */
    res = ssd1681_gram_clear(&gs_handle, SSD1681_COLOR_RED);
    if (res != 0)
    {
        ssd1681_interface_debug_print("ssd1681: clear failed.\n");
        (void)ssd1681_deinit(&gs_handle);

        return 1;
    }

    return 0;
}

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t ssd1681_basic_deinit(void)
{
    /* deinit ssd1681 */
    if (ssd1681_deinit(&gs_handle) != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief     basic example clear
 * @param[in] color is the color type
 * @return    status code
 *            - 0 success
 *            - 1 clear failed
 * @note      none
 */
uint8_t ssd1681_basic_clear(ssd1681_color_t color)
{
    /* clear */
    if (ssd1681_clear(&gs_handle, color) != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

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
uint8_t ssd1681_basic_write_point(ssd1681_color_t color, uint8_t x, uint8_t y, uint8_t data)
{
    uint8_t res;

    /* write point */
    res = ssd1681_gram_write_point(&gs_handle, color, x, y, data);
    if (res != 0)
    {
        return 1;
    }

    /* update gram */
    if (ssd1681_gram_update(&gs_handle, color) != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

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
uint8_t ssd1681_basic_read_point(ssd1681_color_t color, uint8_t x, uint8_t y, uint8_t *data)
{
    uint8_t res;

    /* read point in gram */
    res = ssd1681_gram_read_point(&gs_handle, color, x, y, data);
    if (res != 0)
    {
        return 1;
    }

    return 0;
}

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
uint8_t ssd1681_basic_string(ssd1681_color_t color, uint8_t x, uint8_t y, char *str, uint16_t len, uint8_t data, ssd1681_font_t font)
{
    uint8_t res;

    /* write string in gram */
    res = ssd1681_gram_write_string(&gs_handle, color, x, y, str, len, data, font);
    if (res != 0)
    {
        return 1;
    }

    /* update gram */
    if (ssd1681_gram_update(&gs_handle, color) != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

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
uint8_t ssd1681_basic_rect(ssd1681_color_t color, uint8_t left, uint8_t top, uint8_t right, uint8_t bottom, uint8_t data)
{
    uint8_t res;

    /* fill rect in gram */
    res = ssd1681_gram_fill_rect(&gs_handle, color, left, top, right, bottom, data);
    if (res != 0)
    {
        return 1;
    }

    /* update gram */
    if (ssd1681_gram_update(&gs_handle, color) != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

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
uint8_t ssd1681_basic_picture(ssd1681_color_t color, uint8_t left, uint8_t top, uint8_t right, uint8_t bottom, uint8_t *img)
{
    uint8_t res;

    /* draw picture in gram */
    res = ssd1681_gram_draw_picture(&gs_handle, color, left, top, right, bottom, img);
    if (res != 0)
    {
        return 1;
    }

    /* update gram */
    if (ssd1681_gram_update(&gs_handle, color) != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
