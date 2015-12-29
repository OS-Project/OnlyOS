//
// Created by thibault on 10/11/15.
//

#ifndef ONLYOS_DMTIMER_H
#define ONLYOS_DMTIMER_H

void TIMER_start(int timer_number);
void TIMER_stop(int timer_number);
long TIMER_get(int timer_number);
long TIMER_reset(int timer_number);

long * TIMER_getPhysicalAdress(int timer_number);


#endif //ONLYOS_DMTIMER_H
