all: drivers.c
	@echo "Compiling drivers..."
	arm-none-eabi-gcc -nodefaultlibs -nostdlib -nostartfiles -ffreestanding -mcpu=cortex-a8 -march=armv7-a -pedantic -Wextra -std=c99 -O0 drivers.c -o ../drivers.out
