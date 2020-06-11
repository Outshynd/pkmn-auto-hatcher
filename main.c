/*
Nintendo Switch Fightstick - Proof-of-Concept

Based on the LUFA library's Low-Level Joystick Demo
    (C) Dean Camera
Based on the HORI's Pokken Tournament Pro Pad design
    (C) HORI

This project implements a modified version of HORI's Pokken Tournament Pro Pad
USB descriptors to allow for the creation of custom controllers for the
Nintendo Switch. This also works to a limited degree on the PS3.

Since System Update v3.0.0, the Nintendo Switch recognizes the Pokken
Tournament Pro Pad as a Pro Controller. Physical design limitations prevent
the Pokken Controller from functioning at the same level as the Pro
Controller. However, by default most of the descriptors are there, with the
exception of Home and Capture. Descriptor modification allows us to unlock
these buttons for our use.
*/

#include "main.h"

#undef F_CPU
#define F_CPU 16000000UL                         // 16 MHz
#define CTC_MATCH_OVERFLOW ((F_CPU / 1000) / 64) //250 @ 16MHz

volatile unsigned long timer0_milliseconds = 0;

void timer0_init()
{
    // Set the Timer Mode to CTC
    TCCR0A |= (1 << WGM01);

    //set the compare value
    OCR0A = CTC_MATCH_OVERFLOW;

    //set the interrupt COMPA vect
    TIMSK0 |= (1 << OCIE0A);

    sei();

    //set prescaler 64 & start
    TCCR0B |= (1 << CS00) | (1 << CS01);
}

//interrupt and increment milliseconds
ISR(TIMER0_COMPA_vect)
{
    timer0_milliseconds++;
}

//rough implementation of arduino millis func
unsigned long millis()
{
    unsigned long ms_ret;

    ATOMIC_BLOCK(ATOMIC_FORCEON)
    {
        ms_ret = timer0_milliseconds;
    }

    return ms_ret;
}

void HandleUSB()
{
    // We need to run our task to process and deliver data for our IN and OUT endpoints.
    HID_Task();
    // We also need to run the main USB management task.
    USB_USBTask();
}

//unsigned long prevMillis = 0;

// Main entry point.
int main(void)
{
    // We'll start by performing hardware and peripheral setup.
    SetupHardware();

    //init our timer
    timer0_init();

    // We'll then enable global interrupts for our use.
    GlobalInterruptEnable();
    // Once that's done, we'll enter an infinite loop.
    // unsigned long i = 0;
    bool buttonPressed = false;

    for (;;)
    {
        //this is where you call the function you want to use
        Test();
    }
}

// Configures hardware and peripherals, such as the USB peripherals.
void SetupHardware(void)
{
    // We need to disable watchdog if enabled by bootloader/fuses.
    MCUSR &= ~(1 << WDRF);
    wdt_disable();
    // We need to disable clock division before initializing the USB hardware.
    clock_prescale_set(clock_div_1);
    // We can then initialize our hardware and peripherals, including the USB stack.
    // The USB stack should be initialized last.
    USB_Init();
}

// Fired to indicate that the device is enumerating.
void EVENT_USB_Device_Connect(void)
{
    // We can indicate that we're enumerating here (via status LEDs, sound, etc.).
}

// Fired to indicate that the device is no longer connected to a host.
void EVENT_USB_Device_Disconnect(void)
{
    // We can indicate that our device is not ready (via status LEDs, sound, etc.).
}

// Fired when the host set the current configuration of the USB device after enumeration.
void EVENT_USB_Device_ConfigurationChanged(void)
{
    bool ConfigSuccess = true;

    // We setup the HID report endpoints.
    ConfigSuccess &= Endpoint_ConfigureEndpoint(JOYSTICK_OUT_EPADDR, EP_TYPE_INTERRUPT, JOYSTICK_EPSIZE, 1);
    ConfigSuccess &= Endpoint_ConfigureEndpoint(JOYSTICK_IN_EPADDR, EP_TYPE_INTERRUPT, JOYSTICK_EPSIZE, 1);

    // We can read ConfigSuccess to indicate a success or failure at this point.
}

// Process control requests sent to the device from the USB host.
void EVENT_USB_Device_ControlRequest(void)
{
    // We can handle two control requests: a GetReport and a SetReport.
    // Not used here, it looks like we don't receive control request from the Switch.
}

// Process and deliver data from IN and OUT endpoints.
void HID_Task(void)
{
    // If the device isn't connected and properly configured, we can't do anything here.
    if (USB_DeviceState != DEVICE_STATE_Configured)
        return;

    // We'll start with the OUT endpoint.
    Endpoint_SelectEndpoint(JOYSTICK_OUT_EPADDR);
    // We'll check to see if we received something on the OUT endpoint.
    if (Endpoint_IsOUTReceived())
    {
        // If we did, and the packet has data, we'll react to it.
        if (Endpoint_IsReadWriteAllowed())
        {
            // We'll create a place to store our data received from the host.
            USB_JoystickReport_Output_t JoystickOutputData;
            // We'll then take in that data, setting it up in our storage.
            Endpoint_Read_Stream_LE(&JoystickOutputData, sizeof(JoystickOutputData), NULL);
            // At this point, we can react to this data.
            // However, since we're not doing anything with this data, we abandon it.
        }
        // Regardless of whether we reacted to the data, we acknowledge an OUT packet on this endpoint.
        Endpoint_ClearOUT();
    }

    // We'll then move on to the IN endpoint.
    Endpoint_SelectEndpoint(JOYSTICK_IN_EPADDR);
    // We first check to see if the host is ready to accept data.
    if (Endpoint_IsINReady())
    {
        // Once populated, we can output this data to the host. We do this by first writing the data to the control stream.
        Endpoint_Write_Stream_LE(&ReportData, sizeof(ReportData), NULL);
        // We then send an IN packet on this endpoint.
        Endpoint_ClearIN();
        /* Clear the report data afterwards */
        memset(&ReportData, 0, sizeof(ReportData));
    }
}