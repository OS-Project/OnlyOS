#include "drivers/uart/uart.h"

void UART_init()
{
    // UART mux config
    HW_SET_REG_WORD(CONF_UART0_RXD, (0x1<<4)|(0x1<<5));
    HW_SET_REG_WORD(CONF_UART0_TXD, 0x0);

    // Setup clocks
    *(volatile unsigned int *) (CM_WKUP_CLKSTCTRL) = ((*(unsigned int *) (CM_WKUP_CLKSTCTRL) & ~(0x3)) | (0x2));
    *(volatile unsigned int *) (CM_PER_L4HS_CLKSTCTRL) = ((*(unsigned int *) (CM_PER_L4HS_CLKSTCTRL) & ~(0x3)) | (0x2));
    *(volatile unsigned int *) (CM_WKUP_UART0_CLKCTRL) = ((*(unsigned int *) (CM_WKUP_UART0_CLKCTRL) & ~(0x3)) | (0x2));

    HW_SET_REG_WORD(GPIO1_SETDATAOUT, (7 & 0xf)<<21);
    HW_SET_REG_WORD(GPIO1_CLEARDATAOUT, (~7 & 0xf)<<21);

    // Software reset
    HW_OR_REG_WORD(UART0_BASE + UART_SYSC, UART_SYSC_SOFTRESET); // Enable software reset bit
    while (HW_GET_REG_WORD(UART0_BASE + UART_SYSS) & UART_SYSS_RESETDONE == 0); // Wait until the end of the reset operation

    // Disable idle mode
    HW_OR_REG_WORD(UART0_BASE + UART_SYSC, UART_SYSC_IDLEMODE_NOIDLE << UART_SYSC_IDLEMODE_SHIFT);

    // Uart init
    while (!(HW_GET_REG_WORD(UART0_BASE + 20) & 0x40));

    HW_SET_REG_WORD(UART0_BASE + 4, 0);
    HW_SET_REG_WORD(UART0_BASE + 32, 7);
    HW_SET_REG_WORD(UART0_BASE + 12, ~0x7c);
    HW_SET_REG_WORD(UART0_BASE + 0, 0);
    HW_SET_REG_WORD(UART0_BASE + 4, 0);
    HW_SET_REG_WORD(UART0_BASE + 12, 3);
    HW_SET_REG_WORD(UART0_BASE + 16, 3);
    HW_SET_REG_WORD(UART0_BASE + 8, 7);
    HW_SET_REG_WORD(UART0_BASE + 12, ~0x7c);
    HW_SET_REG_WORD(UART0_BASE + 0, 26);
    HW_SET_REG_WORD(UART0_BASE + 4, 0);
    HW_SET_REG_WORD(UART0_BASE + 12, 3);
    HW_SET_REG_WORD(UART0_BASE + 32, 0);
}


void UART_writeByte(char c)
{
    // Switch to access mode using LCR

    // Wait until ongoing transmission is over. UART_LSR_TX_SR_E not needed?
    while (HW_GET_REG_WORD(UART0_BASE + UART_LSR) & (UART_LSR_TX_FIFO_E | UART_LSR_TX_SR_E) != 0);

    // while ((HW_GET_REG_WORD(UART0_BASE + UART_MDR1) & 32) == 0)

    HW_SET_REG_WORD(UART0_BASE + UART_THR, c); // Write data

    // Restore LCR
}

void UART_writeStr(char* str, int length)
{
    int i = 0;
    while (i<length)
    {
        UART_writeByte(str[i]);
        i++;
    }
}


void UART_newline()
{
    UART_writeByte('\r');
    UART_writeByte('\n');
}

char UART_readByte()
{
    // Switch to access mode using LCR

    // Waits indefinitely until a byte arrives in the RX FIFO(or RHR).
    while((HW_GET_REG_WORD(UART0_BASE + UART_LSR) & UART_LSR_RX_FIFO_E) == 0);


    return ((char) HW_GET_REG_BYTE(UART0_BASE + UART_RHR));

    // Restore LCR (after accessing the value in the register)
}


void UART_writeLn(const char *str)
{
    UART_writeStr(str, UART_strlen(str));
    UART_newline();
}
void UART_write(const char *str)
{
    UART_writeStr(str, UART_strlen(str));
}

unsigned int UART_strlen(const char *str)
{
    const char *s;
    for (s = str; *s; ++s);
    return(s - str);
}