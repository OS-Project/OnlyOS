# Adapted by Thibault PIANA & Alan Gardin
# Creation : 13/01/2016

ROOT=..
FILE_NAME = lib_drivers.a

include ${ROOT}/build/makedefs

OBJ=${BIN_LIBS_SRC}/drivers/lib_dUART.a \
    #${BIN_LIBS_SRC}/drivers/lib_dGPIO.a \
    ${BIN_LIBS_SRC}/drivers/lib_dTIMER.a

all:
	@echo "## Compilation des drivers"
	@(cd timer; make)
	#@(cd gpio; make)
	@(cd uart; make)

	@echo "Assemblage des librairies en ${FILE_NAME}"
	@$(CC) -shared -o ${FILE_NAME} ${OBJ} ${CCFLAGS}
	@(mkdir -p ${BIN_LIBS_SRC}/drivers; mv ${FILE_NAME} ${BIN_LIBS_SRC}/drivers/${FILE_NAME})
clean:
	@rm -rf ${OBJ}

include ${ROOT}/build/makefuncs


