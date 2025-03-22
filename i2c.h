#include "macros.h"

struct i2c {
    volatile uint32_t cr1, cr2, oart1, oar2, dr, sr1, sr2, ccr, trise;
};

void i2c_write_bytes(struct i2c *i2c, uint8_t slave_address, char *buf, size_t size_bytes);

void i2c_master_enable(struct i2c *i2c, uint16_t frequency_scl_khz);

void i2c_read_buf(struct i2c *i2c, uint8_t slave_address, char *buf, size_t size_bytes);

uint8_t i2c_read_byte(struct i2c *i2c, uint8_t slave_address);
