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
 * @file      driver_ssd1681.c
 * @brief     driver ssd1681 source file
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

#include "driver_ssd1681.h"
#include "driver_ssd1681_font.h"

/**
 * @brief chip information definition
 */
#define CHIP_NAME                 "Solomon Systech SSD1681"        /**< chip name */
#define MANUFACTURER_NAME         "Solomon Systech"                /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        2.2f                             /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        3.7f                             /**< chip max supply voltage */
#define MAX_CURRENT               500.00f                          /**< chip max current */
#define TEMPERATURE_MIN           -40.0f                           /**< chip min operating temperature */
#define TEMPERATURE_MAX           85.0f                            /**< chip max operating temperature */
#define DRIVER_VERSION            1000                             /**< driver version */

/**
 * @brief chip command data definition
 */
#define SSD1681_CMD          0        /**< command */
#define SSD1681_DATA         1        /**< data */

/**
 * @brief chip command definition
 */
#define SSD1681_CMD_DRIVER_OUTPUT_CONTROL                          0x01        /**< command driver output control */
#define SSD1681_CMD_GATE_DRIVING_VOLTAGE_CONTROL                   0x03        /**< command gate driving voltage control */
#define SSD1681_CMD_SOURCE_DRIVING_VOLTAGE_CONTROL                 0x04        /**< command source driving voltage control */
#define SSD1681_CMD_INITIAL_CODE_SETTING_OTP_PROGRAM               0x08        /**< command initial code setting otp program */
#define SSD1681_CMD_WRITE_REGISTER_FOR_INITIAL_CODE_SETTING        0x09        /**< command write register for initial code setting */
#define SSD1681_CMD_READ_REGISTER_FOR_INITIAL_CODE_SETTING         0x0A        /**< command read register for initial code setting */
#define SSD1681_CMD_BOOSTER_SOFT_START_CONTROL                     0x0C        /**< command booster soft start control */
#define SSD1681_CMD_DEEP_SLEEP_MODE                                0x10        /**< command deep sleep mode */
#define SSD1681_CMD_DATA_ENTRY_MODE_SETTING                        0x11        /**< command data entry mode setting */
#define SSD1681_CMD_SW_RESET                                       0x12        /**< command software reset */
#define SSD1681_CMD_HV_READY_DETECTION                             0x14        /**< command hv ready detection */
#define SSD1681_CMD_VCI_DETECTION                                  0x15        /**< command vci detection */
#define SSD1681_CMD_TEMPERATURE_SENSOR_CONTROL                     0x18        /**< command temperature sensor control */
#define SSD1681_CMD_TEMPERATURE_SENSOR_CONTROL_WRITE               0x1A        /**< command temperature sensor control
                                                                                    (write to temperature register) */
#define SSD1681_CMD_TEMPERATURE_SENSOR_CONTROL_READ                0x1B        /**< command temperature sensor control
                                                                                    (read from temperature register) */
#define SSD1681_CMD_TEMPERATURE_SENSOR_CONTROL_WRITE_EXT           0x1C        /**< command temperature sensor control
                                                                                    (write command to external temperature sensor) */
#define SSD1681_CMD_MASTER_ACTIVATION                              0x20        /**< command master activation */
#define SSD1681_CMD_DISPLAY_UPDATA_CONTROL_1                       0x21        /**< command display update control 1 */
#define SSD1681_CMD_DISPLAY_UPDATA_CONTROL_2                       0x22        /**< command display update control 2 */
#define SSD1681_CMD_WRITE_RAM_BLACK                                0x24        /**< command write ram(black white) */
#define SSD1681_CMD_WRITE_RAM_RED                                  0x26        /**< command write ram(read) */
#define SSD1681_CMD_READ_RAM                                       0x27        /**< command read ram */
#define SSD1681_CMD_VCOM_SENSE                                     0x28        /**< command vcom sense */
#define SSD1681_CMD_VCOM_SENSE_DURATION                            0x29        /**< command vcom sense duration */
#define SSD1681_CMD_PROGRAM_VCOM_OTP                               0x2A        /**< command program vcom otp duration */
#define SSD1681_CMD_WRITE_REGISTER_FOR_VCOM_CONTROL                0x2B        /**< command write register for vcom control */
#define SSD1681_CMD_WRITE_VCOM_REGISTER                            0x2C        /**< command write vcom register */
#define SSD1681_CMD_OTP_REGISTER_READ_FOR_DISPLAY_OPTION           0x2D        /**< command otp register read for display option */
#define SSD1681_CMD_USER_ID_READ                                   0x2E        /**< command user id read */
#define SSD1681_CMD_STATUS_BIT_READ                                0x2F        /**< command status bit read */
#define SSD1681_CMD_PROGRAM_WS_OTP                                 0x30        /**< command program ws otp */
#define SSD1681_CMD_LOAD_WS_OTP                                    0x31        /**< command load ws otp */
#define SSD1681_CMD_WRITE_LUT_REGISTER                             0x32        /**< command write lut register */
#define SSD1681_CMD_CRC_CALCULATION                                0x34        /**< command crc calculation */
#define SSD1681_CMD_CRC_STATUS_READ                                0x35        /**< command crc status read */
#define SSD1681_CMD_PROGRAM_OTP_SELECTION                          0x36        /**< command program otp selection */
#define SSD1681_CMD_WRITE_REGISTER_FOR_DISPLAY_OPTION              0x37        /**< command write register for display option */
#define SSD1681_CMD_WRITE_REGISTER_FOR_USER_ID                     0x38        /**< command write register for user id */
#define SSD1681_CMD_OTP_PROGRAM_MODE                               0x39        /**< command otp program mode */
#define SSD1681_CMD_BORDER_WAVEFORM_CONTROL                        0x3C        /**< command border waveform control */
#define SSD1681_CMD_END_OPTION                                     0x3F        /**< command end option */
#define SSD1681_CMD_READ_RAM_OPTION                                0x41        /**< command read ram option */
#define SSD1681_CMD_SET_RAM_X                                      0x44        /**< command set ram x */
#define SSD1681_CMD_SET_RAM_Y                                      0x45        /**< command set ram y */
#define SSD1681_CMD_AUTO_WRITE_RED_RAM_FOR_REGULAR_PATTERN         0x46        /**< command auto write red ram for regular pattern */
#define SSD1681_CMD_AUTO_WRITE_BW_RAM_FOR_REGULAR_PATTERN          0x47        /**< command auto write b/w ram for regular pattern */
#define SSD1681_CMD_SET_RAM_X_ADDRESS_COUNTER                      0x4E        /**< command set ram x address counter */
#define SSD1681_CMD_SET_RAM_Y_ADDRESS_COUNTER                      0x4F        /**< command set ram y address counter */
#define SSD1681_CMD_NOP                                            0x7F        /**< command nop */

/**
 * @brief     write multiple bytes
 * @param[in] *handle pointer to an ssd1681 handle structure
 * @param[in] command set command
 * @param[in] *data pointer to a data buffer
 * @param[in] len data length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
static uint8_t a_ssd1681_multiple_write_byte(ssd1681_handle_t *handle, uint8_t command, uint8_t *data, uint16_t len)
{
    uint8_t res;
    uint8_t value;
    uint16_t i;
    
    value = 1;                                                     /* set value 1 */
    for (i = 0; i < SSD1681_BUSY_MAX_RETRY_TIMES; i++)             /* SSD1681_BUSY_MAX_RETRY_TIMES times */
    {
        res = handle->busy_gpio_read(&value);                      /* read the busy */
        if (res != 0)                                              /* check error */
        {
            return 1;                                              /* return error */
        }
        if (value == 1)                                            /* if busy */
        {
            handle->delay_ms(SSD1681_BUSY_MAX_DELAY_MS);           /* delay SSD1681_BUSY_MAX_DELAY_MS */
        }
        else
        {
            break;                                                 /* break */
        }
    }
    if (value == 1)                                                /* check the value */
    {
        return 1;                                                  /* return error */
    }
    
    res = handle->spi_cmd_data_gpio_write(SSD1681_CMD);            /* write command */
    if (res != 0)                                                  /* check error */
    {
        return 1;                                                  /* return error */
    }
    res = handle->spi_write_cmd(&command, 1);                      /* write command */
    if (res != 0)                                                  /* check error */
    {
        return 1;                                                  /* return error */
    }
    if (len != 0)                                                  /* check the length */
    {
        res = handle->spi_cmd_data_gpio_write(SSD1681_DATA);       /* write data */
        if (res != 0)                                              /* check error */
        {
            return 1;                                              /* return error */
        }
        for (i = 0; i < len; i++)                                  /* len times */
        {
            if (handle->spi_write_cmd(data + i, 1) != 0)           /* write command */
            {
                return 1;                                          /* return error */
            }
        }
    }
    
    return 0;                                                      /* success return 0 */
}

