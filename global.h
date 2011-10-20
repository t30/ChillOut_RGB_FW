/*! @file global.h
 @author Ing. M.Lampugnani
 @par Company:
 MyCompany
 @version 0.0.1-RF brach
 @date 27th july 2011 */
#ifndef	GLOBAL_H
#define	GLOBAL_H

//#define RF

/*!  @name  State 
 Variabili e definizioni utilizzate per la gestione degli stati del sistema.  */
//@{

//!  Numero massimo di stati in cui si puo' trovare il sistema.
/*!  Questa variabile e' usata per gestire i cicli fra gli stati, ad esempio
 con il tasto di un telecomando ir "AV/TV/VCR"   */
#define MAX_STATUS 4
/*!  Da tenere presente che sebbene lo stato 0 indichi il LED spento.
 Anche lo 0 e' uno stato a tutti gli effetti  */
#define STAT_OFF       0x00    //!<  0 = off                    @todo  Non ancora usata 
#define STAT_STATIC    0x01    //!<  1 = static color           @todo  Non ancora usata 
#define STAT_RAND      0x02    //!<  2 = rand_col function      @todo  Usata in parte 
#define STAT_FLASH     0x03    //!<  3 = flash function         @todo  Usata in parte
#define STAT_UFO       0x04    //!<  4 = ufo function
#define STAT_CIRCLE    0x05    //!<  5 = Circle function !! Synchronized func

//! Codice stato attuale in cui si trova il sistema
int system_stat = STAT_OFF; //!< La variabile dovra' assumere solo valori predefiniti dalle define STAT_*
//@}

/*! @name Colore Attuale RGB
 	Variabili in cui vengono salvati i valori da scrivere sull'uscita per generare un colore \n
 	Dopo aver cambiato il valore di queste variabili, viene chiamata la funzione rgb() per scriverli fisicamente
 @param [0-255]  */
//@{

/*!  Da tenere presente che anche con valori bassi il led potrebbe non dare segno di vita*/
unsigned int max_pwm=255;  //!<  Valore massimo assumibile dai colori (1-255); con 0 non si accenderebbe proprio il led
/*unsigned*/int r=100; //!< Variabile colore Rosso	(Red) - Questa variabile non puo' mai superare il valore di var::max_pwm
/*unsigned*/int g=100; //!< Variabile colore Verde	(Green) - Questa variabile non puo' mai superare il valore di var::max_pwm
/*unsigned*/int b=100; //!< Variabile colore Blu	(Blue) - Questa variabile non puo' mai superare il valore di var::max_pwm

//@}

/*!  @name Variaibli di appoggio
 Varibili di appoggio utilizzate per la comunicazione seriale e RF (se presente).  */
//@{

//! Array da 11 colonne in cui viene appoggiato il comando proveniente dalla seriale/RF
/*! Le prime 3 posizioni sono il comando
 //  La quarta no è usata
 //  sette posizioni usate per l'agomento piu' terminatore */
char com_data[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};  //!<  @todo verificare perche' devo usare un elemento in piu' nell'array
//diversamente da come fatto nella versione IR

//! Variabile di parcheggio per l'ultimo byte arrivato dalla porta seriale
int incomingByte = 0;

//@}


/*!  @name  Dynamic Color function 
 Variabili e definizioni utilizzate per la gestione delle funzioni dinamiche del sistema.  */
//@{

#define DYN_COL_MAX 3

#define DYN_COL_INIT        0xFD    //!<  253 = Ciclo dinamico colori - init
#define DYN_COL_ERR         0xFE    //!<  254 = Ciclo dinamico colori - err                    
#define DYN_COL_OFF         0xFF    //!<  255 = Ciclo dinamico colori - terminato                    
#define DYN_COL_WHITE       0x00    //!<    0 = Ciclo dinamico colori - white                  
#define DYN_COL_RED         0x01    //!<    1 = Ciclo dinamico colori - red          
#define DYN_COL_GREEN       0x02    //!<    2 = Ciclo dinamico colori - green    
#define DYN_COL_BLUE        0x03    //!<    3 = Ciclo dinamico colori - blue 

#define DYN_DEST_OFF        0xFF

int DYNcolor = DYN_COL_OFF;   //!< La variabile dovra' assumere solo valori predefiniti dalle define DYN_COL_*
int DESTvalue = DYN_DEST_OFF; //!< La variabile dovra' assumere solo valori compresi fra 0 e max_pwm

void ReInitDynVars(){
  DYNcolor = DYN_COL_INIT;
  DESTvalue = DYN_DEST_OFF;  //!< @todo non dovrebbe essere necessario riinizializzarla
}
//@}

#endif


