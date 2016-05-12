/*
    * Created by Thibault on 16/01/2016.
*/

#include "kernel/kernel.h"
#include "kernel/config.h"

#include DRIVER_RTC_PATH

#include <stdlib.h>
#include <stdio.h>

int klaunch()
{
    int k = 0;
    while(k % 5000 != 0)
    {
        printf("%d", RTC_getTime(0));
        k++;
    }
    return 0;
}
