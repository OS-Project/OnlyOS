# OnlyOS
The operating system

# Kernel
- [ ] kexit() or call to _exit() syscall ?
- [x] Disable interrupts in exit function


# Boot
- [x] Disable fiq, enable irq.
- [x] Check flags values for processor modes in the doc.
- [x] Check flags values for irq and fiq in the doc.
- [x] Stack implementation: FA, FD, EA, ED? Currently ED.
- [x] Init stacks for all modes. Stack sizes in boot.s must match the linker script.
- [x] Clear .bss section.
- [x] Call main function: do not use branch. Address may be out of range.
- [x] Linker script.
- [ ] Prefetch abort and data abort modes differences?
- [ ] Branch prediction p59 Cortex Guide.


# Interrupts/Exceptions handling
- [x] Interruption table.
- [x] Svc call.
- [x] Svc handler
- [x] Abort handler
- [x] Undefined instruction handler
- [ ] Irq handler
- [x] Fiq handler: print message.

|    Value   | r0 Code       |     r1                     |   r2                   | return (r0)            |  
| ---------- | ------------- | -------------------------- | ---------------------- | ---------------------- |  
| error      | 0x00000       |  Error number              | Undefined              | 0 if success, else 1   |  
| UART_putc  | 0x00100       |  the char to push          | Null                   | 0 if success, else 1   |  
| minit      | 0x00200       |  process heap_start adress | Null                   | 0 if success, else 1   |  
| kmalloc    | 0x00201       |  process heap_start adress | Null                   | adress of memory block |  


# Filesystem driver
- [ ] File system (must code diskio.c)


# UART driver
- [ ] uart_init(): causes crashes
- [X] Mettre uart_strLen dans un fichier util
- [X] Séparer les fichiers du syscalls.c
- Operational mode configuration necesssary?
- uart_write_byte(): is UART_LSR_TX_SR_E necessary?
- uart_write_byte(): alternate version using diferrent register?
- uart_read_byte(): alternate version for signed values?


# Misc
How to compile a new source ?
-----------------------------
Create a file "makesrc" in the directory of the source(s) file(s) and add the name of the sources inside.  
The script will automaticaly reconize the files and compile them.  

Bugs for asm source files.  

Questions
---------
- fichier tempo en C
- [ ] Compilation: use arm instruction (-marm option in gcc)
- [x] Difference .code 32 and .arm: none.


How to compile newlib ?
-----------------------
./configure --target=arm-none-eabi --enable-interwork --enable-multilib --with-gnu-as --with-gnu-ld --disable-shared --disable-libssp --disable-libada --disable-newlib-supplied-syscalls --enable-lite-exit --disable-newlib-multithread

sources : https://gcc.gnu.org/ml/gcc-help/2012-08/msg00190.html
./configure --target=arm-none-eabi --enable-interwork --enable-multilib --with-newlib --disable-nls --disable-shared --disable-threads --with-gnu-ld --with-gnu-as --disable-libssp --disable-libmudflap --disable-libgomp --with-dwarf2 -v --disable-werror --with-cpu=cortex-a8 --with-mode=thumb --enable-target-optspace --with-fpu=fpv4-sp-d16 --with-float=soft --enable-languages=c,c++ --disable-newlib-multithread

