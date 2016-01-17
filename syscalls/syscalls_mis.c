//
// Created by Thibault PIANA on 24/10/15.
//

/**
 * This file contain the rewrite of the POSIX interface
 */

#include <sys/stat.h>
#include <sys/types.h>
#include <stddef.h>
#include <errno.h>

#undef errno
extern int  errno;

int _close(int file) {
    return -1;
}

int _fstat(int file, struct stat *st) {
    st->st_mode = S_IFCHR;
    return 0;
}

int _isatty(int file) {
    return 1;
}

int _lseek(int file, int ptr, int dir) {
    return 0;
}

int _open(const char *name, int flags, int mode) {
    return -1;
}

int _wait (int *status) {
    errno = ECHILD;
    return -1;                    /* Always fails */
}
