/*
 * Created by Thibault PIANA on 10/11/15.
*/
#include "kernel/kernel.h"
#include "drivers/uart/uart.h"
#include "soc_AM335x.h"
#include "hal/uart/uart_irda_cir.h"
#define kprintf UART_writeStr

int kmain()
{
    kinit();
    int k = 0;

    char tableau[40];

    for(k = 0; k < 40; k++)
        tableau[k] = 'a';

    UARTCharPut((unsigned int)SOC_UART_0_REGS, (unsigned char)'l');

    for(k = 0; k < 40; k++)
        UART_putc((unsigned char)tableau[k]);

    while(1);
    return 0;
}


int kinit()
{
    // Init UART
    UART_stdioInit();
    UART_putc('\n');
    UART_putc('\n');

    return 0;
}

void kexit(int err_num)
{
    while(1);
}