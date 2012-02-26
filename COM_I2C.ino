/*! @file COM_I2C.ino
 Function for I2C connection (incoming cmd - Slave mode).
 @author Ing. M.Lampugnani
 @par Company:
 MyCompany
 @version 0.0.1-RF brach
 @date 26th february 2012 */

#if defined BUILD_COMM_I2C

void I2CProcess(){

}

void I2CreceiveEvent(int HowManyByteExpect){
  DBGp_I2C(8,"I2C byte: %u \n",HowManyByteExpect);
  if(HowManyByteExpect == 10){

  } 
}

void I2Csetup(){
  Wire.begin(I2C_NODE);                // Start I2C Bus as a Slave (Device Number 9)
  Wire.onReceive(I2CreceiveEvent); // register event
}

#endif


