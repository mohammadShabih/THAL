#include "SysTick.h"

inline void systick_init(uint32_t ticks) {
    if ((ticks - 1) > 0xffffff) {
        return;
    }
    SYSTICK->LOAD = ticks - 1;
    SYSTICK->VAL = 0U;
    SYSTICK->CNTRL = BIT(0U) | BIT(1U) | BIT(2U);
    RCC->APB2_EN |= BIT(14U);
}

void SysTick_Handler(void) {
    s_ticks++;
}

void delay(unsigned ms) {
    uint32_t until = s_ticks + ms;
    while (s_ticks < until) (void) 0;
}

// t corresponds to expiration, period, now = current time
bool timer_expired(uint32_t *t, uint32_t prd, uint32_t now) {
    if (now + prd < *t) {
        *t = 0;
    } //
    if (*t == 0) {
        *t = now + prd;
    }
    if (*t > now) {
        return false;
    }
    *t = (now - *t) > prd ? now + prd : *t + prd;
    return true;
}

void spin(uint32_t ms) {
	while(ms--) (void) 0;
}
