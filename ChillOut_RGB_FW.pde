/*! @file TaskSync.h
 @author Ing. M.Lampugnani
 @par Company:
 MyCompany
 @version 0.0.1-RF brach
 @date 27th july 2011 */
#include <Metro.h>
#include <VirtualWire.h>
#include "pin_def.h"
#include "global.h"
#include "timing.h"


void setup() {
  /*!  <b> Operazioni eseguite dalla funzione: </b>  */
  
  /*!  - Start-up porta seriale e ricevitore IR
   	\arg Avvio della porta seriale  */
  Serial.begin(9600); 
  Serial.println("Booting up..");

  /*!  - Settaggio dei pin di OUTPUT  
   \arg Settaggio var::RED_PIN  */
  pinMode(RED_PIN, OUTPUT);		
  /*! \arg Settaggio var::GREEN_PIN */
  pinMode(GREEN_PIN, OUTPUT);		
  /*! \arg Settaggio var::BLUE_PIN */
  pinMode(BLUE_PIN, OUTPUT);

  /*! \arg Settaggio var::GND_PIN */
  pinMode(GND_PIN, OUTPUT);		
  /*! \arg Settaggio var::VCC_PIN */
  pinMode(VCC_PIN, OUTPUT);		
  /*! \arg Settaggio var::LEDPP */
  pinMode(LEDPP, OUTPUT);		
  //!\n

  /*!- Settaggio dello stato dei PIN di alimentazione del ricevitore IR
   \arg Settaggio stato LOW al var::GND_PIN  */
  digitalWrite(GND_PIN, LOW);		
  /*!   \arg Settaggio stato HIGH al pin var::VCC_PIN */
  digitalWrite(VCC_PIN, HIGH);  	
  //!\n

  /*!	\arg Accensione del LED di stato var::LEDPP*/
  digitalWrite(LEDPP,HIGH);		
  //!\n

  //#ifdef  RF
  /*!	\arg Init modulo RF */
  RFInit();
  //#endif

  /*!  - Final Test 
   \arg Init Test Led RGB */
  LedInitTest();
  /*!  \arg Invio sulla porta del messaggio "Ready!!" */
  Serial.println("Ready!!");
  //  p("Decimal a: %l\nDecimal unsigned a: %lu\n", millis(), millis()); 	

}

#include "debug.h"
#include "RGBfunc.h"
#include "COMfunc.h"
#include "PSfunc.h"
//#ifdef  RF
#include "RFfunc.h"
//#endif

/*! Funzione che emette tre lampeggi da 200ms dei tre colori principali del led*/
//! Funzione di test LED RGB
void LedInitTest() {
  led_off();
  led_red();
  delay(DELAY_INIT_TEST_ON);
  led_off();
  delay(DELAY_INIT_TEST_OFF);
  led_green();
  delay(DELAY_INIT_TEST_ON);
  led_off();
  delay(DELAY_INIT_TEST_OFF);
  led_blue();
  delay(DELAY_INIT_TEST_ON);
  led_off();
  delay(DELAY_INIT_TEST_OFF);
}

//#ifdef  RF
void RFInit(){
  vw_set_rx_pin(RECV_PIN);
  vw_setup(RF_BIT_PER_SEC);	   // Bits per sec
  vw_rx_start();                   // Start the receiver PLL running
  DBGp_RF(5,"init RF\n", r);
}
//#endif


void loop() {
  //  PSprocess();
  //#ifdef  RF
  // RFprocess();
  //#endif

  if (Period.check() == 1) {
    Period.reset();
    switch(system_stat){
    case STAT_RAND:
      RGBrandom();
      break;
    case STAT_FLASH:
      //RGBflash();
      break;
    case STAT_UFO:
      RGBufo();
      break;
    }
  } 
  else {
    PSprocess();
    RFprocess();
  }

  if (Update.check() == 1) {
    Update.reset();
    DBGp(5,"Actual RGB state - r: %u g: %u b: %u => com_data: %s \n", r, g, b, com_data); 	

  }

}












