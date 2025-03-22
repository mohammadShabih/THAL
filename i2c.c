#include "i2c.h"

inline void i2c_master_enable(struct i2c *i2c, uint16_t frequency_scl_khz) {
    uint16_t smba = 0, scl = 0, sda = 0;
    uint8_t af = 4;
    
    if (i2c == I2C1) {
    	smba = PIN('B', 5);
    	scl = PIN('B', '6');
    	sda = PIN('B', '7');
    	RCC->APB1_EN |= BIT(21);
    } else if (i2c == I2C2) {
    	smba = PIN('B', 12);
    	scl = PIN('B', '10');
    	sda = PIN('B', '11');
    	RCC->APB1_EN |= BIT(22);
    } else if (i2c == I2C3) {
    	smba = PIN('H', 9);
    	scl = PIN('H', '7');
    	sda = PIN('H', '8');
    	RCC->APB1_EN |= BIT(23);
    }
    
    gpio_set_mode(sda, AF);
    gpio_set_af(sda, af);
    gpio_set_mode(scl, AF);
    gpio_set_af(scl, af);
    
    i2c->cr2 &= 0xeec0;
    // setting the frequency 16Mhz, same as sys_clk, 
    // we assume the prescalar is 1 all times
    i2c->cr2 |= 0x0010;
    uint16_t frequency_clk_Mhz = 0x10;
    uint16_t ccr_bits = (frequency_clk_Mhz * 1000) / (2 * frequency_scl_khz);
    ccr_bits &= 0x00000fff;
    i2c->ccr |= BIT(15);
    i2c->ccr |= ccr_bits;
    uint16_t t_rise_bits = (1000 / (1000/frequency_clk_Mhz)) + 1;
    t_rise_bits &= 0x003f;
    i2c->trise |= t_rise_bits;
    // acknowledge enable
    i2c->cr1 |= BIT(10);
    // enable peripheral
    i2c->cr1 |= BIT(0);
}

inline void i2c_write_bytes(struct i2c *i2c, uint8_t slave_address, char *buf, size_t size_bytes) {
    slave_address <<= 1; // transciever mode
    i2c->cr1 |= BIT(8U);
    volatile uint32_t temp = i2c->sr1;
    i2c->dr |= slave_address;
    volatile uint32_t temp1 = i2c->sr1;
    volatile uint32_t temp2 = i2c->sr2;
    while (size_bytes-- > 0U) {
    	if (size_byets == 1U) {
    		btf_bit = (((i2c->sr1) & 0x00000004) >> 2U);
    		txe_bit = (((i2c->sr1) & 0x00000080) >> 7U);
    		while (btf_bit != 1U && txe_bit != 1) {
    			spin(1);
    		}
    		i2c->cr1 |= BIT(9); // set stop high after txe or btf is high
    	}
    	i2c->dr = *buf++;
    }
}

inline void i2c_read_buf(struct i2c *i2c, uint8_t slave_address, char *buf, size_t size_bytes) {
    slave_address <<= 1;
    slave_address |= BIT(0U); // reciever mode
    i2c->cr1 |= BIT(8U);
    volatile uint32_t temp = i2c->sr1;
    i2c->dr |= slave_address;
    volatile uint32_t temp1 = i2c->sr1;
    volatile uint32_t temp2 = i2c->sr2;
    uint8_t byte, btf_bit;
    while (size_bytes-- > 0U) {
    	if (size_bytes == 2U) {
    		btf_bit = (((i2c->sr1) & 0x00000004) >> 2U);
    		while (btf_bit != 1) {
    			spin(1);
    			btf_bit = (((i2c->sr1) & 0x00000004) >> 2U);
    		}
    		i2c->cr1 |= BIT(9); // set stop high
    		byte = (i2c->dr) & 0x000000ff;
    	}
    	else if (size_bytes == 3U) {
    		btf_bit = (((i2c->sr1) & 0x00000004) >> 2U);
    		while (btf_bit != 1) {
    			spin(1);
    			btf_bit = (((i2c->sr1) & 0x00000004) >> 2U);
    		}
    		i2c->cr1 &= 0xfffffbff; // set ack low
    		byte = (i2c->dr) & 0x000000ff;
    	}
    	else {
    		byte = (i2c->dr) & 0x000000ff;
    	}
    	*buf++ = byte;
    }
}

inline uint8_t i2c_read_byte(struct i2c *i2c, uint8_t slave_address) {
    slave_address <<= 1;
    slave_address |= BIT(0U); // reciever mode
    i2c->cr1 |= BIT(8U);
    volatile uint32_t temp = i2c->sr1;
    i2c->dr |= slave_address;
    i2c->cr1 &= 0xfffffbff; // set ack low
    volatile uint32_t temp1 = i2c->sr1;
    volatile uint32_t temp2 = i2c->sr2;
    i2c->cr1 |= BIT(9); // set stop high
    uint8_t byte = (i2c->dr) & 0x000000ff;;
    return byte;
}

