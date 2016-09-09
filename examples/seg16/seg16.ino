/****************************************************************
 * Simple test of ht16k33 library turning on and off LEDs
 */

#include "ht16k33.h"
#include <Wire.h>
#include "asciifont-pinout12.h"

// Define the class
HT16K33 HT;

/****************************************************************/
void setup() {
  Serial.begin(38400);
  Serial.println(F("ht16k33 test of 16 seg digits v0.03"));
  Serial.println();
  /*
  Serial.print("DEBUGA: ");Serial.println((uint16_t)fontTable,HEX);
  Serial.print("DEBUGB: ");Serial.println(fontTable[0],HEX);
  Serial.println(fontTable[1],HEX);
  Serial.println(fontTable[2],HEX);
  Serial.println();
*/
    // initialize everything, 0x00 is the i2c address for the first one (0x70 is added in the class).
  HT.begin(0x00);
  HT.define16segFont((uint16_t*) &fontTable);
}

/****************************************************************/
void loop() {
  char i;
  
  HT.clearAll();
  delay(5000);
  /*
  Serial.println('!'); HT.set16Seg(4,'!'-' ');
  Serial.println('1'); HT.set16Seg(5,'1'-' ');
  Serial.println('O'); HT.set16Seg(6,'O'-' ');
  Serial.println('0'); HT.set16Seg(7,'0'-' ');
  delay(5000);
  */
  for (i=' ';i<='`';i++){
    Serial.println(i);
    HT.set16Seg(4,i-' ');
    HT.sendLed();
    delay(1000);
  }
  
} // loop  
    
