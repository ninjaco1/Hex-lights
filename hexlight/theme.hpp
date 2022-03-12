#include <FastLED.h>

#define NUM_LEDS 14
#define LED_PIN 2

class Theme{
    private:
    //    uint16_t NUM_LEDS; 
       CRGB leds[NUM_LEDS];
    public:
        Theme();
        // functions that have themes
        void rgbCheck(); // cycles through solid rbg
        void gradientMagentaToYellow();
        void gradientRedYellowGreenBlue();
}