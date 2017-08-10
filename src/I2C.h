#ifndef _I2C_H
#define _I2C_H

#include <Wire.h>
#include <inttypes.h>

namespace g3rb3n
{

  class I2C
  {
    private:
      uint8_t _address;

    public:
      I2C(uint8_t address);
      I2C(uint8_t address, uint8_t sda, uint8_t cls);
      ~I2C();

      uint8_t address();
      
      void writeByte(uint8_t reg, uint8_t data);
      uint8_t readByte(uint8_t reg);
      void readBytes(uint8_t reg, uint8_t count, uint8_t * dest);

      bool readMaskBit(uint8_t reg, uint8_t pattern);

      uint8_t readMaskShift(uint8_t reg, uint8_t mask, uint8_t shift);
      void writeMaskClear(uint8_t reg, uint8_t pattern);
      void writeMaskSet(uint8_t register, uint8_t pattern);
      void writeMaskClearSet(uint8_t register, uint8_t pattern);
      void writeMaskShiftValue(uint8_t reg, uint8_t mask, uint8_t shift, uint8_t value);
  };

}
#endif
