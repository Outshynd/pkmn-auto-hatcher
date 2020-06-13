#ifndef _EGG_HATCH_H_
#define _EGG_HATCH_H_

#include "Joystick.h"

#include "Descriptors.h"

#define CENTER_STICKS_AND_UPDATE_USB() ReportData.LX = STICK_CENTER;ReportData.LY = STICK_CENTER;ReportData.RX = STICK_CENTER;ReportData.RY = STICK_CENTER;HandleUSB();
#define bit_set(target, bit) target |= (1 << bit)
#define bit_unset(target, bit) target &= ~(1 << bit)

void MainInputLoop(void);
void HoldButton(uint16_t button, int duration, int delay);
void PressButton(uint16_t button, int delay);
void ButtonDown(int button);
void ButtonUp(int button);
void Sleep(int delay);

#endif