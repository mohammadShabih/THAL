#include "rcc.h"

//inline void enable_clock_gpio(uint16_t pin) {
	//uint8_t bank = PINBANK(pin);
	//RCC->AHB1_EN |= (1UL << bank);
//}

// choose between hse, pll, and hsi
// we also need to set the speed of this peripheral
// i am assuming that once an input clock is set for the sys_clk
// it will automatically go through to the ahb1, apb1
// the only thing neccesory would be to set the en bits in ahb and apb registers
// for the different peripherals
sys_clk_config()

// enabling and disbling of clock sources, such as into sys_clk
// we will probbably only do this for sys_clk
// will have to wait for hse, hsi, clocks stabalzie and then set them or use them
// there are flags to check for this
clock_source_managment()

// config pll for higher freq operation
// set pll input source clock
// congif pll multiplication factor, remember there was r,n and p which were the multiplication factors
//
pll_source_and_multipliers()

// I think the indepenedent watchdog would require its own driver

// for measuing the speed of the clk to determine if it's running at expected speed
// need a timer for this, so write the timer driver
rcc_check_clk_status

deinit()

