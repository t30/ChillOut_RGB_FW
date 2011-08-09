/*! @file debug.h
 @author Ing. M.Lampugnani
 @par Company:
 MyCompany
 @version 0.0.1-RF brach
 @date 31th july 2011 */
#ifndef	DEBUG_H
#define	DEBUG_H
#include <stdarg.h>

#define DBGp(lvlDBG, fmt, ... )                      p(lvlDBG, fmt, __VA_ARGS__ )
#define DBGp_COM(lvlDBG, fmt, ... )                  DBGp(lvlDBG, fmt, __VA_ARGS__ )
#define DBGp_PS(lvlDBG, fmt, ... )                   DBGp(lvlDBG, fmt, __VA_ARGS__ )
#define DBGp_RF(lvlDBG, fmt, ... )                   DBGp(lvlDBG, fmt, __VA_ARGS__ )
#define DBGp_RGB(lvlDBG, fmt, ... )                  DBGp(lvlDBG, fmt, __VA_ARGS__ )

/*!  Definition of debug level */
#define DEBUG  7
unsigned int debugL = DEBUG;

/*!  Write out a debug string over serial port */
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


#endif







