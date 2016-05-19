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
    UART_write("salut", 5);
    int a = 0;
    return 0;
}

/*
int kinit()
{
    // Init UART
    UART_stdioInit();
    UART_putc('\n');
    UART_putc('\n');

    return 0;
}
 */

void kexit(int err_num)
{
    while(1);
}
