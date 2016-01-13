/*
    * Created by Thibault PIANA on 20/10/15.
*/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef DRIVER_GPIO_H
#define DRIVER_GPIO_H
    #include "hal/gpio/gpio_v2.h"
    #include "soc_AM335x.h"

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
    void GPIO_setPin(char gpio_number, char gpio_pin, GPIO_PIN state);

    /**
     * Return an array with actual state of pin
     * [level, state]
     */
    unsigned int GPIO_getPinState(char gpio_number, char gpio_pin);

    /**
     * Enable GPIO
     */
    void GPIO_enable(char gpio_number);
    void GPIO_disable(char gpio_number);
    void GPIO_reset(char gpio_number);
    unsigned int GPIO_getPhysicalAdress(char gpio_number);


#endif /* DRIVER_GPIO_H */
#ifdef __cplusplus
}
#endif