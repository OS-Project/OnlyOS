//
// Created by Thibault PIANA on 20/10/15.
// Last modification : 20/10/2015
//

#ifndef ONLYOS_DRIVER_GPIO_H
#define ONLYOS_DRIVER_GPIO_H

/* Values used to configure the direction of GPIO pins. */
#define GPIO_PIN_INPUT                   (0x10)
#define GPIO_PIN_OUTPUT                  (0x11)

/* Values helping to decide the value on a GPIO pin. */
#define GPIO_PIN_LOW                     (0x0)
#define GPIO_PIN_HIGH                    (0x1)

    /**
     * GPIO_setPin can change state and level of a pin
     * For exeample :
     */
    void GPIO_setPin(unsigned int pin, unsigned int state);

    /**
     * Return an array with actual state of pin
     * [level, state]
     */
    void GPIO_getPin(unsigned int pin);
#endif //ONLYOS_DRIVER_GPIO_H
