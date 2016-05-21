#ifdef __cplusplus
"C" {
#endif

#ifndef DRIVER_UART_H
#define DRIVER_UART_H
    #define va_list  __builtin_va_list
    #define va_arg  __builtin_va_arg
    #define va_start  __builtin_va_start
    #define va_end  __builtin_va_end

    static const char * const g_pcHex = "0123456789abcdef";

    /* Functions */
    void UART_stdioInit(void);

    /* Output */
    unsigned int UART_puts(char *pTxBuffer, int numBytesToWrite);
    void UART_putc(unsigned char byteTx);
    unsigned int UART_write(const char *pcBuf, unsigned int len);

    unsigned int UART_writeStr(const char *str);
    void UART_printf(const char *pcString, ...);

    /* Input */
    char*  UART_gets(char *pRxBuffer, int numBytesToRead);
    unsigned char UART_getc(void);
    void UART_stdioRead(unsigned char *rxBuff, unsigned char rxByte);
    //int UART_scanf(const char *format, va_list vaArg);
#endif

#ifdef __cplusplus
}
#endif