#include <FastLED.h>

#define NUM_LEDS 14
#define LED_PIN 2

class Theme{
    private:
    //    uint16_t NUM_LEDS; 
       CRGB leds[NUM_LEDS];
       uint8_t current_theme;
       uint8_t num_themes;
       uint8_t hue;
    public:
        Theme();
        // change themes
        void changeTheme();

        // functions that have themes
        void rgbCheck(); // cycles through solid rbg
        void gradientMagentaToYellow();
        void gradientRedYellowGreenBlue();
        void showRainbow();

        // playing around with RGB and HSV
        void setOneColor();
        void changeOnlyHue();
        void travelingRainbow();
        void coldBluePattern();


};