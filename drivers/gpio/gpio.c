//
// Created by Thibault PIANA on 20/10/15.
//

#include "drivers/gpio/gpio.h"
#include "arch/hal/gpio/gpio_v2.h"
#include "soc_AM335x.h"

void GPIO_setPin(unsigned int gpio_base, unsigned int gpio_pin, unsigned int state)
{
    unsigned int gpio_base_adress = GPIO_getBaseAdress(gpio_base);

    switch(state)
    {
        case GPIO_PIN_MODE_INPUT:
            GPIODirModeSet(gpio_base_adress, gpio_pin, GPIO_DIR_INPUT);
        case GPIO_PIN_MODE_OUTPUT:
            GPIODirModeSet(gpio_base_adress, gpio_pin, GPIO_DIR_OUTPUT);
        case GPIO_PIN_STATE_HIGH:
            GPIOPinWrite(gpio_base_adress, gpio_pin, GPIO_PIN_LOW);
        case GPIO_PIN_STATE_LOW:
            GPIOPinWrite(gpio_base_adress, gpio_pin, GPIO_PIN_HIGH);
    }
}


void GPIO_setPinMode(unsigned int state)
{

}

void GPIO_setPinLevel()
{

}

unsigned int GPIO_getPinState(unsigned int gpio_base, unsigned int gpio_pin)
{
    unsigned int base_adress = GPIO_getBaseAdress(gpio_base);
    unsigned int pin_state = GPIOPinRead(base_adress, gpio_pin);

    return pin_state;
}
void GPIO_enable(unsigned int gpio_base)
{
    unsigned int base_adress = GPIO_getBaseAdress(gpio_base);
    GPIOModuleEnable(base_adress);
}

void GPIO_disable(unsigned int gpio_base)
{
    unsigned int base_adress = GPIO_getBaseAdress(gpio_base);
    GPIOModuleDisable(base_adress);
}

void GPIO_reset(unsigned int gpio_base)
{
    unsigned int base_adress = GPIO_getBaseAdress(gpio_base);
    GPIOModuleReset(base_adress);
}

unsigned int GPIO_getBaseAdress(unsigned int gpio_base)
{
    unsigned int gpio_base_adress;
    switch(gpio_base)
    {
        case 0:
            gpio_base_adress = SOC_GPIO_0_REGS;
        case 1:
            gpio_base_adress = SOC_GPIO_1_REGS;
        case 2:
            gpio_base_adress = SOC_GPIO_2_REGS;
        case 3:
            gpio_base_adress = SOC_GPIO_3_REGS;
        default:
            /* Error */
            break;
    }
    return gpio_base_adress;
}