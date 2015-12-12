//
// Created by Thibault PIANA on 12/12/15.
//

#include "drivers/gpio/gpio.h"

void delay(int d);

int main()
{
    GPIO_enable(1);
    GPIO_setPin(1,23,GPIO_PIN_MODE_OUTPUT);
    while(1)
    {
        delay(1000);
        GPIO_setPin(1,23,GPIO_PIN_STATE_HIGH);
        delay(1000);
        GPIO_setPin(1,23,GPIO_PIN_STATE_LOW);
    }
    while(1) {}
    return 0;
}

void delay(int d)
{
    while(d) {}
}
