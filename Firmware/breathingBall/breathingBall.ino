#include <Adafruit_NeoPixel.h>

#define PIN 4

// Factors to try and set the colour of the light just right, always less than or equal to 1
#define REDCAL 1
#define BLUECAL 1
#define GREENCAL 1

// Initial settings for the breathing program
#define StartBrightness 50    
#define EndBrightness 256
#define StepSize 2
#define StepDelay 10

Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();  // Initialize the pixel
  strip.show();   // Initialize all pixels to 'off'
  // Breathing look that gradually gets brighter, we only do this once then maintain max brightness
  for(int i = StartBrightness; i < EndBrightness ; i=i+StepSize){
    breath(i, StepDelay);
  }
}

void loop() {
  breath(EndBrightness-1, StepDelay);    // Stay at max brightness
}

//Creates the breathing look that apple computers have with the set colour
// Need to figure out a more generic algorithm that can fade any colour
// Perhaps even cycling the fading amoung many colours
void breath(uint8_t maxBrightness, uint8_t rate)
{
  uint16_t j;
  for(j=0; j<256; j++) {
    strip.setPixelColor(0, strip.Color(int((float(256-j)/256)*maxBrightness*REDCAL),int((float(256-j)/256)*maxBrightness*GREENCAL),int((float(256-j)/256)*maxBrightness*BLUECAL)));
//    strip.setPixelColor(0, strip.Color(255-j,0,0));  //red
//    strip.setPixelColor(0, strip.Color(0,255-j,0));  //green
//    strip.setPixelColor(0, strip.Color(0,0,255-j));  //blue
    strip.show();
    delay(rate);
  }
  for(j=0; j<256; j++) {
    strip.setPixelColor(0, strip.Color(int((float(j)/256)*maxBrightness*REDCAL),int((float(j)/256)*maxBrightness*GREENCAL),int((float(j)/256)*maxBrightness*BLUECAL)));  
//    strip.setPixelColor(0, strip.Color(j,0,0));  //red
//    strip.setPixelColor(0, strip.Color(0,j,0));  //red
//    strip.setPixelColor(0, strip.Color(0,0,j));  //red
    strip.show();
    delay(rate);
  }
}
