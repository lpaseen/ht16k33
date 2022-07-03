# ht16k33
This library is used to allow an arduino like platform talk to the holtek ht16k33 chip
to do things like turn on/off LEDs or scan keys

You set/clear whatever LEDs you want, then you call `sendLed()` to update the display with the new values.

# simple code sample

```c
/****************************************************************
* Simple test of ht16k33 library turning on and off LEDs
*/

#include "ht16k33.h"

// Define the class
HT16K33 HT;

/****************************************************************/
void setup() {
    Serial.begin(115200);
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

```
Sample to Read keyboard and seg16 is in example directory.


# Methods
```c
void      clearAll();               // clear all LEDs
uint8_t   sleep();                  // stop oscillator to put the chip to sleep
uint8_t   normal();                 // wake up chip and start ocillator
uint8_t   clearLed(uint8_t ledno);  // 16x8 = 128 LEDs to turn off, 0-127
uint8_t   setLed(uint8_t ledno);    // 16x8 = 128 LEDs to turn on, 0-127
void      define7segFont(uint8_t *ptr);                     // Pass a pointer to a font table for 7seg
void      define16segFont(uint16_t *ptr);                   // Pass a pointer to a font table for 16seg see example/seg16/asciifont-pinout11.h & asciifont-pinout12.h
uint8_t   set7Seg(uint8_t dig, uint8_t cha, boolean dp);    // position 0-15, 0-15 (0-F Hexadecimal), decimal point
uint8_t   set16Seg(uint8_t dig, uint8_t cha);               // position 0-7, see asciifont.h
boolean   getLed(uint8_t ledno,boolean Fresh=false);        // check if a specific led is on(true) or off(false)
uint8_t   setDisplayRaw(uint8_t pos, uint8_t val);          // load byte "pos" with value "val"
uint8_t   sendLed();                                        // send whatever led patter you set
uint8_t   set7SegNow(uint8_t dig, uint8_t cha, boolean dp); // position 0-15, 0-15 (0-F Hexadecimal), decimal point and send led in one function
uint8_t   set7SegRaw(uint8_t dig, uint8_t val);             // load byte "pos" with value "val"
uint8_t   set16SegNow(uint8_t dig, uint8_t cha);            // position 0-17, see asciifont.h and send led in one function
uint8_t   setLedNow(uint8_t ledno);                         // Set a single led and send led in one function
uint8_t   clearLedNow(uint8_t ledno);                       // Clear a single led and send led in one function
uint8_t   setBrightness(uint8_t level);                     // level 0-16, 0 means display off
uint8_t   keyINTflag();                                     // INTerrupt flag value, set when a key is pressed
uint8_t   keysPressed();                                    // report how many keys that are pressed, clear means report as if new
int8_t    readKey(boolean clear=false);                     // read what key was pressed, Fresh=false to go from cache
void      readKeyRaw(KEYDATA keydata,boolean Fresh=true);   // read the raw key info, bitmapped info of all key(s) pressed
uint8_t   setBlinkRate(uint8_t rate);                       // HT16K33_DSP_{NOBLINK,BLINK2HZ,BLINK1HZ,BLINK05HZ}
void      displayOn();
void      displayOff();
```
