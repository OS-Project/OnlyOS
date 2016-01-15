# Adapted by Thibault PIANA & Alan Gardin
# Creation : 13/01/2016

ROOT=..
FILE_NAME = libdrivers.a

include ${ROOT}/build/makedefs
SRC =
SRC += $(wildcard gpio/*.c)
SRC += $(wildcard uart/*.c)
SRC += $(wildcard timer/*.c)

OBJ= $(SRC:.c=.o)

all: ${OBJ}
	@echo "# Assemblage des librairies en ${FILE_NAME}"
	@$(AR) -rv ${FILE_NAME} ${OBJ}
	@(mkdir -p ${BIN_LIBS_SRC}; mv ${FILE_NAME} ${BIN_LIBS_SRC}/${FILE_NAME})
	@make clean

clean:
	@rm -rf ${OBJ}

include ${ROOT}/build/makefuncs


