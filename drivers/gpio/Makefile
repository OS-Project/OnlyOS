# Created by Thibault PIANA
# Creation : 12/12/2015

ROOT=../..
FILE_NAME = libdGPIO.a

include ${ROOT}/makedefs

SRC=${DRIVER_SRC}/gpio/gpio.c	 \
     ${HAL_SRC}/gpio/gpio_v2.c

OBJ= $(SRC:.c=.o)

all: ${OBJ}
	$(LD) -T ${ROOT}/linker.ld ${OBJ} -o ${FILE_NAME} ${LDFLAGS}
	@make clean

%.o: %.c
	@$(CC) -o $@ -c $< $(CCLAGS)


clean:
	@rm -rf ${OBJ}