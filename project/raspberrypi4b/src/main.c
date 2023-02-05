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
#include "shell.h"
#include <getopt.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

/**
 * @brief global var definition
 */
uint8_t g_buf[256];                              /**< uart buffer */
volatile uint16_t g_len;                         /**< uart buffer length */
static int gs_listen_fd;                         /**< network handle */
static int gs_conn_fd;                           /**< network handle */
static struct sockaddr_in gs_server_addr;        /**< server address */

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
    int c;
    int longindex = 0;
    const char short_options[] = "hipe:t:";
    const struct option long_options[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {"port", no_argument, NULL, 'p'},
        {"example", required_argument, NULL, 'e'},
        {"test", required_argument, NULL, 't'},
        {"color", required_argument, NULL, 1},
        {"mode", required_argument, NULL, 2},
        {"str", required_argument, NULL, 3},
        {"x0", required_argument, NULL, 4},
        {"x1", required_argument, NULL, 5},
        {"x2", required_argument, NULL, 6},
        {"y0", required_argument, NULL, 7},
        {"y1", required_argument, NULL, 8},
        {"y2", required_argument, NULL, 9},
        {NULL, 0, NULL, 0},
    };
    char type[33] = "unknown";
    ssd1681_color_t mode = SSD1681_COLOR_BLACK;
    uint8_t color = 1;
    uint8_t x0 = 0;
    uint8_t x1 = 0;
    uint8_t x2 = 0;
    uint8_t y0 = 0;
    uint8_t y1 = 0;
    uint8_t y2 = 0;
    uint8_t x0_flag = 0;
    uint8_t x1_flag = 0;
    uint8_t x2_flag = 0;
    uint8_t y0_flag = 0;
    uint8_t y1_flag = 0;
    uint8_t y2_flag = 0;
    uint8_t color_flag = 0;
    char str[49] = "libdriver";
    
    /* if no params */
    if (argc == 1)
    {
        /* goto the help */
        goto help;
    }
    
    /* init 0 */
    optind = 0;
    
    /* parse */
    do
    {
        /* parse the args */
        c = getopt_long(argc, argv, short_options, long_options, &longindex);
        
        /* judge the result */
        switch (c)
        {
            /* help */
            case 'h' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "h");
                
                break;
            }
            
            /* information */
            case 'i' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "i");
                
                break;
            }
            
            /* port */
            case 'p' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "p");
                
                break;
            }
            
            /* example */
            case 'e' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "e_%s", optarg);
                
                break;
            }
            
            /* test */
            case 't' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "t_%s", optarg);
                
                break;
            }
            
            /* color */
            case 1 :
            {
                /* set the color */
                color = atol(optarg);
                color_flag = 1;

                break;
            }
            
            /* mode */
            case 2 :
            {
                /* set the mode */
                if (strcmp("BLACK", optarg) == 0)
                {
                    mode = SSD1681_COLOR_BLACK;
                }
                else if (strcmp("RED", optarg) == 0)
                {
                    mode = SSD1681_COLOR_RED;
                }
                else
                {
                    return 5;
                }
                
                break;
            } 
            
            /* str */
            case 3 :
            {
                /* set the str */
                memset(str, 0, sizeof(char) * 49);
                strncpy(str, optarg, 48);
                
                break;
            }
            
            /* x0 */
            case 4 :
            {
                /* convert */
                x0 = atol(optarg);
                x0_flag = 1;
                
                break;
            }
            
            /* x1 */
            case 5 :
            {
                /* convert */
                x1 = atol(optarg);
                x1_flag = 1;
                
                break;
            }
            
            /* x2 */
            case 6 :
            {
                /* convert */
                x2 = atol(optarg);
                x2_flag = 1;
                
                break;
            }
            /* y0 */
            case 7 :
            {
                /* convert */
                y0 = atol(optarg);
                y0_flag = 1;
                
                break;
            }
            
            /* y1 */
            case 8 :
            {
                /* convert */
                y1 = atol(optarg);
                y1_flag = 1;
                
                break;
            }
            
            /* y2 */
            case 9 :
            {
                /* convert */
                y2 = atol(optarg);
                y2_flag = 1;
                
                break;
            }
            
            /* the end */
            case -1 :
            {
                break;
            }
            
            /* others */
            default :
            {
                return 5;
            }
        }
    } while (c != -1);
    
    /* run the function */
    if (strcmp("t_display", type) == 0)
    {
        /* run display test */
        if (ssd1681_display_test() != 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (strcmp("e_basic-str", type) == 0)
    {
        /* basic string */
        if (ssd1681_basic_string(mode, 0, 0, str, strlen(str), color, SSD1681_FONT_16) != 0)
        {
            ssd1681_interface_debug_print("ssd1681: string failed.\n");
            (void)ssd1681_basic_deinit();
            
            return 1;
        }
        else
        {
            ssd1681_interface_debug_print("ssd1681: %s.\n", str);
            
            return 0;
        }
    }
    else if (strcmp("e_basic-init", type) == 0)
    {
        /* basic init */
        if (ssd1681_basic_init() != 0)
        {
            (void)ssd1681_basic_deinit();
            
            return 1;
        }
        else
        {
            ssd1681_interface_debug_print("ssd1681: init success.\n");
            
            return 0;
        }
    }
    else if (strcmp("e_basic-clear", type) == 0)
    {
        /* basic clear */
        if (ssd1681_basic_clear(mode) != 0)
        {
            ssd1681_interface_debug_print("ssd1681: clear failed.\n");
            (void)ssd1681_basic_deinit();
            
            return 1;
        }
        else
        {
            ssd1681_interface_debug_print("ssd1681: clear success.\n");
            
            return 0;
        }
    }
    else if (strcmp("e_basic-deinit", type) == 0)
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
    else if (strcmp("e_basic-point", type) == 0)
    {
        if ((x0_flag == 1) && (y0_flag == 1) && (color_flag == 0))
        {
            uint8_t data;
            
            /* basic read point */
            if (ssd1681_basic_read_point(mode, x0, y0, &data) != 0)
            {
                ssd1681_interface_debug_print("ssd1681: read point failed.\n");
                (void)ssd1681_basic_deinit();
                
                return 1;
            }
            else
            {
                ssd1681_interface_debug_print("ssd1681: read point %d %d %d.\n", x0, y0, data);
                
                return 0;
            }
        }
        else if ((x0_flag == 1) && (y0_flag == 1) && (color_flag == 1))
        {
            /* basic write point */
            if (ssd1681_basic_write_point(mode, x0, y0, color) != 0)
            {
                ssd1681_interface_debug_print("ssd1681: write point failed.\n");
                (void)ssd1681_basic_deinit();
                
                return 1;
            }
            else
            {
                ssd1681_interface_debug_print("ssd1681: write point %d %d %d.\n", x0, y0, color);
                
                return 0;
            }
        }
        else
        {
            return 5;
        }
    }
    else if (strcmp("e_basic-rect", type) == 0)
    {
        /* check the flag */
        if ((x1_flag != 1) || (y1_flag != 1) || (x2_flag != 1) || (y2_flag != 1))
        {
             return 5;
        }

        /* basic write rect */
        if (ssd1681_basic_rect(mode, x1, y1, x2, y2, color) != 0)
        {
            (void)ssd1681_basic_deinit();
            
            return 1;
        }
        else
        {
            ssd1681_interface_debug_print("ssd1681: write rect %d %d %d %d.\n", x1, y1, x2, y2);
            
            return 0;
        }
    }
    else if (strcmp("h", type) == 0)
    {
        help:
        ssd1681_interface_debug_print("Usage:\n");
        ssd1681_interface_debug_print("  ssd1681 (-i | --information)\n");
        ssd1681_interface_debug_print("  ssd1681 (-h | --help)\n");
        ssd1681_interface_debug_print("  ssd1681 (-p | --port)\n");
        ssd1681_interface_debug_print("  ssd1681 (-t display | --test=display)\n");
        ssd1681_interface_debug_print("  ssd1681 (-e basic-init | --example=basic-init)\n");
        ssd1681_interface_debug_print("  ssd1681 (-e basic-deinit | --example=basic-deinit)\n");
        ssd1681_interface_debug_print("  ssd1681 (-e basic-str | --example=basic-str) [--str=<string>] [--mode=<RED | BLACK>] [--color=<0 | 1>]\n");
        ssd1681_interface_debug_print("  ssd1681 (-e basic-clear | --example=basic-clear) [--mode=<RED | BLACK>]\n");
        ssd1681_interface_debug_print("  ssd1681 (-e basic-point | --example=basic-point) --x0=<x0> --y0=<y0> [--mode=<RED | BLACK>] [--color=<0 | 1>]\n");
        ssd1681_interface_debug_print("  ssd1681 (-e basic-rect | --example=basic-rect) --x1=<x1> --y1=<y1> --x2=<x2> --y2=<y2> [--mode=<RED | BLACK>] [--color=<0 | 1>]\n");
        ssd1681_interface_debug_print("\n");
        ssd1681_interface_debug_print("Options:\n");
        ssd1681_interface_debug_print("      --color=<0 | 1>     Set the chip color.([default: 1])\n");
        ssd1681_interface_debug_print("  -e <basic-init | basic-deinit | basic-str | basic-clear | basic-point | basic-rect>, --example=\n");
        ssd1681_interface_debug_print("     <basic-init | basic-deinit | basic-str | basic-clear | basic-point | basic-rect>\n");
        ssd1681_interface_debug_print("                          Run the driver example.\n");
        ssd1681_interface_debug_print("  -h, --help              Show the help.\n");
        ssd1681_interface_debug_print("  -i, --information       Show the chip information.\n");
        ssd1681_interface_debug_print("      --mode=<RED | BLACK>\n");
        ssd1681_interface_debug_print("                          Set the chip display mode.([default: BLACK])\n");
        ssd1681_interface_debug_print("  -p, --port              Display the pin connections of the current board.\n");
        ssd1681_interface_debug_print("      --str=<string>      Set the display string.([default: libdriver])\n");
        ssd1681_interface_debug_print("  -t <display>, --test=<display>\n");
        ssd1681_interface_debug_print("                          Run the driver test.\n");
        ssd1681_interface_debug_print("      --x0=<x0>           Set the x0 and it is the x of the point.\n");
        ssd1681_interface_debug_print("      --x1=<x1>           Set the x1 and it is the top left x of the rect.\n");
        ssd1681_interface_debug_print("      --x2=<x2>           Set the x2 and it is the bottom right x of the rect.\n");
        ssd1681_interface_debug_print("      --y0=<y0>           Set the y0 and it is the y of the point.\n");
        ssd1681_interface_debug_print("      --y1=<y1>           Set the y1 and it is the top left y of the rect.\n");
        ssd1681_interface_debug_print("      --y2=<y2>           Set the y2 and it is the bottom right y of the rect.\n");
        
        return 0;
    }
    else if (strcmp("i", type) == 0)
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
    else if (strcmp("p", type) == 0)
    {
        /* print pin connection */
        ssd1681_interface_debug_print("ssd1681: SPI interface SCK connected to GPIO11(BCM).\n");
        ssd1681_interface_debug_print("ssd1681: SPI interface MISO connected to GPIO9(BCM).\n");
        ssd1681_interface_debug_print("ssd1681: SPI interface MOSI connected to GPIO10(BCM).\n");
        ssd1681_interface_debug_print("ssd1681: SPI interface CS connected to GPIO8(BCM).\n");
        ssd1681_interface_debug_print("ssd1681: cmd data gpio GPIO connected to GPIO22(BCM).\n");
        ssd1681_interface_debug_print("ssd1681: reset GPIO connected to GPIO27(BCM).\n");
        ssd1681_interface_debug_print("ssd1681: busy GPIO connected to GPIO17(BCM).\n");

        return 0;
    }
    else
    {
        return 5;
    }
}

/**
 * @brief  socket init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
static uint8_t a_socket_init(void)
{
    int optval;
    
    /* creat a socket */
    gs_listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (gs_listen_fd < 0) 
    {
        ssd1681_interface_debug_print("ssd1681: create socket failed.\n");
        
        return 1;
    }
    
    /* set the server port */
    memset(&gs_server_addr, 0, sizeof(gs_server_addr));
    gs_server_addr.sin_family = AF_INET;
    gs_server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    gs_server_addr.sin_port = htons(6666);
    
    /* enable same port binding */
    optval = 1;
    if (setsockopt(gs_listen_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&optval, sizeof(optval)) < 0)
    {
        ssd1681_interface_debug_print("ssd1681: create socket failed.\n");
        (void)close(gs_listen_fd);
        
        return 1;
    }
    
    /* bind the port */
    if (bind(gs_listen_fd, (struct sockaddr*)&gs_server_addr, sizeof(gs_server_addr)) < 0) 
    {
        ssd1681_interface_debug_print("ssd1681: bind failed.\n");
        (void)close(gs_listen_fd);
        
        return 1;
    }
    
    /* listen the port */
    if (listen(gs_listen_fd, 10) < 0) 
    {
        ssd1681_interface_debug_print("ssd1681: listen failed.\n");
        (void)close(gs_listen_fd);
        
        return 1;
    } 
    
    return 0;
}

