#include "Adafruit_FloraPixel.h"
#include <CapacitiveSensor.h>

/*
 * This code is a student project
 * It was modified from CapitiveSense Library Demo Sketch made by by Becky Stern 2013 
 */
 
CapacitiveSensor   cs_9_10 = CapacitiveSensor(9,10);        // pins 9 & 10 are sensor pins
//CapacitiveSensor   cs_9_2 = CapacitiveSensor(9,2);        // add an extrea sensor if it needed

Adafruit_FloraPixel strip = Adafruit_FloraPixel(4);         // set numbers of LED lights
#define LED_NUM 4

void setup()                    
{
cs_9_10.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1
    strip.begin();
    strip.show();

}

void rainbow(uint8_t wait) {
  int i, j, k;
   
  for (j=0; j < 256; j++) {     // 3 cycles of all 256 colors in the wheel
    for (i=0; i < strip.numPixels(); i++) {
      for (k=0; k < LED_NUM; k++)
      strip.setPixelColor(i, Wheel( (i + j) % 255));
    }  
    strip.show();   // write all the pixels out
    delay(wait);
  }
}

void loop()                    
{
  int num = 0;
   long start = millis();
   long total1 =  cs_9_10.capacitiveSensor(30);
    //long total2 =  cs_9_2.capacitiveSensor(30);  // add an extrea sensor if it needed
   int status = 0 ;

if (total1 > 10){                          // set the level of pressure to turn on the lights
  digitalWrite(7, HIGH);
  rainbow(50);
 } else {
  for (num = 0; num < LED_NUM ; num++)
  {
  strip.setPixelColor(num, Color(255,0,0)); 
  }
  strip.show();
}
  
    Serial.print(millis() - start);        // check on performance in milliseconds
    Serial.print("\t");                    // tab character for debug windown spacing
    Serial.println(total1);                  // print sensor output 1
    //Serial.print("\t");
    //Serial.println(total2);                  // print sensor output 2
    // delay(100);                             // arbitrary delay to limit data to serial port 
}


RGBPixel Color(byte r, byte g, byte b)     // Create a 24 bit color value from R,G,B
{
  RGBPixel p;
  
  p.red = r;
  p.green = g;
  p.blue = b;
  
  return p;
}

RGBPixel Wheel(byte WheelPos)
{
  if (WheelPos < 85) {
   return Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if (WheelPos < 170) {
   WheelPos -= 85;
   return Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170; 
   return Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
