//
// Created by thibault on 21/10/15.
//

#ifndef ONLYOS_ERRNO_H
#define ONLYOS_ERRNO_H

#include "string.h"

enum ERROR_TYPE {
    WARNING,
    FATAL_ERROR
};

void error(string error, ERROR type);

#endif //ONLYOS_ERRNO_H
