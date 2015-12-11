//
// Created by Thibault PIANA on 20/10/15.
//

#ifdef __cplusplus
extern "C" {
#endif

#ifndef DRIVER_GPIO_H
#define DRIVER_GPIO_H

    /* Values used to configure the direction of GPIO pins. */
    #define GPIO_PIN_MODE_INPUT    (0x0010)
    #define GPIO_PIN_MODE_OUTPUT   (0x0011)

    /* Values helping to decide the value on a GPIO pin. */
    #define GPIO_PIN_STATE_LOW     (0x0000)
    #define GPIO_PIN_STATE_HIGH    (0x0001)

    /**
     * GPIO_setPin can change state and level of a pin
     */
    void GPIO_setPin(unsigned int gpio_base, unsigned int gpio_pin, unsigned int state);

    /**
     * Return an array with actual state of pin
     * [level, state]
     */
    unsigned int GPIO_getPinState(unsigned int gpio_base, unsigned int gpio_pin);

    /**
     * Enable GPIO
     */
    void GPIO_enable(unsigned int gpio_base);
    void GPIO_disable(unsigned int gpio_base);
    void GPIO_reset(unsigned int gpio_base);
    unsigned int GPIO_getBaseAdress(unsigned int gpio_base);

    #ifdef __cplusplus
    }
    #endif
#endif //DRIVER_GPIO_H
