#ifndef UART_H
#define UART_H
    #define HW_GET_REG_WORD(addr) (*(volatile unsigned int *) (addr))
    #define HW_GET_REG_BYTE(addr) (*(volatile unsigned char *) (addr))
    #define HW_SET_REG_WORD(addr, val) (*(volatile unsigned int *) (addr) = (unsigned int) (val))
    #define HW_SET_REG_BYTE(addr, val) (*(volatile unsigned char *) (addr) = (unsigned char) (val))
    #define HW_OR_REG_WORD(addr, val) (*(volatile unsigned int *) (addr) = HW_GET_REG_WORD(addr) | ((unsigned int) (val)))
    #define HW_OR_REG_BYTE(addr, val) (*(volatile unsigned char *) (addr) = HW_GET_REG_BYTE(addr) | ((unsigned char) (val)))

    #include "hw_uart.h"

    #define UART0_BASE  0x44E09000

    void uart_init();
    void uart_write_byte(char c);
    char uart_read_byte();

#endif
