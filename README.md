An utility wrapper around Wire to easily set registry values over I2C.

# Example #
```
#define address  0x00 //The address of the I2C device
#define registry 0x00 //The register to manipulate
#define mask     0xF0 //The bits to manipulate
#define shift    4    //The corresponding shift

I2C i2c(address);

uint8_t value = i2c.readMaskShift(registry, mask, shift);
value = 3;
i2c.writeMaskShiftValue(registry, mask, shift, value);
```
