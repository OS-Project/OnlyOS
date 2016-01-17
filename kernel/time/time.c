/*
    * Created by Thibault on 17/01/2016.
*/

#include <kernel/time/time.h>
#include <kernel/kernel.h>
#include <drivers/timer/dmtimer.h>

int kgetIime()
{
    return TIMER_get(0);
}