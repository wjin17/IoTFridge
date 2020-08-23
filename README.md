# IoTFridge

Is your fridge in your kitchen or garage? Is it a pain to have to walk around your house just to take a sip of an ice cold beverage? Want to set the fridge temperature from your mobile device? If you're like me, IoTFridge is the perfect DIY solution to fit your needs. IoTFridge is a project for an IoT mini fridge created so that I can drink soda or water at a temperature between 38F-42F directly in my room.

## Values for config file
```
// thermistor params
#define THERMISTOR_POWER: Pin to provide power to thermistor prior to reading
#define THERMISTOR_READ: Analog pin for reading thermistor voltage divider circuit

#define THERMISTOR_DELAY: How often in milliseconds you want to read the temp

#define VCC: Voltage of thermistor power pin
#define R1: Value of known resistor in thermistor circuit, should be equivalent to thermistor
#define C1: First coefficient of Steinhart-Hart Equation
#define C2: Second coefficient of Steinhart-Hart Equation
#define C3: Third coefficient of Steinhart-Hart Equation

// relay params
#define RELAY_PIN: Relay pin

// fridge settings
#define LOWER_TEMP: Lower bound of fridge temp (float)
#define UPPER_TEMP: Upper bound of fridge temp (float)
```
## Fridge components
* ESP8266 (WeMos D1 mini)
* Relay
* OLED Shield
* 100k Thermistor
* Peltier cooling device (TEC 12706)
* Step down switching regulator (LM2596)
* Water cooling system for TEC 12706 (water block, radiator, reservoir, pump)
* 12V 10A power supply
* Insulating foam

## Calculating Steinhart-Hart coefficients
[Steinhart-Hart Calculator](https://rusefi.com/Steinhart-Hart.html)

## License
[MIT](https://choosealicense.com/licenses/mit/)