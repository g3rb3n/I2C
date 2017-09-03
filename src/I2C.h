#ifndef _I2C_H
#define _I2C_H

#include <inttypes.h>

#include <Wire.h>

#undef TWO_WIRE_PINS

#ifdef ARDUINO_ARCH_ESP8266
  #define PINS_ON_BEGIN
#elif ARDUINO_ARCH_AVR
  #define PINS_ON_PROPERTIES
#else
  #warning "No support for setting SDA and SCL pins"
#endif

namespace g3rb3n
{

  class I2C
  {
    private:
      uint8_t _address;

    public:
      I2C(uint8_t address);
      I2C(uint8_t address, uint8_t sda, uint8_t scl);
      ~I2C();

      uint8_t address() const;
      
      void writeByte(uint8_t reg, uint8_t data) const;
      uint8_t readByte(uint8_t reg) const;
      void readBytes(uint8_t reg, uint8_t count, uint8_t * dest) const;

      bool readMaskBit(uint8_t reg, uint8_t pattern) const;

      uint8_t readMaskShift(uint8_t reg, uint8_t mask, uint8_t shift) const;
      void writeMaskClear(uint8_t reg, uint8_t pattern) const;
      void writeMaskSet(uint8_t register, uint8_t pattern) const;
      void writeMaskClearSet(uint8_t register, uint8_t pattern) const;
      void writeMaskShiftValue(uint8_t reg, uint8_t mask, uint8_t shift, uint8_t value) const;
  };

}
#endif
