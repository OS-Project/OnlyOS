# Created by Thibault PIANA
# Creation : 19/12/2015

ROOT=../..
FILE_NAME = lib_dUART.a

include ${ROOT}/build/makedefs

SRC=${DRIVER_SRC}/uart/uart.c
OBJ= $(SRC:.c=.o)

all: ${OBJ}
	@echo "# Creation de la librairie ${FILE_NAME}"
	@$(CC) -shared -o ${FILE_NAME} ${OBJ} ${CCFLAGS}
	@(mkdir -p ${BIN_LIBS_SRC}; mv ${FILE_NAME} ${BIN_LIBS_SRC}/drivers/${FILE_NAME})
	@make clean

clean:
	@rm -rf ${OBJ}

include ${ROOT}/build/makefuncs