/*! @file RFfunc.h
 @author Ing. M.Lampugnani
 @par Company:
 MyCompany
 @version 0.0.1-RF brach
 @date 27th july 2011 */
#ifndef	RFFUNC_H
#define	RFFUNC_H

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

#endif







