/*! @file pin_def.h
 @author Ing. M.Lampugnani
 @par Company:
 MyCompany
 @version 0.0.1-RF brach
 @date 9th august 2011 */

#ifndef	PIN_DEF_H
#define	PIN_DEF_H

//! Pin di segnalazione POWER On/Off.
/*! Sul pin13 della scheda, dove spesso e' gia' connesso un led
NON e'possibile collegarsi, in quanto usato dal chip ethernet.
*/
#define STATUS_PIN 7
#define ENABLE_PIN 8

//!< @param MCU pin


#define RANDOM_PIN A5 // analog pin 5 - digital pin9

//pinout PCB
/*! @name INPUT IR/RF PinOut
 Defenizione delle connessioni dell IR/RF Receiver all MCU
 @param MCU pin  */
//@{

//IR TSOP1838
//#define GND_PIN 15        //!< Pin di massa - OUTPUT
//#define VCC_PIN 16        //!< Pin di alimentazione (5V; 20mA - 40mA MAX) - OUTPUT
//#define RECV_PIN 14       //!< Pin di ricezione dati - INPUT

#ifdef CHIP_328
// 433 RF MODULE
#ifdef PROTO
#define GND_PIN 16        //!< Pin di massa - OUTPUT
#define VCC_PIN 14        //!< Pin di alimentazione (5V; 20mA - 40mA MAX) - OUTPUT
#define RECV_PIN 15       //!< Pin di ricezione dati - INPUT
#else
#define GND_PIN 17        //!< Pin di massa - OUTPUT
#define VCC_PIN 14        //!< Pin di alimentazione (5V; 20mA - 40mA MAX) - OUTPUT
#define RECV_PIN 16       //!< Pin di ricezione dati - INPUT
#endif

#endif

//ARDUINO TEST
//#define GND_PIN 17        //!< Pin di massa - OUTPUT
//#define VCC_PIN 14        //!< Pin di alimentazione (5V; 20mA - 40mA MAX) - OUTPUT
//#define RECV_PIN 15       //!< Pin di ricezione dati - INPUT

#ifdef CHIP_1280
//433 RF ARDUINO-mega TEST
#define GND_PIN 27        //!< Pin di massa - OUTPUT
#define VCC_PIN 28        //!< Pin di alimentazione (5V; 20mA - 40mA MAX) - OUTPUT
#define RECV_PIN 23       //!< Pin di ricezione dati - INPUT
#endif
//@}


/*! @name OUTPUT RGB PinOut
 	Definizione delle Connessioni dei tre anodi del led RGB
 @param MCU pin  */
//@{

//IR TSOP1838
//#define RED_PIN 10 	//!< Pin dell'MCU al quale e' connesso l'anodo Rosso (R) - OUTPUT 
//#define GREEN_PIN 9 	//!< Pin dell'MCU al quale e' connesso l'anodo Verde (G) - OUTPUT
//#define BLUE_PIN 5 	//!< Pin dell'MCU al quale e' connesso l'anodo Blu (B)   - OUTPUT

#ifdef CHIP_328
// 433 RF MODULE
#define RED_PIN 11  	//!< anodo Rosso (R)
#define GREEN_PIN 3	//!< anodo Verde (G)
#define BLUE_PIN 6 	//!< anodo Blu (B)
#endif

#ifdef CHIP_1280
//433 RF ARDUINO-mega TEST 
#define RED_PIN 8  	//!< anodo Rosso (R)
#define GREEN_PIN 4	//!< anodo Verde (G)
#define BLUE_PIN 7 	//!< anodo Blu (B)
#endif

//@}

#endif


