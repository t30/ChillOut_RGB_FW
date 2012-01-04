/*! @file COM_RF.pde
Function for Serial Port connection (incoming cmd).
 @author Ing. M.Lampugnani
 @par Company:
 MyCompany
 @version 0.0.1-RF brach
 @date 21th October 2011 */

void RFprocess(){
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  //strcpy(com_data,"000000000");
  if ( vw_get_message(buf, &buflen) ){
    //if ( vw_get_message((uint8_t* )com_data, (uint8_t* ) strlen(com_data)) ){
    //for (int i = 0; i < buflen; i++){
    for (int i = 0; i < 10; i++){
      com_data[i] = (char)buf[i];
      //com_data[i+1] = '\0';
    }
    //posiziono il terminatore di stringa per non avere "sporcizia"
    com_data[10] = '\0';
    DBGp_RF(8,"RF data==> %s\n",com_data);
    COMprocess();
  }
}

//#ifdef  RF
void RFsetup(){
  DBGp_RF(5,"setup RF\n", r);
  vw_set_rx_pin(RECV_PIN);
  vw_setup(RF_BIT_PER_SEC);	   // Bits per sec
  vw_rx_start();                   // Start the receiver PLL running
}
//#endif

void RFinit(){
    DBGp_RF(5,"init RF\n", r);
    /*! \arg Settaggio var::GND_PIN */
  pinMode(GND_PIN, OUTPUT);		
  /*! \arg Settaggio var::VCC_PIN */
  pinMode(VCC_PIN, OUTPUT);		
  /*! \arg Settaggio var::STATUS_PIN */
  pinMode(STATUS_PIN, OUTPUT);		
  //!\n

  /*!- Settaggio dello stato dei PIN di alimentazione del ricevitore IR
   \arg Settaggio stato LOW al var::GND_PIN  */
  digitalWrite(GND_PIN, LOW);		
  /*!   \arg Settaggio stato HIGH al pin var::VCC_PIN */
  digitalWrite(VCC_PIN, HIGH);  	
  //!\n
}