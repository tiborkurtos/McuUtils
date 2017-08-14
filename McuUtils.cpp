#include <Arduino.h>
#include "McuUtils.h"
#include <LowPower.h>
#include <EEPROM.h>

inline void McuUtils::tempInitialize()
{
  ADMUX = 0xC8; // select reference, select temp sensor
  delay(5); // wait for the analog reference to stabilize
  readAdc(); // discard first sample (never hurts to be safe)
}

inline void McuUtils::vccInitialize()
{
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1); // Read 1.1V reference against AVcc
  delay(5); // wait for the analog reference to stabilize
  readAdc(); // discard first sample (never hurts to be safe)
}

inline int McuUtils::readAdc()
{
  ADCSRA |= _BV(ADSC); // start the conversion
  while (bit_is_set(ADCSRA, ADSC)); // ADSC is cleared when the conversion finishes
  return (ADCL | (ADCH << 8)); // combine bytes
}

int McuUtils::temperatureDeciC()
{
  //return chip temperature in degree Celsius
  long averageTemp=0;
  tempInitialize(); // must be done everytime
  for (int i=0; i < tempSamples; i++)
    averageTemp += readAdc();
  averageTemp -= tempOffsetFactor;
  return averageTemp / tempDivideFactor; // return deci degree Celsius
}

//https://code.google.com/archive/p/tinkerit/wikis/SecretVoltmeter.wiki
int McuUtils::vccmV() {
  // returns in Vcc in mV
  unsigned long int result = 0;
  vccInitialize();  
  for (int i=0; i < vccSamples; i++)
    result += readAdc();
  result = result / vccSamples;    
  result = (intRef1v1 * 1024L)  / result; // Back-calculate AVcc in mV
  return result;
}

int McuUtils::intRefCalib(unsigned int _vccmv = 5000) // if the Vcc is 5.000V
{
  unsigned long int result = 0;
  vccInitialize();  
  for (int i=0; i < vccSamples; i++)
    result += readAdc();
  result = result / vccSamples;    
  return (_vccmv * result) / 1024;   
}

void McuUtils::setClock1MHZ()
{
  if (F_CPU == 16000000L)
    setClockPrescaler(CLOCK_PRESCALER_16);
  else if (F_CPU == 8000000L)
    setClockPrescaler(CLOCK_PRESCALER_8);
  else if (F_CPU == 4000000L)
    setClockPrescaler(CLOCK_PRESCALER_4);
  else if (F_CPU == 2000000L)
    setClockPrescaler(CLOCK_PRESCALER_2);
  else if (F_CPU == 1000000L)
    setClockPrescaler(CLOCK_PRESCALER_1);
}


void McuUtils::setIntRef1v1(unsigned int _value)
{
  if (_value != 0)
  {
    intRef1v1 = _value;
  }
}
int McuUtils::getIntRef1v1()
{
    return intRef1v1;
}

int McuUtils::freeRam() {
  extern int __heap_start, *__brkval; 
  int v; 
  int fr = (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
  
  return fr;
}


McuUtils Mcu;

//TODO
// set/get intRef1v1 to store in eeprom
//set prescaler to 1, 8, 16 F_CPU long int
