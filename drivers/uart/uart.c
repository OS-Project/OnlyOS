/*
 * Created by Alan Gardin
 * Modified by Thibault Piana
 * Inspired by Starware Uart-manager
 * UART driver to manage UART0 (TODO : maybe other UART)
*/

#include "drivers/uart/uart.h"
#include "hal/uart/uart_irda_cir.h"
#include "soc_AM335x.h"
#include "hw_uart_irda_cir.h"

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
    UART_ConsoleInit();
}

/*
static inline void UART_stdioRead(unsigned char *rxBuff, unsigned char rxByte)
{
    unsigned int inputCount = 0u;

    while((rxByte != '\r') && (rxByte != ' '))
    {
        UART_Putc(rxByte);

        *//* Account for the backspace to allow user to edit the input *//*
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
        rxByte = UART_Getc();
    }
    *//* Add the delimiting character at the end of the buffer *//*
    *rxBuff = rxByte;
}*/

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
            UART_Putc('\r');
            UART_Putc('\n');
        }
        else
            UART_Putc((unsigned char)*pTxBuffer);

        pTxBuffer++;
        count++;

        if((0 == flag) && (count == numBytesToWrite))
            break;
    }
    /* Returns the number of bytes written onto the transmitter FIFO. */
    return count;
}

void UART_printf(const char *string, va_list vaArg)
{
    unsigned int idx, pos, count, base, neg;
    char *pcStr, pcBuf[16], cFill;
    int value;

    /* Loop while there are more characters in the string. */
    while(*string)
    {
        /* Find the first non-% character, or the end of the string. */
        for(idx = 0u; (string[idx] != '%') && (string[idx] != '\0'); idx++) { }

        /* Write this portion of the string. */
        UART_write(string, idx);

        /* Skip the portion of the string that was written. */
        string += idx;

        /* See if the next character is a %. */
        if(*string == '%')
        {
            /* Skip the %. */
            string++;

            count = 0u;
            cFill = ' ';

            again:

            /* Determine how to handle the next character. */
            switch(*string++)
            {
                /* Handle the digit characters. */
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                {
                    /*
                    ** If this is a zero, and it is the first digit, then the
                    ** fill character is a zero instead of a space.
                    */
                    if((string[-1] == '0') && (count == 0))
                        cFill = '0';

                    /* Update the digit count. */
                    count *= 10;
                    count += string[-1] - '0';

                    /* Get the next character. */
                    goto again;
                }

                /* Handle the %c command. */
                case 'c':
                {
                    /* Get the value from the varargs. */
                    value = va_arg(vaArg, unsigned int);

                    /* Print out the character. */
                    UART_write((char *)&value, 1);

                    /* This command has been handled. */
                    break;
                }

                    /* Handle the %d command. */
                case 'd':
                {
                    /* Get the value from the varargs. */
                    value = va_arg(vaArg, unsigned int);

                    /* Reset the buffer position. */
                    pos = 0u;

                    /*
                    ** If the value is negative, make it positive and indicate
                    ** that a minus sign is needed.
                    */
                    if((int)value < 0)
                    {
                        /* Make the value positive. */
                        value = -(int)value;

                        /* Indicate that the value is negative. */
                        neg = 1u;
                    }
                    else
                    {
                        /*
                        ** Indicate that the value is positive so that a minus
                        ** sign isn't inserted.
                        */
                        neg = 0u;
                    }

                    /* Set the base to 10. */
                    base = 10u;

                    /* Convert the value to ASCII. */
                    goto convert;
                }

                    /* Handle the %s command. */
                case 's':
                {
                    /* Get the string pointer from the varargs. */
                    pcStr = va_arg(vaArg, char *);

                    /* Determine the length of the string. */
                    for(idx = 0u; pcStr[idx] != '\0'; idx++)
                    {
                    }

                    /* Write the string. */
                    UART_write(pcStr, idx);

                    /* Write any required padding spaces */
                    if(count > idx)
                    {
                        count -= idx;
                        while(count--)
                        {
                            UART_write((const char *)" ", 1);
                        }
                    }
                    /* This command has been handled. */
                    break;
                }

                    /* Handle the %u command. */
                case 'u':
                {
                    /* Get the value from the varargs. */
                    value = va_arg(vaArg, unsigned int);

                    /* Reset the buffer position. */
                    pos = 0u;

                    /* Set the base to 10. */
                    base = 10u;

                    /* Indicate that the value is positive so that a minus sign
                     * isn't inserted. */
                    neg = 0u;

                    /* Convert the value to ASCII. */
                    goto convert;
                }

                    /*
                    ** Handle the %x and %X commands.  Note that they are treated
                    ** identically; i.e. %X will use lower case letters for a-f
                    ** instead of the upper case letters it should use.  We also
                    ** alias %p to %x.
                    */
                case 'x':
                case 'X':
                case 'p':
                {
                    /* Get the value from the varargs. */
                    value = va_arg(vaArg, unsigned int);

                    /* Reset the buffer position. */
                    pos = 0u;

                    /* Set the base to 16. */
                    base = 16u;

                    /*
                    ** Indicate that the value is positive so that a minus sign
                    ** isn't inserted.
                    */
                    neg = 0u;

                    /*
                    ** Determine the number of digits in the string version of
                    ** the value.
                    */
                    convert:
                    for(idx = 1;
                        (((idx * base) <= value) &&
                         (((idx * base) / base) == idx));
                        idx *= base, count--)
                    {
                    }

                    /*
                    ** If the value is negative, reduce the count of padding
                    ** characters needed.
                    */
                    if(neg)
                    {
                        count--;
                    }

                    /*
                    ** If the value is negative and the value is padded with
                    ** zeros, then place the minus sign before the padding.
                    */
                    if(neg && (cFill == '0'))
                    {
                        /* Place the minus sign in the output buffer. */
                        pcBuf[pos++] = '-';

                        /*
                        ** The minus sign has been placed, so turn off the
                        ** negative flag.
                        */
                        neg = 0u;
                    }

                    /* Provide additional padding at the beginning of the
                     * string conversion if needed. */
                    if((count > 1) && (count < 16))
                    {
                        for(count--; count; count--)
                        {
                            pcBuf[pos++] = cFill;
                        }
                    }

                    /* If the value is negative, then place the minus sign
                     * before the number. */
                    if(neg)
                    {
                        /* Place the minus sign in the output buffer. */
                        pcBuf[pos++] = '-';
                    }

                    /* Convert the value into a string. */
                    for(; idx; idx /= base)
                    {
                        pcBuf[pos++] = g_pcHex[(value / idx) % base];
                    }

                    /* Write the string. */
                    UART_write(pcBuf, pos);

                    /* This command has been handled. */
                    break;
                }

                    /* Handle the %% command. */
                case '%':
                {
                    /* Simply write a single %. */
                    UART_write(string - 1, 1);

                    /* This command has been handled. */
                    break;
                }

                    /* Handle all other commands. */
                default:
                {
                    /* Indicate an error. */
                    UART_write((const char *)"ERROR", 5);

                    /* This command has been handled. */
                    break;
                }
            }
        }
    }
}

