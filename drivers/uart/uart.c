/*
 * Created by Alan Gardin
 * Modified by Thibault Piana
 * Inspired by Starware Uart-manager
 * UART driver to manage UART0 (TODO : maybe other UART)
*/

#include "drivers/uart/uart.h"
#include "hal/uart/uart_irda_cir.h"

#include "hw_uart_irda_cir.h"
#include "soc_AM335x.h"

/* Utils */
#include "utils/string.h"

/* System config */
#include "kernel/config.h"

/*****************************************************************************
**                      INTERNAL MACRO DEFINITIONS
*****************************************************************************/
#define BASE_10             (10u)
#define BASE_16             (16u)
#define INVALID_INPUT       (0xFFu)
#define MAX_STRING_WIDTH    (80u)

/*
** Loop continuously until user enters any character other
** than space, carriage return, tab space and backspace
*/
#define IS_WHITESPACE(rxByte)    rxByte = UARTGetc(); \
                                 while(('\r' == rxByte) || (' ' == rxByte) || \
                                       ('\t' == rxByte) || ('\b' == rxByte)) { \
                                      UARTPutc(rxByte);   \
                                      rxByte = UARTGetc(); }

/* 
** Echoes back the delimiting character entered by the user
** after the actual input value has been read from the user.
*/
#define UART_SCANF_ECHO_INPUT(rxByte)                                     \
                                 if(('\n' == rxByte) || ('\r' == rxByte)) \
                                 {                                        \
                                     UARTPutc('\r');                      \
                                     UARTPutc('\n');                      \
                                 }                                        \
                                 else                                     \
                                     UARTPutc(rxByte);

/* A mapping from an integer between 0 and 15 to its ASCII character
 * equivalent. */
static const char * const g_pcHex = "0123456789abcdef";

/****************************************************************************
**                    EXTERNAL FUNCTION DECLARATIONS
****************************************************************************/
extern void UARTConsolePutc(unsigned char data);
extern unsigned char UARTConsoleGetc(void);
extern void UARTConsoleInit(void);

void UART_StdioInit(void)
{
    UARTConsoleInit();
}

static inline void UART_stdioRead(unsigned char *rxBuff, unsigned char rxByte)
{
    unsigned int inputCount = 0u;

    while((rxByte != '\r') && (rxByte != ' '))
    {
        UART_putc(rxByte);

        /* Account for the backspace to allow user to edit the input */
        if(('\b' == rxByte) && (inputCount > 0))
        {
            rxBuff--;
            inputCount--;
        }
        else
        {
            *rxBuff++ = rxByte;
            inputCount++;
        }
        rxByte = UART_getc();
    }
    /* Add the delimiting character at the end of the buffer */
    *rxBuff = rxByte;
}

unsigned int UART_puts(char *pTxBuffer, int numBytesToWrite)
{
    unsigned int count = 0;
    unsigned int flag = 0;

    if(numBytesToWrite < 0)
        flag = 1;

    while('\0' != *pTxBuffer)
    {
        /* Checks if data is a newline character. */
        if('\n' == *pTxBuffer)
        {
            /* Ensuring applicability to serial console.*/
            UART_putc('\r');
            UART_putc('\n');
        }
        else
            UART_putc((unsigned char)*pTxBuffer);

        pTxBuffer++;
        count++;

        if((0 == flag) && (count == numBytesToWrite))
            break;
    }
    /* Returns the number of bytes written onto the transmitter FIFO. */
    return count;
}


void UART_putc(unsigned char byteTx)
{
    UARTConsolePutc(byteTx);
}

char* UART_gets(char *pRxBuffer, int numBytesToRead)
{
    unsigned int count = 0;
    unsigned char ch;
    char *writePtr = pRxBuffer;

    if((0 != pRxBuffer) && (numBytesToRead > 0))
    {
        ch = UART_getc();

        /*
        ** Read till Carriage return (0xD - ASCII Value of Carriage return)
        ** Or till the specified number of bytes are entered
        */
        while((0xD != ch) && (count < (numBytesToRead - 1u)))
        {
            /* Echoing the typed character back to the serial console. */
            UART_putc(ch);

            *writePtr++  = ch;
            ch = UART_getc();
            count++;
        }

        *writePtr = '\0';
    }

    return pRxBuffer;
}

unsigned char UART_getc(void)
{
    return (UARTConsoleGetc());
}

unsigned int UART_write(const char *pcBuf, unsigned int len)
{
    unsigned int uIdx;

    /* Send the characters */
    for(uIdx = 0; uIdx < len; uIdx++)
    {
        /* If the character to the UART is \n, then add a \r before it so that
         * \n is translated to \n\r in the output. */
        if(pcBuf[uIdx] == '\n')
            UART_putc('\r');

        /* Send the character to the UART output. */
        UART_putc(pcBuf[uIdx]);
    }

    /* Return the number of characters written. */
    return(uIdx);
}

unsigned int UART_writeStr(const char *str) {
    unsigned int len = str_strlen(str);
    unsigned int written = UART_write(str, len);

    return written;
}









