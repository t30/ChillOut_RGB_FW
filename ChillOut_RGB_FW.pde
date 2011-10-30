/*! @file ChillOut_RGB_FW.h
 @author Ing. M.Lampugnani
 @par Company:
 MyCompany
 @version 0.0.1-RF brach
 @date 21th October 2011 */

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

  Serial.begin(9600); 
  Serial.println("Booting up..");

  RGBinit();
  RFinit();
	
  blinkStatus();		

  RFsetup();

  LedInitTest();

  Serial.println("Ready!!");

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
