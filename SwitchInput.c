#include "SwitchInput.h"

bool _isInit = false;

void MainInputLoop()
{
    //this will be run a single time, initialize whatever is needed here
    if (_isInit == false)
    {
        _isInit = true;

        // Sleep(1000);
        // ButtonDown(SWITCH_R);
        // ButtonDown(SWITCH_L);
        // Sleep(100);
        // ButtonUp(SWITCH_R);
        // ButtonUp(SWITCH_L);
        // Sleep(500);
        // ButtonDown(SWITCH_R);
        // ButtonDown(SWITCH_L);
        // Sleep(100);
        // ButtonUp(SWITCH_R);
        // ButtonUp(SWITCH_L);
        Sleep(2000);
    }

//     int16_t data = serial_popshort();

//     if (data >= 0)
//     {
// #ifdef DEBUG
//         printf("Command: %c - Arg: %c\n", (char)(data >> 8), (char)(data));
// #endif

//         char command = (char)(data >> 8);
//         char arg = (char)data;

//         //react to command and arg
//         switch (command)
//         {
//         case 1:
//             ButtonDown(1 << (arg - 1));
//             break;
//         case 2:
//             ButtonUp(1 << (arg - 1));
//             break;
//         default:
//             break;
//         }
//     }

    PressButton(SWITCH_A, 1000);
    //printf("Pressing A");
    //make sure we're handling USB
    //HandleUSB();
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