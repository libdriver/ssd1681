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
 * @file      main.c
 * @brief     main source file
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
#include "driver_ssd1681_display_test.h"
#include "clock.h"
#include "delay.h"
#include "uart.h"
#include "shell.h"
#include <stdlib.h>

/**
 * @brief global var definition
 */
uint8_t g_buf[256];        /**< uart buffer */
uint16_t g_len;            /**< uart buffer length */

/**
 * @brief     ssd1681 full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *             - 0 success
 *             - 1 run failed
 *             - 5 param is invalid
 * @note      none
 */
uint8_t ssd1681(uint8_t argc, char** argv)
{
    if (argc == 1)
    {
        goto help;
    }
    else if (argc == 2)
    {
        if (strcmp("-i", argv[1]) == 0)
        {
            ssd1681_info_t info;

            /* print ssd1681 info */
            ssd1681_info(&info);
            ssd1681_interface_debug_print("ssd1681: chip is %s.\n", info.chip_name);
            ssd1681_interface_debug_print("ssd1681: manufacturer is %s.\n", info.manufacturer_name);
            ssd1681_interface_debug_print("ssd1681: interface is %s.\n", info.interface);
            ssd1681_interface_debug_print("ssd1681: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
            ssd1681_interface_debug_print("ssd1681: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
            ssd1681_interface_debug_print("ssd1681: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
            ssd1681_interface_debug_print("ssd1681: max current is %0.2fmA.\n", info.max_current_ma);
            ssd1681_interface_debug_print("ssd1681: max temperature is %0.1fC.\n", info.temperature_max);
            ssd1681_interface_debug_print("ssd1681: min temperature is %0.1fC.\n", info.temperature_min);

            return 0;
        }
        else if (strcmp("-p", argv[1]) == 0)
        {
            /* print pin connection */
            ssd1681_interface_debug_print("ssd1681: SPI interface SCK connected to GPIOA PIN5.\n");
            ssd1681_interface_debug_print("ssd1681: SPI interface MISO connected to GPIOA PIN6.\n");
            ssd1681_interface_debug_print("ssd1681: SPI interface MOSI connected to GPIOA PIN7.\n");
            ssd1681_interface_debug_print("ssd1681: SPI interface CS connected to GPIOA PIN4.\n");
            ssd1681_interface_debug_print("ssd1681: cmd data gpio GPIO connected to GPIOB PIN1.\n");
            ssd1681_interface_debug_print("ssd1681: reset GPIO connected to GPIOB PIN0.\n");
            ssd1681_interface_debug_print("ssd1681: busy GPIO connected to GPIOA PIN8.\n");

            return 0;
        }
        else if (strcmp("-h", argv[1]) == 0)
        {
            /* show ssd1681 help */

            help:
            ssd1681_interface_debug_print("ssd1681 -i\n\tshow ssd1681 chip and driver information.\n");
            ssd1681_interface_debug_print("ssd1681 -h\n\tshow ssd1681 help.\n");
            ssd1681_interface_debug_print("ssd1681 -p\n\tshow ssd1681 pin connections of the current board.\n");
            ssd1681_interface_debug_print("ssd1681 -t display\n\trun ssd1681 display test.\n");
            ssd1681_interface_debug_print("ssd1681 -c basic -init\n\trun ssd1681 init function.\n");
            ssd1681_interface_debug_print("ssd1681 -c basic -deinit\n\trun ssd1681 deinit function.\n");
            ssd1681_interface_debug_print("ssd1681 -c basic (-r | -b) -str <string>\n\trun ssd1681 show string function.string is the shown string.\n");
            ssd1681_interface_debug_print("ssd1681 -c basic (-r | -b) -clear\n\trun ssd1681 clear screen function.\n");
            ssd1681_interface_debug_print("ssd1681 -c basic (-r | -b) -writepoint <x> <y> <data>\n\trun ssd1681 writepoint function.\n");
            ssd1681_interface_debug_print("ssd1681 -c basic (-r | -b) -readpoint <x> <y>\n\trun ssd1681 readpoint function.\n");
            ssd1681_interface_debug_print("ssd1681 -c basic (-r | -b) -rect <x1> <y1> <x2> <y2>\n\trun ssd1681 drawing rectangle function."
                                          "x1 means x start.y1 means y start.x2 means x end.y2 means y end.\n");
            
            return 0;
        }
        else
        {
            return 5;
        }
    }
    else if (argc == 3)
    {
        /* run test */
        if (strcmp("-t", argv[1]) == 0)
        {
            /* display test */
            if (strcmp("display", argv[2]) == 0)
            {
                /* run reg test */
                if (ssd1681_display_test() != 0)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    else if (argc == 4)
    {
        /* run function */
        if (strcmp("-c", argv[1]) == 0)
        {
            /* basic function */
            if (strcmp("basic", argv[2]) == 0)
            {
                /* init */
                if (strcmp("-init", argv[3]) == 0)
                {
                    /* basic init */
                    if (ssd1681_basic_init() != 0)
                    {
                        return 1;
                    }
                    else
                    {
                        ssd1681_interface_debug_print("ssd1681: init success.\n");
                        
                        return 0;
                    }
                }
                /* deinit */
                else if (strcmp("-deinit", argv[3]) == 0)
                {
                    /* basic deinit */
                    if (ssd1681_basic_deinit() != 0)
                    {
                        return 1;
                    }
                    else
                    {
                        ssd1681_interface_debug_print("ssd1681: deinit success.\n");
                        
                        return 0;
                    }
                }
                else
                {
                    return 5;
                }
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    else if (argc == 5)
    {
        /* run function */
        if (strcmp("-c", argv[1]) == 0)
        {
            /* basic function */
            if (strcmp("basic", argv[2]) == 0)
            {
                ssd1681_color_t color;
                
                /* check the color */
                if (strcmp("-r", argv[3]) == 0)
                {
                    color = SSD1681_COLOR_RED;
                }
                else if (strcmp("-b", argv[3]) == 0)
                {
                    color = SSD1681_COLOR_BLACK;
                }
                else
                {
                    return 5;
                }
                
                /* clear */
                if (strcmp("-clear", argv[4]) == 0)
                {
                    /* basic clear */
                    if (ssd1681_basic_clear(color) != 0)
                    {
                        return 1;
                    }
                    else
                    {
                        ssd1681_interface_debug_print("ssd1681: clear success.\n");
                        
                        return 0;
                    }
                }
                else
                {
                    return 5;
                }
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    else if (argc == 6)
    {
        /* run function */
        if (strcmp("-c", argv[1]) == 0)
        {
            /* basic function */
            if (strcmp("basic", argv[2]) == 0)
            {
                ssd1681_color_t color;
                
                /* check the color */
                if (strcmp("-r", argv[3]) == 0)
                {
                    color = SSD1681_COLOR_RED;
                }
                else if (strcmp("-b", argv[3]) == 0)
                {
                    color = SSD1681_COLOR_BLACK;
                }
                else
                {
                    return 5;
                }
                
                /* clear */
                if (strcmp("-str", argv[4]) == 0)
                {
                    /* basic string */
                    if (ssd1681_basic_string(color, 0, 0, argv[5], (uint16_t)strlen(argv[5]), 1, SSD1681_FONT_16) != 0)
                    {
                        return 1;
                    }
                    else
                    {
                        ssd1681_interface_debug_print("ssd1681: %s.\n", argv[5]);
                        
                        return 0;
                    }
                }
                else
                {
                    return 5;
                }
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    else if (argc == 7)
    {
        /* run function */
        if (strcmp("-c", argv[1]) == 0)
        {
            /* basic function */
            if (strcmp("basic", argv[2]) == 0)
            {
                ssd1681_color_t color;
                
                /* check the color */
                if (strcmp("-r", argv[3]) == 0)
                {
                    color = SSD1681_COLOR_RED;
                }
                else if (strcmp("-b", argv[3]) == 0)
                {
                    color = SSD1681_COLOR_BLACK;
                }
                else
                {
                    return 5;
                }
                
                /* read point */
                if (strcmp("-readpoint", argv[4]) == 0)
                {
                    uint8_t data;
                    
                    /* basic read point */
                    if (ssd1681_basic_read_point(color, (uint8_t)atoi(argv[5]), (uint8_t)atoi(argv[6]), &data) != 0)
                    {
                        return 1;
                    }
                    else
                    {
                        ssd1681_interface_debug_print("ssd1681: read point %d %d %d.\n", (uint8_t)atoi(argv[5]), (uint8_t)atoi(argv[6]), data);
                        
                        return 0;
                    }
                }
                else
                {
                    return 5;
                }
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    else if (argc == 8)
    {
        /* run function */
        if (strcmp("-c", argv[1]) == 0)
        {
            /* basic function */
            if (strcmp("basic", argv[2]) == 0)
            {
                ssd1681_color_t color;
                
                /* check the color */
                if (strcmp("-r", argv[3]) == 0)
                {
                    color = SSD1681_COLOR_RED;
                }
                else if (strcmp("-b", argv[3]) == 0)
                {
                    color = SSD1681_COLOR_BLACK;
                }
                else
                {
                    return 5;
                }
                
                /* write point */
                if (strcmp("-writepoint", argv[4]) == 0)
                {
                    /* basic write point */
                    if (ssd1681_basic_write_point(color, (uint8_t)atoi(argv[5]), (uint8_t)atoi(argv[6]), (uint8_t)atoi(argv[7])) != 0)
                    {
                        return 1;
                    }
                    else
                    {
                        ssd1681_interface_debug_print("ssd1681: write point %d %d %d.\n", (uint8_t)atoi(argv[5]), (uint8_t)atoi(argv[6]), (uint8_t)atoi(argv[7]));
                        
                        return 0;
                    }
                }
                else
                {
                    return 5;
                }
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    else if (argc == 9)
    {
        /* run function */
        if (strcmp("-c", argv[1]) == 0)
        {
            /* basic function */
            if (strcmp("basic", argv[2]) == 0)
            {
                ssd1681_color_t color;
                
                /* check the color */
                if (strcmp("-r", argv[3]) == 0)
                {
                    color = SSD1681_COLOR_RED;
                }
                else if (strcmp("-b", argv[3]) == 0)
                {
                    color = SSD1681_COLOR_BLACK;
                }
                else
                {
                    return 5;
                }
                
                /* write rect */
                if (strcmp("-rect", argv[4]) == 0)
                {
                    /* basic write rect */
                    if (ssd1681_basic_rect(color, (uint8_t)atoi(argv[5]), (uint8_t)atoi(argv[6]), (uint8_t)atoi(argv[7]), (uint8_t)atoi(argv[8]), 1) != 0)
                    {
                        return 1;
                    }
                    else
                    {
                        ssd1681_interface_debug_print("ssd1681: write rect %d %d %d %d.\n", (uint8_t)atoi(argv[5]), (uint8_t)atoi(argv[6]), (uint8_t)atoi(argv[7]), (uint8_t)atoi(argv[8]));
                        
                        return 0;
                    }
                }
                else
                {
                    return 5;
                }
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    /* param is invalid */
    else
    {
        return 5;
    }
}

/**
 * @brief main function
 * @note  none
 */
int main(void)
{
    uint8_t res;
    
    /* stm32f407 clock init and hal init */
    clock_init();
    
    /* delay init */
    delay_init();
    
    /* uart1 init */
    uart1_init(115200);
    
    /* shell init && register ssd1681 fuction */
    shell_init();
    shell_register("ssd1681", ssd1681);
    uart1_print("ssd1681: welcome to libdriver ssd1681.\n");
    
    while (1)
    {
        /* read uart */
        g_len = uart1_read(g_buf, 256);
        if (g_len)
        {
            /* run shell */
            res = shell_parse((char *)g_buf, g_len);
            if (res == 0)
            {
                /* run success */
            }
            else if (res == 1)
            {
                uart1_print("ssd1681: run failed.\n");
            }
            else if (res == 2)
            {
                uart1_print("ssd1681: unknow command.\n");
            }
            else if (res == 3)
            {
                uart1_print("ssd1681: length is too long.\n");
            }
            else if (res == 4)
            {
                uart1_print("ssd1681: pretreat failed.\n");
            }
            else if (res == 5)
            {
                uart1_print("ssd1681: param is invalid.\n");
            }
            else
            {
                uart1_print("ssd1681: unknow status code.\n");
            }
            uart1_flush();
        }
        delay_ms(100);
    }
}
