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
  DBGp_STAT(5,"Actual state - r: %u g: %u b: %u => com_data: %s\n", r, g, b, com_data); 	
//  DBGp_STAT(7,"com_Ig: %s\n", com_Ig); 	
  DBGp_STAT(7,"com_Id: %s\n", com_Id); 	
  //DBGp_STAT(7,"Actual RGB state - r: %u g: %u b: %u => com_data: %s com_Ig: %c com_Id:%s \n", r, g, b, com_data, com_Ig, com_Id); 	
  //blinkEnable();
}





