#include "MotorControllerV1.h"
#include "Arduino.h"
#include <LiquidCrystal.h>
#include "./LCDKeypad.h"
#include "./AccelStepper.h"
#include "./LCDKeypadExtraChars.h"

////////////////////////////////////////////////////////////////////////////////
// VARIABLE INITIALIZATIONS AND CONSTANTS
////////////////////////////////////////////////////////////////////////////////

enum Main_Menu {
  mode_rotate_and_zero,
  mode_1_cycle,
  mode_10_cycles,
  mode_100_cycles,
  mode_100_cycles_slow,
  mode_about,
  MAIN_MENU_ENUM_LAST_ITEM
};

const char* Main_Menu_Names[] = {
  "Rotate/re-zero",
  "1 cycle",
  "10 cycles",
  "100 cycles",
  "100 cyclesSLOW",
  "About"
};

enum Confirm_Menu {
  mode_cancel,
  mode_confirm,
  CONFIRM_MENU_ENUM_LAST_ITEM
};

const char* Confirm_Menu_Names[] = {
  "Cancel",
  "Confirm"
};

LCDKeypad lcd;
AccelStepper stepper(AccelStepper::DRIVER, 22, 24, 0xFF, 0xFF, false); //false so pins are not enabled
//AccelStepper stepper(AccelStepper::HALF4WIRE, 8, 11, 9, 10, 8);

const int SUPERCYCLE_WAIT_TIME = 5000; //wait time between each group of 10 cycles

////////////////////////////////////////////////////////////////////////////////
// MAIN
////////////////////////////////////////////////////////////////////////////////

void setup() {
  stepper.setEnablePin(26); //enable pin is pin 26

  stepper.setMaxSpeed(4000);  // max supported is about 4000
  stepper.setAcceleration(10000);
  //Test Setup Config:
  //stepper.setMaxSpeed(1000);
  //stepper.setAcceleration(1000);
  //stepper.runToNewPosition(6400);

  lcd.begin(16, 2);
  // initialize the extra up/down/left//right/select icons:
  LCDKeypadExtraCharsInit(lcd);

  // Start getting user input
  lcd.clear();
  lcd.print("Pick menu option");
  delay(1000);

  int main_menu_choice = showMenu(Main_Menu_Names, MAIN_MENU_ENUM_LAST_ITEM);

  lcd.clear();
  lcd.print("Are you sure?");
  delay(1000);
  int confirm_menu_choice = showMenu(Confirm_Menu_Names, CONFIRM_MENU_ENUM_LAST_ITEM);

  if (confirm_menu_choice == mode_confirm) {
    stepper.enableOutputs();

    switch (main_menu_choice) {
      case mode_rotate_and_zero:
        rotateAndZero();
        break;
      case mode_1_cycle:
        doStepper(1);
        break;
      case mode_10_cycles:
        doStepper(10);
        break;
      case mode_100_cycles:
        doStepper(100);
        break;
      case mode_100_cycles_slow:
        lcd.clear();
        lcd.print("Slow demo mode");
        //for safe demo purposes
        delay(1000);
        stepper.setMaxSpeed(1000);  // max supported is about 4000
        stepper.setAcceleration(1000);
        doStepper(100);
        break;
      case mode_about:
        showAboutScreen();
        break;
    }
  }

  // END OF PROGRAM
  lcd.clear();
  lcd.print("Done.");
  delay(2000);
  lcd.clear();
  lcd.print("Hit RESET to do");
  lcd.setCursor(0, 1);
  lcd.print("something else.");
}

void loop() {
}

////////////////////////////////////////////////////////////////////////////////
// FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

// LCD KEYPAD LOWER LEVEL

int waitButton() {
  int which_button;
  waitReleaseButton();
  lcd.blink();
  while ((which_button = lcd.button()) == KEYPAD_NONE) {
  }
  delay(50);
  lcd.noBlink();
  return which_button;
}

void waitReleaseButton() {
  delay(50);
  while (lcd.button() != KEYPAD_NONE) {
  }
  delay(50);
}

// USER INTERFACE

void showAboutScreen() {
  lcd.print("Knee Wear Tester");
  delay(1000);
  lcd.clear();
  lcd.print("Designed 2015 by");
  lcd.setCursor(0, 1);
  lcd.print(" Chris Blaydon, ");
  delay(1000);
  lcd.clear();
  lcd.print(" Alan Bylund &");
  lcd.setCursor(0, 1);
  lcd.print(" Patrick Miller");
  delay(1000);
}

