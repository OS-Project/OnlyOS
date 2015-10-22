//
// Created by Thibault PIANA on 20/10/15.
// Last modification : 22/10/2015 by Thibault PIANA
//

#ifdef __cplusplus
extern "C" {
#endif

#ifndef ONLYOS_DRIVER_GPIO_H
#define ONLYOS_DRIVER_GPIO_H

/* Values used to configure the direction of GPIO pins. */
#define GPIO_PIN_MODE_INPUT    (0x0010)
#define GPIO_PIN_MODE_OUTPUT   (0x0011)

/* Values helping to decide the value on a GPIO pin. */
#define GPIO_PIN_STATE_LOW     (0x0000)
#define GPIO_PIN_STATE_HIGH    (0x0001)

/**
 * GPIO_setPin can change state and level of a pin
 */
void GPIO_setPin(unsigned int base_gpio, unsigned int pin, unsigned int state);

/**
 * Return an array with actual state of pin
 * [level, state]
 */
void GPIO_getPin(unsigned int pin);

/**
 * Enable GPIO
 */
void GPIO_enable();
void GPIO_disable();
void GPIO_reset();

#ifdef __cplusplus
}
#endif
#endif //ONLYOS_DRIVER_GPIO_H
