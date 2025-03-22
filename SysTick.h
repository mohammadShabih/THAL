#ifndef SYSTICK_H
#define SYSTICK_H

#include "rcc.h"
#include "macros.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

extern volatile uint32_t s_ticks;

struct sys_tick {
    volatile uint32_t CNTRL, LOAD, VAL, CALIB;
};

void systick_init(uint32_t ticks);

void SysTick_Handler(void);

void delay(unsigned ms);

bool timer_expired(uint32_t *t, uint32_t prd, uint32_t now);

void spin(uint32_t ms);

#endif
