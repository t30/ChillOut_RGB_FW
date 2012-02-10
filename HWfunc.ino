/*! @file HWfunc.ino
 @author Ing. M.Lampugnani
 @par Company:
 MyCompany
 @version 0.0.1
 @date 21th October 2011 */

//! Init LED status (GREEN)
void initStatus(){
  pinMode(OUTPUT, STATUS_PIN);
}

//! Init LED ENABLE (YELLOW)
void initEnable(){
  pinMode(OUTPUT, ENABLE_PIN);
}

//! Blinking led Status.
/*!  Connected to pin def::STATUS_PIN */
void blinkStatus(){
  digitalWrite( STATUS_PIN,!digitalRead(STATUS_PIN) );
  //digitalWrite( ENABLE_PIN,!digitalRead(ENABLE_PIN) );
}

//! Blinking led ENABLE
/*!  Connected to pin def::ENABLE_PIN */
void blinkEnable(){
  //digitalWrite( STATUS_PIN,!digitalRead(STATUS_PIN) );
  digitalWrite( ENABLE_PIN,!digitalRead(ENABLE_PIN) );
}

//! Action led ENABLE
/*!  Connected to pin def::ENABLE_PIN */
void blinkEnable(char action){
  switch(action){
  case -127:
    DBGp_ERR(1,"blinkERR:%u",action);
    break;
  case 0:
    digitalWrite( ENABLE_PIN,LOW );
    break; 
  case 1:
    digitalWrite( ENABLE_PIN,HIGH );
    break;  
  }
}

void blinkAll(){
  blinkStatus();
  blinkEnable();
}

//! CheckShutDown function
/*!  Configured by external command and called by func::TSKlog() */
void chkSHUTdn(){

  if(tickTIMER == 1){      //! Shutdown light --> go to define::STAT_OFF
    led_off();
    blinkEnable(0);
    tickTIMER--;
    system_stat = STAT_OFF;
    DBGp_STAT(0,"Shutting Down Now\n", tickTIMER);
  }
  else if(tickTIMER > 1){  //! Decrease the value count
    tickTIMER--;
    DBGp_STAT(2,"%u tick to ShutDown\n", tickTIMER);
  }
  else{                    //! Do nothing

  }

}





