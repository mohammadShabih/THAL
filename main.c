#include "gpio.h"
#include "rcc.h"
#include "macros.h"
#include "SysTick.h"
#include "uart.h"

volatile uint32_t s_ticks;

int main (void) {
    uint16_t green_led = PIN('D', 12);
    uint16_t orange_led = PIN('D', 13);
    uint16_t red_led = PIN('D', 14);
    uint16_t blue_led = PIN('D', 15);
    systick_init(16000000/1000);
    uart_init(USART2, 115200);
    enable_clock_gpio(green_led);
    gpio_set_mode(green_led, OUTPUT);
    gpio_set_mode(orange_led, OUTPUT);
    gpio_set_mode(red_led, OUTPUT);
    gpio_set_mode(blue_led, OUTPUT);
    uint32_t timer = 0, period = 500;
    for (;;) {
    	if (timer_expired(&timer, period, s_ticks)) {
    		/*delay(100);
    		gpio_set_output(green_led);
    		delay(100);
    		gpio_reset_output(green_led);
    		delay(100);
    		gpio_set_output(orange_led);
		delay(100);
		gpio_reset_output(orange_led);
		delay(100);
		gpio_set_output(red_led);
		delay(100);
		gpio_reset_output(red_led);
		delay(100);
		gpio_set_output(blue_led);
		delay(100);
		gpio_reset_output(blue_led);*/
		
		uart_write_buf(USART2, "hi\r\n", 4);
    	}
    }    
    return 0;
}

// startupcode
__attribute__((naked, noreturn)) void _reset(void) {
    extern long _sbss, _ebss, _sdata, _edata, _sidata;
    for (long *dst = &_sbss; dst < &_ebss; dst++) {
    	*dst = 0; 
    }
    for (long *dst = &_sdata, *src = &_sidata; dst < &_edata;) {
    	*dst++ = *src++;
    }

    main();

    for (;;) (void) 0;
}

extern void _estack(void);

__attribute__((section(".vectors"))) void (*const tab[16 + 82])(void) = {
    _estack, _reset, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, SysTick_Handler};
    
