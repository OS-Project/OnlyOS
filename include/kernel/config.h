/*
    * Created by Thibault PIANA on 10/11/15.
*/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef ONLYOS_FILES_REFERENCES_H
#define ONLYOS_FILES_REFERENCES_H
    #include <utils/libbool.h>
    #include <utils/libtypes.h>

    /* Config */
    #define DEBUG 1

    /* Paths */
    #define DRIVER_UART_PATH "drivers/uart/uart.h"

    /* EXIT values */
    #define EXIT_SUCCESS (int)0
    #define EXIT_FAILURE (int)1

    #define kprintf UART_printf
#endif //ONLYOS_FILES_REFERENCES_H

#ifdef __cplusplus
}
#endif