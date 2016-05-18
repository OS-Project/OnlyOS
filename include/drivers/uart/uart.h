#ifdef __cplusplus
"C" {
#endif

#ifndef DRIVER_UART_H
#define DRIVER_UART_H
    void UART_stdioInit(void);

    /* Output */
    unsigned int UART_puts(char *pTxBuffer, int numBytesToWrite);
    void UART_putc(unsigned char byteTx);
    unsigned int UART_write(const char *pcBuf, unsigned int len);

    void UART_printf(const char *string, va_list vaArg);

    /* Input */
    char*  UART_gets(char *pRxBuffer, int numBytesToRead);
    unsigned char UART_getc(void);
    int UART_scanf(const char *format, va_list vaArg);
#endif

#ifdef __cplusplus
}
#endif