void UART_putc(unsigned char byteTx)
{
    UART_ConsolePutc(byteTx);
}

char* UART_gets(char *pRxBuffer, int numBytesToRead)
{
    unsigned int count = 0;
    unsigned char ch;
    char *writePtr = pRxBuffer;

    if((0 != pRxBuffer) && (numBytesToRead > 0))
    {
        ch = UART_Getc();

        /*
        ** Read till Carriage return (0xD - ASCII Value of Carriage return)
        ** Or till the specified number of bytes are entered
        */
        while((0xD != ch) && (count < (numBytesToRead - 1u)))
        {
            /* Echoing the typed character back to the serial console. */
            UART_Putc(ch);

            *writePtr++  = ch;
            ch = UART_Getc();
            count++;
        }

        *writePtr = '\0';
    }

    return pRxBuffer;
}

unsigned char UART_getc(void)
{
    return (UART_ConsoleGetc());
}

unsigned int UART_write(const char *pcBuf, unsigned int len)
{
    unsigned int uIdx;

    /* Send the characters */
    for(uIdx = 0; uIdx < len; uIdx++)
    {
        /* If the character to the UART_ is \n, then add a \r before it so that
         * \n is translated to \n\r in the output. */
        if(pcBuf[uIdx] == '\n')
        {
            UART_Putc('\r');
        }

        /* Send the character to the UART_ output. */
        UART_Putc(pcBuf[uIdx]);
    }

    /* Return the number of characters written. */
    return(uIdx);
}