int showMenu(const char** menu_item_names, int menu_length) {
  // RETURNS INT OF SELECTED MENU ITEM
  // int menu_length = FINAL_MENU_ITEMS_ENTRY;
  int menu_active_item = 0;  // always start at the first item
  bool has_chosen = 0;

  while (!has_chosen) {
    lcd.clear();
    lcd.print(menu_active_item + 1);
    lcd.print(".");
    lcd.print(menu_item_names[menu_active_item]);
    lcd.setCursor(0, 1);
    lcd.write(lcd_char_select);
    lcd.print(":Ok/Select");
    lcd.setCursor(15, 1);
    lcd.write(lcd_char_updown);

    // TODO: Consider adding extra debouncing to button presses

    // Waits for a button to be pressed then interprets the result.

    switch (waitButton()) {
      case KEYPAD_UP:
        // wrap around if minimum
        menu_active_item--;
        if (menu_active_item == -1)
          menu_active_item = menu_length - 1;
        break;
      case KEYPAD_DOWN:
        // wrap around if maximum
        menu_active_item++;
        if (menu_active_item == menu_length)
          menu_active_item = 0;
        break;
      case KEYPAD_SELECT:
        // TODO: have user confirm by pressing again or to cancel and terminate
        // everything
        has_chosen = true;  // ends loop
        break;
    }
    waitReleaseButton();
  }
  return menu_active_item;
}

// STEPPER AND MAIN MOVEMENT CODES

void doStepperOneCycle() {
  // Moves back and forth once, then returns.
  stepper.runToNewPosition(-267); //8 microstep mode, 1.8 degs/step, so 267 steps = 60 degrees
  stepper.runToNewPosition(0);
}

void doStepper(int repetitions) {
  int starting_time = millis();
  // Does as many stepper cycles as requested
  for (int i = 1; i < (repetitions + 1); i++) {
    lcd.clear();
    lcd.print("time=");
    lcd.print(millis() - starting_time);
    lcd.print("ms");
    lcd.setCursor(0, 1);
    lcd.print("Doing Cycle#");
    lcd.print(i);
    doStepperOneCycle();

    if ( (i % 10) == 0 ) {
      lcd.clear();
      lcd.print("Wait for Instron");
      lcd.setCursor(0, 1);
      lcd.print("for ");
      lcd.print(SUPERCYCLE_WAIT_TIME);
      lcd.print(" ms");
      delay(SUPERCYCLE_WAIT_TIME);
    }
  }
}

void rotateAndZero() {
  lcd.clear();

  // Allows user to move motor forwards and backwards to set starting position.
  bool is_done = 0;
  int last_millis = 0;

  while (!is_done) {
    if ((millis() - last_millis) > 1000) {
      last_millis = millis();
      lcd.clear();
      lcd.print("steps=");
      lcd.print(stepper.currentPosition());
      lcd.print(",");
      lcd.print(stepper.targetPosition());
      // TODO: Replace with showing current adjustment amount like "angledelta=[...]
      // degs"
      lcd.setCursor(0, 1);
      lcd.write(lcd_char_select);
      lcd.print(":Ok  ");
      lcd.write(lcd_char_updown);
      lcd.print(":adj 1.8");
      lcd.write(lcd_char_degrees);
    }


    // Waits for a button to be pressed then interprets the result

    // int which_button;
    // waitReleaseButton();
    // // lcd.blink();
    // while ((which_button = lcd.button()) == KEYPAD_NONE) {
    //   stepper.run();
    // }
    // delay(50);
    // lcd.noBlink();

    switch (lcd.button()) {
      case KEYPAD_UP:
        stepper.moveTo(stepper.targetPosition()+8);
        waitReleaseButton();
        //delay(50);
        //stepper.runToPosition();
        break;
      case KEYPAD_DOWN:
        stepper.moveTo(stepper.targetPosition()-8);
        waitReleaseButton();
        //delay(50);
        //stepper.runToPosition();
        break;
      case KEYPAD_SELECT:
        // TODO: have user confirm by pressing again or to cancel and terminate
        // everything
        is_done = true;  // ends loop
        break;
    }

    stepper.run();
    //waitReleaseButton();
  }
}
