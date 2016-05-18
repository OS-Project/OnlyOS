//
// Created by Thibault PIANA on 24/10/15.
//

/**
 * This file contain the rewrite of the POSIX interface
 */

*
#define UART_DEFAULT (char)0x0

/* I/O management */
int _read(int file, char *ptr, int len) {
    int data_len = UART_read(ptr, len, UART_DEFAULT);
    return data_len;
}

int _write(int file, char *ptr, int len) {
    int data_len = UART_write(ptr, len, UART_DEFAULT);
    return data_len;
}