CC     := gcc
SRC1   := $(wildcard ./interface/src/*.c) \
		  $(wildcard ./driver/src/*.c) \
		  $(wildcard ./src/main.c) \
		  $(wildcard ../../src/*.c) \
		  $(wildcard ../../test/*.c) \
		  $(wildcard ../../example/*.c)
LIBS   := -lgpiod
CFLAGS := -O3 \
		  -I ./interface/inc/ \
		  -I ../../interface/ \
		  -I ../../src/ \
		  -I ../../test/ \
		  -I ../../example/
all: ssd1681_server ssd1681
ssd1681_server : $(SRC1)
		 "$(CC)" $(CFLAGS) $^ $(LIBS) -o $@
SRC2   := $(wildcard ./src/client.c)
ssd1681 : $(SRC2)
		 "$(CC)" $(CFLAGS) $^ $(LIBS) -o $@