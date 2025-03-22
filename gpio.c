#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "gpio.h"
#include <macros.h>

// sets gpiox mode 
inline void gpio_set_mode(uint16_t pin, uint8_t mode) {
	struct gpio *gpio = GPIO(PINBANK(pin));
	uint8_t n = PINNO(pin);
	gpio->moder &= ~(3U << (n * 2));
	gpio->moder |= ((mode & 3) << (n * 2));
}

// sets gpiox speed 
inline void gpio_set_speed(uint16_t pin, uint8_t speed) {
	struct gpio *gpio = GPIO(PINBANK(pin));
	uint8_t n = PINNO(pin);
	gpio->ospeedr &= ~(3U << (n * 2));
	gpio->ospeedr |= ((speed & 3) << (n * 2));
}

// sets gpio output state 
inline void gpio_set_output_state(uint16_t pin, uint8_t output_state) {
	struct gpio *gpio = GPIO(PINBANK(pin));
	uint8_t n = PINNO(pin);
	gpio->otyper &= ~(3U << (n * 2));
	gpio->otyper |= ((3 & output_state) << (n * 2));
}

// set pull up or pull down register
inline void gpio_set_pupd(uint16_t pin, uint8_t output_state) {
	struct gpio *gpio = GPIO(PINBANK(pin));
	uint8_t n = PINNO(pin);
	gpio->pupdr &= ~(3U << (n * 2));
	gpio->pupdr |= ((3 & output_state) << (n * 2));
}

// sets output via bsrr register
inline void gpio_set_output(uint16_t pin) {
	struct gpio *gpio = GPIO(PINBANK(pin));
	uint8_t n = PINNO(pin);
	gpio->bsrr = (1U << n);
}

// resets output via bsrr register
inline void gpio_reset_output(uint16_t pin) {
	struct gpio *gpio = GPIO(PINBANK(pin));
	uint8_t n = PINNO(pin);
	gpio->bsrr = (1U << (n+16));
}

// reads from gpiox_idr register
inline uint8_t gpio_read_pin(uint16_t pin) {
	struct gpio *gpio = GPIO((PINBANK(pin)));
	uint8_t n = PINNO(pin);
	uint8_t pin_state = ((gpio->idr) >> n) & 0x1;
	return pin_state;
}

// writes 1 to bit in lckk register 
// corresponding to pin to lock 
inline void gpio_write_lock(uint16_t pin) {
	struct gpio *gpio = GPIO(PINBANK(pin));
	uint8_t n = PINNO(pin);
	gpio->lckr |= (0x00000001 << n);
}

// this code locks the pin with a lock sequence
//by writing 1, 0, 1 to bit 16(LCKK) of lckr register
inline void gpio_lock_pin(uint16_t pin) {
	struct gpio *gpio = GPIO(PINBANK(pin));
	gpio->lckr |= (0x00010000);
	gpio->lckr &= (0xfffeffff);
	gpio->lckr |= (0x00010000);
	volatile uint32_t temp = gpio->lckr;
	temp |= 0x0;
}

// sets alternate function for specified pin
inline void gpio_set_af(uint16_t pin, uint8_t af) {
	struct gpio *gpio = GPIO(PINBANK(pin));
	uint8_t n = (PINNO(pin));
	if (n < 8) {
		gpio->afrl &= ~(15U << (n*4));
		gpio->afrl |= ((af & 0x0f) << (n*4));
	} else {
		gpio->afrh &= ~(15U << ((n-8)*4));
		gpio->afrh |= ((af & 0x0f) << ((n-8)*4));
	}
}

void print_binary(uint32_t x) {
    char ret_arr[33];
    uint32_t i, mask;
    for (i = 0U; i < 32U; i++) {
        mask = (1U<<i);
        if ((mask & x) == 0U) {
            ret_arr[31U-i] = '0';
        }
        else {
            ret_arr[31U-i] = '1';
        }
    }
    ret_arr[32U] = '\0';
    printf("%s\n", ret_arr);
}
