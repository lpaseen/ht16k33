/****************************************************************
 * Simple test of ht16k33 library both led and keyboard
 */

#include "ht16k33.h"

// Define the class
HT16K33 HT;


/****************************************************************/
void setup() {
  uint8_t led;
  Serial.begin(57600);
  Serial.println("ht16k33 keyboard and led test v0.01");
  Serial.println();
  // initialize everything, 0x00 is the i2c address for the first chip (0x70 is added in the class).
  HT.begin(0x00);

  // flash the LEDs, first turn them on
  Serial.println(F("Turn on all LEDs"));
  for (led=0; led<128; led++) {
    HT.setLedNow(led);
    delay(10);
  } // for led

  //Next clear them
  Serial.println(F("Clear all LEDs"));
  for (led=0; led<128; led++) {
    HT.clearLedNow(led);
    delay(10);
  } // for led
}

/****************************************************************/
void loop() {
  static uint8_t led=0;
  static uint8_t lastKey=0;
  static int8_t dir=1;
  int8_t key;

  //Now do one by one, slowly, and print out which one
  // if any key is pressed change direction

  HT.setLedNow(led);
  Serial.print(F("Led no "));
  Serial.print(led,DEC);
  Serial.print(F(": On"));
  delay(1000);
  HT.clearLedNow(led);
  //  Serial.println(F(" Off"));
  Serial.print(F(" Off - "));
  Serial.println(dir,DEC);

  key=HT.readKey();
  if (key != 0) { // key is pressed
    if (key != lastKey){
      dir=-dir;
      Serial.print(F("Key pressed: ")); 
      Serial.println(key);
      lastKey=key;
    }
  }

  if (led == 0 ) {
    dir=1;
  } else if (led == 127){
    dir=-1;
  }
  led+=dir;
} // loop
    