/**
 * @brief      read multiple bytes
 * @param[in]  *handle pointer to an ssd1681 handle structure
 * @param[in]  command set command
 * @param[out] *data pointer to a data buffer
 * @param[in]  len data length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
static uint8_t a_ssd1681_multiple_read_byte(ssd1681_handle_t *handle, uint8_t command, uint8_t *data, uint16_t len)
{
    uint8_t res;
    uint8_t value;
    uint16_t i;
    
    value = 1;                                                     /* set value 1 */
    for (i = 0; i < SSD1681_BUSY_MAX_RETRY_TIMES; i++)             /* SSD1681_BUSY_MAX_RETRY_TIMES times */
    {
        res = handle->busy_gpio_read(&value);                      /* read the busy */
        if (res != 0)                                              /* check error */
        {
            return 1;                                              /* return error */
        }
        if (value == 1)                                            /* if busy */
        {
            handle->delay_ms(SSD1681_BUSY_MAX_DELAY_MS);           /* delay SSD1681_BUSY_MAX_DELAY_MS */
        }
        else
        {
            break;                                                 /* break */
        }
    }
    if (value == 1)                                                /* check the value */
    {
        return 1;                                                  /* return error */
    }
    
    res = handle->spi_cmd_data_gpio_write(SSD1681_CMD);            /* write command */
    if (res != 0)                                                  /* check error */
    {
        return 1;                                                  /* return error */
    }
    res = handle->spi_write_cmd(&command, 1);                      /* write command */
    if (res != 0)                                                  /* check error */
    {
        return 1;                                                  /* return error */
    }
    if (len != 0)                                                  /* check the length */
    {
        res = handle->spi_cmd_data_gpio_write(SSD1681_DATA);       /* write data */
        if (res != 0)                                              /* check error */
        {
            return 1;                                              /* return error */
        }
        for (i = 0; i < len; i++)                                  /* len times */
        {
            if (handle->spi_read_cmd(data + i, 1) != 0)            /* read command */
            {
                return 1;                                          /* return error */
            }
        }
    }
    
    return 0;                                                      /* success return 0 */
}

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
uint8_t ssd1681_set_driver_output(ssd1681_handle_t *handle, uint16_t mux, ssd1681_bool_t gd, ssd1681_bool_t sm, ssd1681_bool_t tb)
{
    uint8_t res;
    uint8_t b;
    uint8_t buf[3];
    
    if (handle == NULL)                                                                                       /* check handle */
    {
        return 2;                                                                                             /* return error */
    }
    if (handle->inited != 1)                                                                                  /* check handle initialization */
    {
        return 3;                                                                                             /* return error */
    }
    if (mux > 0x1FF)                                                                                          /* check mux */
    {
        handle->debug_print("ssd1681: mux is invalid.\n");                                                    /* mux is invalid */
        
        return 4;                                                                                             /* return error */
    }
    
    buf[0] = (mux >> 0) & 0xFF;                                                                               /* set mux */
    buf[1] = (mux >> 8) & 0x01;                                                                               /* set mux */
    b = 0;                                                                                                    /* init 0 */
    if (gd != 0)                                                                                              /* check the gd */
    {
        b |= 1 << 2;                                                                                          /* set the gd */
    }
    if (sm != 0)                                                                                              /* check the sm */
    {
        b |= 1 << 1;                                                                                          /* set the sm */
    }
    if (tb != 0)                                                                                              /* check the tb */
    {
        b |= 1 << 0;                                                                                          /* set the tb */
    }
    buf[2] = b;                                                                                               /* set the b */
  
    res = a_ssd1681_multiple_write_byte(handle, SSD1681_CMD_DRIVER_OUTPUT_CONTROL, (uint8_t *)buf, 3);        /* write byte */
    if (res != 0)                                                                                             /* check the result */
    {
        handle->debug_print("ssd1681: multiple write byte failed.\n");                                        /* multiple write byte failed */
        
        return 1;                                                                                             /* return error */
    }
    
    return 0;                                                                                                 /* success return 0 */
}

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
uint8_t ssd1681_set_gate_driving_voltage(ssd1681_handle_t *handle, ssd1681_gate_driving_voltage_t voltage)
{
    uint8_t res;
    uint8_t buf[1];
    
    if (handle == NULL)                                                                                              /* check handle */
    {
        return 2;                                                                                                    /* return error */
    }
    if (handle->inited != 1)                                                                                         /* check handle initialization */
    {
        return 3;                                                                                                    /* return error */
    }
    
    buf[0] = voltage;                                                                                                /* set the voltage */
    res = a_ssd1681_multiple_write_byte(handle, SSD1681_CMD_GATE_DRIVING_VOLTAGE_CONTROL, (uint8_t *)buf, 1);        /* write byte */
    if (res != 0)                                                                                                    /* check the result */
    {
        handle->debug_print("ssd1681: multiple write byte failed.\n");                                               /* multiple write byte failed */
        
        return 1;                                                                                                    /* return error */
    }
    
    return 0;                                                                                                        /* success return 0 */
}

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
uint8_t ssd1681_set_source_driving_voltage(ssd1681_handle_t *handle, ssd1681_vsh_t vsh1, ssd1681_vsh_t vsh2, ssd1681_vsl_t vsl)
{
    uint8_t res;
    uint8_t buf[3];
    
    if (handle == NULL)                                                                                              /* check handle */
    {
        return 2;                                                                                                    /* return error */
    }
    if (handle->inited != 1)                                                                                         /* check handle initialization */
    {
        return 3;                                                                                                    /* return error */
    }
    
    buf[0] = vsh1;                                                                                                   /* set vsh1 */
    buf[1] = vsh2;                                                                                                   /* set vsh2 */
    buf[2] = vsl;                                                                                                    /* set vsl */
    res = a_ssd1681_multiple_write_byte(handle, SSD1681_CMD_SOURCE_DRIVING_VOLTAGE_CONTROL, (uint8_t *)buf, 3);      /* write byte */
    if (res != 0)                                                                                                    /* check the result */
    {
        handle->debug_print("ssd1681: multiple write byte failed.\n");                                               /* multiple write byte failed */
        
        return 1;                                                                                                    /* return error */
    }
    
    return 0;                                                                                                        /* success return 0 */
}

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
uint8_t ssd1681_otp_initial(ssd1681_handle_t *handle)
{
    uint8_t res;
    
    if (handle == NULL)                                                                                      /* check handle */
    {
        return 2;                                                                                            /* return error */
    }
    if (handle->inited != 1)                                                                                 /* check handle initialization */
    {
        return 3;                                                                                            /* return error */
    }
    
    res = a_ssd1681_multiple_write_byte(handle, SSD1681_CMD_INITIAL_CODE_SETTING_OTP_PROGRAM, NULL, 0);      /* write byte */
    if (res != 0)                                                                                            /* check the result */
    {
        handle->debug_print("ssd1681: multiple write byte failed.\n");                                       /* multiple write byte failed */
        
        return 1;                                                                                            /* return error */
    }
    
    return 0;                                                                                                /* success return 0 */
}

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
uint8_t ssd1681_otp_initial_write(ssd1681_handle_t *handle, uint8_t param[4])
{
    uint8_t res;
    
    if (handle == NULL)                                                                                                /* check handle */
    {
        return 2;                                                                                                      /* return error */
    }
    if (handle->inited != 1)                                                                                           /* check handle initialization */
    {
        return 3;                                                                                                      /* return error */
    }
    
    res = a_ssd1681_multiple_write_byte(handle, SSD1681_CMD_WRITE_REGISTER_FOR_INITIAL_CODE_SETTING, param, 4);        /* write byte */
    if (res != 0)                                                                                                      /* check the result */
    {
        handle->debug_print("ssd1681: multiple write byte failed.\n");                                                 /* multiple write byte failed */
        
        return 1;                                                                                                      /* return error */
    }
    
    return 0;                                                                                                          /* success return 0 */
}

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
uint8_t ssd1681_otp_initial_read(ssd1681_handle_t *handle)
{
    uint8_t res;
    
    if (handle == NULL)                                                                                             /* check handle */
    {
        return 2;                                                                                                   /* return error */
    }
    if (handle->inited != 1)                                                                                        /* check handle initialization */
    {
        return 3;                                                                                                   /* return error */
    }
    
    res = a_ssd1681_multiple_read_byte(handle, SSD1681_CMD_READ_REGISTER_FOR_INITIAL_CODE_SETTING, NULL, 0);        /* read byte */
    if (res != 0)                                                                                                   /* check the result */
    {
        handle->debug_print("ssd1681: multiple read byte failed.\n");                                               /* multiple read byte failed */
        
        return 1;                                                                                                   /* return error */
    }
    
    return 0;                                                                                                       /* success return 0 */
}

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
                                       uint8_t phase3, uint8_t duration)
{
    uint8_t res;
    uint8_t buf[4];
    
    if (handle == NULL)                                                                                 /* check handle */
    {
        return 2;                                                                                       /* return error */
    }
    if (handle->inited != 1)                                                                            /* check handle initialization */
    {
        return 3;                                                                                       /* return error */
    }
    
    buf[0] = 0x80 | phase1;                                                                             /* set the phase1 */
    buf[1] = 0x80 | phase2;                                                                             /* set the phase2 */
    buf[2] = 0x80 | phase3;                                                                             /* set the phase3 */
    buf[3] = duration;                                                                                  /* set the duration */
    res = a_ssd1681_multiple_write_byte(handle, SSD1681_CMD_BOOSTER_SOFT_START_CONTROL, buf, 4);        /* write byte */
    if (res != 0)                                                                                       /* check the result */
    {
        handle->debug_print("ssd1681: multiple write byte failed.\n");                                  /* multiple write byte failed */
        
        return 1;                                                                                       /* return error */
    }
    
    return 0;                                                                                           /* success return 0 */
}

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
uint8_t ssd1681_set_mode(ssd1681_handle_t *handle, ssd1681_mode_t mode)
{
    uint8_t res;
    uint8_t buf[1];
    
    if (handle == NULL)                                                                      /* check handle */
    {
        return 2;                                                                            /* return error */
    }
    if (handle->inited != 1)                                                                 /* check handle initialization */
    {
        return 3;                                                                            /* return error */
    }
    
    buf[0] = mode;                                                                           /* set the mode */
    res = a_ssd1681_multiple_write_byte(handle, SSD1681_CMD_DEEP_SLEEP_MODE, buf, 1);        /* write byte */
    if (res != 0)                                                                            /* check the result */
    {
        handle->debug_print("ssd1681: multiple write byte failed.\n");                       /* multiple write byte failed */
        
        return 1;                                                                            /* return error */
    }
    
    return 0;                                                                                /* success return 0 */
}

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
uint8_t ssd1681_set_data_entry_mode(ssd1681_handle_t *handle, ssd1681_address_mode_t mode, ssd1681_address_direction_t direction)
{
    uint8_t res;
    uint8_t buf[1];
    
    if (handle == NULL)                                                                              /* check handle */
    {
        return 2;                                                                                    /* return error */
    }
    if (handle->inited != 1)                                                                         /* check handle initialization */
    {
        return 3;                                                                                    /* return error */
    }
    
    buf[0] = (uint8_t)((mode << 0) | (direction << 2));                                              /* set the config */
    res = a_ssd1681_multiple_write_byte(handle, SSD1681_CMD_DATA_ENTRY_MODE_SETTING, buf, 1);        /* write byte */
    if (res != 0)                                                                                    /* check the result */
    {
        handle->debug_print("ssd1681: multiple write byte failed.\n");                               /* multiple write byte failed */
        
        return 1;                                                                                    /* return error */
    }
    
    return 0;                                                                                        /* success return 0 */
}

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
uint8_t ssd1681_software_reset(ssd1681_handle_t *handle)
{
    uint8_t res;
    
    if (handle == NULL)                                                                /* check handle */
    {
        return 2;                                                                      /* return error */
    }
    if (handle->inited != 1)                                                           /* check handle initialization */
    {
        return 3;                                                                      /* return error */
    }
    
    res = a_ssd1681_multiple_write_byte(handle, SSD1681_CMD_SW_RESET, NULL, 0);        /* write byte */
    if (res != 0)                                                                      /* check the result */
    {
        handle->debug_print("ssd1681: multiple write byte failed.\n");                 /* multiple write byte failed */
        
        return 1;                                                                      /* return error */
    }
    
    return 0;                                                                          /* success return 0 */
}

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
uint8_t ssd1681_set_hv_ready_detection(ssd1681_handle_t *handle, uint8_t cool_down_duration, uint8_t cool_down_loop_num)
{
    uint8_t res;
    uint8_t buf[1];
    
    if (handle == NULL)                                                                         /* check handle */
    {
        return 2;                                                                               /* return error */
    }
    if (handle->inited != 1)                                                                    /* check handle initialization */
    {
        return 3;                                                                               /* return error */
    }
    if (cool_down_duration > 0x7)                                                               /* check the cool_down_duration */
    {
        handle->debug_print("ssd1681: cool_down_duration is over 7.\n");                        /* cool_down_duration is over 7 */
        
        return 4;                                                                               /* return error */
    }
    if (cool_down_loop_num > 0x7)                                                               /* check the cool_down_loop_num */
    {
        handle->debug_print("ssd1681: cool_down_loop_num is over 7.\n");                        /* cool_down_loop_num is over 7 */
        
        return 5;                                                                               /* return error */
    }
    
    buf[0] = (cool_down_duration << 4) | (cool_down_loop_num << 0);                             /* set the config */
    res = a_ssd1681_multiple_write_byte(handle, SSD1681_CMD_HV_READY_DETECTION, buf, 1);        /* write byte */
    if (res != 0)                                                                               /* check the result */
    {
        handle->debug_print("ssd1681: multiple write byte failed.\n");                          /* multiple write byte failed */
        
        return 1;                                                                               /* return error */
    }
    
    return 0;                                                                                   /* success return 0 */
}

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
uint8_t ssd1681_set_vci_detection(ssd1681_handle_t *handle, ssd1681_vci_level_t level)
{
    uint8_t res;
    uint8_t buf[1];
    
    if (handle == NULL)                                                                    /* check handle */
    {
        return 2;                                                                          /* return error */
    }
    if (handle->inited != 1)                                                               /* check handle initialization */
    {
        return 3;                                                                          /* return error */
    }
    
    buf[0] = level;                                                                        /* set the level */
    res = a_ssd1681_multiple_write_byte(handle, SSD1681_CMD_VCI_DETECTION, buf, 1);        /* write byte */
    if (res != 0)                                                                          /* check the result */
    {
        handle->debug_print("ssd1681: multiple write byte failed.\n");                     /* multiple write byte failed */
        
        return 1;                                                                          /* return error */
    }
    
    return 0;                                                                              /* success return 0 */
}

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
uint8_t ssd1681_set_temperature_sensor(ssd1681_handle_t *handle, ssd1681_temperature_sensor_t sensor)
{
    uint8_t res;
    uint8_t buf[1];
    
    if (handle == NULL)                                                                                 /* check handle */
    {
        return 2;                                                                                       /* return error */
    }
    if (handle->inited != 1)                                                                            /* check handle initialization */
    {
        return 3;                                                                                       /* return error */
    }
    
    buf[0] = sensor;                                                                                    /* set the temperature sensor */
    res = a_ssd1681_multiple_write_byte(handle, SSD1681_CMD_TEMPERATURE_SENSOR_CONTROL, buf, 1);        /* write byte */
    if (res != 0)                                                                                       /* check the result */
    {
        handle->debug_print("ssd1681: multiple write byte failed.\n");                                  /* multiple write byte failed */
        
        return 1;                                                                                       /* return error */
    }
    
    return 0;                                                                                           /* success return 0 */
}

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
uint8_t ssd1681_write_temperature_sensor(ssd1681_handle_t *handle, uint16_t control)
{
    uint8_t res;
    uint8_t buf[2];
    
    if (handle == NULL)                                                                                       /* check handle */
    {
        return 2;                                                                                             /* return error */
    }
    if (handle->inited != 1)                                                                                  /* check handle initialization */
    {
        return 3;                                                                                             /* return error */
    }
    if (control > 0xFFF)                                                                                      /* check the control */
    {
        handle->debug_print("ssd1681: control is over 0xFFF.\n");                                             /* control is over 0xFFF */
        
        return 4;                                                                                             /* return error */
    }
    
    buf[0] = (control >> 4) & 0xFF;                                                                           /* set the temperature data */
    buf[1] = ((control >> 0) << 4) & 0xFF;                                                                    /* set the temperature data */
    res = a_ssd1681_multiple_write_byte(handle, SSD1681_CMD_TEMPERATURE_SENSOR_CONTROL_WRITE, buf, 2);        /* write byte */
    if (res != 0)                                                                                             /* check the result */
    {
        handle->debug_print("ssd1681: multiple write byte failed.\n");                                        /* multiple write byte failed */
        
        return 1;                                                                                             /* return error */
    }
    
    return 0;                                                                                                 /* success return 0 */
}

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
uint8_t ssd1681_read_temperature_sensor(ssd1681_handle_t *handle, uint16_t *control)
{
    uint8_t res;
    uint8_t buf[2];
    
    if (handle == NULL)                                                                                     /* check handle */
    {
        return 2;                                                                                           /* return error */
    }
    if (handle->inited != 1)                                                                                /* check handle initialization */
    {
        return 3;                                                                                           /* return error */
    }
    
    res = a_ssd1681_multiple_read_byte(handle, SSD1681_CMD_TEMPERATURE_SENSOR_CONTROL_READ, buf, 2);        /* read byte */
    if (res != 0)                                                                                           /* check the result */
    {
        handle->debug_print("ssd1681: multiple read byte failed.\n");                                       /* multiple read byte failed */
        
        return 1;                                                                                           /* return error */
    }
    *control = (((uint16_t)buf[0]) << 4) | ((buf[1] >> 4) & 0xFF);                                          /* set the control */
    
    return 0;                                                                                               /* success return 0 */
}

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
uint8_t ssd1681_write_temperature_sensor_ext(ssd1681_handle_t *handle, uint8_t param[3])
{
    uint8_t res;
    
    if (handle == NULL)                                                                                             /* check handle */
    {
        return 2;                                                                                                   /* return error */
    }
    if (handle->inited != 1)                                                                                        /* check handle initialization */
    {
        return 3;                                                                                                   /* return error */
    }
    
    res = a_ssd1681_multiple_write_byte(handle, SSD1681_CMD_TEMPERATURE_SENSOR_CONTROL_WRITE_EXT, param, 3);        /* write byte */
    if (res != 0)                                                                                                   /* check the result */
    {
        handle->debug_print("ssd1681: multiple write byte failed.\n");                                              /* multiple write byte failed */
        
        return 1;                                                                                                   /* return error */
    }
    
    return 0;                                                                                                       /* success return 0 */
}

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
uint8_t ssd1681_set_master_activate(ssd1681_handle_t *handle)
{
    uint8_t res;
    
    if (handle == NULL)                                                                         /* check handle */
    {
        return 2;                                                                               /* return error */
    }
    if (handle->inited != 1)                                                                    /* check handle initialization */
    {
        return 3;                                                                               /* return error */
    }
    
    res = a_ssd1681_multiple_write_byte(handle, SSD1681_CMD_MASTER_ACTIVATION, NULL, 0);        /* write byte */
    if (res != 0)                                                                               /* check the result */
    {
        handle->debug_print("ssd1681: multiple write byte failed.\n");                          /* multiple write byte failed */
        
        return 1;                                                                               /* return error */
    }
    
    return 0;                                                                                   /* success return 0 */
}

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
uint8_t ssd1681_set_display_update_control(ssd1681_handle_t *handle, ssd1681_display_control_t red_control, ssd1681_display_control_t black_control)
{
    uint8_t res;
    uint8_t buf[1];
    
    if (handle == NULL)                                                                               /* check handle */
    {
        return 2;                                                                                     /* return error */
    }
    if (handle->inited != 1)                                                                          /* check handle initialization */
    {
        return 3;                                                                                     /* return error */
    }
    
    buf[0] = (uint8_t)((red_control << 4) | (black_control << 0));                                    /* set the display update control */
    res = a_ssd1681_multiple_write_byte(handle, SSD1681_CMD_DISPLAY_UPDATA_CONTROL_1, buf, 1);        /* write byte */
    if (res != 0)                                                                                     /* check the result */
    {
        handle->debug_print("ssd1681: multiple write byte failed.\n");                                /* multiple write byte failed */
        
        return 1;                                                                                     /* return error */
    }
    
    return 0;                                                                                         /* success return 0 */
}

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
uint8_t ssd1681_set_display_sequence(ssd1681_handle_t *handle, ssd1681_display_sequence_t sequence)
{
    uint8_t res;
    uint8_t buf[1];
    
    if (handle == NULL)                                                                               /* check handle */
    {
        return 2;                                                                                     /* return error */
    }
    if (handle->inited != 1)                                                                          /* check handle initialization */
    {
        return 3;                                                                                     /* return error */
    }
    
    buf[0] = sequence;                                                                                /* set the display sequence */
    res = a_ssd1681_multiple_write_byte(handle, SSD1681_CMD_DISPLAY_UPDATA_CONTROL_2, buf, 1);        /* write byte */
    if (res != 0)                                                                                     /* check the result */
    {
        handle->debug_print("ssd1681: multiple write byte failed.\n");                                /* multiple write byte failed */
        
        return 1;                                                                                     /* return error */
    }
    
    return 0;                                                                                         /* success return 0 */
}

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
uint8_t ssd1681_set_black_ram(ssd1681_handle_t *handle)
{
    uint8_t res;
    
    if (handle == NULL)                                                                       /* check handle */
    {
        return 2;                                                                             /* return error */
    }
    if (handle->inited != 1)                                                                  /* check handle initialization */
    {
        return 3;                                                                             /* return error */
    }
    
    res = a_ssd1681_multiple_write_byte(handle, SSD1681_CMD_WRITE_RAM_BLACK, NULL, 0);        /* write byte */
    if (res != 0)                                                                             /* check the result */
    {
        handle->debug_print("ssd1681: multiple write byte failed.\n");                        /* multiple write byte failed */
        
        return 1;                                                                             /* return error */
    }
    
    return 0;                                                                                 /* success return 0 */
}

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
uint8_t ssd1681_set_red_ram(ssd1681_handle_t *handle)
{
    uint8_t res;
    
    if (handle == NULL)                                                                     /* check handle */
    {
        return 2;                                                                           /* return error */
    }
    if (handle->inited != 1)                                                                /* check handle initialization */
    {
        return 3;                                                                           /* return error */
    }
    
    res = a_ssd1681_multiple_write_byte(handle, SSD1681_CMD_WRITE_RAM_RED, NULL, 0);        /* write byte */
    if (res != 0)                                                                           /* check the result */
    {
        handle->debug_print("ssd1681: multiple write byte failed.\n");                      /* multiple write byte failed */
        
        return 1;                                                                           /* return error */
    }
    
    return 0;                                                                               /* success return 0 */
}

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
uint8_t ssd1681_get_ram(ssd1681_handle_t *handle)
{
    uint8_t res;
    
    if (handle == NULL)                                                                /* check handle */
    {
        return 2;                                                                      /* return error */
    }
    if (handle->inited != 1)                                                           /* check handle initialization */
    {
        return 3;                                                                      /* return error */
    }
    
    res = a_ssd1681_multiple_write_byte(handle, SSD1681_CMD_READ_RAM, NULL, 0);        /* write byte */
    if (res != 0)                                                                      /* check the result */
    {
        handle->debug_print("ssd1681: multiple write byte failed.\n");                 /* multiple write byte failed */
        
        return 1;                                                                      /* return error */
    }
    
    return 0;                                                                          /* success return 0 */
}

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
uint8_t ssd1681_set_enter_vcom_sense(ssd1681_handle_t *handle)
{
    uint8_t res;
    
    if (handle == NULL)                                                                  /* check handle */
    {
        return 2;                                                                        /* return error */
    }
    if (handle->inited != 1)                                                             /* check handle initialization */
    {
        return 3;                                                                        /* return error */
    }
    
    res = a_ssd1681_multiple_write_byte(handle, SSD1681_CMD_VCOM_SENSE, NULL, 0);        /* write byte */
    if (res != 0)                                                                        /* check the result */
    {
        handle->debug_print("ssd1681: multiple write byte failed.\n");                   /* multiple write byte failed */
        
        return 1;                                                                        /* return error */
    }
    
    return 0;                                                                            /* success return 0 */
}

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
uint8_t ssd1681_set_vcom_sense_duration(ssd1681_handle_t *handle, uint8_t duration)
{
    uint8_t res;
    uint8_t buf[1];
    
    if (handle == NULL)                                                                          /* check handle */
    {
        return 2;                                                                                /* return error */
    }
    if (handle->inited != 1)                                                                     /* check handle initialization */
    {
        return 3;                                                                                /* return error */
    }
    
    buf[0] = duration;                                                                           /* set the duration */
    res = a_ssd1681_multiple_write_byte(handle, SSD1681_CMD_VCOM_SENSE_DURATION, buf, 1);        /* write byte */
    if (res != 0)                                                                                /* check the result */
    {
        handle->debug_print("ssd1681: multiple write byte failed.\n");                           /* multiple write byte failed */
        
        return 1;                                                                                /* return error */
    }
    
    return 0;                                                                                    /* success return 0 */
}

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
uint8_t ssd1681_otp_program_vcom(ssd1681_handle_t *handle)
{
    uint8_t res;
    
    if (handle == NULL)                                                                        /* check handle */
    {
        return 2;                                                                              /* return error */
    }
    if (handle->inited != 1)                                                                   /* check handle initialization */
    {
        return 3;                                                                              /* return error */
    }
    
    res = a_ssd1681_multiple_write_byte(handle, SSD1681_CMD_PROGRAM_VCOM_OTP, NULL, 0);        /* write byte */
    if (res != 0)                                                                              /* check the result */
    {
        handle->debug_print("ssd1681: multiple write byte failed.\n");                         /* multiple write byte failed */
        
        return 1;                                                                              /* return error */
    }
    
    return 0;                                                                                  /* success return 0 */
}

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
uint8_t ssd1681_set_vcom_control_reg(ssd1681_handle_t *handle)
{
    uint8_t res;
    uint8_t buf[2];
    
    if (handle == NULL)                                                                                      /* check handle */
    {
        return 2;                                                                                            /* return error */
    }
    if (handle->inited != 1)                                                                                 /* check handle initialization */
    {
        return 3;                                                                                            /* return error */
    }
    
    buf[0] = 0x04;                                                                                           /* command 1 */
    buf[1] = 0x63;                                                                                           /* command 2 */
    res = a_ssd1681_multiple_write_byte(handle, SSD1681_CMD_WRITE_REGISTER_FOR_VCOM_CONTROL, buf, 2);        /* write byte */
    if (res != 0)                                                                                            /* check the result */
    {
        handle->debug_print("ssd1681: multiple write byte failed.\n");                                       /* multiple write byte failed */
        
        return 1;                                                                                            /* return error */
    }
    
    return 0;                                                                                                /* success return 0 */
}

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
uint8_t ssd1681_set_vcom_register(ssd1681_handle_t *handle, ssd1681_vcom_t vcom)
{
    uint8_t res;
    uint8_t buf[1];
    
    if (handle == NULL)                                                                          /* check handle */
    {
        return 2;                                                                                /* return error */
    }
    if (handle->inited != 1)                                                                     /* check handle initialization */
    {
        return 3;                                                                                /* return error */
    }
    
    buf[0] = vcom;                                                                               /* set the vcom */
    res = a_ssd1681_multiple_write_byte(handle, SSD1681_CMD_WRITE_VCOM_REGISTER, buf, 1);        /* write byte */
    if (res != 0)                                                                                /* check the result */
    {
        handle->debug_print("ssd1681: multiple write byte failed.\n");                           /* multiple write byte failed */
        
        return 1;                                                                                /* return error */
    }
    
    return 0;                                                                                    /* success return 0 */
}

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
uint8_t ssd1681_otp_read_register(ssd1681_handle_t *handle, uint8_t param[11])
{
    uint8_t res;
    
    if (handle == NULL)                                                                                             /* check handle */
    {
        return 2;                                                                                                   /* return error */
    }
    if (handle->inited != 1)                                                                                        /* check handle initialization */
    {
        return 3;                                                                                                   /* return error */
    }
    
    res = a_ssd1681_multiple_read_byte(handle, SSD1681_CMD_OTP_REGISTER_READ_FOR_DISPLAY_OPTION, param, 11);        /* read byte */
    if (res != 0)                                                                                                   /* check the result */
    {
        handle->debug_print("ssd1681: multiple read byte failed.\n");                                               /* multiple read byte failed */
        
        return 1;                                                                                                   /* return error */
    }
    
    return 0;                                                                                                       /* success return 0 */
}

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
uint8_t ssd1681_get_user_id(ssd1681_handle_t *handle, uint8_t id[10])
{
    uint8_t res;
    
    if (handle == NULL)                                                                  /* check handle */
    {
        return 2;                                                                        /* return error */
    }
    if (handle->inited != 1)                                                             /* check handle initialization */
    {
        return 3;                                                                        /* return error */
    }
    
    res = a_ssd1681_multiple_read_byte(handle, SSD1681_CMD_USER_ID_READ, id, 10);        /* read byte */
    if (res != 0)                                                                        /* check the result */
    {
        handle->debug_print("ssd1681: multiple read byte failed.\n");                    /* multiple read byte failed */
        
        return 1;                                                                        /* return error */
    }
    
    return 0;                                                                            /* success return 0 */
}

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
uint8_t ssd1681_get_status(ssd1681_handle_t *handle, uint8_t *status)
{
    uint8_t res;
    
    if (handle == NULL)                                                                        /* check handle */
    {
        return 2;                                                                              /* return error */
    }
    if (handle->inited != 1)                                                                   /* check handle initialization */
    {
        return 3;                                                                              /* return error */
    }
    
    res = a_ssd1681_multiple_read_byte(handle, SSD1681_CMD_STATUS_BIT_READ, status, 1);        /* read byte */
    if (res != 0)                                                                              /* check the result */
    {
        handle->debug_print("ssd1681: multiple read byte failed.\n");                          /* multiple read byte failed */
        
        return 1;                                                                              /* return error */
    }
    
    return 0;                                                                                  /* success return 0 */
}

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
uint8_t ssd1681_otp_program_waveform(ssd1681_handle_t *handle)
{
    uint8_t res;
    
    if (handle == NULL)                                                                      /* check handle */
    {
        return 2;                                                                            /* return error */
    }
    if (handle->inited != 1)                                                                 /* check handle initialization */
    {
        return 3;                                                                            /* return error */
    }
    
    res = a_ssd1681_multiple_write_byte(handle, SSD1681_CMD_PROGRAM_WS_OTP, NULL, 0);        /* write byte */
    if (res != 0)                                                                            /* check the result */
    {
        handle->debug_print("ssd1681: multiple write byte failed.\n");                       /* multiple write byte failed */
        
        return 1;                                                                            /* return error */
    }
    
    return 0;                                                                                /* success return 0 */
}

