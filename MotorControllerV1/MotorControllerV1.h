#ifndef _MOTOR_CONTROLLER_V1_H
#define _MOTOR_CONTROLLER_V1_H

int waitButton();
void waitReleaseButton();

int showMenu(const char** menu_item_names, int menu_length);
void showAboutScreen();
void doStepper(int repetitions);
void rotateAndZero();

#endif
