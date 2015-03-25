#include <LiquidCrystal.h>
#include "LCDKeypad.h"
#include "AccelStepper.h"

LCDKeypad lcd;
AccelStepper stepper(AccelStepper::DRIVER, 22, 24);

byte c_up[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00100,
  0b01110,
  0b11111,
  0b00000
};

byte c_down[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b11111,
  0b01110,
  0b00100,
  0b00000,
};

byte c_select[8] = {
  0b00000,
  0b00000,
  0b11111,
  0b10001,
  0b10001,
  0b10001,
  0b11111,
  0b00000
};

char* testOptions[] = {"#1: Demo mode", "#2: 100 Cycles", "#3: 10M Cycles"};
int testOptionsCount = 3;
int testNumber = 0; //default test number

void setup()
{
  stepper.setMaxSpeed(4000); //max supported is about 4000
  stepper.setAcceleration(10000);
  
  lcd.createChar(1, c_select);
  lcd.createChar(2, c_up);
  lcd.createChar(3, c_down);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Knee Wear Tester");
  delay(500);
  lcd.clear();
  lcd.print("Designed 2015 by");
  lcd.setCursor(0, 1);
  lcd.print(" Chris Blaydon, ");
  delay(500);
  lcd.clear();
  lcd.print(" Alan Bylund &");
  lcd.setCursor(0, 1);
  lcd.print(" Patrick Miller");
  delay(500);

  //Start getting user input
  lcd.clear();
  lcd.print("Pick Test Number");
  lcd.setCursor(0, 1);
  lcd.print("to begin.");
  delay(1000);

  //waitButton();
  //waitReleaseButton();

  bool hasChosenTest = 0;
  while (!hasChosenTest) {
    lcd.clear();
    lcd.print(testOptions[testNumber]);
    lcd.setCursor(0, 1);
    lcd.write(1);
    lcd.print(" Sel ");
    lcd.write(2);
    lcd.print(" Up ");
    lcd.write(3);
    lcd.print(" Dn");

    //Wait for correct input
    //TODO: Add debouncing support
    int buttonPressed;

    do
    {
      buttonPressed = waitButton();
    }
    while (!(buttonPressed == KEYPAD_SELECT || buttonPressed == KEYPAD_UP || buttonPressed == KEYPAD_DOWN));

    if (buttonPressed == KEYPAD_SELECT)
    {
      hasChosenTest = true; //ends loop
    }
    if (buttonPressed == KEYPAD_DOWN)
    {
      testNumber++;
      //loop back if maximum
      if (testNumber == testOptionsCount) testNumber = 0;
    }
    if (buttonPressed == KEYPAD_UP)
    {
      testNumber--;
      //loop back if minimum
      if (testNumber == -1) testNumber = testOptionsCount - 1;
    }
    waitReleaseButton();
  }


  //Just some demo code for now
  for (int i = 1; i < 2; i++) {
    lcd.clear();
    lcd.print("Testing...");
    lcd.setCursor(0, 1);
    // print the number of seconds since reset:
    lcd.print("Cycle # ");
    lcd.print(i);

    stepper.runToNewPosition(1600);
    //stepper.runToNewPosition(0);
  }
  lcd.clear();
  lcd.print("Done");
  //delay(1000);
}

void loop()
{


}

int waitButton()
{
  int buttonPressed;
  waitReleaseButton;
  lcd.blink();
  while ((buttonPressed = lcd.button()) == KEYPAD_NONE)
  {
  }
  delay(50);
  lcd.noBlink();
  return buttonPressed;
}

void waitReleaseButton()
{
  delay(50);
  while (lcd.button() != KEYPAD_NONE)
  {
  }
  delay(50);
}


