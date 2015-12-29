#ifdef __cplusplus
extern "C" {
#endif

#ifndef DRIVER_UART_H
#define DRIVER_UART_H
    #include "hw_uart_irda_cir.h"
    #include "hal/uart/uart_irda_cir.h"
    #include "soc_AM335x.h"

    /* Write */
    void UART_writeByte(const char data);
    int UART_write(const char *pcBuf, unsigned int len);

    void UART_newline();
    void UART_writeLn(char *str);
    void UART_writeStr(char *str);

    /* Read */
    char UART_readByte();
    int UART_read(char *pRxBuffer, int numBytesToRead);

    /* Other */
    unsigned int UART_strlen(char *str);
#endif

#ifdef __cplusplus
}
#endif