/**
 * @brief     load otp of waveform setting
 * @param[in] *handle pointer to an ssd1681 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 otp load waveform failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ssd1681_otp_load_waveform(ssd1681_handle_t *handle)
{
    uint8_t res;
    
    if (handle == NULL)                                                                   /* check handle */
    {
        return 2;                                                                         /* return error */
    }
    if (handle->inited != 1)                                                              /* check handle initialization */
    {
        return 3;                                                                         /* return error */
    }
    
    res = a_ssd1681_multiple_write_byte(handle, SSD1681_CMD_LOAD_WS_OTP, NULL, 0);        /* write byte */
    if (res != 0)                                                                         /* check the result */
    {
        handle->debug_print("ssd1681: multiple write byte failed.\n");                    /* multiple write byte failed */
        
        return 1;                                                                         /* return error */
    }
    
    return 0;                                                                             /* success return 0 */
}

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
uint8_t ssd1681_set_lut_register(ssd1681_handle_t *handle, uint8_t *reg, uint16_t len)
{
    uint8_t res;
    
    if (handle == NULL)                                                                           /* check handle */
    {
        return 2;                                                                                 /* return error */
    }
    if (handle->inited != 1)                                                                      /* check handle initialization */
    {
        return 3;                                                                                 /* return error */
    }
    
    res = a_ssd1681_multiple_write_byte(handle, SSD1681_CMD_WRITE_LUT_REGISTER, reg, len);        /* write byte */
    if (res != 0)                                                                                 /* check the result */
    {
        handle->debug_print("ssd1681: multiple write byte failed.\n");                            /* multiple write byte failed */
        
        return 1;                                                                                 /* return error */
    }
    
    return 0;                                                                                     /* success return 0 */
}

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
uint8_t ssd1681_set_crc_calculation(ssd1681_handle_t *handle)
{
    uint8_t res;
    
    if (handle == NULL)                                                                       /* check handle */
    {
        return 2;                                                                             /* return error */
    }
    if (handle->inited != 1)                                                                  /* check handle initialization */
    {
        return 3;                                                                             /* return error */
    }
    
    res = a_ssd1681_multiple_write_byte(handle, SSD1681_CMD_CRC_CALCULATION, NULL, 0);        /* write byte */
    if (res != 0)                                                                             /* check the result */
    {
        handle->debug_print("ssd1681: multiple write byte failed.\n");                        /* multiple write byte failed */
        
        return 1;                                                                             /* return error */
    }
    
    return 0;                                                                                 /* success return 0 */
}

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
uint8_t ssd1681_get_crc_status(ssd1681_handle_t *handle, uint16_t *status)
{
    uint8_t res;
    uint8_t buf[2];
    
    if (handle == NULL)                                                                     /* check handle */
    {
        return 2;                                                                           /* return error */
    }
    if (handle->inited != 1)                                                                /* check handle initialization */
    {
        return 3;                                                                           /* return error */
    }
    
    res = a_ssd1681_multiple_read_byte(handle, SSD1681_CMD_CRC_STATUS_READ, buf, 2);        /* read byte */
    if (res != 0)                                                                           /* check the result */
    {
        handle->debug_print("ssd1681: multiple read byte failed.\n");                       /* multiple read byte failed */
        
        return 1;                                                                           /* return error */
    }
    *status = (uint16_t)(buf[0] << 0) | buf[1];                                             /* set the status */
    
    return 0;                                                                               /* success return 0 */
}

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
uint8_t ssd1681_otp_program_selection(ssd1681_handle_t *handle)
{
    uint8_t res;
    
    if (handle == NULL)                                                                             /* check handle */
    {
        return 2;                                                                                   /* return error */
    }
    if (handle->inited != 1)                                                                        /* check handle initialization */
    {
        return 3;                                                                                   /* return error */
    }
    
    res = a_ssd1681_multiple_write_byte(handle, SSD1681_CMD_PROGRAM_OTP_SELECTION, NULL, 0);        /* write byte */
    if (res != 0)                                                                                   /* check the result */
    {
        handle->debug_print("ssd1681: multiple write byte failed.\n");                              /* multiple write byte failed */
        
        return 1;                                                                                   /* return error */
    }
    
    return 0;                                                                                       /* success return 0 */
}

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
uint8_t ssd1681_otp_write_register(ssd1681_handle_t *handle, uint8_t param[11])
{
    uint8_t res;
    
    if (handle == NULL)                                                                                           /* check handle */
    {
        return 2;                                                                                                 /* return error */
    }
    if (handle->inited != 1)                                                                                      /* check handle initialization */
    {
        return 3;                                                                                                 /* return error */
    }
    
    res = a_ssd1681_multiple_write_byte(handle, SSD1681_CMD_WRITE_REGISTER_FOR_DISPLAY_OPTION, param, 11);        /* write byte */
    if (res != 0)                                                                                                 /* check the result */
    {
        handle->debug_print("ssd1681: multiple write byte failed.\n");                                            /* multiple write byte failed */
        
        return 1;                                                                                                 /* return error */
    }
    
    return 0;                                                                                                     /* success return 0 */
}

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
uint8_t ssd1681_set_user_id(ssd1681_handle_t *handle, uint8_t id[10])
{
    uint8_t res;
    
    if (handle == NULL)                                                                                 /* check handle */
    {
        return 2;                                                                                       /* return error */
    }
    if (handle->inited != 1)                                                                            /* check handle initialization */
    {
        return 3;                                                                                       /* return error */
    }
    
    res = a_ssd1681_multiple_write_byte(handle, SSD1681_CMD_WRITE_REGISTER_FOR_USER_ID, id, 10);        /* write byte */
    if (res != 0)                                                                                       /* check the result */
    {
        handle->debug_print("ssd1681: multiple write byte failed.\n");                                  /* multiple write byte failed */
        
        return 1;                                                                                       /* return error */
    }
    
    return 0;                                                                                           /* success return 0 */
}

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
uint8_t ssd1681_otp_program_mode(ssd1681_handle_t *handle, ssd1681_otp_mode_t mode)
{
    uint8_t res;
    uint8_t buf[1];
    
    if (handle == NULL)                                                                       /* check handle */
    {
        return 2;                                                                             /* return error */
    }
    if (handle->inited != 1)                                                                  /* check handle initialization */
    {
        return 3;                                                                             /* return error */
    }
    
    buf[0] = mode;                                                                            /* set the mode */
    res = a_ssd1681_multiple_write_byte(handle, SSD1681_CMD_OTP_PROGRAM_MODE, buf, 1);        /* write byte */
    if (res != 0)                                                                             /* check the result */
    {
        handle->debug_print("ssd1681: multiple write byte failed.\n");                        /* multiple write byte failed */
        
        return 1;                                                                             /* return error */
    }
    
    return 0;                                                                                 /* success return 0 */
}

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
                                    ssd1681_gs_transition_t gs_tran, ssd1681_vbd_transition_t vbd_tran)
{
    uint8_t res;
    uint8_t buf[1];
    
    if (handle == NULL)                                                                              /* check handle */
    {
        return 2;                                                                                    /* return error */
    }
    if (handle->inited != 1)                                                                         /* check handle initialization */
    {
        return 3;                                                                                    /* return error */
    }
    
    buf[0] = (uint8_t)((vbd << 6) | (level << 4) | (gs_tran << 2) | (vbd_tran << 0));                /* set the mode */
    res = a_ssd1681_multiple_write_byte(handle, SSD1681_CMD_BORDER_WAVEFORM_CONTROL, buf, 1);        /* write byte */
    if (res != 0)                                                                                    /* check the result */
    {
        handle->debug_print("ssd1681: multiple write byte failed.\n");                               /* multiple write byte failed */
        
        return 1;                                                                                    /* return error */
    }
    
    return 0;                                                                                        /* success return 0 */
}

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
uint8_t ssd1681_set_end_option(ssd1681_handle_t *handle, ssd1681_end_opt_t opt)
{
    uint8_t res;
    uint8_t buf[1];
    
    if (handle == NULL)                                                                 /* check handle */
    {
        return 2;                                                                       /* return error */
    }
    if (handle->inited != 1)                                                            /* check handle initialization */
    {
        return 3;                                                                       /* return error */
    }
    
    buf[0] = opt;                                                                       /* set the mode */
    res = a_ssd1681_multiple_write_byte(handle, SSD1681_CMD_END_OPTION, buf, 1);        /* write byte */
    if (res != 0)                                                                       /* check the result */
    {
        handle->debug_print("ssd1681: multiple write byte failed.\n");                  /* multiple write byte failed */
        
        return 1;                                                                       /* return error */
    }
    
    return 0;                                                                           /* success return 0 */
}

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
uint8_t ssd1681_set_read_ram(ssd1681_handle_t *handle, ssd1681_read_ram_t ram)
{
    uint8_t res;
    uint8_t buf[1];
    
    if (handle == NULL)                                                                      /* check handle */
    {
        return 2;                                                                            /* return error */
    }
    if (handle->inited != 1)                                                                 /* check handle initialization */
    {
        return 3;                                                                            /* return error */
    }
    
    buf[0] = ram;                                                                            /* set the mode */
    res = a_ssd1681_multiple_write_byte(handle, SSD1681_CMD_READ_RAM_OPTION, buf, 1);        /* write byte */
    if (res != 0)                                                                            /* check the result */
    {
        handle->debug_print("ssd1681: multiple write byte failed.\n");                       /* multiple write byte failed */
        
        return 1;                                                                            /* return error */
    }
    
    return 0;                                                                                /* success return 0 */
}

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
uint8_t ssd1681_set_ram_x(ssd1681_handle_t *handle, uint8_t start, uint8_t end)
{
    uint8_t res;
    uint8_t buf[2];
    
    if (handle == NULL)                                                                /* check handle */
    {
        return 2;                                                                      /* return error */
    }
    if (handle->inited != 1)                                                           /* check handle initialization */
    {
        return 3;                                                                      /* return error */
    }
    if (start > 0x3F)                                                                  /* check the start */
    {
        handle->debug_print("ssd1681: start > 0x3F.\n");                               /* start > 0x3F */
        
        return 4;                                                                      /* return error */
    }
    if (end > 0x3F)                                                                    /* check the end */
    {
        handle->debug_print("ssd1681: end > 0x3F.\n");                                 /* end > 0x3F */
        
        return 5;                                                                      /* return error */
    }
    
    buf[0] = start;                                                                    /* set the start address */
    buf[1] = end;                                                                      /* set the end address */
    res = a_ssd1681_multiple_write_byte(handle, SSD1681_CMD_SET_RAM_X, buf, 2);        /* write byte */
    if (res != 0)                                                                      /* check the result */
    {
        handle->debug_print("ssd1681: multiple write byte failed.\n");                 /* multiple write byte failed */
        
        return 1;                                                                      /* return error */
    }
    
    return 0;                                                                          /* success return 0 */
}

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
uint8_t ssd1681_set_ram_y(ssd1681_handle_t *handle, uint16_t start, uint16_t end)
{
    uint8_t res;
    uint8_t buf[4];
    
    if (handle == NULL)                                                                /* check handle */
    {
        return 2;                                                                      /* return error */
    }
    if (handle->inited != 1)                                                           /* check handle initialization */
    {
        return 3;                                                                      /* return error */
    }
    
    buf[0] = start & 0xFF;                                                             /* set the start address */
    buf[1] = (start >> 8) & 0x1;                                                       /* set the start address */
    buf[2] = end & 0xFF;                                                               /* set the end address */
    buf[3] = (end >> 8) & 0x01;                                                        /* set the end address */
    res = a_ssd1681_multiple_write_byte(handle, SSD1681_CMD_SET_RAM_Y, buf, 4);        /* write byte */
    if (res != 0)                                                                      /* check the result */
    {
        handle->debug_print("ssd1681: multiple write byte failed.\n");                 /* multiple write byte failed */
        
        return 1;                                                                      /* return error */
    }
    
    return 0;                                                                          /* success return 0 */
}

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
uint8_t ssd1681_set_auto_write_red_ram(ssd1681_handle_t *handle, ssd1681_step_height_t height, ssd1681_step_width_t width)
{
    uint8_t res;
    uint8_t buf[1];
    
    if (handle == NULL)                                                                                             /* check handle */
    {
        return 2;                                                                                                   /* return error */
    }
    if (handle->inited != 1)                                                                                        /* check handle initialization */
    {
        return 3;                                                                                                   /* return error */
    }
    
    buf[0] = (uint8_t)((height << 4) | (width << 0));                                                               /* set the param */
    res = a_ssd1681_multiple_write_byte(handle, SSD1681_CMD_AUTO_WRITE_RED_RAM_FOR_REGULAR_PATTERN, buf, 1);        /* write byte */
    if (res != 0)                                                                                                   /* check the result */
    {
        handle->debug_print("ssd1681: multiple write byte failed.\n");                                              /* multiple write byte failed */
        
        return 1;                                                                                                   /* return error */
    }
    
    return 0;                                                                                                       /* success return 0 */
}

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
uint8_t ssd1681_set_auto_write_black_ram(ssd1681_handle_t *handle, ssd1681_step_height_t height, ssd1681_step_width_t width)
{
    uint8_t res;
    uint8_t buf[1];
    
    if (handle == NULL)                                                                                            /* check handle */
    {
        return 2;                                                                                                  /* return error */
    }
    if (handle->inited != 1)                                                                                       /* check handle initialization */
    {
        return 3;                                                                                                  /* return error */
    }
    
    buf[0] = (uint8_t)((height << 4) | (width << 0));                                                              /* set the param */
    res = a_ssd1681_multiple_write_byte(handle, SSD1681_CMD_AUTO_WRITE_BW_RAM_FOR_REGULAR_PATTERN, buf, 1);        /* write byte */
    if (res != 0)                                                                                                  /* check the result */
    {
        handle->debug_print("ssd1681: multiple write byte failed.\n");                                             /* multiple write byte failed */
        
        return 1;                                                                                                  /* return error */
    }
    
    return 0;                                                                                                      /* success return 0 */
}

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
uint8_t ssd1681_set_ram_x_address_counter(ssd1681_handle_t *handle, uint8_t cnt)
{
    uint8_t res;
    uint8_t buf[1];
    
    if (handle == NULL)                                                                                /* check handle */
    {
        return 2;                                                                                      /* return error */
    }
    if (handle->inited != 1)                                                                           /* check handle initialization */
    {
        return 3;                                                                                      /* return error */
    }
    if (cnt > 0x3F)                                                                                    /* check the result */
    {
        handle->debug_print("ssd1681: cnt > 0x3F.\n");                                                 /* cnt > 0x3F */
        
        return 4;                                                                                      /* return error */
    }
    
    buf[0] = cnt;                                                                                      /* set the counter */
    res = a_ssd1681_multiple_write_byte(handle, SSD1681_CMD_SET_RAM_X_ADDRESS_COUNTER, buf, 1);        /* write byte */
    if (res != 0)                                                                                      /* check the result */
    {
        handle->debug_print("ssd1681: multiple write byte failed.\n");                                 /* multiple write byte failed */
        
        return 1;                                                                                      /* return error */
    }
    
    return 0;                                                                                          /* success return 0 */
}

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
uint8_t ssd1681_set_ram_y_address_counter(ssd1681_handle_t *handle, uint16_t cnt)
{
    uint8_t res;
    uint8_t buf[2];
    
    if (handle == NULL)                                                                                /* check handle */
    {
        return 2;                                                                                      /* return error */
    }
    if (handle->inited != 1)                                                                           /* check handle initialization */
    {
        return 3;                                                                                      /* return error */
    }
    if (cnt > 0x1FF)                                                                                   /* check the result */
    {
        handle->debug_print("ssd1681: cnt > 0x1FF.\n");                                                /* cnt > 0x1FF */
        
        return 4;                                                                                      /* return error */
    }
    
    buf[0] = cnt & 0xFF;                                                                               /* set the counter low */
    buf[1] = (cnt >> 8)& 0x01;                                                                         /* set the counter high */
    res = a_ssd1681_multiple_write_byte(handle, SSD1681_CMD_SET_RAM_Y_ADDRESS_COUNTER, buf, 2);        /* write byte */
    if (res != 0)                                                                                      /* check the result */
    {
        handle->debug_print("ssd1681: multiple write byte failed.\n");                                 /* multiple write byte failed */
        
        return 1;                                                                                      /* return error */
    }
    
    return 0;                                                                                          /* success return 0 */
}

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
uint8_t ssd1681_nop(ssd1681_handle_t *handle)
{
    uint8_t res;
    
    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }
    
    res = a_ssd1681_multiple_write_byte(handle, SSD1681_CMD_NOP, NULL, 0);        /* write byte */
    if (res != 0)                                                                 /* check the result */
    {
        handle->debug_print("ssd1681: multiple write byte failed.\n");            /* multiple write byte failed */
        
        return 1;                                                                 /* return error */
    }
    
    return 0;                                                                     /* success return 0 */
}

