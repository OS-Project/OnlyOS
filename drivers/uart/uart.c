/*
 * Created by Alan Gardin
 * Modified by Thibault Piana
 * Inspired by Starware Uart-manager
 * UART driver to manage UART0 (TODO : maybe other UART)
*/

#include "drivers/uart/uart.h"
#include "hal/uart/uart_irda_cir.h"
#include "hal/uart/uart_console.h"

#include "hw_uart_irda_cir.h"
#include "soc_AM335x.h"

/* Utils */
#include "utils/string.h"

void UART_stdioInit(void)
{
    UARTConsoleInit();
}

void UART_stdioRead(unsigned char *rxBuff, unsigned char rxByte)
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

        if((0 == flag) && (count == (unsigned int)numBytesToWrite))
            break;
    }
    /* Returns the number of bytes written onto the transmitter FIFO. */
    return count;
}


void UART_putc(unsigned char byteTx)
{
    UARTConsolePutc(byteTx);
}

/* Not working :( */
void UART_printf(const char *string, ...)
{
    va_list vaArg;
    unsigned int idx, pos, count, base, neg;
    char *pcStr, pcBuf[16], cFill;
    int value;

    /* Loop while there are more characters in the string. */
    while(*string)
    {
        /* Find the first non-% character, or the end of the string. */
        for(idx = 0u; (string[idx] != '%') && (string[idx] != '\0'); idx++)
        {
        }

        /* Write this portion of the string. */
        UART_write(string, idx);

        /* Skip the portion of the string that was written. */
        string += idx;

        /* See if the next character is a %. */
        if(*string == '%')
        {
            /* Skip the %. */
            string++;

            /*
            ** Set the digit count to zero, and the fill character to space
            ** (i.e. to the defaults).
            */
            count = 0u;
            cFill = ' ';

            /*
            ** It may be necessary to get back here to process more characters.
            ** Goto's aren't pretty, but effective. I feel extremely dirty for
            ** using not one but two of the beasts.
            */
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
                    {
                        cFill = '0';
                    }

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
                    UART_putc((unsigned char)value);

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
                            UART_putc((unsigned char)(" "));
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
                        (((int)(idx * base) <= value) && // value changed to unsigned int
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