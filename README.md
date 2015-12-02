# OnlyOS
The operating system

# UART driver
Uart driver for the BeagleBone Black

Todo
-----
- [ ] uart_init()
- [x] uart_write_byte()
- [x] uart_read_byte()
- [ ] Makefile.
- [ ] C++ support.
- [ ] File system (must code diskio.c)

Questions
---------
- Operational mode configuration necesssary?
- uart_write_byte(): is UART_LSR_TX_SR_E necessary?
- uart_write_byte(): alternate version using diferrent register?
- uart_read_byte(): alternate version for signed values?



fichier tempo en C