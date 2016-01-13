# Created by Thibault PIANA
# Creation : 19/12/2015

ROOT=
FILE_NAME = lib_dTIMER.a

include ${ROOT}/build/makedefs

SRC=
OBJ= $(SRC:.c=.o)

all: ${OBJ}
	@echo "### Compilation du système"
	@(cd ${DRIVER_SRC}; make)
	@(cd ${HAL_SRC}; make)

	@(mkdir -p ${BIN_LIBS_SRC}/drivers; mv ${FILE_NAME} ${BIN_LIBS_SRC}/drivers/${FILE_NAME})
	@make clean

clean:
	@rm -rf ${OBJ}

include ${ROOT}/build/makefuncs