// these are memory addresses f didffernt periherals
// these are the baae adddrese at which peripherals stores their registers

#define PIN(bank, num) (((bank - 'A') << 8) | (num))
#define PINNO(pin) ((uint8_t)(pin & 255))
#define PINBANK(pin) ((uint8_t)(pin >> 8))

#define GPIO(bank) ((struct gpio *) (0x40020000 + (0x400 * bank)))
#define RCC ((struct rcc *) 0x40023800)
#define SYSTICK ((struct sys_tick *) 0xe000e010)
#define BIT(x) (1UL << (x))
#define FRQ 16000000

#define USART6 ((struct uart *) 0x40011400)
#define USART1 ((struct uart *) 0x40011000)
#define UART8 ((struct uart *) 0x40007000)
#define UART7 ((struct uart *) 0x40007800)
#define UART5 ((struct uart *) 0x40007800)
#define UART4 ((struct uart *) 0x40004c00)
#define USART3 ((struct uart *) 0x40004800)
#define USART2 ((struct uart *) 0x400044000)

#define I2C1 ((struct i2c *) 0x40005C00)
#define I2C2 ((struct i2c *) 0x40005800)
#define I2C3 ((struct i2c *) 0x40005400)

#define DCMI ((struct dcmi *) 0x5005 0000)

#define DMA1 ((struct dma *) 0x40026000)
#define DMA2 ((struct dma *) 0x40026400)
