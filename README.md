# OnlyOS
The operating system

# Filesystem driver
Todo
-----
- [ ] File system (must code diskio.c)

# UART driver
Todo
-----
- [ ] uart_init(): causes crashes
- [x] uart_write_byte()
- [x] uart_read_byte()
- [ ] C++ support.

Questions
---------
- Operational mode configuration necesssary?
- uart_write_byte(): is UART_LSR_TX_SR_E necessary?
- uart_write_byte(): alternate version using diferrent register?
- uart_read_byte(): alternate version for signed values?


# Others
Questions
---------
- fichier tempo en C
- C init

How to compile newlib ?
---------
./configure --target=arm-none-eabi --enable-interwork --enable-multilib --with-gnu-as --with-gnu-ld --disable-shared --disable-libssp --disable-libada --disable-newlib-supplied-syscalls --enable-lite-exit --disable-newlib-multithread

sources : https://gcc.gnu.org/ml/gcc-help/2012-08/msg00190.html
./configure --target=arm-none-eabi --enable-interwork --enable-multilib --with-newlib --disable-nls --disable-shared --disable-threads --with-gnu-ld --with-gnu-as --disable-libssp --disable-libmudflap --disable-libgomp --with-dwarf2 -v --disable-werror --with-cpu=cortex-a8 --with-mode=thumb --enable-target-optspace --with-fpu=fpv4-sp-d16 --with-float=soft --enable-languages=c,c++ --disable-newlib-multithread

with