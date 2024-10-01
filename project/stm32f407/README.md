### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

SPI Pin: SCK/MISO/MOSI/CS PA5/PA6/PA7/PA4.

GPIO Pin: CMD/RESET/BUSY PB1/PA0/PA8.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

### 3. SSD1681

#### 3.1 Command Instruction

1. Show ssd1681 chip and driver information.

   ```shell
   ssd1681 (-i | --information)
   ```

2. Show ssd1681 help.

   ```shell
   ssd1681 (-h | --help)
   ```

3. Show ssd1681 pin connections of the current board.

   ```shell
   ssd1681 (-p | --port)
   ```

4. Run ssd1681 display test.

   ```shell
   ssd1681 (-t display | --test=display)
   ```

5. Run ssd1681 init function.

   ```shell
   ssd1681 (-e basic-init | --example=basic-init)
   ```

6. Run ssd1681 deinit function.

   ```shell
   ssd1681 (-e basic-deinit | --example=basic-deinit)
   ```

7. Run ssd1681 show string function, string is the shown string. 

   ```shell
   ssd1681 (-e basic-str | --example=basic-str) [--str=<string>] [--mode=<RED | BLACK>] [--color=<0 | 1>]
   ```

8. Run ssd1681 clear screen function.

   ```shell
   ssd1681 (-e basic-clear | --example=basic-clear) [--mode=<RED | BLACK>]
   ```

9. Run ssd1681 write point function, x0 is the x of the point and y0 is the y of the point.

   ```shell
   ssd1681 (-e basic-point | --example=basic-point) --x0=<x0> --y0=<y0> [--mode=<RED | BLACK>] [--color=<0 | 1>]
   ```

10. Run ssd1681 read point function, x0 is the x of the point and y0 is the y of the point.

    ```shell
    ssd1681 (-e basic-point | --example=basic-point) --x0=<x0> --y0=<y0> [--mode=<RED | BLACK>]
    ```

11. Run ssd1681 drawing rectangle function, x1 is the top left x of the rect, y1 is the top left y of the rect, x2 is the bottom right x of the rect and y2 is the bottom right y of the rect.

    ```shell
    ssd1681 (-e basic-rect | --example=basic-rect) --x1=<x1> --y1=<y1> --x2=<x2> --y2=<y2> [--mode=<RED | BLACK>] [--color=<0 | 1>]
    ```

#### 3.2 Command Example

```shell
ssd1681 -i

ssd1681: chip is Solomon Systech SSD1681.
ssd1681: manufacturer is Solomon Systech.
ssd1681: interface is SPI.
ssd1681: driver version is 1.0.
ssd1681: min supply voltage is 2.2V.
ssd1681: max supply voltage is 3.7V.
ssd1681: max current is 500.00mA.
ssd1681: max temperature is 85.0C.
ssd1681: min temperature is -40.0C.
```

```shell
ssd1681 -p

ssd1681: SPI interface SCK connected to GPIOA PIN5.
ssd1681: SPI interface MISO connected to GPIOA PIN6.
ssd1681: SPI interface MOSI connected to GPIOA PIN7.
ssd1681: SPI interface CS connected to GPIOA PIN4.
ssd1681: cmd data gpio GPIO connected to GPIOB PIN1.
ssd1681: reset GPIO connected to GPIOA PIN0.
ssd1681: busy GPIO connected to GPIOA PIN8.
```

```shell
ssd1681 -t display

ssd1681: chip is Solomon Systech SSD1681.
ssd1681: manufacturer is Solomon Systech.
ssd1681: interface is SPI.
ssd1681: driver version is 1.0.
ssd1681: min supply voltage is 2.2V.
ssd1681: max supply voltage is 3.7V.
ssd1681: max current is 500.00mA.
ssd1681: max temperature is 85.0C.
ssd1681: min temperature is -40.0C.
ssd1681: start display test.
ssd1681: black color test.
ssd1681: gram rand point test.
ssd1681: font 12 test.
ssd1681: font 16 test.
ssd1681: font 24 test.
ssd1681: fill rect test.
ssd1681: draw picture test.
ssd1681: red color test.
ssd1681: gram rand point test.
ssd1681: font 12 test.
ssd1681: font 16 test.
ssd1681: font 24 test.
ssd1681: fill rect test.
ssd1681: draw picture test.
ssd1681: finish display test.
```

```shell
ssd1681 -e basic-str --str=12345abcdEFGH!@#$<>?{}[];<> --mode=BLACK --color=1

ssd1681: 12345abcdEFGH!@#$<>?{}[];<>.
```

```shell
ssd1681 -e basic-init

ssd1681: init success.
```

```shell
ssd1681 -e basic-deinit

ssd1681: deinit success.
```

```shell
ssd1681 -e basic-clear --mode=BLACK

ssd1681: clear success.
```

```shell
ssd1681 -e basic-point --x0=16 --y0=16 --mode=BLACK --color=1

ssd1681: write point 16 16 1.
```

```shell
ssd1681 -e basic-point --x0=16 --y0=16 --mode=BLACK 

ssd1681: read point 16 16 1.
```

```shell
ssd1681 -e basic-rect --x1=0 --y1=0 --x2=32 --y2=32 --mode=BLACK --color=1

ssd1681: write rect 0 0 32 32.
```

```shell
ssd1681 -h

Usage:
  ssd1681 (-i | --information)
  ssd1681 (-h | --help)
  ssd1681 (-p | --port)
  ssd1681 (-t display | --test=display)
  ssd1681 (-e basic-init | --example=basic-init)
  ssd1681 (-e basic-deinit | --example=basic-deinit)
  ssd1681 (-e basic-str | --example=basic-str) [--str=<string>] [--mode=<RED | BLACK>] [--color=<0 | 1>]
  ssd1681 (-e basic-clear | --example=basic-clear) [--mode=<RED | BLACK>]
  ssd1681 (-e basic-point | --example=basic-point) --x0=<x0> --y0=<y0> [--mode=<RED | BLACK>] [--color=<0 | 1>]
  ssd1681 (-e basic-rect | --example=basic-rect) --x1=<x1> --y1=<y1> --x2=<x2> --y2=<y2> [--mode=<RED | BLACK>] [--color=<0 | 1>]

Options:
      --color=<0 | 1>     Set the chip color.([default: 1])
  -e <basic-init | basic-deinit | basic-str | basic-clear | basic-point | basic-rect>, --example=
     <basic-init | basic-deinit | basic-str | basic-clear | basic-point | basic-rect>
                          Run the driver example.
  -h, --help              Show the help.
  -i, --information       Show the chip information.
      --mode=<RED | BLACK>
                          Set the chip display mode.([default: BLACK])
  -p, --port              Display the pin connections of the current board.
      --str=<string>      Set the display string.([default: libdriver])
  -t <display>, --test=<display>
                          Run the driver test.
      --x0=<x0>           Set the x0 and it is the x of the point.
      --x1=<x1>           Set the x1 and it is the top left x of the rect.
      --x2=<x2>           Set the x2 and it is the bottom right x of the rect.
      --y0=<y0>           Set the y0 and it is the y of the point.
      --y1=<y1>           Set the y1 and it is the top left y of the rect.
      --y2=<y2>           Set the y2 and it is the bottom right y of the rect.
```

