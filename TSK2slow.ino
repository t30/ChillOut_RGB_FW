/*! @file TSK2slow.ino
 Routine lanciata da loop(). E' eseguita ogni var::slowPeriod ms (all'incirca).\n
 @author Ing. M.Lampugnani
 @par Company:
 MyCompany
 @version 0.0.1-RF brach
 @date 21th October 2011 */

void TSKslow(){
  //blinkEnable();

  randomSeed(analogRead(RANDOM_PIN));
  DBGp_STAT(5,"Actual RGB state - r: %u g: %u b: %u => com_data: %s \n", r, g, b, com_data); 	
  //blinkEnable();
}



