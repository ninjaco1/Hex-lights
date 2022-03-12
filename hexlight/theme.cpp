#include "theme.hpp"

Theme::Theme(){
    FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds,NUM_LEDS);
    FastLED.setBrightness(50);
}

// **************************************
//             rgbCheck
// Show solid Red, Green, Blue
// **************************************
void Theme::rgbCheck(){
    // show red
    fill_solid(leds, NUM_LEDS, CRGB::Red);
    FastLED.show();
    delay(500);

    // show green
    fill_solid(leds, NUM_LEDS, CRGB::Green);
    FastLED.show();
    delay(500);


    // show blue
    fill_solid(leds, NUM_LEDS, CRGB::Blue);
    FastLED.show();
    delay(500);

    return;
}

//******************************************
//          gradientMagentaToYellow
// show gradient of Magenta to Yellow
//******************************************
void Theme::gradientMagentaToYellow(){

    fill_gradient_RGB(leds, NUM_LEDS, CRGB::Magenta, CRGB::Yellow);
    FastLED.show();
    delay(500);

    return;
}

// *******************************************
//          gradientRedYellowGreenBlue
// show gradient red -> yellow -> green -> blue
// *******************************************
void Theme::gradientRedYellowGreenBlue(){

    fill_gradient_RGB(leds, NUM_LEDS, CRGB::Magenta, CRGB::Yellow);
    FastLED.show();
    delay(500);
 
    return;
}