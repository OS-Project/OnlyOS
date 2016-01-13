# Created by Thibault PIANA
# Creation : 19/12/2015

ROOT=.

include ${ROOT}/build/makedefs

SRC=${KERNEL_SRC}/kernel.c \
    ${KERNEL_SRC}/console.c \
    ${KERNEL_SRC}/drivers/drivers.c
OBJ= $(SRC:.c=.o) boot/boot.o

LIBS=${BIN_LIBS_SRC}/drivers/lib_dUART.a \
    ${BIN_LIBS_SRC}/drivers/lib_dGPIO.a \
    ${BIN_LIBS_SRC}/drivers/lib_dTIMER.a \
    ${BIN_LIBS_SRC}/hal/lib_HAL.a

all: ${OBJ}
	@echo "### Compilation du système"
	@echo "\n## Compilation des drivers"
	@(cd ${DRIVER_SRC}; make)

	@echo "\n## Compilation de la HAL"
	@(cd ${HAL_SRC}; make)

	@echo "\n## Assemblage des drivers et de la HAL"
	@$(CC) -shared -o libfunc.a ${LIBS} ${CCFLAGS}
	@(mkdir -p ${BIN_LIBS_SRC}; mv libfunc.a ${BIN_LIBS_SRC}/libfunc.a)
	@make clean

clean:
	@rm -rf ${OBJ} ${SYSCALLS_SRC}/syscalls.o

include ${ROOT}/build/makefuncs