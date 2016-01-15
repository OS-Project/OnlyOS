# Created by Thibault PIANA
# Creation : 19/12/2015

ROOT=.
FILE_NAME = kernel.bin
include ${ROOT}/build/makedefs

SRC=${KERNEL_SRC}/kernel.c \
    ${KERNEL_SRC}/drivers/drivers.c \
    ${SYSCALLS_SRC}/syscalls.c

OBJ= $(SRC:.c=.o) boot/boot.o

all: libs ${OBJ}
	@echo "\n### Linkage des sources"
	$(LD) -T ${LINKER_PATH} ${LDFLAGS} ${OBJ} -o ${FILE_NAME}.elf ${INCLUDE_STD_LIB_C} -lhal -ldrivers
	$(PREFIX)-objdump -D ${FILE_NAME}.elf > ${FILE_NAME}.list
	$(PREFIX)-objcopy ${FILE_NAME}.elf -O srec ${FILE_NAME}.srec
	$(PREFIX)-nm ${FILE_NAME}.elf -n > ${FILE_NAME}.sections
	$(PREFIX)-objcopy ${FILE_NAME}.elf -O binary ${FILE_NAME}.bin
	mv ${FILE_NAME}.bin boot.bin

	@make clean

libs:
	@echo "### Compilation du système"
	@echo "\n## Archivage des drivers"
	@(cd ${DRIVER_SRC}; make)

	@echo "\n## Archivage de la HAL"
	@(cd ${HAL_SRC}; make)
	#@echo "\n## Archivage final des drivers"
	#@(cd ${BIN_LIBS_SRC}/hal; ${AR} -x libhal.a)
	#@(cd ${BIN_LIBS_SRC}/drivers; ${AR} -x libdrivers.a)
    #@$(AR) -rv ${BIN_LIBS_SRC}/libfunc.a ${OBJ}
clean:
	@rm -rf ${OBJ}

include ${ROOT}/build/makefuncs