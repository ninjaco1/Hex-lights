// #include "theme.hpp"
#include <FastLED.h>



// number of leds total (14 is the number for 1 hex)
// #define NUM_LEDS 35
#define NUM_LEDS 98
#define NUM_THEMES 11
#define NUM_HEX 7
#define NUM_LEDS_HEX 14
// change this value later
#define LED_PIN 5 // the data pin for the led

CRGB leds[NUM_LEDS];
uint8_t colorIndex[NUM_LEDS];

uint8_t current_theme;
uint8_t hue;
uint8_t whichPalette = 0; 
uint8_t hexValue[7] = {0,0,0,0,0,0,0}; // the brightness of the hex


volatile unsigned long last_button_time = 0;
volatile unsigned long currentTime;

// palettes
// creating color palettes
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

CRGBPalette16 purpleGreentoLightBlue = purplegreenlightblue;
CRGBPalette16 GMT_sealand = GMT_sealand_gp;
CRGBPalette16 spellbound = spellbound_gp;
CRGBPalette16 bhw2_grrrrr = bhw2_grrrrr_gp;

// functions
uint8_t chk_buttons(uint8_t pin);
void changeTheme();
void showTheme();

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

// creating my own themes
void constantFades(); // having the hex always fading

void setup()
{
    // pinMode for buttons
    pinMode(2, INPUT); // button 1
    pinMode(3, INPUT); // button
    attachInterrupt(digitalPinToInterrupt(2), ISR1, RISING);
    // attachInterrupt(digitalPinToInterrupt(3), ISR2, RISING);

    hue = 0;
    current_theme = 0;

    for (int i = 0; i < 7; i++)
        hexValue[i] = random8();    


    FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds,NUM_LEDS);
    FastLED.setBrightness(75);

    for (int i = 0; i < NUM_LEDS; i++){
        colorIndex[i] = random8();
    }

}

void loop()
{

    showTheme();

}


// increase the current theme
void ISR1()
{
    currentTime = millis();
    if (currentTime - last_button_time > 100)
    {
        // insert task here
        changeTheme();
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


// change the theme
void changeTheme(){
    current_theme++;
    current_theme %= NUM_THEMES;
}

// show the theme selected
void showTheme(){

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
void rgbCheck(){
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
void gradientMagentaToYellow(){

    fill_gradient_RGB(leds, NUM_LEDS, CRGB::Magenta, CRGB::Yellow);
    FastLED.show();
    delay(500);

    return;
}

// *******************************************
//          gradientRedYellowGreenBlue
// show gradient red -> yellow -> green -> blue
// *******************************************
void gradientRedYellowGreenBlue(){

    fill_gradient_RGB(leds, NUM_LEDS, CRGB::Magenta, CRGB::Yellow);
    FastLED.show();
    delay(500);
 
    return;
}


//*********************************
//          showRainbow
// show rainbow down the line
// ********************************
void showRainbow(){
    fill_rainbow(leds, NUM_LEDS, 0, 255 / NUM_LEDS);
    FastLED.show();
    return;
}

//*************************************
//          setOneColor();
// **************************************
void setOneColor(){
    for (int i = 0; i < NUM_LEDS; i++)
        leds[i] = CRGB(120,255,15);
    FastLED.show();
    return;
}

//*****************************************
//       changing the hue only
//*****************************************
void changeOnlyHue(){
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
void travelingRainbow(){

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
void coldBluePattern(){
    // create a new pixel for led[0]
    EVERY_N_MILLISECONDS(75){
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

void showRandomPurpleBlue(){
    uint8_t paletteIndex = 0;
    for (int i = 0; i < NUM_LEDS; i++){
        leds[i] = ColorFromPalette(purpleGreentoLightBlue, random8());
    }

    fill_palette(leds, NUM_LEDS, paletteIndex, 255 / NUM_LEDS, purpleGreentoLightBlue, 255, LINEARBLEND);
    FastLED.show();
}

// the leds fading slowly 
void gradientFading(){

    EVERY_N_MILLISECONDS(50){
        // switch on an LED at random, choosing a random color from the palette
        leds[random8(0, NUM_LEDS - 1)] = ColorFromPalette(purpleGreentoLightBlue, random8(), 255, LINEARBLEND);
    }

    // Fade all LEDs down by 1 in brightness each time this is called
    FastLED.show();
}


// random index will fade into different colors within the gradient
void travelingGradient1(){
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


void fadeGradientTogether(){
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
            targetPalette = spellbound_gp;
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


// constantly changing the hex
void constantFades(){

    // keeping track of hex 
    for (int i = 0; i < NUM_HEX; i++){


        for (int j = 0; j < NUM_LEDS_HEX; j++){

            leds[i*j] = CHSV(100, 60, hexValue);
        }
    }

    EVERY_N_MILLISECONDS(50){
        for (int i = 0; i < NUM_HEX; i++){
            hexValue[i]--; // decrease the brightness of the color
        }
    }

    FastLED.show();


}