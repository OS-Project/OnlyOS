//
// Created by Thibault PIANA on 18/05/16.
//

#include "utils/strlen.h"

int strlen(char *str) {
    char *s;
    for (s = str; *s; ++s);
    return(s - str);
}
