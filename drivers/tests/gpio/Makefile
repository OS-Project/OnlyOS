# Created by Thibault PIANA
# Creation : 12/12/2015

ROOT=../../..
FILE_NAME = gpio_test
include ${ROOT}/makedefs

SRC=${DRIVER_SRC}/tests/gpio/gpio.c	 \
OBJ= $(SRC:.c=.o)

all: ${OBJ}
	(cd ${DRIVER_SRC}/gpio && ${MAKE})

	$(LD) -T ${ROOT}/linker.ld ${OBJ} -o ${FILE_NAME}.elf ${DRIVER_SRC}/gpio/lib.a ${ROOT}/boot/boot.o ${LDFLAGS}

	$(PREFIX)-objdump -D ${FILE_NAME}.elf > ${FILE_NAME}.list
	$(PREFIX)-objcopy ${FILE_NAME}.elf -O srec ${FILE_NAME}.srec
	$(PREFIX)-nm ${FILE_NAME}.elf -n > ${FILE_NAME}.sections
	$(PREFIX)-objcopy ${FILE_NAME}.elf -O binary ${FILE_NAME}.bin

	make clean

%.o: %.c
	@$(CC) -o $@ -c $< $(CCLAGS)


clean:
	rm -rf ${OBJ}