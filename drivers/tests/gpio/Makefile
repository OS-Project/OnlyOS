# Created by Thibault PIANA
# Creation : 12/12/2015

ROOT=../../..
FILE_NAME = gpio_test
include ${ROOT}/makedefs

SRC=${DRIVER_SRC}/tests/gpio/gpio.c
OBJ=$(SRC:.c=.o)

all: EXEC ${OBJ}
	@echo "Linkage"
	$(LD) -T ${ROOT}/linker.ld -o ${FILE_NAME}.elf ${ROOT}/boot/boot.o ${OBJ} ${LDFLAGS} -L${DRIVER_SRC}/gpio/ -ldGPIO

	$(PREFIX)-objdump -D ${FILE_NAME}.elf > ${FILE_NAME}.list
	$(PREFIX)-objcopy ${FILE_NAME}.elf -O srec ${FILE_NAME}.srec
	$(PREFIX)-nm ${FILE_NAME}.elf -n > ${FILE_NAME}.sections
	$(PREFIX)-objcopy ${FILE_NAME}.elf -O binary ${FILE_NAME}.bin

	@make clean

EXEC:
	@echo "Compilation de la librairy GPIO"
	@(cd ${DRIVER_SRC}/gpio && make)

%.o: %.c
	@echo "Compilation de $^"
	@$(CC) -o $@ -c $< $(CCLAGS)

clean:
	@rm -rf ${OBJ}