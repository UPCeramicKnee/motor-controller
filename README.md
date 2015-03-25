# Arduino Stepper Motor Controller

### About

Arduino 1.6.0 code and experiments to control our NEMA 34 stepper motor with a microcontroller. For our [capstone project at University of Portland](https://engineering.projects.up.edu/ceramicknee/). Right now these are just some prototypes but we will try to keep this updated with future code.

### Parts List

- Arduino Mega 2560
  - chosen over an Arduino Uno R3 so we can access pins while LCD keypad shield is attached
- [Nema 34 CNC Stepper Motor](http://www.omc-stepperonline.com/nema-34-cnc-stepper-motor-5nm708ozin-30a-34hs383008s-p-32.html) (most economical source we could find)
- [2M542 Stepper Motor Driver Controller](http://www.sainsmart.com/cnc-2m542-stepper-motor-driver-controller-4-5a-support-nema17-23-34.html)
- [1602 LCD Keypad Shield](http://www.sainsmart.com/sainsmart-1602-lcd-keypad-shield-for-arduino-duemilanove-uno-mega2560-mega1280.html) (generic version purchased off of ebay)
- 24V-50V for motor driver (we are using a pretty nice one courtesy of the school)
- USB or 5V Power Supply for Arduino Mega 2560

### Motor Driver Configuration & Wiring

The stepper motor came with 8 exposed wires. So it can be used in Unipolar, Bipolar Series and Bipolar Parallel configurations. Bi-Polar Series seemed like the best option for us, considering the capabilities of our power supply and project outcomes.

[to be completed]

#### Pins from Arduion to ST-M5045

- Pul+ goes to +5V
- Pul- goes to Arduino Pin 22
- Dir+ goes to +5V
- Dir- goes to to Arduino Pin 24
- Enable+ to nothing
- Enable- to nothing

#### Microsteps

- We put the driver in 8-microstep mode. We would like to use more but the Arduino is not fast enough to pulses for that.

### Questions

- What speed profile to use? Constant acceleration, constant jerk (s-curve), etc? Looks like AccelStepper library uses constant acceleration.

### Repository Contents

**KeypadTest[1...n]** - Simple keypad based menu chooser prototype for 1602 shield. Custom LCD characters were generated using the online tool at http://omerk.github.io/lcdchargen/.

**LCDKeypad** - Keypad/LCD library that worked best with my 1602 LCD Keypad shield, which uses nonstandard pinouts.

**Make Magazine Motor Test** - Code from [Driving Big Stepper Motors with Arduino](http://makezine.com/video/driving-big-stepper-motors-with-arduino/) article with modifications.

**Reference** - Spec sheets
