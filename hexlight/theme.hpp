#include <FastLED.h>

#define NUM_LEDS 14
#define LED_PIN 2

// creating color palettes
DEFINE_GRADIENT_PALETTE(heatmap_gp){
    0, 0, 0, 0,        // black
    128, 255, 0, 0,    // red
    200, 255, 255, 0,  // bright yellow
    255, 255, 255, 255 // full white
};

DEFINE_GRADIENT_PALETTE(purplegreenlightblue){
    0x00, 0xd9, 0x1e, 0xd7, // magenta
    125, 0x12, 0xab, 0x85,  // weird green
    255, 0x00, 0xd4, 0xff   // light blue
};

// Gradient palette "GMT_sealand_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/gmt/tn/GMT_sealand.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 80 bytes of program space.

DEFINE_GRADIENT_PALETTE(GMT_sealand_gp){
    0, 53, 33, 255,
    14, 23, 33, 255,
    28, 23, 68, 255,
    42, 23, 115, 255,
    56, 23, 178, 255,
    70, 23, 255, 255,
    84, 23, 255, 170,
    99, 23, 255, 103,
    113, 23, 255, 56,
    127, 23, 255, 25,
    141, 53, 255, 25,
    155, 100, 255, 25,
    170, 167, 255, 25,
    170, 255, 255, 87,
    184, 255, 193, 87,
    198, 255, 141, 87,
    212, 255, 99, 87,
    226, 255, 115, 135,
    240, 255, 135, 182,
    255, 255, 156, 223
};

// Gradient palette "spellbound_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/rc/tn/spellbound.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 84 bytes of program space.

DEFINE_GRADIENT_PALETTE(spellbound_gp){
    0, 232, 235, 40,
    12, 157, 248, 46,
    25, 100, 246, 51,
    45, 53, 250, 33,
    63, 18, 237, 53,
    81, 11, 211, 162,
    94, 18, 147, 214,
    101, 43, 124, 237,
    112, 49, 75, 247,
    127, 49, 75, 247,
    140, 92, 107, 247,
    150, 120, 127, 250,
    163, 130, 138, 252,
    173, 144, 131, 252,
    186, 148, 112, 252,
    196, 144, 37, 176,
    211, 113, 18, 87,
    221, 163, 33, 53,
    234, 255, 101, 78,
    247, 229, 235, 46,
    255, 229, 235, 46
};

// Gradient palette "bhw2_grrrrr_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw2/tn/bhw2_grrrrr.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 32 bytes of program space.

DEFINE_GRADIENT_PALETTE(bhw2_grrrrr_gp){
    0, 184, 15, 155,
    35, 78, 46, 168,
    84, 65, 169, 230,
    130, 9, 127, 186,
    163, 77, 182, 109,
    191, 242, 246, 55,
    216, 142, 128, 103,
    255, 72, 50, 168
};

class Theme
{
private:
    CRGB leds[NUM_LEDS];
    uint8_t colorIndex[NUM_LEDS];

    uint8_t current_theme;
    uint8_t num_themes;
    uint8_t hue;
    uint8_t whichPalette = 0; // 


    // gradient palettes
    CRGBPalette16 purpleGreentoLightBlue = purplegreenlightblue;
    CRGBPalette16 GMT_sealand = GMT_sealand_gp;
    CRGBPalette16 spellbound = spellbound_gp;
    CRGBPalette16 bhw2_grrrrr = bhw2_grrrrr_gp;

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
    void gradientFading();       // all LEDs fading
    void travelingGradient1();
    void fadeGradientTogether(); // change the gradient color
};