#include "I2C.h"

#include <Arduino.h>

#undef TWO_WIRE_PINS

#ifdef ARDUINO_ARCH_ESP8266
  #define PINS_ON_BEGIN
#elif ARDUINO_ARCH_AVR
  #define PINS_ON_PROPERTIES
#else
  #define NO_PINS
  #warning "No support for setting SDL and SDA pins"
#endif

namespace g3rb3n
{
  
  I2C::I2C(uint8_t address):
    _address(address)
  {
    Wire.begin();
  }

  I2C::I2C(uint8_t address, uint8_t sda, uint8_t scl):
    _address(address)
  {
    #ifdef PINS_ON_PROPERTIES
        Wire.scl_pin = scl;
        Wire.sda_pin = sda;
        Wire.begin();
    #endif
    #ifdef PINS_ON_BEGIN
        Wire.begin(scl, sda);
    #endif
    #ifdef NO_PINS
      Wire.begin();
    #endif
  }

  I2C::~I2C()
  {}

  uint8_t I2C::address() const
  {
    return _address;
  }
  
  void I2C::writeByte(uint8_t reg, uint8_t data) const
  {
    Wire.beginTransmission(_address);
    Wire.write(reg);
    Wire.write(data);
    Wire.endTransmission();
    delay(10);
  }

  uint8_t I2C::readByte(uint8_t reg) const
  {
    uint8_t data; 
    Wire.beginTransmission(_address);
    Wire.write(reg);
    Wire.endTransmission(false);
    Wire.requestFrom(_address, (uint8_t) 1);
    data = Wire.read();
    return data;
  }

  void I2C::readBytes(uint8_t reg, uint8_t count, uint8_t * dest) const
  {  
    Wire.beginTransmission(_address);
    Wire.write(reg);
    Wire.endTransmission(false);
    uint8_t i = 0;
    Wire.requestFrom(_address, count);
    while (Wire.available())
    {
      dest[i++] = Wire.read();
    }
  }

  bool I2C::readMaskBit(uint8_t reg, uint8_t mask) const
  {
    uint8_t value = readByte(reg);
    return value & mask;  
  }

  uint8_t I2C::readMaskShift(uint8_t reg, uint8_t mask, uint8_t shift) const
  {
    uint8_t value = readByte(reg);
    value &= mask;
    return value >> shift;
  }

  void I2C::writeMaskShiftValue(uint8_t reg, uint8_t mask, uint8_t shift, uint8_t value) const
  {
    uint8_t r = readByte(reg);
    r &= ~mask;
    r |= value << shift;
    writeByte(reg, r);
  }

  void I2C::writeMaskClearSet(uint8_t reg, uint8_t mask) const
  {
    uint8_t value = readByte(reg);
    value &= ~mask;
    value |= mask;
    writeByte(reg, value);
  }

  void I2C::writeMaskSet(uint8_t reg, uint8_t mask) const
  {
    uint8_t value = readByte(reg);
    value |= mask;
    writeByte(reg, value);
  }

  void I2C::writeMaskClear(uint8_t reg, uint8_t mask) const
  {
    uint8_t value = readByte(reg);
    value &= ~mask;
    writeByte(reg, value);
  }

}
