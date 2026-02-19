# RC_car 🚗
A simple and elegent, biginner friendly Arduino sketch for RC car, consisting of parking lights, rear wheel drive, park mode and safety brakes. 🚥
Note: This sketch uses IRremote library v2.8.0 for simplicity.

## How to use 🎮

- Create the suggested circuit by following the provided circuit diagram.
- Download the files and import _"Firmware.ino"_ into Arduino IDE.
- Update the hex codes for the specific DIY or TV remote. A code reader program maybe employed to get hex codes of corresponding keys. Suggested keys are: UP, DOWN, LEFT, RIGHT, OK/SELECT
- Upload the code into Arduino.

## Components/BOM ⚙️

- Any Arduino Uno compatible board 
- 2xLeds of any color (indication) 
- 220 ohm resistors for LED
- L293D or similar H-bridge IC
- 2xMotors (halt current of max 1A with L293D)
- IR demodulator (component or module)
- 9V battery
- Optional: Chasis for the car

### Demo
A demo of the internal working of curcuit via leds for each pin is given in _"LED_Circuit_Demo.mp4"_
