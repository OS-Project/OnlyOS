#include "uart.h"

void uart_init()
{

    // Software reset
    HW_OR_REG_WORD(UART0_BASE + UART_SYSC, UART_SYSC_SOFTRESET) // Enable software reset bit
    while (HW_GET_REG_WORD(UART0_BASE + UART_SYSS) & UART_SYSS_RESETDONE == 0); // Wait until the end of the reset operation

    // Disable idle mode
    HW_OR_REG_WORD(UART0_BASE + UART_SYSC, UART_SYSC_IDLEMODE_NOIDLE << UART_SYSC_IDLEMODE_SHIFT);
}


void uart_write_byte(char c)
{
    // Switch to access mode using LCR

    // Wait until ongoing transmission is over. UART_LSR_TX_SR_E not needed?
    while (HW_GET_REG_WORD(UART0_BASE + UART_LSR) & (UART_LSR_TX_FIFO_E | UART_LSR_TX_SR_E) != 0);

    // while ((HW_GET_REG_WORD(UART0_BASE + UART_MDR1) & 32) == 0)

    HW_SET_REG_WORD(UART0_BASE + UART_THR, c); // Write data

    // Restore LCR
}


char uart_read_byte()
{
    // Switch to access mode using LCR

    // Waits indefinitely until a byte arrives in the RX FIFO(or RHR).
    while((HW_GET_REG_WORD(baseAdd + UART_LSR) & UART_LSR_RX_FIFO_E) == 0);


    return ((char) HW_GET_REG_BYTE(UART0_BASE + UART_RHR))

    // Restore LCR (after accessing the value in the register)
}
