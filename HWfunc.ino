/*! @file HWfunc.ino
 @author Ing. M.Lampugnani
 @par Company:
 MyCompany
 @version 0.0.1
 @date 21th October 2011 */

//! Blinking led status.
/*!  Connected to pin pin def::STATUS_PIN */
void blinkStatus(){
  digitalWrite( STATUS_PIN,!digitalRead(STATUS_PIN) );
  //digitalWrite( ENABLE_PIN,!digitalRead(ENABLE_PIN) );
}

//! Blinking led status.
/*!  Connected to pin pin def::STATUS_PIN */
void blinkEnable(char action){
  switch(action){
  case -127:
    DBGp_ERR(1,"blinkERR:%u",action);
    break;
  case 0:
    digitalWrite( ENABLE_PIN,0 );
    break; 
  case 1:
    digitalWrite( ENABLE_PIN,1 );
    break;  
  }
}
void blinkEnable(){
  //digitalWrite( STATUS_PIN,!digitalRead(STATUS_PIN) );
  digitalWrite( ENABLE_PIN,!digitalRead(ENABLE_PIN) );
}

void blinkAll(){
  blinkStatus();
  blinkEnable();
}

void chkSHUTdn(){
  if(tickTIMER == 1){      //! Shutdown light --> go to define::STAT_OFF
    led_off();
    tickTIMER--;
    system_stat = STAT_OFF;
    DBGp_STAT(0,"Programmed ShutDown Now\n", tickTIMER);
  }
  else if(tickTIMER > 1){  //! Decrease the value count
    tickTIMER--;
    DBGp_STAT(2,"Again %u tick to ShutDown\n", tickTIMER);
  }
  else{                    //! Do nothing

  }

}




