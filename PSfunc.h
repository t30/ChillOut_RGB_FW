/*! @file PSfunc.h
 @author Ing. M.Lampugnani
 @par Company:
 MyCompany
 @version 0.0.1-RF brach
 @date 27th july 2011 */
#ifndef	PSFUNC_H
#define	PSFUNC_H

//Se ci sono dati disponibili nel buffer seriale elabora il primo e poi esce.
//dall'esecuzione della funzione
void PSprocess(){
  if (Serial.available() > 0) {
    //system_stat = 1;
    incomingByte = Serial.read();
    if(incomingByte > 32){
      for (int i=0; i < 10; i++){
        com_data[i] = com_data[i+1];
        com_data[10] = '\0';
        //Serial.print(i);
      }
      com_data[9] = incomingByte;

      DBGp_PS(8,"PS incByte==> %c\n", incomingByte);
      //Serial.println(incomingByte,DEC);
      //COMprocess();
      return;
    }
  } 
//Quando non ci sono piu' dati nel buffer da elaborare e l'ultimo byte ricevuto
//e' un terminatore di riga '\n' processa la stringa di dati.
  if( (Serial.available() <= 0) && ( incomingByte == '\n' ) ){
    DBGp_PS(8,"Serial.avail: %u incByte:%u\n", Serial.available(),incomingByte);
    incomingByte = 0;
    COMprocess();
  }
  
}

#endif