/**
 * @brief     draw a point in gram
 * @param[in] *handle pointer to an ssd1681 handle structure
 * @param[in] color color type
 * @param[in] x coordinate x
 * @param[in] y coordinate y
 * @param[in] data written data
 * @return    status code
 *            - 0 success
 *            - 1 gram draw point failed
 * @note      none
 */
static uint8_t a_ssd1681_gram_draw_point(ssd1681_handle_t *handle, ssd1681_color_t color, uint8_t x, uint8_t y, uint8_t data)
{
    uint8_t pos;
    uint8_t bx;
    uint8_t temp = 0;
    
    pos = y / 8;                                        /* get y page */
    bx = y % 8;                                         /* get y point */
    temp = 1 << (7 - bx);                               /* set data */
    if (color == SSD1681_COLOR_BLACK)                   /* if black */
    {
        if (data == 0)                                  /* if 0 */
        {
            handle->black_gram[x][pos] |= temp;         /* set 1 */
        }
        else
        {
            handle->black_gram[x][pos] &= ~temp;        /* set 0 */
        }
    }
    else                                                /* if red */
    {
        if (data != 0)                                  /* if 1 */
        {
            handle->red_gram[x][pos] |= temp;           /* set 1 */
        }
        else
        {
            handle->red_gram[x][pos] &= ~temp;          /* set 0 */
        }
    }
  
    return 0;                                           /* success return 0 */
}

