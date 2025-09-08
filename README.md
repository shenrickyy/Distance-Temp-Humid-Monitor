# Distance-Temp-Humid-Monitor
A simple Arduino based project that uses a DHT11 to read temperature and humidity and an ultrasonic sensor for distance. The results are then displayed on a 16x2 LCD and its contrast is controlled with a potentiometer. An active buzzer will alert the user when distance is too close to the sensor or when the temperature exceeds a certain limit.

## HardWare (Elegoo UNO R3 Super Starter Kit)
- Arduino UNO R3
- Ultrasonic Sensor
- DHT11 Temperature and Humidity Module
- 16x2 LCD
- Active Buzzer
- Breadboard
- Jumper wires
- Potentiometer 10K

## Pins
-  DHT11: DATA -> D3
-  Ultrasonic Sensor: TRIG -> D5, ECHO -> D4
-  Active Buzzer: D2
-  LCD: RS -> D12, E -> 11, D4 -> 10, D5 -> 9, D6 -> 7, D7 -> 6
-  LCD V0 -> Pot Wiper, Pot Ends -> 5V & GND

## Libraries Installed
- DHT sensor library by Adafruit
- Adafruit Unified Sensor by Adafruit
- LiquidCrystal by Arduino, Adafruit

## Notes
- When I PWM V0, random glyphs were displayed after around 5 executions of the code. Use the potentiometer.
