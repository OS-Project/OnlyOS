# Created by Thibault PIANA
# Creation : 19/12/2015

ROOT=../..
FILE_NAME = libdUART.a

include ${ROOT}/build/makedefs

SRC=${DRIVER_SRC}/uart/uart.c \
    ${HAL_SRC}/uart/uart_irda_cir.c
OBJ= $(SRC:.c=.o)

all: ${OBJ}
	@echo "Creation de la librairie ${FILE_NAME}"
	@$(CC) -shared -o ${FILE_NAME} ${OBJ} ${CCFLAGS}

clean:
	@rm -rf ${OBJ}
	@rm -rf ${FILE_NAME}