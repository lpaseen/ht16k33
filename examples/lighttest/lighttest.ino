/****************************************************************
 * Simple test of ht16k33 library turning on and off LEDs
 */

#include "ht16k33.h"

// Define the class
HT16K33 HT;

/****************************************************************/
void setup() {
  Serial.begin(57600);
  Serial.println(F("ht16k33 light test v0.01"));
  Serial.println();
  // initialize everything, 0x00 is the i2c address for the first one (0x70 is added in the class).
  HT.begin(0x00);
}

/****************************************************************/
void loop() {
  uint8_t led;

  Serial.println(F("Turn on all LEDs"));
  // first light up all LEDs
  for (led=0; led<128; led++) {
    HT.setLedNow(led);
    delay(10);
  } // for led

  Serial.println(F("Clear all LEDs"));
  //Next clear them
  for (led=0; led<128; led++) {
    HT.clearLedNow(led);
    delay(10);
  } // for led

  //Now do one by one, slowly, and print out which one
  for (led=0; led<128; led++) {
    HT.setLedNow(led);
    Serial.print(F("Led no "));
    Serial.print(led,DEC);
    Serial.print(F(": On"));
    delay(1000);
    HT.clearLedNow(led);
    Serial.println(F(" Off"));
  } // for led
} // loop  
    