/**
 * @brief     socket read
 * @param[in] *buf points to a buffer address
 * @param[in] len is the buffer length
 * @return    status code
 *             - 0 success
 *             - 1 read failed
 * @note      none
 */
static uint16_t a_socket_read(uint8_t *buf, uint16_t len)
{
    int n;
    
    /* wait data */
    gs_conn_fd = accept(gs_listen_fd, (struct sockaddr *)NULL, NULL);
    if (gs_conn_fd < 0) 
    {
        ssd1681_interface_debug_print("ssd1681: accept failed.\n");
        (void)close(gs_conn_fd);

        return 1;
    }
    
    /* read data */
    n = recv(gs_conn_fd, buf, len, 0);
    
    /* close the socket */
    (void)close(gs_conn_fd);
    
    return n;
}

/**
 * @brief     signal handler
 * @param[in] signum is the signal number
 * @note      none
 */
static void a_sig_handler(int signum)
{
    if (SIGINT == signum)
    {
        ssd1681_interface_debug_print("ssd1681: close the server.\n");
        (void)close(gs_listen_fd);
        exit(0);
    }
    
    return;
}

/**
 * @brief main function
 * @note  none
 */
int main(void)
{
    uint8_t res;
    
    /* socket init */
    res = a_socket_init();
    if (res)
    {
        ssd1681_interface_debug_print("ssd1681: socket init failed.\n");

        return 1;
    }

    /* shell init && register ssd1681 function */
    shell_init();
    shell_register("ssd1681", ssd1681);
    ssd1681_interface_debug_print("ssd1681: welcome to libdriver ssd1681.\n");

    /* set the signal */
    signal(SIGINT, a_sig_handler);

    while (1)
    {
        /* read uart */
        g_len = a_socket_read(g_buf, 256);
        if (g_len != 0)
        {
            /* run shell */
            res = shell_parse((char *)g_buf, g_len);
            if (res == 0)
            {
                /* run success */
            }
            else if (res == 1)
            {
                ssd1681_interface_debug_print("ssd1681: run failed.\n");
            }
            else if (res == 2)
            {
                ssd1681_interface_debug_print("ssd1681: unknown command.\n");
            }
            else if (res == 3)
            {
                ssd1681_interface_debug_print("ssd1681: length is too long.\n");
            }
            else if (res == 4)
            {
                ssd1681_interface_debug_print("ssd1681: pretreat failed.\n");
            }
            else if (res == 5)
            {
                ssd1681_interface_debug_print("ssd1681: param is invalid.\n");
            }
            else
            {
                ssd1681_interface_debug_print("ssd1681: unknown status code.\n");
            }
        }
    }
}
