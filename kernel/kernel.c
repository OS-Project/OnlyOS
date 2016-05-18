/*
 * Created by Thibault PIANA on 10/11/15.
*/
#include "kernel/kernel.h"
#include "drivers/uart/uart.h"

#define kprintf UART_writeStr

int kmain()
{
    UART_write("Salut", 5);
    while(1);
    return 0;
}
void kexit(int err_num)
{
    while(1);
}