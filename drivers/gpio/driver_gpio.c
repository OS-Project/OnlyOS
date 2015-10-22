//
// Created by thibault on 20/10/15.
//

#include "driver_gpio.h"

/**
 * Ressources for beaglebone
 */
#include "soc_AM335x.h"
#include "beaglebone.h"
#include "gpio_v2.h"
#include "utils_errno.h"

void GPIO_setPin(unsigned int gpio_base, unsigned int pin, unsigned int state)
{
    unsigned int gpio_base_adress = GPIO_getBaseAdress(base_gpio);

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

void GPIO_enable(unsigned int gpio_base)
{
    unsigned int base_adress = GPIO_getBaseAdress(gpio_base);
    GPIOModuleEnable(base_adress);
}

void GPIO_reset(unsigned int gpio_base)
{
    unsigned int base_adress = GPIO_getBaseAdress(gpio_base);
    GPIOModuleReset(base_adress);
}

unsigned int GPIO_getBaseAdress(unsigned int gpio_base)
{
    switch(gpio_base)
    {
        case 0:
            unsigned int base_adress = SOC_GPIO_0_REGS;
        case 1:
            unsigned int base_adress = SOC_GPIO_1_REGS;
        case 2:
            unsigned int base_adress = SOC_GPIO_2_REGS;
        case 3:
            unsigned int base_adress = SOC_GPIO_3_REGS;
        default:
            error("GPIO invalide pour la beaglebone");
    }
    return gpio_base_adress;
}