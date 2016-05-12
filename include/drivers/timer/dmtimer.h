/*
    Created by Thibault on 10/11/15.
*/
#ifdef __cplusplus
extern "C" {
#endif

#ifndef ONLYOS_DMTIMER_H
#define ONLYOS_DMTIMER_H
    void TIMER_start(char timer_number);
    void TIMER_stop(char timer_number);
    void TIMER_set(unsigned int counter, char timer_number);
    unsigned int TIMER_get(char timer_number);
    unsigned int TIMER_reset(char timer_number);

    unsigned int TIMER_getPhysicalAdress(char timer_number);

#endif //ONLYOS_DMTIMER_H

#ifdef __cplusplus
}
#endif