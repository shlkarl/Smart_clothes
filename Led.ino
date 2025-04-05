#include "LED.h"

LED::LED(){
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
}

void LED::light(int c){

if(c == 0){
    for(int i=0; i<50; i++) { // For each pixel in strip...
    strip.setPixelColor(i, strip.Color(255,   0,   0));         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(50);
  }
}

if(c == 1){
    for(int i=0; i<50; i++) { // For each pixel in strip...
    strip.setPixelColor(i, strip.Color(0,   255,   0));         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(50);
  }
}

if(c == 2){
    for(int i=0; i<50; i++) { // For each pixel in strip...
    strip.setPixelColor(i, strip.Color(0,   0,   255));         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(50);
  }
}
if(c == 3){
        for(int i=0; i<50; i++) { // For each pixel in strip...
    strip.setPixelColor(i, strip.Color(0,   0,   0));         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(50);                           //  Pause for a moment
  }
}
}
  

