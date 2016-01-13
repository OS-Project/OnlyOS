# Adapted by Thibault PIANA & Alan Gardin
# First modification : 20/10/2015
# Last modification : 22/10/2015

ROOT=../../..
FILE_NAME = lib_HAL.a

include ${ROOT}/build/makedefs

SRC=${HAL_SRC}/timer/dmtimer.c	 \
    ${HAL_SRC}/uart/uart_irda_cir.c   \
    ${HAL_SRC}/gpio/gpio_v2.c	 \
    ${HAL_SRC}/timer/watchdog.c	\
    ${HAL_SRC}/timer/rtc.c
OBJ= $(SRC:.c=.o)

all: ${OBJ}
	@echo "# Creation de la librairie ${FILE_NAME}"
	@$(CC) -shared -o ${FILE_NAME} ${OBJ} ${CCFLAGS}
	@(mkdir -p ${BIN_LIBS_SRC}/hal; mv ${FILE_NAME} ${BIN_LIBS_SRC}/hal/${FILE_NAME})
	@make clean

clean:
	@rm -rf ${OBJ}

include ${ROOT}/build/makefuncs

