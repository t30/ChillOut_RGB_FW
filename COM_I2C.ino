/*! @file COM_I2C.ino
 Function for I2C connection (incoming cmd - Slave mode).
 @author Ing. M.Lampugnani
 @par Company:
 MyCompany
 @version 0.0.4
 @date 26th february 2012 */

#if defined BUILD_COMM_I2C

//! Process I2C data
void I2Cprocess(){
  if(bitRead(I2CSW, 0)){
    DBGp_I2C(5,"Processing I2C data\n", I2C_NODE);
    COMprocess();
    bitClear(I2CSW, 0);
  }
}

//! I2C data handler function
/*!function that executes whenever data is received from master\n
 this function is registered as an event, see setup()
 */
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

//! Setup I2C comunication service
void I2Csetup(){
  DBGp_I2C(5,"setup I2C node: %u\n", I2C_NODE);
  Wire.begin(I2C_NODE);                // Start I2C Bus as a Slave (Device Number 9)
  Wire.onReceive(I2CreceiveEvent); // register event
}

#endif












