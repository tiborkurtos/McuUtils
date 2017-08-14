#include <LowPower.h>
#include <EEPROM.h>
#include <prescaler.h>
#include <McuUtils.h>

byte serialByte;

/*
Albert van Dalen www.avdweb.nl
Set the offset in ChipTemp.h to:
offset’ = deciCelsius * gain / 10 + offset – gain * T

Definitions
offset’ = the new offset value for ChipTemp.h
gain = 1.06154
offset = is the offset in ChipTemp.h (335.2)
T = room temperature

Formula distraction
deciCelsius = 10 * (ADC - offset) / gain
ADC = gain’ * T + offset’
deciCelsius = (gain’ * T + offset’ – offset) * 10 / gain
if offset’ = offset and gain’ = gain
deciCelsius = 10T
Assume gain’ = gain
offset’ = deciCelsius * gain / 10 + offset – gain * T
Set offset in ChipTemp.h to offset’
*/

void setup(void) {
  Serial.begin(57600);
}


int msrArduinoRawTomV(int _raw)
{
  return (_raw / 1024.0) * Mcu.vccmV();
}

int msrArduinoRaw(byte _channel)
{
  unsigned long int resultmV = 0;

  for (int i=0; i < 100; i++)
  {
    resultmV += analogRead(_channel);
  }
  resultmV = resultmV / 100;
  return resultmV;
  
}

void loop()
{

  Serial.print("Vcc:");
  Serial.print(Mcu.vccmV());

  Serial.print(" A0:");
  Serial.print(msrArduinoRawTomV(msrArduinoRaw(A0)));

  Serial.print(" Int ref:");
  Serial.print(Mcu.getIntRef1v1());

  Serial.print(" Chip temp:");
  Serial.println(Mcu.temperatureDeciC());

  if(Serial.available())
  {
    serialByte = Serial.read();
    if (serialByte == 'u')
    {
      Mcu.setIntRef1v1(Mcu.getIntRef1v1()+1);
    } else if (serialByte == 'd')
    {
      Mcu.setIntRef1v1(Mcu.getIntRef1v1()-1);
    }  
    Serial.println(Mcu.getIntRef1v1());
  }
  
  delay(1000);
}
