#ifndef GPIO_H
#define GPIO_H
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// gpio data structure
struct gpio {
	volatile uint32_t moder, otyper, ospeedr, pupdr, idr, odr, bsrr, lckr, afrl, afrh;
};

// pin modes
enum eModer {
	INPUT, OUTPUT, AF, ANALOG
};

// output states
enum eOtyper {
	PUSH_PULL, OPEN_DRAIN
};

// speed
enum eOspeedr {
	LOW, MEDIUM, HIGH, TURBO
};

// activates pull up and down registers
enum ePupdr {
	NONE, PULL_UP, PULL_DOWN, RESERVED
};

// function declerations
void print_binary(uint32_t x);
void gpio_set_mode(uint16_t pin, uint8_t mode);
void gpio_set_speed(uint16_t pin, uint8_t speed);
void gpio_set_output_state(uint16_t pin, uint8_t output_state);
void gpio_set_pupd(uint16_t pin, uint8_t output_state);
void gpio_set_output(uint16_t pin);
void gpio_reset_output(uint16_t pin);
uint8_t gpio_read_pin(uint16_t pin);
void gpio_write_lock(uint16_t pin);
void gpio_lock_pin(uint16_t pin);
void gpio_set_af(uint16_t pin, uint8_t af);

#endif
