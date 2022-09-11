### 1. chip

#### 1.1 chip info

chip name : Raspberry Pi 4B

spi pin: SCLK/MOSI/MISO/CS GPIO11/GPIO10/GPIO9/GPIO8

gpio pin: RESET/CMD_DATA/BUSY_GPIO GPIO27/GPIO22/GPIO17

### 2. shell

#### 2.1 install info

```shell
sudo apt-get install libgpiod-dev

make
```

#### 2.2 run server

```shell
./ssd1306_server 
```

### 3. ssd1681

#### 3.1 command Instruction

​            ssd1681 is a basic command which can test all ssd1681 driver function:

​            -i        show ssd1681 chip and driver information.

​            -h       show ssd1681 help.

​            -p       show ssd1681 pin connections of the current board.

​            -t display

​            -t display        run ssd1681 display test. 

​            -c basic (-init | -deinit | (-r | -b) -str <string> |  (-r | -b) -clear | (-r | -b)  -writepoint <x> <y> <data> | (-r | -b)  -readpoint <x> <y> |  (-r | -b)  -rect <x1> <y1> <x2> <y2>)

​            -c basic -init        run ssd1681 init function. 

​            -c basic -deinit        run ssd1681 deinit function. 

​            -c basic  (-r | -b)  -str <string>        run ssd1681 show string function. string is the shown string. 

​            -c basic (-r | -b)  -clear        run ssd1681 clear screen function. 

​            -c basic (-r | -b)  -writepoint <x> <y> <data>        run ssd1681 writepoint function. 

​            -c basic (-r | -b)  -readpoint <x> <y>        run ssd1681 readpoint function.

​            -c basic (-r | -b)  -rect <x1> <y1> <x2> <y2>        run ssd1681 drawing rectangle function. x1 means x start. y1 means y start. x2 means x end. y2 means y end.

#### 3.2 command example

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

ssd1681: SPI interface SCK connected to GPIOA PIN5.
ssd1681: SPI interface MISO connected to GPIOA PIN6.
ssd1681: SPI interface MOSI connected to GPIOA PIN7.
ssd1681: SPI interface CS connected to GPIOA PIN4.
ssd1681: cmd data gpio GPIO connected to GPIO22.
ssd1681: reset GPIO connected to GPIO27.
ssd1681: busy GPIO connected to GPIO17.
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
./ssd1681 -c basic -b -str 12345abcdEFGH

ssd1681: 12345abcdEFGH.
```

```shell
./ssd1681 -c basic -init 

ssd1681: init success.
```

```shell
./ssd1681 -c basic -deinit

ssd1681: deinit success.
```

```shell
./ssd1681 -c basic -b -clear 

ssd1681: clear success.
```

```shell
./ssd1681 -c basic -b -writepoint 16 16 1

ssd1681: write point 16 16 1.
```

```shell
./ssd1681 -c basic -b -readpoint 16 16

ssd1681: read point 16 16 1.
```

```shell
./ssd1681 -c basic -b -rect 0 0 32 32

ssd1681: write rect 0 0 32 32.
```

```shell
./ssd1681 -h

ssd1681 -i
	show ssd1681 chip and driver information.
ssd1681 -h
	show ssd1681 help.
ssd1681 -p
	show ssd1681 pin connections of the current board.
ssd1681 -t display
	run ssd1681 display test.
ssd1681 -c basic -init
	run ssd1681 init function.
ssd1681 -c basic -deinit
	run ssd1681 deinit function.
ssd1681 -c basic (-r | -b) -str <string>
	run ssd1681 show string function.string is the shown string.
ssd1681 -c basic (-r | -b) -clear
	run ssd1681 clear screen function.
ssd1681 -c basic (-r | -b) -writepoint <x> <y> <data>
	run ssd1681 writepoint function.
ssd1681 -c basic (-r | -b) -readpoint <x> <y>
	run ssd1681 readpoint function.
ssd1681 -c basic (-r | -b) -rect <x1> <y1> <x2> <y2>
	run ssd1681 drawing rectangle function.x1 means x start.y1 means y start.x2 means x end.y2 means y end.
```

