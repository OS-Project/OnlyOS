#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern char* path_;

void pathShow()
{
    printf("OnlyOS:%s$ ", path_);
}