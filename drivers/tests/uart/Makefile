# Created by Thibault PIANA
# Creation : 12/12/2015

ROOT=../../..
FILE_NAME = uart_test
include ${ROOT}/build/makedefs

SRC=${DRIVER_SRC}/tests/uart/uart.c \
    ${DRIVER_SRC}/uart/uart.c \
    ${HAL_SRC}/uart/uart_irda_cir.c \
    ${SYSCALLS_SRC}/syscalls_io.c \
    ${SYSCALLS_SRC}/syscalls_mis.c \
    ${SYSCALLS_SRC}/syscalls_memory.c
OBJ=$(SRC:.c=.o) ${BOOT_SRC}/boot.o

all: INIT_MAKE ${OBJ}
	@echo "### Linkage des sources"
	$(LD) -T ${LINKER_PATH} ${LDFLAGS} ${OBJ} -o ${FILE_NAME}.elf ${INCLUDE_STD_LIB_C}
	$(PREFIX)-objdump -D ${FILE_NAME}.elf > ${FILE_NAME}.list
	$(PREFIX)-objcopy ${FILE_NAME}.elf -O srec ${FILE_NAME}.srec
	$(PREFIX)-nm ${FILE_NAME}.elf -n > ${FILE_NAME}.sections
	$(PREFIX)-objcopy ${FILE_NAME}.elf -O binary ${FILE_NAME}.bin
	mv ${FILE_NAME}.bin boot.bin

	@make clean

clean:
	@rm -rf ${OBJ}

include ${ROOT}/build/makefuncs