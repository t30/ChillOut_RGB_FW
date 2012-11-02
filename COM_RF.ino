/*! @file COM_RF.ino
Function for RF connection (incoming cmd).
 @author Ing. M.Lampugnani
 @par Company:
 MyCompany
 @version 0.0.1-RF brach
 @date 21th October 2011 */

#if defined BUILD_COMM_RF

//! Process RF data
void RFprocess(){
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  //strcpy(com_data,"000000000");
  if ( vw_get_message(buf, &buflen) ){
    DBGp_RF(8,"buflen: %u buf:%s\n",VW_MAX_MESSAGE_LEN,buf);

    for (int i = 0; i < buflen; i++){
      if(i<10){ //process data
        com_data[i] = (char)buf[i];
      } 
      else if(i>=10 || i<=12) {  //ident data
        com_Id[i-10] = (char)buf[i];
      }
      else {  
        //do nothing
      }
    }
    com_data[10] = '\0';
    com_Id[3] = '\0';

    DBGp_RF(5,"data: %s, Id: %s\n",com_data, com_Id);

    //Checking Dev and Group
    if (CheckTarget(com_Id)){
      COMprocess();
      DBGp_RF(8,"RF data==> %s\n",com_data);
    }

  }
}

//! Setup RF comunication service
void RFsetup(){
  DBGp_RF(5,"setup RF dev:%u - grp:%u\n", dev_Id,dev_Ig);
  vw_set_rx_pin(RECV_PIN);
  vw_setup(RF_BIT_PER_SEC);	   // Bits per sec
  vw_rx_start();                   // Start the receiver PLL running
}

//! Init RF comunication service
void RFinit(){
  DBGp_RF(5,"init RF\n", r);
  /*! \arg Settaggio var::GND_PIN */
  pinMode(GND_PIN, OUTPUT);		
  /*! \arg Settaggio var::VCC_PIN */
  pinMode(VCC_PIN, OUTPUT);				
  //!\n

  /*!- Settaggio dello stato dei PIN di alimentazione del ricevitore IR
   \arg Settaggio stato LOW al var::GND_PIN  */
  digitalWrite(GND_PIN, LOW);		
  /*!   \arg Settaggio stato HIGH al pin var::VCC_PIN */
  digitalWrite(VCC_PIN, HIGH);  	
  //!\n

//  DBGp_RF(5,"Dev: %u - Group: %u\n",dev_Id,dev_Ig);
}

#endif







