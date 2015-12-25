# Created by Thibault PIANA
# Creation : 25/12/2015

ROOT=../..
FILE_NAME = LibDriver.a
include ${ROOT}/makedefs

LIBS_PATHS=-L${DRIVER_SRC}/uart \
    -L${DRIVER_SRC}/gpio

LIBS=-ldUART \
    -ldGPIO

all: EXEC
	@echo "Linkage des sources"
	$(LD) -T ${ROOT}/linker.ld ${LDFLAGS} -o ${FILE_NAME} ${LIBS_PATHS} ${LIBS}

	@make clean

EXEC:
	@echo "Compilation de la lib UART"
	@(cd ${DRIVER_SRC}/uart && make)

	@echo "Compilation de la lib GPIO"
	@(cd ${DRIVER_SRC}/gpio && make)

clean:
	@echo "Nettoyage de la lib GPIO"
	@(cd ${DRIVER_SRC}/gpio && make clean)

	@echo "Nettoyage de la lib UART"
	@(cd ${DRIVER_SRC}/uart && make clean)