#include "theme.hpp"

Theme::Theme(){
    hue = 0;
    current_theme = 0;
    num_themes = 10; // the number of themes there are


    FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds,NUM_LEDS);
    FastLED.setBrightness(50);

    for (int i = 0; i < NUM_LEDS; i++){
        colorIndex[i] = random8();
    }


}

// change the theme
void Theme::changeTheme(){
    current_theme++;
    current_theme %= num_themes;
}

// show the theme selected
void Theme::showTheme(){

    switch(current_theme){
        case 0:
            rgbCheck();
            break;
        case 1:
            gradientMagentaToYellow();
            break;
        case 2:
            gradientRedYellowGreenBlue();
            break;
        case 3: 
            showRainbow();
            break;
        case 4:
            setOneColor();
            break;
        case 5:
            changeOnlyHue();
            break;
        case 6:
            travelingRainbow();
            break;
        case 7:
            coldBluePattern();
            break;
        case 8:
            showRandomPurpleBlue();
            break;
        case 9:
            gradientFading();
            break;
        case 10:
            travelingGradient1();
            break;
        case 11:
            fadeGradientTogether();
            break;

    }


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


//*********************************
//          showRainbow
// show rainbow down the line
// ********************************
void Theme::showRainbow(){
    fill_rainbow(leds, NUM_LEDS, 0, 255 / NUM_LEDS);
    FastLED.show();
    return;
}

//*************************************
//          setOneColor();
// **************************************
void Theme::setOneColor(){
    for (int i = 0; i < NUM_LEDS; i++)
        leds[i] = CRGB(120,255,15);
    FastLED.show();
    return;
}

//*****************************************
//       changing the hue only
//*****************************************
void Theme::changeOnlyHue(){
    for (int i = 0; i < NUM_LEDS; i++){
        leds[i] = CHSV(hue, 255,255);
    }

    EVERY_N_MILLISECONDS(15){
        hue++;
    }
    FastLED.show();

    return;
}

// a rainbow traveling down the strip
void Theme::travelingRainbow(){

    for (int i = 0; i < NUM_LEDS; i++){
        leds[i] = CHSV(hue + (i+10), 255, 255);
    }

    EVERY_N_MILLISECONDS(15){
        hue++;
    }

    FastLED.show();

    return;
}

// cold blue pattern
void Theme::coldBluePattern(){
    // create a new pixel for led[0]
    EVERY_N_MILLISECONDS(50){
        leds[0] = CHSV(160, random8(), random8(100,255));
        
        // copy each pixel to the next one, starting at the far end 
        // thereby 'moving' the pattern along the strip
        for (int i = NUM_LEDS -1; i > 0; i--){
            leds[i] = leds[i-1];
        }

        FastLED.show();
    }
    return;

}

void Theme::showRandomPurpleBlue(){
    uint8_t paletteIndex = 0;
    for (int i = 0; i < NUM_LEDS; i++){
        led[i] = ColorFromPalette(purpleGreentoLightBlue, random8());
    }

    fill_palette(leds, NUM_LEDS, paletteIndex, 255 / NUM_LEDS, purpleGreentoLightBlue, 255, LINEARBLEND);
    FastLED.show();
}

// the leds fading slowly 
void Theme::gradientFading(){

    EVERY_N_MILLISECONDS(50){
        // switch on an LED at random, choosing a random color from the palette
        leds[random8(0, NUM_LEDS - 1)] = ColorFromPalette(purpleGreentoLightBlue, random8(), 255, LINEARBLEND);
    }

    // Fade all LEDs down by 1 in brightness each time this is called
    FastLED.show();
}


// random index will fade into different colors within the gradient
void Theme::travelingGradient1(){
    // color each pixel from the palette using the undex from colorIndex[]
    for (int i = 0; i < NUM_LEDS; i++){
        leds[i] = ColorFromPalette(spellbound, colorIndex[i]);

    }

    EVERY_N_MILLISECONDS(5){
        for (int i = 0; i < NUM_LEDS; i++){
            colorIndex[i]++;
        }
    }
    FastLED.show();
}

//
void Theme::fadeGradientTogether(){
    CRGBPalette16 currentPalette(GMT_sealand_gp);
    CRGBPalette16 targetPalette(bhw2_grrrrr_gp);

    for (int i = 0; i < NUM_LEDS; i++){
        leds[i] = ColorFromPalette(currentPalette, colorIndex[i]);
    }
    
    // the amount of steps it takes for the palette takes to blend into the next one
    nblendPaletteTowardPalette(currentPalette, targetPalette, 10);

    switch(whichPalette){
        case 0:
            targetPalette = bhw2_grrrrr_gp;
            break;
        case 1:
            targetPalette = purplegreenlightblue;
            break;

       case 2:
            targetPalette = spellbound_gbhw2_grrrrr_gp;
            break;
    }

    EVERY_N_SECONDS(5){
        whichPalette++;

        if (whichPalette > 2) 
            whichPalette = 0;

    }

    EVERY_N_MILLISECONDS(5){
        for (int i = 0; i < NUM_LEDS; i++){
            colorIndex[i]++;
        }
    }

    FastLED.show();


}