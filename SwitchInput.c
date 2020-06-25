#include "SwitchInput.h"

bool _isInit = false;

void MainInputLoop()
{
    //this will be run a single time, initialize whatever is needed here
    if (_isInit == false)
    {
        _isInit = true;

        Sleep(2000);
    }

    PressButton(SWITCH_A, 1000);
}

void HoldButton(uint16_t button, int duration, int delay)
{
    unsigned long start = millis();

    ButtonDown(button);

    while ((millis() - start) < duration)
    {
        HandleUSB();
    }

    ButtonUp(button);

    if (delay > 0)
    {
        Sleep(delay);
    }
}

void PressButton(uint16_t button, int delay)
{
    HoldButton(button, 100, delay);
}

void ButtonDown(int button)
{
    ReportData.Button |= button;
}

void ButtonUp(int button)
{
    ReportData.Button &= ~button;
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
        HandleUSB();
    }
}