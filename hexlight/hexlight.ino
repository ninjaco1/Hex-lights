#include "theme.hpp"



// number of leds total (14 is the number for 1 hex)
// #define NUM_LEDS 14
// change this value later
// #define LED_PIN 5 // the data pin for the led

volatile unsigned long last_button_time = 0;
volatile unsigned long currentTime;
Theme theme; // create object themes

// functions

//******************************************************************************
//                            chk_buttons
// Checks the state of the button number passed to it. It shifts in ones till
// the button is pushed. Function returns a 1 only once per debounced button
// push so a debounce and toggle function can be implemented at the same time.
// Adapted to check all buttons from Ganssel's "Guide to Debouncing"
// Expects active low pushbuttons on PINA port.  Debounce time is determined by
// external loop delay times 12. Looks for rising edge on button so held actions
// have no unexpected effect.
//******************************************************************************
uint8_t chk_buttons(uint8_t pin)
{
    static uint16_t state = 0;                          // holds state of debounce reading
    state = (state << 1) | (digitalRead(pin)) | 0xE000; // mask on PINA button
    if (state == 0xEFFF)                                // compares to rising edge value (so holding doesn't stack)
        return 1;

    // if not true for 12 times, return false
    return 0;
}

void setup()
{
    // pinMode for buttons
    pinMode(2, INPUT); // button 1
    pinMode(3, INPUT); // button
    attachInterrupt(digitalPinToInterrupt(2), ISR1, RISING);
    attachInterrupt(digitalPinToInterrupt(3), ISR2, RISING);
}

void loop()
{
    theme.showTheme();
}

// increase the current theme
void ISR1()
{
    currentTime = millis();
    if (currentTime - last_button_time > 100)
    {
        // theme.current_theme++;
        theme.changeTheme();
        last_button_time = millis();
    }
}

// decrease the current theme
// void ISR2()
// {
//     currentTime = millis();
//     if (currentTime - last_button_time > 100)
//     {
//         theme.current_theme--; 
//         last_button_time = millis();
//     }
// }

