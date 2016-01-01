#ifdef __cplusplus
extern "C" {
#endif

#ifndef DRIVER_UART_H
#define DRIVER_UART_H
    #include "hw_uart_irda_cir.h"
    #include "hal/uart/uart_irda_cir.h"
    #include "soc_AM335x.h"

    /* Write */
    void UART_writeByte(const char data, char uart_number);
    int UART_write(const char *pcBuf, int len, char uart_number);
    int UART_writeStr(char *str, char uart_number);

    /* Read */
    char UART_readByte(char uart_number);
    int UART_read(char *pRxBuffer, int numBytesToRead, char uart_number);

    /* Other */
    unsigned int UART_getPhysicalAdress(char uart_number);
    int UART_strlen(char *str);
#endif

#ifdef __cplusplus
}
#endif