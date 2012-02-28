/*! @file global.h
 @author Ing. M.Lampugnani
 @par Company:
 MyCompany 
 @version 0.0.1-RF brach
 @date 27th july 2011 */
#ifndef	GLOBAL_H
#define	GLOBAL_H

/*! @name  Firmware and Hardware 
 Definizioni di versioni.\n
 Velocita' e tipi di comunicazione.\n
 */
//@{
//! Versione Firmware
#define FW_VER_STRING  "0.004-I2C"
#define FW_VER 0004
//! BPS comunicazione seriale
#define COM_BPS 9600
//@}

/*! @name  State 
 Variabili e definizioni utilizzate per la gestione degli stati del sistema.  */
//@{

//!  Numero massimo di stati in cui si puo' trovare il sistema.
/*!  Questa variabile e' usata per gestire i cicli fra gli stati, ad esempio
 con il tasto di un telecomando ir "AV/TV/VCR"   */
#define MAX_STATUS 5
/*!  Da tenere presente che sebbene lo stato 0 indichi il LED spento.
 Anche lo 0 e' uno stato a tutti gli effetti  */
#define STAT_OFF       0x00    //!<  0 = off                  
#define STAT_STATIC    0x01    //!<  1 = static color          
#define STAT_RAND      0x02    //!<  2 = rand_col function      
#define STAT_FLASH     0x03    //!<  3 = flash function       
#define STAT_UFO       0x04    //!<  4 = ufo function
#define STAT_CIRCLE    0x05    //!<  5 = Circle function !! Synchronized func

//! Codice stato attuale in cui si trova il sistema
/*!  Da tenere presente che il valore con cui vuene settata in fase di dichiarazione,
     sara' il valore assegnato in fase di avvio del dispositivo.*/
int system_stat = STAT_OFF; //!< La variabile dovra' assumere solo valori predefiniti dalle define STAT_*

//! Device identification
/*!   @param [0-254]  */
unsigned int dev_Id = 1; // 1 - 254
//! Group identification
/*!   @param [0-15]  */
unsigned int dev_Ig = 1; // 0 - 15

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


/*! @name Variaibli di appoggio
 Varibili di appoggio utilizzate per la comunicazione seriale e RF (se presente).  */
//@{

//! Array da 11 colonne in cui viene appoggiato il comando proveniente dalla seriale/RF
/*! Le prime 3 posizioni sono il comando\n
 //  La quarta no è usata\n
 //  sette posizioni usate per l'agomento piu' terminatore */
char com_data[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};  //!<  @todo verificare perche' devo usare un elemento in piu' nell'array
//diversamente da come fatto nella versione IR

//! Array di parcheggio dati RF Gruppo e Dispositivo
/*! La posizione zero contiene il dato del gruppo (15 possibili).\n
    La posizione uno e due contiene i dati del dispositivo (1-254; 0 nessuno - 255 broadcast).\n
    La matrice contiene valori esadecimali.
*/

//! Array da 3 colonne in cui viene appoggiato il gruppo e il dispositivo di destinazione settato via RF
/*! La prima posizione è il gruppo\n
 //  la seconda e la terza sono il dispositivo\n */
char com_Id[] = {0, 0, 0};
//char com_Ig = '0';

//! Variabile di parcheggio per l'ultimo byte arrivato dalla porta seriale
int incomingByte = 0;

//@}


/*!  @name  Dynamic Color var and def. 
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
//@}

//! Dyn color reinit var
void ReInitDynVars(){
  DYNcolor = DYN_COL_INIT;
  DESTvalue = DYN_DEST_OFF;  //!< @todo non dovrebbe essere necessario riinizializzarla
}

//! Varibile per l'autospegnimento
unsigned int tickTIMER = 0;    

//###################################################################################
//###################################################################################
//############################    I"C   BEGIN         ###############################
//###################################################################################
//###################################################################################
#ifdef  BUILD_COMM_I2C

#define I2C_NODE          4

//I2C Status Word
//bit0 = B0000000X =>  There's new data?
char I2CSW;

#endif
//###################################################################################
//############################    I"C      END        ###############################
//###################################################################################
#endif


