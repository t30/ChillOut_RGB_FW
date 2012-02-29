/*! @file ChillOut_RGB_FW.ino
 @author Ing. M.Lampugnani
 @par Company:
 MyCompany
 @version 0.0.1-RF brach
 @date 21th October 2011 */

//#define PROTO

#if defined __AVR_ATmega168__ || defined __AVR_ATmega328P__
#define CHIP_328
#endif

#if defined __AVR_ATmega1280__
#define CHIP_1280
#endif

#include <Metro.h>
#include <VirtualWire.h>
#include "pin_def.h"
#include "global.h"
#include "timing.h"
#include "Debug.h"
#include "RGBfunc.h"

void setup() {

  initStatus();
  initEnable();

  blinkEnable(1);
  blinkStatus();		

  Serial.begin(COM_BPS); 

  //Serial.println("Booting up..");
  DBGp_SETUP(0,"ChillOUT RGB Controller FW %s\n",FW_VER_STRING);

  RGBinit();
  RFinit();
  RFsetup();
  LedInitTest();

  randomSeed(analogRead(RANDOM_PIN));

  DBGp_SETUP(5,"Ready!!\n",FW_VER_STRING);
  //Serial.println("Ready!!");

  blinkEnable(0);
}

void loop() {

  if (FastTask.check() == 1) {
    FastTask.reset();
    TSKfast();
  } 
  else {
    PSprocess();
    RFprocess();
  }

  if (SlowTask.check() == 1) {
    SlowTask.reset();
    TSKslow();
  }

  if (LogTask.check() == 1) {
    LogTask.reset();
    TSKlog();
  }

}




