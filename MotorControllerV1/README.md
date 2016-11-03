# MotorControllerV1

Actual software to control the motor and handle LCD UI. Code written by Patrick Miller.

## Features

- Oscillate stepper motor for number of cycles configurable at runtime.
- Different timing values can easily be adjusted in .ino file.
- Shows current status on LCD screen.
- Adjust zero point, in case of unexpected power loss.

## 3rd-party Libraries

- AccelStepper: interface for controlling stepper motor
- LCDKeypad: wrapper to interace with LCD and keypad

## Internal Libraries

- LCDKeypadExtraChars: defines arrow button, select button and degree icons for LCD UI

## Other

- .linter-clang-includes to enable linter-clang Arduino header in Atom Editor
- .ctags to enable .ino support in Atom Editor
- following Chromium style guide
