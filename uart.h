#include <stdint.h>
#include "gpio.h"
#include "macros.h"
#include "SysTick.h"

struct uart {
    volatile uint32_t sr, dr, brr, cr1, cr2, cr3, gtpr;
};

void uart_init(struct uart *uart, unsigned long baud_rate);

void uart_write_byte(struct uart *uart, uint8_t byte);

uint8_t uart_read_byte(struct uart *uart);

uint8_t uart_read_ready(struct uart *uart);

uint8_t uart_transmit_ready(struct uart *uart);

void uart_write_buf(struct uart *uart, char *buf, size_t len);
