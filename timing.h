/*! @file timing.h
 @author Ing. M.Lampugnani
 @par Company:
 MyCompany
 @version 0.0.1-RF brach
 @date 27th july 2011 */
#ifndef	TIMING_H
#define	TIMING_H

#define DELAY_INIT_TEST_OFF  200
#define DELAY_INIT_TEST_ON   200

#define RF_BIT_PER_SEC       2000

/*!  @name  Task timing function definition
 //  Creazione degli oggetti timer utilizzati per le chiamate ai task  */
//@{
//!Setting up execution frequency f[kHz]= 1/period[msec]
unsigned int period = 50;
//!  Task Veloce.
/*!  Utilizzato per mantenere aggiornate le varibili interne del sistema.  */
Metro Period = Metro(period);

//!Setting up execution frequency f[kHz]= 1/period[msec]
unsigned int periodUpdate = 5000;
//!  Task Lento.
/*!  Utilizzato per mantenere aggiornato lo stato dei sensori e componenti lenti
 //  in risposta o nella variazione del loro segnale.  */
Metro Update = Metro(periodUpdate); 
//@}

#endif


