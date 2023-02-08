#include <Wire.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219;
uint32_t currentFrequency;


float powerread()
{
  ina219.begin();
  float power_mW = 0;
  power_mW = ina219.getPower_mW();
  return (power_mW);
}

float vread()
{
  ina219.begin();
  float shuntvoltage = 0;
  float busvoltage = 0;
  float current_mA = 0;
  float loadvoltage = 0;
  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  current_mA = ina219.getCurrent_mA();
  loadvoltage = busvoltage + (shuntvoltage / 1000);
  return(loadvoltage);
}

