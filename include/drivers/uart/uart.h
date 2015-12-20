#ifdef __cplusplus
extern "C" {
#endif

#ifndef DRIVER_UART_H
    #define DRIVER_UART_H
    #define HW_GET_REG_WORD(addr) (*(volatile unsigned int *) (addr))
    #define HW_GET_REG_BYTE(addr) (*(volatile unsigned char *) (addr))
    #define HW_SET_REG_WORD(addr, val) (*(volatile unsigned int *) (addr) = (unsigned int) (val))
    #define HW_SET_REG_BYTE(addr, val) (*(volatile unsigned char *) (addr) = (unsigned char) (val))
    #define HW_OR_REG_WORD(addr, val) (*(volatile unsigned int *) (addr) = HW_GET_REG_WORD(addr) | ((unsigned int) (val)))
    #define HW_OR_REG_BYTE(addr, val) (*(volatile unsigned char *) (addr) = HW_GET_REG_BYTE(addr) | ((unsigned char) (val)))

    #include "hw_uart_irda_cir.h"

    #define UART0_BASE          (0x44E09000)
    #define CONF_UART0_RXD      (0x44E10970)
    #define CONF_UART0_TXD      (0x44E10974)

    #define CM_WKUP_CLKSTCTRL       (0x44E00400)
    #define CM_WKUP_UART0_CLKCTRL   (0x44E004B4)
    #define CM_PER_L4HS_CLKSTCTRL   (0x44E0011C)

    #define GPIO1_SETDATAOUT        (0x4804C194)
    #define GPIO1_CLEARDATAOUT      (0x4804C190)

    void UART_init();
    void UART_writeByte(char c);
    void UART_writeStr(char* str, int length);
    void UART_newline();
    char UART_readByte();

    void UART_write(const char *str);
    void UART_writeLn(const char *str);
    unsigned int UART_strlen(const char *str);
#ifdef __cplusplus
}
#endif
#endif