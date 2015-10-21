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

void GPIO_setPin(unsigned int base_gpio, unsigned int pin, unsigned int state)
{
    unsigned int base_adress = GPIO_getBaseAdress(base_gpio);

    switch(state)
    {
        case GPIO_PIN_MODE_INPUT:
            GPIODirModeSet(base_adress,
                           pin,
                           GPIO_DIR_INPUT);
        case GPIO_PIN_MODE_OUTPUT:
        case GPIO_PIN_STATE_HIGH:
        case GPIO_PIN_STATE_LOW:
    }
}

void GPIO_enable(unsigned int base_gpio)
{
    unsigned int base_adress = GPIO_getBaseAdress(base_gpio);
    GPIOModuleEnable(base_adress);
}

void GPIO_reset(unsigned int base_gpio)
{
    unsigned int base_adress = GPIO_getBaseAdress(base_gpio);
    GPIOModuleReset(base_adress);
}

void GPIO_getBaseAdress(unsigned int base_gpio)
{
    switch(base_gpio)
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
    return base_adress;
}