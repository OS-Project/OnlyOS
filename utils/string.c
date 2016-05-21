//
// Created by Thibault PIANA on 18/05/16.
//

#include "utils/string.h"

unsigned int str_strlen(const char *str) {
    const char *s;
    for (s = str; *s; s++);
    return((unsigned int)(s - str));
}
