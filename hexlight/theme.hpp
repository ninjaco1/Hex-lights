#include <FastLED.h>

#define NUM_LEDS 14
#define LED_PIN 2

// creating color palettes
DEFINE_GRADIENT_PALETTE (heatmap_gp){
      0,   0,   0,   0, // black
    128, 255,   0,   0, // red
    200, 255, 255,   0, // bright yellow
    255, 255, 255, 255  // full white
};

DEFINE_GRADIENT_PALETTE (purplegreenlightblue) {
    0x00, 0xd9, 0x1e, 0xd7, // magenta
    125, 0x12, 0xab, 0x85,  // weird green
    255, 0x00, 0xd4, 0xff   //light blue
};

class Theme{
    private:
    //    uint16_t NUM_LEDS; 
       CRGB leds[NUM_LEDS];
       uint8_t current_theme;
       uint8_t num_themes;
       uint8_t hue;
       CRGBPalette16 purpleGreentoLightBlue = purplegreenlightblue;






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

        // color palettes
        void showRandomPurpleBlue(); // assign a different color to each hex


};