### 1. Board

#### 1.1 Board Info

Board Name: Raspberry Pi 4B.

SPI Pin: SCLK/MOSI/MISO/CS GPIO11/GPIO10/GPIO9/GPIO8.

GPIO Pin: RESET/CMD_DATA/BUSY_GPIO GPIO27/GPIO22/GPIO17.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```

#### 2.2 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.3 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
# open another terminal
./ssd1681_server 

# use the CMake terminal
make test
```

Find the compiled library in CMake. 

```cmake
find_package(ssd1681 REQUIRED)
```
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

#### 3.2 How to run

```shell
# open one terminal and run the server
./ssd1681_server 
```
```shell
# open another terminal and sent the command
./ssd1681 xxx xxx xxx ...
```

#### 3.3 Command Example

```shell
./ssd1681 -i

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
./ssd1681 -p

ssd1681: SPI interface SCK connected to GPIO11(BCM).
ssd1681: SPI interface MISO connected to GPIO9(BCM).
ssd1681: SPI interface MOSI connected to GPIO10(BCM).
ssd1681: SPI interface CS connected to GPIO8(BCM).
ssd1681: cmd data gpio GPIO connected to GPIO22(BCM).
ssd1681: reset GPIO connected to GPIO27(BCM).
ssd1681: busy GPIO connected to GPIO17(BCM).
```

```shell
./ssd1681 -t display

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
./ssd1681 -e basic-str --str=12345abcdEFGH --mode=BLACK --color=1

ssd1681: 12345abcdEFGH.
```

```shell
./ssd1681 -e basic-init

ssd1681: init success.
```

```shell
./ssd1681 -e basic-deinit

ssd1681: deinit success.
```

```shell
./ssd1681 -e basic-clear --mode=BLACK

ssd1681: clear success.
```

```shell
./ssd1681 -e basic-point --x0=16 --y0=16 --mode=BLACK --color=1

ssd1681: write point 16 16 1.
```

```shell
./ssd1681 -e basic-point --x0=16 --y0=16 --mode=BLACK 

ssd1681: read point 16 16 1.
```

```shell
./ssd1681 -e basic-rect --x1=0 --y1=0 --x2=32 --y2=32 --mode=BLACK --color=1

ssd1681: write rect 0 0 32 32.
```

```shell
./ssd1681 -h

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

