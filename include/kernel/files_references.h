//
// Created by Thibault PIANA on 10/11/15.
//
#ifdef __cplusplus
extern "C" {
#endif

#ifndef ONLYOS_FILES_REFERENCES_H
#define ONLYOS_FILES_REFERENCES_H
    /* Config */
    #define CONFIG_SYSTEM_DMTIMER 0
    #define CONFIG_SYSTEM_WDT_STATUS 0

    #define CONFIG_SYSTEM_STDOUT 0
    #define CONFIG_SYSTEM_STDERR 0
    #define CONFIG_SYSTEM_STDIN 0

    /* Paths */
    #define DRIVER_RTC_PATH "drivers/timer/rtc.h"
    #define DRIVER_DMTIMER_PATH "drivers/timer/dmtimer.h"
    #define DRIVER_WDT_PATH "drivers/timer/watchdog.h"
    #define DRIVER_UART_PATH "drivers/uart/uart.h"
    #define DRIVER_SPI_PATH "drivers/spi/spi.h"
    #define DRIVER_I2C_PATH "drivers/i2c/i2c.h"
#endif //ONLYOS_FILES_REFERENCES_H

#ifdef __cplusplus
}
#endif