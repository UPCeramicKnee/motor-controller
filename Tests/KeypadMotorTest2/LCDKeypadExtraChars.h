#ifndef _LCD_KEYPAD_EXTRA_CHARS_H
#define _LCD_KEYPAD_EXTRA_CHARS_H

#include "Arduino.h"
#include <LiquidCrystal.h>
#include "./LCDKeypad.h"

enum LCD_Chars
{
  lcd_char_select = 1, //causes lcd_char_left == 2, and so on...
  lcd_char_left,
  lcd_char_right,
  lcd_char_up,
  lcd_char_down,
  lcd_char_updown,
  lcd_char_degrees
};

void LCDKeypadExtraCharsInit(LCDKeypad&);

#endif
