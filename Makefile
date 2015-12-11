CC=arm-linux-gnueabihf

all:
	$(CC)-gcc -Wall -c -mcpu=cortex-a8 -nostdlib -nostartfiles -ffreestanding  src/main.c
	$(CC)-gcc -Wall -c -mcpu=cortex-a8 -nostdlib -nostartfiles -ffreestanding  src/uart.c
	mv *.o obj/
	$(CC)-as --warn -mcpu=cortex-a8 src/boot.s -o obj/boot.o
	$(CC)-ld -T linker.ld obj/boot.o obj/main.o obj/uart.o -o boot.elf
	$(CC)-objdump -D boot.elf > boot.list
	$(CC)-objcopy boot.elf -O srec boot.srec
	$(CC)-nm boot.elf -n > boot.sections
	$(CC)-objcopy boot.elf -O binary boot.bin

clean:
	rm -rf obj/
	mkdir obj
	rm boot.bin  boot.elf  boot.list  boot.srec boot.sections

