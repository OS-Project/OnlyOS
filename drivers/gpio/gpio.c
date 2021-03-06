/*
    * Created by Thibault PIANA on 20/10/15.
*/

#include "drivers/gpio/gpio.h"

void GPIO_setPin(char gpio_number, char gpio_pin, GPIO_PIN state) {
    unsigned int base_adress = GPIO_getPhysicalAdress(gpio_number);

    switch(state)
    {
        case GPIO_PIN_MODE_INPUT:
            GPIODirModeSet(base_adress, gpio_pin, GPIO_DIR_INPUT);
        case GPIO_PIN_MODE_OUTPUT:
            GPIODirModeSet(base_adress, gpio_pin, GPIO_DIR_OUTPUT);
        case GPIO_PIN_STATE_HIGH:
            GPIOPinWrite(base_adress, gpio_pin, GPIO_PIN_LOW);
        case GPIO_PIN_STATE_LOW:
            GPIOPinWrite(base_adress, gpio_pin, GPIO_PIN_HIGH);
    }
}

unsigned int GPIO_getPinState(char gpio_number, char gpio_pin) {
    unsigned int base_adress = GPIO_getPhysicalAdress(gpio_number);
    unsigned int pin_state = GPIOPinRead(base_adress, gpio_pin);

    return pin_state;
}
void GPIO_enable(char gpio_number) {
    unsigned int base_adress = GPIO_getPhysicalAdress(gpio_number);
    GPIOModuleEnable(base_adress);
}

void GPIO_disable(char gpio_number) {
    unsigned int base_adress = GPIO_getPhysicalAdress(gpio_number);
    GPIOModuleDisable(base_adress);
}

void GPIO_reset(char gpio_number) {
    unsigned int base_adress = GPIO_getPhysicalAdress(gpio_number);
    GPIOModuleReset(base_adress);
}

unsigned int GPIO_getPhysicalAdress(char gpio_number) {
    unsigned int physical_adress;
    switch(gpio_number)
    {
        case 0:
            physical_adress = SOC_GPIO_0_REGS;
            break;
        case 1:
            physical_adress = SOC_GPIO_1_REGS;
            break;
        case 2:
            physical_adress = SOC_GPIO_2_REGS;
            break;
        case 3:
            physical_adress = SOC_GPIO_3_REGS;
            break;
        default:
            physical_adress = 0;
            break;
    }
    return physical_adress;
}