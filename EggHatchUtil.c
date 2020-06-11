#include "EggHatchUtil.h"

unsigned long prevMillis = 0;
bool buttonPressed = false;

void Test()
{
    // if ((millis() - prevMillis) > 1000)
    // {
    //     prevMillis = millis();
    //     buttonPressed = !buttonPressed;
    // }

    // if (buttonPressed)
    //     ReportData.Button |= SWITCH_A;

    // HandleUSB();
    PressButton(SWITCH_A, 1000, 1000);
}

void PressButton(uint16_t button, int duration, int delay)
{
    unsigned long start = millis();

    while ((millis() - start) < duration)
    {
        ReportData.Button |= button;
        // ReportData.LX = STICK_CENTER;
        // ReportData.LY = STICK_CENTER;
        // ReportData.RX = STICK_CENTER;
        // ReportData.RY = STICK_CENTER;
        // HandleUSB();
        CENTER_STICKS_AND_UPDATE_USB();
    }

    if (delay > 0)
    {
        Sleep(delay);
        // start = millis();

        // while ((millis() - start) < delay)
        // {
        //     ReportData.LX = STICK_CENTER;
        //     ReportData.LY = STICK_CENTER;
        //     ReportData.RX = STICK_CENTER;
        //     ReportData.RY = STICK_CENTER;
        //     HandleUSB();
        // }
    }
}

void Sleep(int delay)
{
    unsigned long start = millis();

    while ((millis() - start) < delay)
    {
        // ReportData.LX = STICK_CENTER;
        // ReportData.LY = STICK_CENTER;
        // ReportData.RX = STICK_CENTER;
        // ReportData.RY = STICK_CENTER;
        // HandleUSB();
        CENTER_STICKS_AND_UPDATE_USB();
    }
}