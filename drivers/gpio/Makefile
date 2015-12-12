# Created by Thibault PIANA
# Creation : 12/12/2015

ROOT=../..
FILE_NAME = lib.a

include ${ROOT}/makedefs

SRC=${DRIVER_SRC}/gpio/gpio.c	 \
     ${HAL_SRC}/gpio/gpio_v2.c

OBJ= $(SRC:.c=.o)

all: ${OBJ}
	$(LD) -T ${ROOT}/linker.ld ${OBJ} -o ${FILE_NAME} -nostdlib -nostartfiles
	make clean

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)


clean:
	rm -rf ${OBJ}