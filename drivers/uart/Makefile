# Created by Thibault PIANA
# Creation : 19/12/2015

ROOT=../..
FILE_NAME = libdUART.a

include ${ROOT}/makedefs

SRC=${DRIVER_SRC}/uart/uart.c

OBJ= $(SRC:.c=.o)

all: ${OBJ}
	@echo "Creation de la librairie ${FILE_NAME}"
	@$(LD) ${OBJ} -o ${FILE_NAME} ${LDFLAGS}

clean:
	@rm -rf ${OBJ}
	@rm -rf ${FILE_NAME}