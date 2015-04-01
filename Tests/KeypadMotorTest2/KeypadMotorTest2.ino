#include <LiquidCrystal.h>
#include "./LCDKeypad.h"
#include "./AccelStepper.h"

////////////////////////////////////////////////////////////////////////////////
// VARIABLE INITIALIZATIONS AND CONSTANTS
////////////////////////////////////////////////////////////////////////////////

enum Menu_Items
{
  mode_demo,
  mode_10_cycles,
  mode_100_cycles,
  screen_about,
  FINAL_MENU_ITEMS_ENTRY
};

const char* Menu_Item_As_Strings[] =
{
  "Demo mode",
  "100 Cycles",
  "10M Cycles",
  "About"
};

const char* testOptions[] = {"#1: Demo mode", "#2: 100 Cycles","#3: 10M Cycles","About"};
int testOptionsCount = 4;
int testNumber = 0; //default test number

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

////////////////////////////////////////////////////////////////////////////////
// FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

void showAboutScreen()
{
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
}

////////////////////////////////////////////////////////////////////////////////
// MAIN
////////////////////////////////////////////////////////////////////////////////

void setup()
{
  stepper.setMaxSpeed(4000); //max supported is about 4000
  stepper.setAcceleration(10000);

  lcd.createChar(1, c_select);
  lcd.createChar(2, c_up);
  lcd.createChar(3, c_down);
  lcd.begin(16, 2);

  //Start getting user input
  lcd.clear();
  lcd.print("Pick Test Number");
  lcd.setCursor(0, 1);
  lcd.print("to begin.");
  delay(1000);

  //waitButton();
  //waitReleaseButton();

  int testOptionsCount = FINAL_MENU_ITEMS_ENTRY;

  bool hasChosen = 0;
  int which_button = 0;
  while (!hasChosen) {
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

    do
    {
      which_button = waitButton();
    }
    while (!(which_button == KEYPAD_SELECT || which_button == KEYPAD_UP || which_button == KEYPAD_DOWN));

    if (which_button == KEYPAD_SELECT)
    {
      hasChosen = true; //ends loop
    }
    if (which_button == KEYPAD_DOWN)
    {
      testNumber++;
      //loop back if maximum
      if (testNumber == testOptionsCount) testNumber = 0;
    }
    if (which_button == KEYPAD_UP)
    {
      testNumber--;
      //loop back if minimum
      if (testNumber == -1) testNumber = testOptionsCount - 1;
    }
    waitReleaseButton();
  }

  if (testNumber == 3)
  {
    showAboutScreen();
  }

  //Just some demo code for now
  for (int i = 1; i < 10; i++) {
    lcd.clear();
    lcd.print("Testing...");
    lcd.setCursor(0, 1);
    // print the number of seconds since reset:
    lcd.print("Cycle # ");
    lcd.print(i);

    stepper.runToNewPosition(1600);
    stepper.runToNewPosition(0);
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
  int which_button;
  waitReleaseButton;
  lcd.blink();
  while ((which_button = lcd.button()) == KEYPAD_NONE)
  {
  }
  delay(50);
  lcd.noBlink();
  return which_button;
}

void waitReleaseButton()
{
  delay(50);
  while (lcd.button() != KEYPAD_NONE)
  {
  }
  delay(50);
}
