/*! @file COM_I2C.ino
 Function for I2C connection (incoming cmd - Slave mode).
 @author Ing. M.Lampugnani
 @par Company:
 MyCompany
 @version 0.0.4
 @date 26th february 2012 */

#if defined BUILD_COMM_I2C

void I2Cprocess(){
  if(bitRead(I2CSW, 0)){
    COMprocess();
    bitClear(I2CSW, 0);
  }
}

void I2CreceiveEvent(int HowManyByteExpect){
  unsigned int countPos = 0;
  while(1 <= Wire.available()) // loop through all but the last
  {
    char c = Wire.read(); // receive byte as a character
    if(Wire.available()==0){
      bitSet(I2CSW,0);
    }
    if(countPos < 10) {
      com_data[countPos] = c;
    } 
    countPos++;
  }
  com_data[10] = '\0';
  bitSet(I2CSW,0);
}

void I2CreceiveEventOLD(int HowManyByteExpect){
  DBGp_I2C(8,"I2C byte: %u \n",HowManyByteExpect);
  // if(HowManyByteExpect >= 10){
  unsigned int countPos = 0;
  while(1 <= Wire.available()) // loop through all but the last
  {
    char c = Wire.read(); // receive byte as a character
    DBGp_I2C(8,"I2C incByte==> %c\n", c);
    //Serial.print(c);         // print the character
    //if(Wire.available()==0){
    //  Serial.println();      
    //}
    if(countPos < 10) {
      com_data[countPos] = c;
    } 
    countPos++;
  }


  //    for (int i = 0; i < HowManyByteExpect; i++){
  //      incomingByte = Wire.read();
  //      DBGp_I2C(8,"I2C incByte==> %c\n", incomingByte);
  //      if(i < 10) {
  //        com_data[i] = incomingByte;
  //      } 
  //      //com_data[i+1] = '\0';
  //    }
  //posiziono il terminatore di stringa per non avere "sporcizia"
  com_data[10] = '\0';

  COMprocess();

  // } 
}

void I2Csetup(){
  DBGp_I2C(5,"setup I2C node: %u\n", I2C_NODE);
  Wire.begin(I2C_NODE);                // Start I2C Bus as a Slave (Device Number 9)
  Wire.onReceive(I2CreceiveEvent); // register event
}

#endif











