/*
  ht16k33.h - used to talk to the htk1633 chip to do things like turn on LEDs or scan keys
 * Copyright:  Peter Sjoberg <peters-alib AT techwiz.ca>
 * History:
 * 2015-10-04  Peter Sjoberg <peters-alib AT techwiz.ca>
 *             Created using https://www.arduino.cc/en/Hacking/LibraryTutorial and ht16k33 datasheet
 * 2015-11-25  Peter Sjoberg <peters-alib AT techwiz DOT ca>
 *	       first check in to github
*/



#ifndef ht16k33_h
#define ht16k33_h

#include "Arduino.h"

class HT16K33
{
 public:
  typedef uint16_t KEYDATA[3];
  
  HT16K33(); // the class itself

  void    begin(uint8_t address);
  void    end();
  uint8_t sleep();  // stop oscillator to put the chip to sleep
  uint8_t normal(); // wake up chip and start ocillator
  uint8_t clearLed(uint8_t ledno); // 16x8 = 128 LEDs to turn on, 0-127
  uint8_t setLed(uint8_t ledno); // 16x8 = 128 LEDs to turn on, 0-127
  boolean getLed(uint8_t ledno); // check if a specific led is on(true) or off(false)
  uint8_t sendLed(); // send whatever led patter you set
  uint8_t setLedNow(uint8_t ledno); //Set a single led and send led in one function
  uint8_t clearLedNow(uint8_t ledno); //Clear a single led and send led in one function
  uint8_t setBrightness(uint8_t level); // level 0-16, 0 means display off
  boolean keyReady(); // true if any key is pressed
  int8_t  readKey();  // read what key was pressed
  void    readKeyRaw(KEYDATA keydata); //read the raw key info, bitmapped info of all key(s) pressed
  uint8_t setBlinkRate(uint8_t rate); // HT16K33_DSP_{NOBLINK,BLINK2HZ,BLINK1HZ,BLINK05HZ}
  void    displayOn();
  void    displayOff();
 private:
  void _updateKeyram();
  uint8_t _i2c_write(uint8_t val);
  uint8_t _i2c_write(uint8_t cmd,uint8_t *data,uint8_t size,boolean LSB=false);
  uint8_t _i2c_read(uint8_t addr);
  uint8_t _i2c_read(uint8_t addr,uint8_t *data,uint8_t size);

  KEYDATA _keyram;
  uint8_t _displayram[16];
  uint8_t _address;
};


#endif
