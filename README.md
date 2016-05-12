# OnlyOS
The operating system

# Filesystem driver
Todo
-----
- [ ] Handle exit/error.
- [ ] SVC calls handling.
- [ ] IRQ handling.
- [ ] Exceptions handling.
- [ ] Uart interrupts.
- [ ] File system (must code diskio.c)

# UART driver
Todo
-----
- [ ] uart_init(): causes crashes
- [ ] C++ support.
- [ ] Mettre uart_strLen dans un fichier util
- [X] Séparer les fichiers du syscalls.c

Questions
---------
- Operational mode configuration necesssary?
- uart_write_byte(): is UART_LSR_TX_SR_E necessary?
- uart_write_byte(): alternate version using diferrent register?
- uart_read_byte(): alternate version for signed values?

# Exceptions/interrupts handling
- kexit() or call to _exit() syscall ?
- Branch prediction p59 Cortex Guide.
- Disable interrupts in exit function

# Misc
How to compile a new source ?
-----------------------------
Create a file "makesrc" in the directory of the source(s) file(s) and add the name of the sources inside.
The script will automaticaly reconize the files and compile them

Questions
---------
- fichier tempo en C
- C init


How to compile newlib ?
-----------------------
./configure --target=arm-none-eabi --enable-interwork --enable-multilib --with-gnu-as --with-gnu-ld --disable-shared --disable-libssp --disable-libada --disable-newlib-supplied-syscalls --enable-lite-exit --disable-newlib-multithread

sources : https://gcc.gnu.org/ml/gcc-help/2012-08/msg00190.html
./configure --target=arm-none-eabi --enable-interwork --enable-multilib --with-newlib --disable-nls --disable-shared --disable-threads --with-gnu-ld --with-gnu-as --disable-libssp --disable-libmudflap --disable-libgomp --with-dwarf2 -v --disable-werror --with-cpu=cortex-a8 --with-mode=thumb --enable-target-optspace --with-fpu=fpv4-sp-d16 --with-float=soft --enable-languages=c,c++ --disable-newlib-multithread

with



Pour kmalloc : liballoc
