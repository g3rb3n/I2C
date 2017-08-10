#include <Arduino.h>
#include <unity.h>

#include <inttypes.h>

#include "../src/I2C.h"

#ifdef UNIT_TEST

using namespace g3rb3n;

uint8_t address = 0x68;
uint8_t register_ = 0x1B;
uint8_t WHO_AM_I = 0x75;
uint8_t I_AM = 0x71;

I2C i2c(address);

void testWriteRead(void)
{
  for (uint8_t i = 0 ; i < 16 ; ++i)
  {
    i2c.writeByte(register_, i);
    uint8_t returned = i2c.readByte(register_);
    TEST_ASSERT_EQUAL(i, returned);
  }
}

void testConnection(void)
{
  TEST_ASSERT_EQUAL(I_AM, i2c.readByte(WHO_AM_I));
}

void testWriteReadMasked(void)
{
  uint8_t mask = 0xF0;
  uint8_t shift = 4;
  uint8_t returned;
  for (uint8_t i = 0 ; i < 8 ; ++i)
  {
    i2c.writeMaskShiftValue(register_, mask, shift, i);
    returned = i2c.readByte(register_);
    TEST_ASSERT_EQUAL(i, returned >> shift);
    returned = i2c.readMaskShift(register_, mask, shift);
    TEST_ASSERT_EQUAL(i, returned);
  }
}

void setup()
{
  // NOTE!!! Wait for >2 secs
  // if board doesn't support software reset via Serial.DTR/RTS
  delay(2000);

  UNITY_BEGIN();

  RUN_TEST(testConnection);
  RUN_TEST(testWriteRead);
  
  UNITY_END();
}

void loop() 
{
}

#endif
