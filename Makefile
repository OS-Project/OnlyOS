# Created by Thibault PIANA
# Creation : 19/12/2015

ROOT=.
FILE_NAME = kernel
include ${ROOT}/build/makedefs

SRC = ${shell python scripts/create_src_list.py}
OBJ = $(SRC:.c=.o)

all: INIT_MAKE ${OBJ}
	@echo "\n### Linkage des sources"
	$(LD) -T ${LINKER_PATH} ${LDFLAGS} ${OBJ} -o ${FILE_NAME}.elf -lgcc
	$(PREFIX)-objdump -D ${FILE_NAME}.elf > ${FILE_NAME}.list
	$(PREFIX)-objcopy ${FILE_NAME}.elf -O srec ${FILE_NAME}.srec
	$(PREFIX)-nm ${FILE_NAME}.elf -n > ${FILE_NAME}.sections
	$(PREFIX)-objcopy ${FILE_NAME}.elf -O binary ${FILE_NAME}.bin
	mv ${FILE_NAME}.bin boot.bin

	@make clean

clean:
	@rm -rf ${OBJ}

include ${ROOT}/build/makefuncs