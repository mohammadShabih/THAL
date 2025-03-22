#include "uart.h"

void uart_init(struct uart *uart, unsigned long baud_rate) {
	uint16_t tx = 0, rx = 0;
	uint8_t af = 0;
	if (uart == USART6) {
		RCC->APB2_EN |= BIT(5);
		tx = PIN('C', 6);
		rx = PIN('C', 7);
		af = 8;
	}
	else if (uart == USART1) {
		RCC->APB2_EN |= BIT(4);
		tx = PIN('A', 10);
		rx = PIN('A', 11);
		af = 7;
	}
	else if (uart == UART8) {
		RCC->APB1_EN |= BIT(30);
	}
	else if (uart == UART7) {
		RCC->APB1_EN |= BIT(31);
	}
	else if (uart == UART5) {
		RCC->APB1_EN |= BIT(20);
		tx = PIN('C', 12);
		rx = PIN('D', 2);
		af = 8;
	}
	else if (uart == UART4) {
		RCC->APB1_EN |= BIT(19);
		tx = PIN('A', 0);
		rx = PIN('A', 1);
		af = 7;
	}
	else if (uart == USART3) {
		RCC->APB1_EN |= BIT(18);
		tx = PIN('B', 10);
		rx = PIN('B', 11);
		af = 7;
	}
	else if (uart == USART2) {
		RCC->APB1_EN |= BIT(17);
		tx = PIN('A', 2);
		rx = PIN('A', 3);
		af = 7;
	}
	gpio_set_mode(tx, AF);
	gpio_set_af(tx, af);
	gpio_set_mode(rx, AF);
	gpio_set_af(rx, af);
	uart->cr1 &= 0xffff0000;
	uart->brr = FRQ / baud_rate;
	uart->cr1 |= BIT(13) | BIT(2) | BIT(3);
}

inline void uart_write_byte(struct uart *uart, uint8_t byte) {
	uart->dr = byte;
	while ((uart->sr & BIT(7)) == 0) {
		spin(7);
	}
}

inline uint8_t uart_read_byte(struct uart *uart) {
	uint8_t byte = (uart->dr & 255);
	return byte;
}

inline uint8_t uart_read_ready(struct uart *uart) {
	return uart->sr & BIT(5);
}

inline uint8_t uart_transmit_ready(struct uart *uart) {
	return uart->sr & BIT(7);
}

inline void uart_write_buf(struct uart *uart, char *buf, size_t len) {
	while (len-- > 0) {
		uart_write_byte(uart, *(uint8_t *) buf++);
	}
}

inline void uart_deinit

