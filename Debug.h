/*! @file Debug.h
 The definition are used to call the main funcion limited to its contest.\n
 Commenting definition you should disable debug.\n
 @author Ing. M.Lampugnani
 @par Company:
 MyCompany
 @version 0.0.1-RF brach
 @date 21th October 2011 */
 
#ifndef	DEBUG_H
#define	DEBUG_H


#define DBGp(lvlDBG, fmt, ... )                      p(lvlDBG, fmt, __VA_ARGS__ )
#define DBGp_ERR(lvlDBG, fmt, ... )                  DBGp(lvlDBG, fmt, __VA_ARGS__ )
#define DBGp_STAT(lvlDBG, fmt, ... )                 DBGp(lvlDBG, fmt, __VA_ARGS__ )

#define DBGp_COM(lvlDBG, fmt, ... )                  DBGp(lvlDBG, fmt, __VA_ARGS__ )
#define DBGp_PS(lvlDBG, fmt, ... )                   DBGp(lvlDBG, fmt, __VA_ARGS__ )
#define DBGp_RF(lvlDBG, fmt, ... )                   DBGp(lvlDBG, fmt, __VA_ARGS__ )

//!  Definition of  default level debug
#define DEBUG  9

//!  Actual system level debug
/*!  This can be changed on the fly using serial command.\n
 eg.  dbg_l00000.\n
 0 < l < 9  */
extern unsigned int debugL; // = DEBUG;

extern void p(unsigned int lvlDBG, char *fmt, ... );



#endif

