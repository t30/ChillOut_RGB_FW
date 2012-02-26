/*! @file COM_I2C.ino
 Function for I2C connection (incoming cmd - Slave mode).
 @author Ing. M.Lampugnani
 @par Company:
 MyCompany
 @version 0.0.1-RF brach
 @date 26th february 2012 */

#ifdef  COMMI2C

void I2Csetup(){
  Wire.begin(I2C_NODE);                // Start I2C Bus as a Slave (Device Number 9)
  Wire.onReceive(receiveEvent); // register event
}

#endif

