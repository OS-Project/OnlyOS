/*
 * Created by Alan Gardin
 * Modified by Thibault Piana
*/
#include "drivers/uart/uart.h"
#include <stdio.h>

/* Write */
void UART_writeByte(const char data, char uart_number) {
    unsigned int base_adress = UART_getPhysicalAdress(uart_number);
    UARTCharPut(base_adress, data);
}

int UART_write(const char *pcBuf, int len, char uart_number) {
    int uIdx;

    /* Send the characters */
    for(uIdx = 0; uIdx < len; uIdx++)
    {
        /* If the character to the UART is \n, then add a \r before it so that
         * \n is translated to \n\r in the output. */
        if(pcBuf[uIdx] == '\n')
            UART_writeByte('\r', uart_number);

        /* Send the character to the UART output. */
        UART_writeByte(pcBuf[uIdx], uart_number);
    }

    /* Return the number of characters written. */
    return uIdx;
}

int UART_writeStr(char *str, char uart_number) {
    int len = UART_strlen(str);
    UART_write(str, len, uart_number);

    return len;
}

/* Read */
char UART_readByte(char uart_number) {
    unsigned int base_adress = UART_getPhysicalAdress(uart_number);
    return ((char)UARTCharGet(base_adress));
}

int UART_read(char *pRxBuffer, int numBytesToRead, char uart_number) {
    int count = 0;
    char ch;
    char *writePtr = pRxBuffer;

    if((pRxBuffer != 0) && (numBytesToRead > 0))
    {
        while(count <= (numBytesToRead - 1))
        {
            ch = UART_readByte(uart_number);
            *writePtr = ch;
            writePtr++;
            count++;

            if(ch == 0xD) {
                ch = UART_readByte(uart_number);
                break;
            }
            if(ch == 0xA)
                break;
        }

        *writePtr = '\0';
    }
    return count;

    /*
    if((pRxBuffer != 0) && (numBytesToRead > 0))
    {
        ch = UART_readByte(uart_number);

        while((count <= (numBytesToRead - 1)) && (ch != 0xD) && (ch != 0xA))
        {
            UART_writeByte(ch, uart_number);

            *(writePtr++) = ch;
            ch = UART_readByte(uart_number);
            printf("0x%x\n", ch);
            count++;
        }

        *writePtr = '\0';
    }
    */
}



/* Other */
unsigned int UART_getPhysicalAdress(char uart_number) {
    unsigned int physical_adress;
    switch (uart_number)
    {
        case 0:
            physical_adress = SOC_UART_0_REGS;
            break;
        case 1:
            physical_adress = SOC_UART_1_REGS;
            break;
        case 2:
            physical_adress = SOC_UART_2_REGS;
            break;
        case 3:
            physical_adress = SOC_UART_3_REGS;
            break;
        case 4:
            physical_adress = SOC_UART_4_REGS;
            break;
        case 5:
            physical_adress = SOC_UART_5_REGS;
            break;
        default:
            physical_adress = 0; /* Error */
            break;
    }
    return physical_adress;
}

int UART_strlen(char *str) {
    char *s;
    for (s = str; *s; ++s);
    return(s - str);
}







