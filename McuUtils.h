#ifndef McuUtils_H
#define McuUtils_H

#include <LowPower.h>
#include <EEPROM.h>
#include <prescaler.h>


//noise reduction adc read
//http://forum.arduino.cc/index.php/topic,38119.0.html#14

// Calibration values
static const float tempGain = 1.06154;
static const float tempOffset = 331.69;//324.58;//326.07; //;326.5; // change this by calibration result

static const unsigned int tempSamples = 1000;
static const unsigned int vccSamples = 100;

// Compile time calculations
static const long tempOffsetFactor = tempOffset * tempSamples;
static const int tempDivideFactor = (tempSamples * tempGain)/10; // deci = 1/10


class McuUtils
{
public:
  LowPowerClass Sleep;
  EEPROMClass Eeprom;
  int temperatureDeciC();
  int vccmV();  
  int intRefCalib(unsigned int _vccmv);
  void setClock1MHZ();
  void setIntRef1v1(unsigned int _value);
  int getIntRef1v1();
  int freeRam();
  // set/get intRef1v1 to store in eeprom
  // set/get tempOffset to store in eeprom

private:
  inline void tempInitialize();  
  inline void vccInitialize();
  inline int readAdc();

  
  unsigned int intRef1v1 = 1100; // 1v1 ref in mVolts

};

extern McuUtils Mcu;

#endif
