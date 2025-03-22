#ifndef RCC_H
#define RCC_H
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "macros.h"

struct rcc {
    uint32_t CR, PLL_CFGR, CFG, CLK_INTRPT, AHB1_RST, AHB2_RST, AHB3_RST, RESERVED0, APB1_RST,
    APB2_RST, RESERVED1[2], AHB1_EN, AHB2_EN, AHB3_EN, RESERVED2, APB1_EN, APB2_EN, RESERVED3[2],
    AHB1_EN_LP, AHB2_EN_LP, AHB3_EN_LP, RESERVED4, APB1_EN_LP, APB2_EN_LP, RESERVED5[2], BCDR, CSR,
    RESERVED6[2], SSCGR, PLL_I2S_CFGR;
};

void enable_clock_gpio(uint16_t pin);

deinit()
#endif
