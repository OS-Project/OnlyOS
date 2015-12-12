# Created by Thibault PIANA
# Creation : 22/10/2015

include ${ROOT}/makedefs

ROOT=../../
FILE_NAME = lib.a


SOURCE=${DRIVER_SRC}/gpio/gpio.c	 \
    ${ARCH_SRC}/hal/gpio/gpio_v2.c

OBJ= $(SRC:.c=.o)

all: ${OBJ}
	mv *.o obj/
	$(CC)-ld -T ${ROOT}/linker.ld $^ -o lib.a

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf ${OBJ}