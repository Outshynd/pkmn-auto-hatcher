#ifndef _EGG_HATCH_H_
#define _EGG_HATCH_H_

#include "main.h"

#include "Descriptors.h"

#define CENTER_STICKS_AND_UPDATE_USB() ReportData.LX = STICK_CENTER;ReportData.LY = STICK_CENTER;ReportData.RX = STICK_CENTER;ReportData.RY = STICK_CENTER;HandleUSB();

void Test(void);

#endif