/**
 * @brief     draw a char in gram
 * @param[in] *handle pointer to an ssd1681 handle structure
 * @param[in] color color type
 * @param[in] x coordinate x
 * @param[in] y coordinate y
 * @param[in] chr written char
 * @param[in] size char size
 * @param[in] mode display mode
 * @return    status code
 *            - 0 success
 *            - 1 gram show char failed
 * @note      none
 */
static uint8_t a_ssd1681_gram_show_char(ssd1681_handle_t *handle, ssd1681_color_t color, uint8_t x, uint8_t y, uint8_t chr, uint8_t size, uint8_t mode)
{
    uint8_t temp, t, t1;
    uint8_t y0 = y;
    uint8_t csize = (size / 8 + ((size % 8) ? 1 : 0)) * (size / 2);                 /* get size */
    
    chr = chr - ' ';                                                                /* get index */
    for (t = 0; t < csize; t++)                                                     /* write size */
    {   
        if (size == 12)                                                             /* if size 12 */
        {
            temp = gsc_ssd1681_ascii_1206[chr][t];                                  /* get ascii 1206 */
        }
        else if (size == 16)                                                        /* if size 16 */
        {
            temp = gsc_ssd1681_ascii_1608[chr][t];                                  /* get ascii 1608 */
        }
        else if(size == 24)                                                         /* if size 24 */
        {
            temp = gsc_ssd1681_ascii_2412[chr][t];                                  /* get ascii 2412 */
        }
        else
        {
            return 1;                                                               /* return error */
        }
        for (t1 = 0; t1 < 8; t1++)                                                  /* write one line */
        {
            if ((temp & 0x80) != 0)                                                 /* if 1 */
            {
                if (a_ssd1681_gram_draw_point(handle, color, x, y, mode) != 0)      /* draw point */
                {
                    return 1;                                                       /* return error */
                }
            }
            else 
            {
                if (a_ssd1681_gram_draw_point(handle, color, x, y, !mode) != 0)     /* draw point */
                {
                    return 1;                                                       /* return error */
                }
            }
            temp <<= 1;                                                             /* left shift 1 */
            y++;
            if ((y - y0) == size)                                                   /* reset size */
            {
                y = y0;                                                             /* set y */
                x++;                                                                /* x++ */
                
                break;                                                              /* break */
            }
        }
    }
  
    return 0;                                                                       /* success return 0 */
}

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
uint8_t ssd1681_clear(ssd1681_handle_t *handle, ssd1681_color_t color)
{
    uint8_t i;
    uint8_t j;
    uint8_t res;
    uint8_t buf[2];
    
    if (handle == NULL)                                                                                /* check handle */
    {
        return 2;                                                                                      /* return error */
    }
    if (handle->inited != 1)                                                                           /* check handle initialization */
    {
        return 3;                                                                                      /* return error */
    }
    
    buf[0] = 0x00;                                                                                     /* set 0x00 */
    res = a_ssd1681_multiple_write_byte(handle, SSD1681_CMD_SET_RAM_X_ADDRESS_COUNTER, buf, 1);        /* write byte */
    if (res != 0)                                                                                      /* check the result */
    {
        handle->debug_print("ssd1681: multiple write byte failed.\n");                                 /* multiple write byte failed */
        
        return 1;                                                                                      /* return error */
    }
    buf[0] = 0xC7;                                                                                     /* set 0xC7 */
    buf[1] = 0x00;                                                                                     /* set 0x00 */
    res = a_ssd1681_multiple_write_byte(handle, SSD1681_CMD_SET_RAM_Y_ADDRESS_COUNTER, buf, 2);        /* write byte */
    if (res != 0)                                                                                      /* check the result */
    {
        handle->debug_print("ssd1681: multiple write byte failed.\n");                                 /* multiple write byte failed */
        
        return 1;                                                                                      /* return error */
    }
    if (color == SSD1681_COLOR_BLACK)                                                                  /* if black */
    {
        res = a_ssd1681_multiple_write_byte(handle, SSD1681_CMD_WRITE_RAM_BLACK, NULL, 0);             /* write byte */
        if (res != 0)                                                                                  /* check the result */
        {
            handle->debug_print("ssd1681: multiple write byte failed.\n");                             /* multiple write byte failed */
            
            return 1;                                                                                  /* return error */
        }
        res = handle->spi_cmd_data_gpio_write(SSD1681_DATA);                                           /* write data */
        if (res != 0)                                                                                  /* check error */
        {
            handle->debug_print("ssd1681: spi cmd data gpio write failed.\n");                         /* spi cmd data gpio write failed */
            
            return 1;                                                                                  /* return error */
        }
        for (i = 0; i < 200; i++)                                                                      /* x */
        {
            for (j = 0; j < 25; j++)                                                                   /* y */
            {
                handle->black_gram[i][j] = 0xFF;                                                       /* set 0xFF */
                res = handle->spi_write_cmd(&handle->black_gram[i][j], 1);                             /* write gram */
                if (res != 0)                                                                          /* check error */
                {
                    handle->debug_print("ssd1681: spi write cmd failed.\n");                           /* spi write cmd failed */
                    
                    return 1;                                                                          /* return error */
                }
            }
        }
    }
    else                                                                                               /* if red */
    {
        res = a_ssd1681_multiple_write_byte(handle, SSD1681_CMD_WRITE_RAM_RED, NULL, 0);               /* write byte */
        if (res != 0)                                                                                  /* check the result */
        {
            handle->debug_print("ssd1681: multiple write byte failed.\n");                             /* multiple write byte failed */
            
            return 1;                                                                                  /* return error */
        }
        res = handle->spi_cmd_data_gpio_write(SSD1681_DATA);                                           /* write data */
        if (res != 0)                                                                                  /* check error */
        {
            handle->debug_print("ssd1681: spi cmd data gpio write failed.\n");                         /* spi cmd data gpio write failed */
            
            return 1;                                                                                  /* return error */
        }
        for (i = 0; i < 200; i++)                                                                      /* x */
        {
            for (j = 0; j < 25; j++)                                                                   /* y */
            {
                handle->red_gram[i][j] = 0x00;                                                         /* set 0x00 */
                res = handle->spi_write_cmd(&handle->red_gram[i][j], 1);                               /* write gram */
                if (res != 0)                                                                          /* check error */
                {
                    handle->debug_print("ssd1681: spi write cmd failed.\n");                           /* spi write cmd failed */
                    
                    return 1;                                                                          /* return error */
                }
            }
        }
    }
    
    buf[0] = 0xF7;                                                                                     /* set 0xF7 */
    res = a_ssd1681_multiple_write_byte(handle, SSD1681_CMD_DISPLAY_UPDATA_CONTROL_2, buf, 1);         /* write byte */
    if (res != 0)                                                                                      /* check the result */
    {
        handle->debug_print("ssd1681: multiple write byte failed.\n");                                 /* multiple write byte failed */
        
        return 1;                                                                                      /* return error */
    }
    res = a_ssd1681_multiple_write_byte(handle, SSD1681_CMD_MASTER_ACTIVATION, NULL, 0);               /* write byte */
    if (res != 0)                                                                                      /* check the result */
    {
        handle->debug_print("ssd1681: multiple write byte failed.\n");                                 /* multiple write byte failed */
        
        return 1;                                                                                      /* return error */
    }
    
    return 0;                                                                                          /* success return 0 */
}

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
uint8_t ssd1681_gram_update(ssd1681_handle_t *handle, ssd1681_color_t color)
{
    uint8_t i;
    uint8_t j;
    uint8_t res;
    uint8_t buf[2];
    
    if (handle == NULL)                                                                                /* check handle */
    {
        return 2;                                                                                      /* return error */
    }
    if (handle->inited != 1)                                                                           /* check handle initialization */
    {
        return 3;                                                                                      /* return error */
    }
    
    buf[0] = 0x00;                                                                                     /* set 0x00 */
    res = a_ssd1681_multiple_write_byte(handle, SSD1681_CMD_SET_RAM_X_ADDRESS_COUNTER, buf, 1);        /* write byte */
    if (res != 0)                                                                                      /* check the result */
    {
        handle->debug_print("ssd1681: multiple write byte failed.\n");                                 /* multiple write byte failed */
        
        return 1;                                                                                      /* return error */
    }
    buf[0] = 0xC7;                                                                                     /* set 0xC7 */
    buf[1] = 0x00;                                                                                     /* set 0x00 */
    res = a_ssd1681_multiple_write_byte(handle, SSD1681_CMD_SET_RAM_Y_ADDRESS_COUNTER, buf, 2);        /* write byte */
    if (res != 0)                                                                                      /* check the result */
    {
        handle->debug_print("ssd1681: multiple write byte failed.\n");                                 /* multiple write byte failed */
        
        return 1;                                                                                      /* return error */
    }
    if (color == SSD1681_COLOR_BLACK)                                                                  /* if black */
    {
        res = a_ssd1681_multiple_write_byte(handle, SSD1681_CMD_WRITE_RAM_BLACK, NULL, 0);             /* write byte */
        if (res != 0)                                                                                  /* check the result */
        {
            handle->debug_print("ssd1681: multiple write byte failed.\n");                             /* multiple write byte failed */
            
            return 1;                                                                                  /* return error */
        }
        res = handle->spi_cmd_data_gpio_write(SSD1681_DATA);                                           /* write data */
        if (res != 0)                                                                                  /* check error */
        {
            handle->debug_print("ssd1681: spi cmd data gpio write failed.\n");                         /* spi cmd data gpio write failed */
            
            return 1;                                                                                  /* return error */
        }
        for (i = 0; i < 200; i++)                                                                      /* x */
        {
            for (j = 0; j < 25; j++)                                                                   /* y */
            {
                res = handle->spi_write_cmd(&handle->black_gram[i][j], 1);                             /* write gram */
                if (res != 0)                                                                          /* check error */
                {
                    handle->debug_print("ssd1681: spi write cmd failed.\n");                           /* spi write cmd failed */
                    
                    return 1;                                                                          /* return error */
                }
            }
        }
    }
    else                                                                                               /* if red */
    {
        res = a_ssd1681_multiple_write_byte(handle, SSD1681_CMD_WRITE_RAM_RED, NULL, 0);               /* write byte */
        if (res != 0)                                                                                  /* check the result */
        {
            handle->debug_print("ssd1681: multiple write byte failed.\n");                             /* multiple write byte failed */
            
            return 1;                                                                                  /* return error */
        }
        res = handle->spi_cmd_data_gpio_write(SSD1681_DATA);                                           /* write data */
        if (res != 0)                                                                                  /* check error */
        {
            handle->debug_print("ssd1681: spi cmd data gpio write failed.\n");                         /* spi cmd data gpio write failed */
            
            return 1;                                                                                  /* return error */
        }
        for (i = 0; i < 200; i++)                                                                      /* x */
        {
            for (j = 0; j < 25; j++)                                                                   /* y */
            {
                res = handle->spi_write_cmd(&handle->red_gram[i][j], 1);                               /* write gram */
                if (res != 0)                                                                          /* check error */
                {
                    handle->debug_print("ssd1681: spi write cmd failed.\n");                           /* spi write cmd failed */
                    
                    return 1;                                                                          /* return error */
                }
            }
        }
    }
    
    buf[0] = 0xF7;                                                                                     /* set 0xF7 */
    res = a_ssd1681_multiple_write_byte(handle, SSD1681_CMD_DISPLAY_UPDATA_CONTROL_2, buf, 1);         /* write byte */
    if (res != 0)                                                                                      /* check the result */
    {
        handle->debug_print("ssd1681: multiple write byte failed.\n");                                 /* multiple write byte failed */
        
        return 1;                                                                                      /* return error */
    }
    res = a_ssd1681_multiple_write_byte(handle, SSD1681_CMD_MASTER_ACTIVATION, NULL, 0);               /* write byte */
    if (res != 0)                                                                                      /* check the result */
    {
        handle->debug_print("ssd1681: multiple write byte failed.\n");                                 /* multiple write byte failed */
        
        return 1;                                                                                      /* return error */
    }
    
    return 0;                                                                                          /* success return 0 */
}

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
uint8_t ssd1681_gram_clear(ssd1681_handle_t *handle, ssd1681_color_t color)
{
    uint8_t i;
    uint8_t j;
    
    if (handle == NULL)                                 /* check handle */
    {
        return 2;                                       /* return error */
    }
    if (handle->inited != 1)                            /* check handle initialization */
    {
        return 3;                                       /* return error */
    }
    
    if (color == SSD1681_COLOR_BLACK)                   /* if black */
    {
        for (i = 0; i < 200; i++)                       /* x */
        {
            for (j = 0; j < 25; j++)                    /* y */
            {
                handle->black_gram[i][j] = 0xFF;        /* set 0xFF */
            }
        }
    }
    else                                                /* if red */
    {
        for (i = 0; i < 200; i++)                       /* x */
        {
            for (j = 0; j < 25; j++)                    /* y */
            {
                handle->red_gram[i][j] = 0x00;          /* set 0x00 */
            }
        }
    }
    
    return 0;                                           /* success return 0 */
}

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
uint8_t ssd1681_gram_write_point(ssd1681_handle_t *handle, ssd1681_color_t color, uint8_t x, uint8_t y, uint8_t data)
{
    uint8_t pos;
    uint8_t bx;
    uint8_t temp = 0;
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    if ((x > 200) || (y > 200))                                      /* check x, y */
    {
        handle->debug_print("ssd1681: x or y is invalid.\n");        /* x or y is invalid */
        
        return 4;                                                    /* return error */
    }
    
    pos = y / 8;                                                     /* get y page */
    bx = y % 8;                                                      /* get y point */
    temp = 1 << (7 - bx);                                            /* set data */
    if (color == SSD1681_COLOR_BLACK)                                /* if black */
    {
        if (data == 0)                                               /* if 0 */
        {
            handle->black_gram[x][pos] |= temp;                      /* set 1 */
        }
        else
        {
            handle->black_gram[x][pos] &= ~temp;                     /* set 0 */
        }
    }
    else                                                             /* if red */
    {
        if (data != 0)                                               /* if 1 */
        {
            handle->red_gram[x][pos] |= temp;                        /* set 1 */
        }
        else
        {
            handle->red_gram[x][pos] &= ~temp;                       /* set 0 */
        }
    }
  
    return 0;                                                        /* success return 0 */
}

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
uint8_t ssd1681_gram_read_point(ssd1681_handle_t *handle, ssd1681_color_t color, uint8_t x, uint8_t y, uint8_t *data)
{
    uint8_t pos;
    uint8_t bx;
    uint8_t temp = 0;
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    if ((x > 200) || (y > 200))                                      /* check x, y */
    {
        handle->debug_print("ssd1681: x or y is invalid.\n");        /* x or y is invalid */
        
        return 4;                                                    /* return error */
    }
    
    pos = y / 8;                                                     /* get y page */
    bx = y % 8;                                                      /* get y point */
    temp = 1 << (7 - bx);                                            /* set data */
    if (color == SSD1681_COLOR_BLACK)                                /* if black */
    {
        if ((handle->black_gram[x][pos] & temp) != 0)                /* get data */
        {
            *data = 0;                                               /* set 0 */
        }
        else
        {
            *data = 1;                                               /* set 1 */
        }
    }
    else                                                             /* if red */
    {
        if ((handle->red_gram[x][pos] & temp) != 0)                  /* get data */
        {
            *data = 1;                                               /* set 1 */
        }
        else
        {
            *data = 0;                                               /* set 0 */
        }
    }
  
    return 0;                                                        /* success return 0 */
}

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
uint8_t ssd1681_gram_write_string(ssd1681_handle_t *handle, ssd1681_color_t color, uint8_t x, uint8_t y, char *str, uint16_t len, uint8_t data, ssd1681_font_t font)
{    
    if (handle == NULL)                                                                  /* check handle */
    {
        return 2;                                                                        /* return error */
    }
    if (handle->inited != 1)                                                             /* check handle initialization */
    {
        return 3;                                                                        /* return error */
    }
    if((x > 199) || (y > 199))                                                           /* check x, y */
    {
        handle->debug_print("ssd1681: x or y is invalid.\n");                            /* x or y is invalid */
        
        return 4;                                                                        /* return error */
    }
    
    while ((len != 0) && (*str <= '~') && (*str >= ' '))                                 /* write all string */
    {       
        if (x > (199 - (font / 2)))                                                      /* check x point */
        {
            x = 0;                                                                       /* set x */
            y += (uint8_t)font;                                                          /* set next row */
        }
        if (y > (199 - font))                                                            /* check y pont */
        {
            y = x = 0;                                                                   /* reset to 0,0 */
        }
        if (a_ssd1681_gram_show_char(handle, color, x, y, *str, font, data) != 0)        /* show a char */
        {
            return 1;                                                                    /* return error */
        }
        x += (uint8_t)(font / 2);                                                        /* x + font / 2 */
        str++;                                                                           /* str address++ */
        len--;                                                                           /* str length-- */
    }
    
    return 0;                                                                            /* success return 0 */
}

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
uint8_t ssd1681_gram_fill_rect(ssd1681_handle_t *handle, ssd1681_color_t color, uint8_t left, uint8_t top, uint8_t right, uint8_t bottom, uint8_t data)
{
    uint8_t x, y;  
    
    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }
    if ((left > 199) || (top > 199))                                              /* check left top */
    {
        handle->debug_print("ssd1681: left or top is invalid.\n");                /* left or top is invalid */
        
        return 4;                                                                 /* return error */
    }
    if ((right > 199) || (bottom > 199))                                          /* check right bottom */
    {
        handle->debug_print("ssd1681: right or bottom is invalid.\n");            /* right or bottom is invalid */
        
        return 5;                                                                 /* return error */
    }
    if ((left > right) || (top > bottom))                                         /* check left right top bottom */
    {
        handle->debug_print("ssd1681: left > right or top > bottom.\n");          /* left > right or top > bottom */
        
        return 6;                                                                 /* return error */
    }
    
    for (x = left; x <= right; x++)                                               /* write x */
    {
        for (y = top; y <= bottom; y++)                                           /* write y */
        {
            if (a_ssd1681_gram_draw_point(handle, color, x, y, data) != 0)        /* draw point */
            {
                return 1;                                                         /* return error */
            }
        }
    }
    
    return 0;                                                                     /* return error */
}

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
uint8_t ssd1681_gram_draw_picture(ssd1681_handle_t *handle, ssd1681_color_t color, uint8_t left, uint8_t top, uint8_t right, uint8_t bottom, uint8_t *img)
{    
    uint8_t x, y;  
    
    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }
    if ((left > 199) || (top > 199))                                              /* check left top */
    {
        handle->debug_print("ssd1681: left or top is invalid.\n");                /* left or top is invalid */
        
        return 4;                                                                 /* return error */
    }
    if ((right > 199) || (bottom > 199))                                          /* check right bottom */
    {
        handle->debug_print("ssd1681: right or bottom is invalid.\n");            /* right or bottom is invalid */
        
        return 5;                                                                 /* return error */
    }
    if ((left > right) || (top > bottom))                                         /* check left right top bottom */
    {
        handle->debug_print("ssd1681: left > right or top > bottom.\n");          /* left > right or top > bottom */
        
        return 6;                                                                 /* return error */
    }
    
    for (x = left; x <= right; x++)                                               /* write x */
    {
        for (y = top; y <= bottom; y++)                                           /* write y */
        {
            if (a_ssd1681_gram_draw_point(handle, color, x, y, *img) != 0)        /* draw point */
            {
                return 1;                                                         /* return error */
            }
            img++;                                                                /* img++ */
        }
    }
    
    return 0;                                                                     /* succeed return 0 */
}

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
uint8_t ssd1681_init(ssd1681_handle_t *handle)
{
    if (handle == NULL)                                                             /* check handle */
    {
        return 2;                                                                   /* return error */
    }
    if (handle->debug_print == NULL)                                                /* check debug_print */
    {
        return 3;                                                                   /* return error */
    }
    if (handle->spi_init == NULL)                                                   /* check spi_init */
    {
        handle->debug_print("ssd1681: spi_init is null.\n");                        /* spi_init is null */
        
        return 3;                                                                   /* return error */
    }
    if (handle->spi_deinit == NULL)                                                 /* check spi_deinit */
    {
        handle->debug_print("ssd1681: spi_deinit is null.\n");                      /* spi_deinit is null */
       
        return 3;                                                                   /* return error */
    }
    if (handle->spi_write_cmd == NULL)                                              /* check spi_write_cmd */
    {
        handle->debug_print("ssd1681: spi_write_cmd is null.\n");                   /* spi_write_cmd is null */
       
        return 3;                                                                   /* return error */
    }
    if (handle->delay_ms == NULL)                                                   /* check delay_ms */
    {
        handle->debug_print("ssd1681: delay_ms is null.\n");                        /* delay_ms is null */
        
        return 3;                                                                   /* return error */
    }
    if (handle->spi_cmd_data_gpio_init == NULL)                                     /* check spi_cmd_data_gpio_init */
    {
        handle->debug_print("ssd1681: spi_cmd_data_gpio_init is null.\n");          /* spi_cmd_data_gpio_init is null */
       
        return 3;                                                                   /* return error */
    }
    if (handle->spi_cmd_data_gpio_deinit == NULL)                                   /* check spi_cmd_data_gpio_deinit */
    {
        handle->debug_print("ssd1681: spi_cmd_data_gpio_deinit is null.\n");        /* spi_cmd_data_gpio_deinit is null */
       
        return 3;                                                                   /* return error */
    }
    if (handle->spi_cmd_data_gpio_write == NULL)                                    /* check spi_cmd_data_gpio_write */
    {
        handle->debug_print("ssd1681: spi_cmd_data_gpio_write is null.\n");         /* spi_cmd_data_gpio_write is null */
        
        return 3;                                                                   /* return error */
    }
    if (handle->reset_gpio_init == NULL)                                            /* check reset_gpio_init */
    {
        handle->debug_print("ssd1681: reset_gpio_init is null.\n");                 /* reset_gpio_init is null */
        
        return 3;                                                                   /* return error */
    }
    if (handle->reset_gpio_deinit == NULL)                                          /* check reset_gpio_deinit */
    {
        handle->debug_print("ssd1681: reset_gpio_deinit is null.\n");               /* reset_gpio_deinit is null */
        
        return 3;                                                                   /* return error */
    }
    if(handle->reset_gpio_write == NULL)                                            /* check reset_gpio_write */
    {
        handle->debug_print("ssd1681: reset_gpio_write is null.\n");                /* reset_gpio_write is null */ 
        
        return 3;                                                                   /* return error */
    }
    if(handle->busy_gpio_init == NULL)                                              /* check busy_gpio_init */
    {
        handle->debug_print("ssd1681: busy_gpio_init is null.\n");                  /* busy_gpio_init is null */ 
        
        return 3;                                                                   /* return error */
    }
    if(handle->busy_gpio_deinit == NULL)                                            /* check busy_gpio_deinit */
    {
        handle->debug_print("ssd1681: busy_gpio_deinit is null.\n");                /* busy_gpio_deinit is null */ 
        
        return 3;                                                                   /* return error */
    }
    if(handle->busy_gpio_read == NULL)                                              /* check busy_gpio_read */
    {
        handle->debug_print("ssd1681: busy_gpio_read is null.\n");                  /* busy_gpio_read is null */ 
        
        return 3;                                                                   /* return error */
    }
    
    if (handle->spi_cmd_data_gpio_init() != 0)                                      /* check spi_cmd_data_gpio_init */
    {
        handle->debug_print("ssd1681: spi cmd data gpio init failed.\n");           /* spi cmd data gpio init failed */
        
        return 5;                                                                   /* return error */
    }
    if (handle->reset_gpio_init() != 0)                                             /* reset gpio init */
    {
        handle->debug_print("ssd1681: reset gpio init failed.\n");                  /* reset gpio init failed */
        (void)handle->spi_cmd_data_gpio_deinit();                                   /* spi_cmd_data_gpio_deinit */
        
        return 5;                                                                   /* return error */
    }
    if (handle->busy_gpio_init() != 0)                                              /* busy gpio init */
    {
        handle->debug_print("ssd1681: busy gpio init failed.\n");                   /* busy gpio init failed */
        (void)handle->spi_cmd_data_gpio_deinit();                                   /* spi_cmd_data_gpio_deinit */
        (void)handle->reset_gpio_deinit();                                          /* reset_gpio_deinit */
        
        return 5;                                                                   /* return error */
    }
    
    if (handle->reset_gpio_write(0) != 0)                                           /* write 0 */
    {
        handle->debug_print("ssd1681: reset gpio write failed.\n");                 /* reset gpio write failed */
        (void)handle->spi_cmd_data_gpio_deinit();                                   /* spi_cmd_data_gpio_deinit */
        (void)handle->reset_gpio_deinit();                                          /* reset_gpio_deinit */
        (void)handle->busy_gpio_deinit();                                           /* busy_gpio_deinit */
        
        return 4;                                                                   /* return error */
    }
    handle->delay_ms(10);                                                           /* delay 10 ms */
    if (handle->reset_gpio_write(1) != 0)                                           /* write 1 */
    {
        handle->debug_print("ssd1681: reset gpio write failed.\n");                 /* reset gpio write failed */
        (void)handle->spi_cmd_data_gpio_deinit();                                   /* spi_cmd_data_gpio_deinit */
        (void)handle->reset_gpio_deinit();                                          /* reset_gpio_deinit */
        (void)handle->busy_gpio_deinit();                                           /* busy_gpio_deinit */
        
        return 4;                                                                   /* return error */
    }
    handle->delay_ms(200);                                                          /* delay 200 ms */

    if (handle->spi_init() != 0)                                                    /* spi init */
    {
        handle->debug_print("ssd1681: spi init failed.\n");                         /* spi init failed */
        (void)handle->spi_cmd_data_gpio_deinit();                                   /* spi_cmd_data_gpio_deinit */
        (void)handle->reset_gpio_deinit();                                          /* reset_gpio_deinit */
        (void)handle->busy_gpio_deinit();                                           /* busy_gpio_deinit */
        
        return 1;                                                                   /* return error */
    }

    handle->inited = 1;                                                             /* flag inited */
    
    return 0;                                                                       /* success return 0 */
}

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
uint8_t ssd1681_deinit(ssd1681_handle_t *handle)
{
    uint8_t res;
    uint8_t buf[1];
    
    if (handle == NULL)                                                                       /* check handle */
    {
        return 2;                                                                             /* return error */
    }
    if (handle->inited != 1)                                                                  /* check handle initialization */
    {
        return 3;                                                                             /* return error */
    }
    
    buf[0] = 0x01;                                                                            /* set 0x01 */
    res = a_ssd1681_multiple_write_byte(handle, SSD1681_CMD_DEEP_SLEEP_MODE, buf, 1);         /* write byte */
    if (res != 0)                                                                             /* check the result */
    {
        handle->debug_print("ssd1681: multiple write byte failed.\n");                        /* multiple write byte failed */
        
        return 4;                                                                             /* return error */
    }
    handle->delay_ms(100);                                                                    /* delay 100 ms */
    
    if (handle->reset_gpio_deinit() != 0)                                                     /* reset gpio deinit */
    {
        handle->debug_print("ssd1681: reset gpio deinit failed.\n");                          /* reset gpio deinit failed */
            
        return 5;                                                                             /* return error */
    }
    if (handle->spi_cmd_data_gpio_deinit() != 0)                                              /* spi cmd data gpio deinit */
    {
        handle->debug_print("ssd1681: spi cmd data gpio deinit failed.\n");                   /* spi cmd data gpio deinit failed */
            
        return 6;                                                                             /* return error */
    }
    if (handle->busy_gpio_deinit() != 0)                                                      /* busy gpio deinit */
    {
        handle->debug_print("ssd1681: busy gpio deinit failed.\n");                           /* busy gpio deinit failed */
            
        return 7;                                                                             /* return error */
    }
    
    if (handle->spi_deinit() != 0)                                                            /* spi deinit */
    {
        handle->debug_print("ssd1681: spi deinit failed.\n");                                 /* spi deinit failed */
        
        return 1;                                                                             /* return error */
    }

    handle->inited = 0;                                                                       /* flag close */
    
    return 0;                                                                                 /* success return 0 */
}

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
uint8_t ssd1681_write_cmd(ssd1681_handle_t *handle, uint8_t *buf, uint8_t len)
{
    uint8_t res;
    uint8_t i;
    
    if (handle == NULL)                                            /* check handle */
    {
        return 2;                                                  /* return error */
    }
    if (handle->inited != 1)                                       /* check handle initialization */
    {
        return 3;                                                  /* return error */
    }
    
    res = handle->spi_cmd_data_gpio_write(SSD1681_CMD);            /* write command */
    if (res != 0)                                                  /* check error */
    {
        return 1;                                                  /* return error */
    }
    for (i = 0; i < len; i++)                                      /* len times */
    {
        if (handle->spi_write_cmd(buf + i, 1) != 0)                /* write command */
        {
            return 1;                                              /* return error */
        }
    }
    
    return 0;                                                      /* success return 0 */
}

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
uint8_t ssd1681_write_data(ssd1681_handle_t *handle, uint8_t *buf, uint8_t len)
{
    uint8_t res;
    uint8_t i;
    
    if (handle == NULL)                                            /* check handle */
    {
        return 2;                                                  /* return error */
    }
    if (handle->inited != 1)                                       /* check handle initialization */
    {
        return 3;                                                  /* return error */
    }
    
    res = handle->spi_cmd_data_gpio_write(SSD1681_DATA);           /* write data */
    if (res != 0)                                                  /* check error */
    {
        return 1;                                                  /* return error */
    }
    for (i = 0; i < len; i++)                                      /* len times */
    {
        if (handle->spi_write_cmd(buf + i, 1) != 0)                /* write command */
        {
            return 1;                                              /* return error */
        }
    }
    
    return 0;                                                      /* success return 0 */
}

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
uint8_t ssd1681_read_data(ssd1681_handle_t *handle, uint8_t *buf, uint8_t len)
{
    uint8_t res;
    uint8_t i;
    
    if (handle == NULL)                                            /* check handle */
    {
        return 2;                                                  /* return error */
    }
    if (handle->inited != 1)                                       /* check handle initialization */
    {
        return 3;                                                  /* return error */
    }
    
    res = handle->spi_cmd_data_gpio_write(SSD1681_DATA);           /* write data */
    if (res != 0)                                                  /* check error */
    {
        return 1;                                                  /* return error */
    }
    for (i = 0; i < len; i++)                                      /* len times */
    {
        if (handle->spi_read_cmd(buf + i, 1) != 0)                 /* read command */
        {
            return 1;                                              /* return error */
        }
    }
    
    return 0;                                                      /* success return 0 */
}

/**
 * @brief      get chip's information
 * @param[out] *info pointer to an ssd1681 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t ssd1681_info(ssd1681_info_t *info)
{
    if (info == NULL)                                               /* check handle */
    {
        return 2;                                                   /* return error */
    }
    
    memset(info, 0, sizeof(ssd1681_info_t));                        /* initialize ssd1681 info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                        /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);        /* copy manufacturer name */
    strncpy(info->interface, "SPI", 8);                             /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;                /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;                /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                             /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                        /* set minimal temperature */
    info->temperature_min = TEMPERATURE_MIN;                        /* set maximum temperature */
    info->driver_version = DRIVER_VERSION;                          /* set driver version */
    
    return 0;                                                       /* success return 0 */
}
