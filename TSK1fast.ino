/*! @file TSK1fast.ino
 Routine lanciata da loop(). E' eseguita ogni var::fastPeriod ms (all'incirca).\n
 @author Ing. M.Lampugnani
 @par Company:
 MyCompany
 @version 0.0.1-RF brach
 @date 21th October 2011 */

void TSKfast(){
  blinkStatus();
  switch(system_stat){
  case STAT_RAND:
//    blinkStatus();
    RGBrandom();
    break;
  case STAT_FLASH:
    RGBflash();
    break;
  case STAT_UFO:
    RGBufo();
    break;
  case STAT_CIRCLE:
    RGBcircle();
    break;
  }
}

