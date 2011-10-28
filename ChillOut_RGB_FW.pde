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
  /*!  <b> Operazioni eseguite dalla funzione: </b>  */

  /*!  - Start-up porta seriale e ricevitore IR
   	\arg Avvio della porta seriale  */
  Serial.begin(9600); 
  Serial.println("Booting up..");

  /*!  - Settaggio dei pin di OUTPUT  
   \arg Settaggio var::RED_PIN  */
  //pinMode(RED_PIN, OUTPUT);		
  /*! \arg Settaggio var::GREEN_PIN */
  //pinMode(GREEN_PIN, OUTPUT);		
  /*! \arg Settaggio var::BLUE_PIN */
  //pinMode(BLUE_PIN, OUTPUT);

  RGBinit();
  RFinit();
  /*! \arg Settaggio var::GND_PIN */
  //pinMode(GND_PIN, OUTPUT);		
  /*! \arg Settaggio var::VCC_PIN */
  //pinMode(VCC_PIN, OUTPUT);		
  /*! \arg Settaggio var::STATUS_PIN */
  //pinMode(STATUS_PIN, OUTPUT);		
  //!\n

  /*!- Settaggio dello stato dei PIN di alimentazione del ricevitore IR
   \arg Settaggio stato LOW al var::GND_PIN  */
  //digitalWrite(GND_PIN, LOW);		
  /*!   \arg Settaggio stato HIGH al pin var::VCC_PIN */
  //digitalWrite(VCC_PIN, HIGH);  	
  //!\n

  /*!	\arg Accensione del LED di stato var::STATUS_PIN*/
  //digitalWrite(STATUS_PIN,HIGH);		
  blinkStatus();		
  //!\n

  //#ifdef  RF
  /*!	\arg Setup modulo RF */
  RFsetup();
  //#endif

  /*!  - Final Test 
   \arg Init Test Led RGB */
  LedInitTest();
  /*!  \arg Invio sulla porta del messaggio "Ready!!" */
  Serial.println("Ready!!");
  //  p("Decimal a: %l\nDecimal unsigned a: %lu\n", millis(), millis()); 	

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
