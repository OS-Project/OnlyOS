# Created by Thibault PIANA
# Creation : 12/12/2015

ROOT=../../..
FILE_NAME = fs_test
include ${ROOT}/makedefs

SRC=${DRIVER_SRC}/tests/fs/fs.c \
    ${HAL_SRC}/mmcsd/hs_mmcsd.c \
    ${SYSCALL_SRC}/syscall.c \
    ${DRIVER_SRC}/uart/uart.c \
    ${HAL_SRC}/uart/uart_irda_cir.c
OBJ=$(SRC:.c=.o) ${BOOT_SRC}/boot.o

all: ${OBJ}
	@echo "Linkage des sources"
	$(LD) -T ${LINKER_PATH} ${LDFLAGS} ${OBJ} -o ${FILE_NAME}.elf -L${ROOT}/syscall -lc -lg -lm -lgcc
	$(PREFIX)-objdump -D ${FILE_NAME}.elf > ${FILE_NAME}.list
	$(PREFIX)-objcopy ${FILE_NAME}.elf -O srec ${FILE_NAME}.srec
	$(PREFIX)-nm ${FILE_NAME}.elf -n > ${FILE_NAME}.sections
	$(PREFIX)-objcopy ${FILE_NAME}.elf -O binary ${FILE_NAME}.bin
	mv ${FILE_NAME}.bin boot.bin

	@make clean

clean:
	@rm -rf ${OBJ}