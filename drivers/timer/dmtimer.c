//
// Created by thibault on 10/11/15.
//

#include "drivers/timer/dmtimer.h"


void TIMER_start(char timer_number) {
    unsigned int adress = TIMER_getPhysicalAdress(timer_number);

    DMTimerEnable(adress);
}
void TIMER_stop(char timer_number) {
    unsigned int adress = TIMER_getPhysicalAdress(timer_number);

    DMTimerDisable(adress);
}

void TIMER_set(char timer_number, unsigned int counter) {
    unsigned int adress = TIMER_getPhysicalAdress(timer_number);
    DMTimerCounterSet(adress, counter);
}

unsigned int TIMER_get(char timer_number) {
    unsigned int adress = TIMER_getPhysicalAdress(timer_number);

    return DMTimerCounterGet(adress);
}

unsigned int TIMER_reset(char timer_number) {
    unsigned int counter = TIMER_get(timer_number);

    TIMER_stop(timer_number);
    TIMER_set(timer_number, 0);
    TIMER_start(timer_number);

    return counter;
}

unsigned int TIMER_getPhysicalAdress(char timer_number) {
    unsigned int physical_adress;
    switch(timer_number)
    {
        case 0:
            physical_adress = SOC_DMTIMER_0_REGS;
            break;
        case 1:
            physical_adress = SOC_DMTIMER_1_REGS;
        break;
        case 2:
            physical_adress = SOC_DMTIMER_2_REGS;
            break;
        case 3:
            physical_adress = SOC_DMTIMER_3_REGS;
            break;
        case 4:
            physical_adress = SOC_DMTIMER_4_REGS;
            break;
        case 5:
            physical_adress = SOC_DMTIMER_5_REGS;
            break;
        case 6:
            physical_adress = SOC_DMTIMER_6_REGS;
            break;
        case 7:
            physical_adress = SOC_DMTIMER_7_REGS;
            break;
        default:
            /* Error */
            break;
    }
    return physical_adress;
}

