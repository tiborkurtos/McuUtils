# McuUtils

ATmega328 utility library for Arduino 

## Getting started

The reason for creating this library is to give simple access for some of the built in features of the ATmega168/328 microprocessor.

* Sleep functions - using the lowPower library
* EEPROM functions - using the EEPROM library
* Clock prescaler to set the clock frequency at runtime - using the Prescaler library
* Measure the chip VCC in mV
* Measure the chip temperature in deci-celcius
* Get the free ram

### Example

Read internal values

```
Serial.print("Vcc:");
Serial.print(Mcu.vccmV());

Serial.print(" Chip temp:");
Serial.println(Mcu.temperatureDeciC());
```

Sleep

```
Mcu.Sleep.powerDown(SLEEP_8S, ADC_OFF, BOD_ON);	
```

EEPROM load and save

```
void eprLoad()
{
  char _ver[sizeof(nodeVersion)];
  Mcu.Eeprom.get(0, _ver);  
  if ( strcmp(_ver, nodeVersion) == 0 )
  {
    Mcu.Eeprom.get(sizeof(nodeVersion), setting);
  }
  else
  {
    defaultSettings();
  }
}

void eprSave()
{
  Mcu.Eeprom.put(0, nodeVersion);
  Mcu.Eeprom.put(sizeof(nodeVersion), setting);  
}
```
  

### Prerequisites

The library uses the following libraries:
Prescaler https://github.com/fschaefer/Prescaler
LowPower https://github.com/rocketscream/Low-Power

## Authors

* **Tubor Kurtos** - *Initial work* - [tiborkurtos](https://github.com/tiborkurtos)

See also the list of [contributors](https://github.com/tiborkurtos/McuUtils/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details

## Acknowledgments

* https://code.google.com/archive/p/tinkerit/wikis/SecretVoltmeter.wiki
* Albert van Dalen www.avdweb.nl
* (c) 2008 Sofian Audry | http://sofianaudry.com
* http://www.rocketscream.com
* Florian Schäfer http://playground.arduino.cc/Code/Prescaler
