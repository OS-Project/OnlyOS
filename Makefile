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
    ${ROOT}/syscalls/standard/libc.a \
    ${ROOT}/syscalls/standard/libg.a \
    ${ROOT}/syscalls/libm.a \
    ${ROOT}/syscalls/libgcc.a

all: ${OBJ} ${SYSCALLS_SRC}/syscalls.o
	@echo "### Compilation du système"
	@echo "\n## Compilation des drivers"
	@(cd ${DRIVER_SRC}; make)

	@echo "\n## Compilation de la HAL"
	@(cd ${HAL_SRC}; make)

	@echo "\n## Assemblage des drivers, de la HAL, et de la lib standard"
	@$(CC) -shared -o libfunc.a ${LIBS} ${SYSCALLS_SRC}/syscalls.c ${CCFLAGS}
	@(mkdir -p ${BIN_LIBS_SRC}; mv libfunc.a ${BIN_LIBS_SRC}/libfunc.a)
	@make clean

clean:
	@rm -rf ${OBJ} ${SYSCALLS_SRC}/syscalls.o

include ${ROOT}/build/makefuncs