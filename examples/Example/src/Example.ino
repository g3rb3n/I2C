#include <Arduino.h>

#include "I2C.h"

using namespace g3rb3n;

#ifdef ARDUINO_ARCH_ESP8266
//  #define SDA D2
//  #define SCL D1
  #define SDA D4
  #define SCL D3
#else
  #warning "No support for setting SDA and SCL pins"
#endif

I2C i2c(0x68, SDA, SCL);

void setup()
{
  Serial.begin(230400);
  Serial.println();
  Serial.println("Start");  
}

void loop()
{
  Serial.println(i2c.readByte(0x75), 16);
}
