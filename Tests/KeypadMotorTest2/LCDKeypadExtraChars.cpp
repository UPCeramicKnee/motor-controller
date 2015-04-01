#include "./LCDKeypadExtraChars.h"

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

byte c_degrees[8] =
{
  0b01100,
  0b10010,
  0b10010,
  0b01100,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

void LCDKeypadExtraCharsInit(LCDKeypad &mylcd)
{
  mylcd.createChar(lcd_char_select, c_select);
  mylcd.createChar(lcd_char_left, c_left);
  mylcd.createChar(lcd_char_right, c_right);
  mylcd.createChar(lcd_char_up, c_up);
  mylcd.createChar(lcd_char_down, c_down);
  mylcd.createChar(lcd_char_updown, c_updown);
  mylcd.createChar(lcd_char_degrees, c_degrees);
}

