/*! @file Debug.pde
 This file contain all the function and all the definition about debug.\n
 @author Ing. M.Lampugnani
 @par Company:
 MyCompany
 @version 0.0.1-RF brach
 @date 21th October 2011 */
 
 #include <stdarg.h>
unsigned int debugL = DEBUG;

//!  Write out a debug string over serial port
/*!  Prende in argomento il livello di dbg e la stringa da comporre e printare sulla seriale.
 @param[in]  lvlDBG  livello minimo per essere printate
 @param[in]  fmt  stringa formattata
 */
void p(unsigned int lvlDBG, char *fmt, ... ){
  if(lvlDBG <= debugL){    
    Serial.print(millis());
    Serial.print(" - ");

    if(lvlDBG>0){
      Serial.print("DBG: ");
      Serial.print(lvlDBG,DEC);
      Serial.print(" msg: ");
    }
    char tmp[64]; // resulting string limited to 64 chars
    va_list args;
    va_start (args, fmt );
    vsnprintf(tmp, 64, fmt, args);
    va_end (args);
    Serial.print(tmp);
  }
}







