//
// Created by Thibault PIANA on 20/10/15.
//

#ifdef __cplusplus
extern "C" {
#endif

#ifndef DRIVER_GPIO_H
#define DRIVER_GPIO_H
    typedef enum GPIO_PIN GPIO_PIN;
    enum GPIO_PIN
    {
        GPIO_PIN_MODE_INPUT,
        GPIO_PIN_MODE_OUTPUT,
        GPIO_PIN_STATE_LOW,
        GPIO_PIN_STATE_HIGH
    };

    /**
     * GPIO_setPin can change state and level of a pin
     */
    void GPIO_setPin(unsigned int gpio_base, unsigned int gpio_pin, GPIO_PIN state);

    /**
     * Return an array with actual state of pin
     * [level, state]
     */
    unsigned int GPIO_getPinState(unsigned int gpio_base, GPIO_PIN gpio_pin);

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
