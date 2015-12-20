# Created by Thibault PIANA
# Creation : 12/12/2015

ROOT=../../..
FILE_NAME = uart_test
include ${ROOT}/makedefs

SRC=${KERNEL_SRC}/kernel.c
OBJ=$(SRC:.c=.o) ${BOOT_SRC}/boot.o

LIB_PATH=-L${DRIVERS_SRC}

LIB=-lDrivers
all: ${OBJ}
	@echo "Linkage des sources"
	$(LD) -T ${ROOT}/linker.ld ${LDFLAGS} ${OBJ} -o ${FILE_NAME}.elf ${LIB_PATH} ${LIB}
	$(PREFIX)-objdump -D ${FILE_NAME}.elf > ${FILE_NAME}.list
	$(PREFIX)-objcopy ${FILE_NAME}.elf -O srec ${FILE_NAME}.srec
	$(PREFIX)-nm ${FILE_NAME}.elf -n > ${FILE_NAME}.sections
	$(PREFIX)-objcopy ${FILE_NAME}.elf -O binary ${FILE_NAME}.bin

	@make clean

EXEC:
	@echo "Compilation de la librairie DRIVER"
	@(cd ${DRIVER_SRC} && make)

clean:
	@(cd ${DRIVER_SRC} && make clean)
	@rm -rf ${OBJ}