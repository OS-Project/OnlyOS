# Created by Thibault PIANA
# Creation : 12/12/2015

ROOT=../..
FILE_NAME = libdGPIO.a

include ${ROOT}/makedefs

SRC=${DRIVER_SRC}/gpio/gpio.c	 \
     ${HAL_SRC}/gpio/gpio_v2.c

OBJ= $(SRC:.c=.o)

all: ${OBJ}
	@echo "Creation de la librairie ${FILE_NAME}"
	@$(LD) ${OBJ} -o ${FILE_NAME} ${LDFLAGS}

clean:
	@rm -rf ${OBJ}
	@rm -rf ${FILE_NAME}