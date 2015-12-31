/*
 * Created by Alan Gardin
*/
#include "drivers/uart/uart.h"

/* Write */
void UART_writeByte(const char data) {
    UARTCharPut(SOC_UART_0_REGS, data);
}

int UART_write(const char *pcBuf, unsigned int len) {
    int uIdx;

    /* Send the characters */
    for(uIdx = 0; uIdx < len; uIdx++)
    {
        /* If the character to the UART is \n, then add a \r before it so that
         * \n is translated to \n\r in the output. */
        if(pcBuf[uIdx] == '\n')
            UART_writeByte('\r');

        /* Send the character to the UART output. */
        UART_writeByte(pcBuf[uIdx]);
    }

    /* Return the number of characters written. */
    return uIdx;
}

void UART_newline() {
    UART_writeByte('\r');
    UART_writeByte('\n');
}


void UART_writeLn(char *str) {
    UART_writeStr(str);
    UART_newline();
}

void UART_writeStr(char *str) {
    UART_write(str, UART_strlen(str));
}

/* Read */
char UART_readByte() {
    return ((unsigned char)UARTCharGet(SOC_UART_0_REGS));
}

int UART_read(char *pRxBuffer, int numBytesToRead) {
    unsigned int count = 0;
    unsigned char ch;
    char *writePtr = pRxBuffer;

    if((0 != pRxBuffer) && (numBytesToRead > 0))
    {
        ch = UART_readByte();

        /*
        ** Read till Carriage return (0xD - ASCII Value of Carriage return)
        ** Or till the specified number of bytes are entered
        */
        while((ch != 0xD) && (count < (numBytesToRead - 1)) && (ch != '\n') && (ch != '\r') && (ch != ' '))
        {
            /* Echoing the typed character back to the serial console. */
            UART_writeByte(ch);

            *writePtr++ = ch;
            ch = UART_readByte();
            count++;
        }

        *writePtr++ = ch;
    }

    return count + 1;
}

unsigned int UART_strlen(char *str) {
    char *s;
    for (s = str; *s; ++s);
    return(s - str);
}







