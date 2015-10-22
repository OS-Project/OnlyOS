# Created by Thibault PIANA
# First modification : 22/10/2015
# Last modification : 22/10/2015

ROOT=../
FILE_NAME = lib_driver.a

DEVICE=am335x

include ${ROOT}/makedefs

SOURCE=${DRIVER_SRC}/gpio/driver_gpio.c	 \

all: debug release

debug:
	mkdir -p Debug
	$(CC) $(CFLAGS) -g $(SOURCE)
	$(AR) $(ARFLAGS) Debug/${FILE_NAME} *.o*
	@mv *.o* Debug/
	@mkdir -p ${DRIVER_BIN}/Debug
	@cp Debug/${FILE_NAME} ${DRIVER_BIN}/Debug/${FILE_NAME}

release:
	mkdir -p Release
	$(CC) $(CFLAGS) -g -O2 $(SOURCE)
	$(AR) $(ARFLAGS) Release/${FILE_NAME} *.o*
	@mv *.o* Release/
	@mkdir -p ${DRIVER_BIN}/Release
	@cp Release/${FILE_NAME} ${DRIVER_BIN}/Release/${FILE_NAME}

clean:
	@rm -rf Debug Release ${DRIVER_BIN}/Debug ${DRIVER_BIN}/Release


