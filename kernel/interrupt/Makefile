CFLAGS=-I ../../include -c

all: interrupt.c interrupt.s
	@echo "Compiling interrupt..."
	arm-none-eabi-gcc $(CFLAGS) interrupt.c -o interrupt_c.out
	arm-none-eabi-as interrupt.s -o interrupt_asm.out
	arm-none-eabi-ar r ../interrupt.out interrupt_c.out interrupt_asm.out
	#arm-none-eabi-gcc $(CFLAGS) interrupt.s interrupt.c -o ../interrupt.out

clean:
	@rm *.out
