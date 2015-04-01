#include <LiquidCrystal.h>
#include "./LCDKeypad.h"
#include "./AccelStepper.h"

////////////////////////////////////////////////////////////////////////////////
// VARIABLE INITIALIZATIONS AND CONSTANTS
////////////////////////////////////////////////////////////////////////////////

enum Main_Menu
{
  mode_rotate_and_zero,
  mode_1_cycle,
  mode_10_cycles,
  mode_100_cycles,
  mode_about,
  MAIN_MENU_ENUM_LAST_ITEM
};

const char* Main_Menu_Names[] =
{
  "Rotate/re-zero",
  "1 cycle",
  "10 cycles",
  "100 cycles",
  "About"
};

LCDKeypad lcd;
AccelStepper stepper(AccelStepper::DRIVER, 22, 24);

enum LCD_Chars
{
    lcd_char_select = 1, //causes lcd_char_left == 2, and so on...
    lcd_char_left,
    lcd_char_right,
    lcd_char_up, 
    lcd_char_down,
    lcd_char_updown,
};

byte c_select[8] =
{
  0b00000,
  0b11111,
  0b10001,
  0b10001,
  0b10001,
  0b11111,
  0b00000,
  0b00000
};

byte c_left[8] =
{
  0b00000,
  0b00010,
  0b00110,
  0b01110,
  0b00110,
  0b00010,
  0b00000,
  0b00000
};

byte c_right[8] =
{
  0b00000,
  0b01000,
  0b01100,
  0b01110,
  0b01100,
  0b01000,
  0b00000,
  0b00000
};

byte c_up[8] =
{
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00100,
  0b01110,
  0b11111,
  0b00000
};

byte c_down[8] =
{
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b11111,
  0b01110,
  0b00100,
  0b00000,
};

byte c_updown[8] =
{
  0b00100,
  0b01110,
  0b11111,
  0b00000,
  0b11111,
  0b01110,
  0b00100,
  0b00000
};



////////////////////////////////////////////////////////////////////////////////
// MAIN
////////////////////////////////////////////////////////////////////////////////

void setup()
{
  stepper.setMaxSpeed(4000); //max supported is about 4000
  stepper.setAcceleration(10000);

  lcd.begin(16, 2);
  lcd.createChar(lcd_char_select, c_select);
  lcd.createChar(lcd_char_left, c_left);
  lcd.createChar(lcd_char_right, c_right);
  lcd.createChar(lcd_char_up, c_up);
  lcd.createChar(lcd_char_down, c_down);
  lcd.createChar(lcd_char_updown, c_updown);

//  lcd.createChar(1, c_select);
//  lcd.createChar(2, c_up);
//  lcd.createChar(3, c_down);
//  lcd.createChar(4, c_updown);
//  lcd.createChar(5, c_left);
//  lcd.createChar(6, c_right);


  //Start getting user input
  lcd.clear();
  lcd.print("Pick menu option");
  delay(1000);

  int main_menu_choice = showMenu(Main_Menu_Names, MAIN_MENU_ENUM_LAST_ITEM);

  switch (main_menu_choice)
  {
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
    case mode_about:
      showAboutScreen();
      break;
  }

  //END OF PROGRAM
  lcd.clear();
  lcd.print("Done.");
  delay(2000);
  lcd.clear();
  lcd.print("Hit RESET to do");
  lcd.setCursor(0, 1);
  lcd.print("something else.");
}

void loop()
{


}

////////////////////////////////////////////////////////////////////////////////
// FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

// LCD KEYPAD LOWER LEVEL

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

// USER INTERFACE

void showAboutScreen()
{
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

int showMenu(const char** menu_item_names, int menu_length)
{
  //RETURNS INT OF SELECTED MENU ITEM
  //int menu_length = FINAL_MENU_ITEMS_ENTRY;
  int which_button = 0;
  int menu_active_item = 0; //always start at the first item
  bool has_chosen = 0;

  while (!has_chosen) {
    lcd.clear();
    lcd.print(menu_active_item + 1);
    lcd.print(".");
    lcd.print(menu_item_names[menu_active_item]);
    lcd.setCursor(0, 1);
    lcd.write(lcd_char_select);
    lcd.print(":SELECT");
    lcd.setCursor(15,1);
    lcd.write(lcd_char_updown);

    //TODO: Consider adding extra debouncing to button presses

    switch (waitButton()) //Waits for a button to be pressed then interprets the result.
    {
      case KEYPAD_UP:
        menu_active_item--;
        if (menu_active_item == -1) menu_active_item = menu_length - 1; //loop back if minimum
        break;
      case KEYPAD_DOWN:
        menu_active_item++;
        if (menu_active_item == menu_length) menu_active_item = 0; //wrap around if maximum
        break;
      case KEYPAD_SELECT:
        has_chosen = true; //ends loop
        break;
    }
    waitReleaseButton();
  }
  return menu_active_item;
}

// STEPPER AND MAIN MOVEMENT CODES

void doStepperOneCycle()
{
  //Moves back and forth once, then returns.
  stepper.runToNewPosition(1600);
  stepper.runToNewPosition(0);
}

void doStepper(int repetitions)
{
  int starting_time = millis();
  //Does as many stepper cycles as requested
  for (int i = 1; i < (repetitions + 1); i++)
  {
    lcd.clear();
    lcd.print("time=");
    lcd.print(millis() - starting_time);
    lcd.print("ms");
    lcd.setCursor(0, 1);
    lcd.print("Cycle #");
    lcd.print(i);
    doStepperOneCycle();
  }
}

void rotateAndZero()
{
  lcd.clear();
  lcd.print("Adjust motor pos.");
  lcd.setCursor(0, 1);
  lcd.write(1);
  lcd.print(" Ok ");
  lcd.write(2); // ^
  lcd.write(3); // V
  lcd.print(" 1.8 deg");
  waitButton();
  waitReleaseButton();
  //Allows user to move motor forwards and backwards to set starting position.
}
