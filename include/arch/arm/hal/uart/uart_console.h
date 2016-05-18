//
// Created by Thibault PIANA on 18/05/16.
//

#ifndef ONLYOS_UART_CONSOLE_H
#define ONLYOS_UART_CONSOLE_H
    #define UART_CONSOLE_BASE                    (SOC_UART_0_REGS)
    #define BAUD_RATE_115200                     (115200)
    #define UART_MODULE_INPUT_CLK                (48000000)

    static void UARTStdioInitExpClk(unsigned int baudRate,
                                    unsigned int rxTrigLevel,
                                    unsigned int txTrigLevel);
    static void UartFIFOConfigure(unsigned int txTrigLevel,
                                  unsigned int rxTrigLevel);
    static void UartBaudRateSet(unsigned int baudRate);
    void UARTConsolePutc(unsigned char data);
    unsigned char UARTConsoleGetc(void);
    void UARTConsoleInit(void);
#endif //ONLYOS_UART_CONSOLE_H