int UART_scanf(const char *format, va_list vaArg)
{
    unsigned char rxByte, rxBuffer[MAX_STRING_WIDTH];
    unsigned int width = MAX_STRING_WIDTH, byteCount = 0u;
    int sign = 1, inputMatch = 0;
    int *value;
    unsigned int *num;
    char *dst;

    /* Loop while there are more characters in the string. */
    while(*format != '\0')
    {
        /* Find the first % character */
        if((*format++ == '%') && (inputMatch >= 0))
        {
            switch(*format++)
            {
                /* Handle the %c command. */
                case 'c':
                    /* Get the address of variable from varargs */
                    dst = va_arg(vaArg, char *);

                    rxByte = UART_Getc();
                    UART_Putc(rxByte);
                    *dst = rxByte;
                    /*
                    ** Increment the count for input values successfully
                    ** read and matched.
                    */
                    inputMatch++;

                    /* 
                    ** Wait until the byte entered is new line or carriage 
                    ** return or space 
                    */
                    while((rxByte != '\n') && (rxByte != '\r') && (rxByte != ' '))
                    {
                        rxByte = UART_Getc();
                    }
                    UART_SCANF_ECHO_INPUT(rxByte);
                    break;

                    /* Handle the %d command. */
                case 'd':
                    /* Get the address of variable from argument */
                    value = va_arg(vaArg, int *);
                    *value = 0;

                    /*
                    ** Increment the count for input values successfully
                    ** read and matched.
                    */
                    inputMatch++;

                    /*
                    ** Continuously loop until user enters a non
                    ** white-space character
                    */
                    IS_WHITESPACE(rxByte);

                    /*
                    ** Continuously read input values from UART_ console
                    ** and update the buffer until user enters a delimiting
                    ** character.
                    */
                    UART_StdioRead(rxBuffer, rxByte);

                    rxByte = rxBuffer[byteCount];

                    /* Account for negative numbers. */
                    if('-' == rxByte)
                    {
                        sign = -1;
                        byteCount++;
                        rxByte = rxBuffer[byteCount];
                    }
                    /*
                    ** Check whether the byte entered is not either the carriage
                    ** return or space or new line, if yes then break from the 
                    ** loop.
                    */
                    while((rxByte != '\n') && (rxByte != '\r') && (rxByte != ' '))
                    {
                        /* Convert the ASCII value to decimal number */
                        rxByte = ASCIIToDigit(rxByte, BASE_10);
                        /*
                        ** Check for invalid input characters if true then
                        ** then break from the loop.
                        */
                        if(INVALID_INPUT == rxByte)
                        {
                            inputMatch = -1;
                            break;
                        }
                        else
                        {
                            *value = ((*value) * BASE_10) + rxByte;
                        }
                        byteCount++;
                        rxByte = rxBuffer[byteCount];
                    }

                    /* Add the sign value to the number */
                    *value = *(value) * sign;
                    byteCount = 0u;
                    UART_SCANF_ECHO_INPUT(rxByte);
                    break;

                    /* Handle the %x,%X and %p command. */
                case 'x':
                case 'X':
                case 'p':
                    /* Get the address of variable from argument */
                    num = va_arg(vaArg, unsigned int*);
                    *num = 0u;

                    /*
                    ** Increment the count for input values successfully
                    ** read and matched.
                    */
                    inputMatch++;

                    /* Continuously loop until user enters a non
                    ** white-space character.
                    */
                    IS_WHITESPACE(rxByte)

                    /*
                    ** Continuously read input values from UART_ console
                    ** and update the buffer until user enters a delimiting
                    ** character.
                    */
                    UART_StdioRead(rxBuffer, rxByte);

                    rxByte = rxBuffer[byteCount];
                    /*
                    ** Check whether the byte entered is not either the carriage
                    ** return or space or new line, if yes then break from the 
                    ** loop.
                    */
                    while((rxByte != '\n') && (rxByte != '\r') && (rxByte != ' '))
                    {
                        /*
                        ** Ignore the first 2 characters from the
                        ** received input if they are 0x or 0X.
                        */
                        if((byteCount < 2) && (('0' == rxByte) ||
                                               ('x' == rxByte) || ('X' == rxByte)))
                        {
                            byteCount++;
                            rxByte = rxBuffer[byteCount];
                            continue;
                        }
                        /* Convert the ASCII value to hexadecimal number */
                        rxByte = ASCIIToDigit(rxByte, BASE_16);

                        /* Check for invalid hexadecimal characters */
                        if(INVALID_INPUT == rxByte)
                        {
                            inputMatch = -1;
                            break;
                        }
                        else
                        {
                            *num = ((*num) * BASE_16) + rxByte;
                        }
                        byteCount++;
                        rxByte = rxBuffer[byteCount];
                    }
                    byteCount = 0u;
                    UART_SCANF_ECHO_INPUT(rxByte);
                    break;

                    /* Handle the %s command. */
                case 's':
                    /* Get the address of variable from the argument*/
                    dst = va_arg(vaArg, char*);

                    /*
                    ** Increment the count for input values successfully
                    ** read and matched.
                    */
                    inputMatch++;

                    /*
                    ** Continuously loop till user enters a non
                    ** white-space character
                    */
                    IS_WHITESPACE(rxByte);

                    /* Read the characters one at a time from UART_ console */
                    while((rxByte != '\n') && (rxByte != '\r') && (rxByte != ' ') && (width--))
                    {
                        UART_Putc(rxByte);

                        /*Account for backspace and decrement the pointer */
                        if('\b' == rxByte)
                        {
                            dst--;
                            width++;
                        }
                        else
                        {
                            *dst++ = (char) rxByte;
                        }
                        rxByte = UART_Getc();
                    }
                    *dst = '\0';
                    UART_SCANF_ECHO_INPUT(rxByte);
                    break;

                    /* Handles %u command */
                case 'u':
                    /* Get the address of variable from varargs */
                    num = va_arg(vaArg, unsigned int*);
                    *num = 0u;
                    inputMatch++;
                    /*
                    ** Continuously loop until user enters a non
                    ** white-space character
                    */
                    IS_WHITESPACE(rxByte);

                    /*
                    ** Continuously read input values from UART_ console
                    ** and update the buffer until user enters a delimiting
                    ** character.
                    */
                    UART_StdioRead(rxBuffer, rxByte);

                    rxByte = rxBuffer[byteCount];
                    while((rxByte != '\n') && (rxByte != '\r') && (rxByte != ' '))
                    {
                        /* Convert the ASCII value to decimal number */
                        rxByte = ASCIIToDigit(rxByte, BASE_10);

                        /*
                        ** Check for invalid input characters if true then
                        ** then break from the loop.
                        */
                        if(INVALID_INPUT == rxByte)
                        {
                            inputMatch = -1;
                            break;
                        }
                        else
                        {
                            *num = ((*num) * BASE_10) + rxByte;
                        }
                        byteCount++;
                        rxByte = rxBuffer[byteCount];
                    }
                    byteCount = 0u;
                    UART_SCANF_ECHO_INPUT(rxByte);
                    break;

                default:
                    UART_Puts("Format specifier is not supported\r\n", -1);
                    inputMatch = -1;
                    break;
            }
        }
    }
    /* Check for invalid format specifiers */
    if(0 == inputMatch)
    {
        UART_Puts("Invalid format specifiers\r\n", -1);
        inputMatch = -1;
    }

    return inputMatch;
}









