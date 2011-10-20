/*! @file HWfunc.pde
 @author Ing. M.Lampugnani
 @par Company:
 MyCompany
 @version 0.0.1
 @date 21th October 2011 */

//! Blinking led status.
/*!  Connected to pin pin def::STATUS_PIN */
void blinkStatus(){
  digitalWrite( STATUS_PIN,!digitalRead(STATUS_PIN) );
  }
