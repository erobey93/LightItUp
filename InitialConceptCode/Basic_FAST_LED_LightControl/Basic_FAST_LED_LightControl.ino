#include <FastLED.h>

#define LED_PIN     7
#define NUM_LEDS    150

CRGB leds[NUM_LEDS];

void setup() {

  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  
}

void loop() {
  int i = 0; 
  int j = 0; 

  for(i=0; i < NUM_LEDS; i++)
  {
    if(j == 0)
    {
      leds[i] = CRGB(255 , 0, 0);
      delay(100);
      FastLED.show();
      j++;
    }
    else if(j == 1)
    {
      leds[i] = CRGB(85, 60, 180);
      delay(100);
      FastLED.show();
      j++;
    }
    else if( j == 2)
    {
      leds[i] = CRGB(0, 0, 255);
      delay(100);
      FastLED.show();
      j = 0; 
    }
    
      
    
  }
  
  /*leds[1] = CRGB(0, 255, 0);
  FastLED.show();
  delay(500);
  leds[2] = CRGB(0, 0, 255);
  FastLED.show();
  delay(500);
  leds[5] = CRGB(150, 0, 255);
  FastLED.show();
  delay(500);
  leds[9] = CRGB(255, 200, 20);
  FastLED.show();
  delay(500);
  leds[14] = CRGB(85, 60, 180);
  FastLED.show();
  delay(500);
  leds[19] = CRGB(50, 255, 20);
  FastLED.show();
  delay(500);*/
}
