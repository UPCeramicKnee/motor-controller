#ifndef _KEYPAD_MOTOR_TEST_H
#define _KEYPAD_MOTOR_TEST_H

int waitButton();
void waitReleaseButton();

int showMenu(const char** menu_item_names, int menu_length);
void showAboutScreen();
void doStepper(int repetitions);
void rotateAndZero();

#endif
