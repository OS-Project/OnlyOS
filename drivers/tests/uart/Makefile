# Created by Thibault PIANA
# Creation : 12/12/2015

ROOT=../../..
FILE_NAME = uart_test
include ${ROOT}/makedefs

SRC=${DRIVER_SRC}/tests/uart/uart.c
OBJ=$(SRC:.c=.o) ${BOOT_SRC}/boot.o

all: EXEC ${OBJ}
	@echo "Linkage des sources"
	$(LD) -T ${ROOT}/linker.ld -o ${FILE_NAME}.elf ${OBJ} ${LDFLAGS} -L${DRIVER_SRC}/uart/ -ldUART
	$(PREFIX)-objdump -D ${FILE_NAME}.elf > ${FILE_NAME}.list
	$(PREFIX)-objcopy ${FILE_NAME}.elf -O srec ${FILE_NAME}.srec
	$(PREFIX)-nm ${FILE_NAME}.elf -n > ${FILE_NAME}.sections
	$(PREFIX)-objcopy ${FILE_NAME}.elf -O binary ${FILE_NAME}.bin

	@make clean

EXEC:
	@echo "Compilation de la librairy UART"
	@(cd ${DRIVER_SRC}/uart && make)

clean:
	@(cd ${DRIVER_SRC}/uart && make clean)
	@rm -rf ${OBJ}