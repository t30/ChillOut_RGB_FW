/*! @file COM_Base.ino
 This file contain the function need to processing data from all kind of comunication protocol.\n
 All data was put by adhoc function in data_com array.\n
 With the content of this file let's process it!
 @author Ing. M.Lampugnani
 @par Company:
 MyCompany
 @version 0.0.1-RF brach
 @date 21th October 2011 */

//!  Converte un esadecimale char in un integer
int HEXcharTOint(char base){
  unsigned int color;
  if(base>='0' && base<='9'){
    color = int(base)-'0';
  }
  else if(base>='a' && base<='f'){
    color = int(base)-'a'+10;
  }
  else if(base>='A' && base<='F'){
    color = int(base)-'A'+10;
  }
  return color;
}

int HEXtoRGB(char first,char second){
  int final = 0;
  char value[]={
    second, first };
  for(int i = 0; i < 2; i++){
    final = final + ( HEXcharTOint(value[i]) << (4*i) ); 
  }
  //return constrain(final, 0, 255);
  return final;
}

unsigned long HEXtoPeriod(char first,char second, char third){
  int final = 0;
  char value[]={
    third, second, first };
  for(int i = 0; i < 3; i++){
    final = final + ( HEXcharTOint(value[i]) << (4*i) ); 
  }
  //return constrain(final, 0, 255);
  return final;
}

bool CheckTarget(char IdDev[3]){
  if(HEXcharTOint(IdDev[0]) == dev_Ig){
    return 1; 
  } 
  else if(HEXtoRGB(IdDev[1], IdDev[2]) == dev_Id || HEXtoRGB(IdDev[1], IdDev[2]) == 255) {
    return 1; 
  } 
  else {
    return 0;
  }

}

//! Processa i dati presenti nel buffer di ricezione
/*! I dati provenienti dalle comunicazioni che possono essere disponibili sul dispositivo vengono parcheggiati nel buffer var::com_data .\n
 Le funzioni di processing dei vari protocolli (eg. PSProcess) dopo aver completato l'aggiornamento del buffer, chiamano questa funzione per l'esecuzione condizionata dei comandi.\n  */
void COMprocess(){
  DBGp_COM(7,"%s#EOL\n",com_data);

  //Set period for clock task
  if(com_data[0] == 'c' && com_data[1] == 'l' && com_data[2] == 'k'){
    DBGp_COM(0,"clock setting=> clk: %c\n", com_data[4]);
    switch(com_data[4]){
    case'0':      
      //fast task res 1ms (from 1 to 4097 msec)
      fastPeriod = (HEXtoPeriod(com_data[5],com_data[6],com_data[7]) + 1) ;
      DBGp_COM(0,"NewPeriodFast setting (ms)=> clk: %u\n", fastPeriod);
      FastTask.interval(fastPeriod);
      break;
    case'1':      
      //slow task  res 1s (1000ms) (from 1 to 4096 sec)
      slowPeriod = ((HEXtoPeriod(com_data[5],com_data[6],com_data[7]) + 1)*1000) ;
      DBGp_COM(0,"NewPeriodSlow setting (ms)=> clk: %u\n", slowPeriod);
      SlowTask.interval(slowPeriod);
      break;
    case'2':      
      //slow task  res 1s (1000ms) (from 1 to 4096 sec)
      logPeriod = ((HEXtoPeriod(com_data[5],com_data[6],com_data[7]) + 1)*1000) ;
      DBGp_COM(0,"NewPeriodLog setting (ms)=> clk: %u\n", logPeriod);
      LogTask.interval(logPeriod);
      break;
    default:
      DBGp_ERR(1,"ERR clk=> char not recognized: %c\n", com_data[4]);
    }
  }

  //Set new debug level. 0 < debugL < 9
  if(com_data[0] == 'd' && com_data[1] == 'b' && com_data[2] == 'g'){
    DBGp_COM(0,"DGB=> lvl: %c\n", com_data[4]);
    debugL = constrain( com_data[4]-'0', 0, 9);    
  }

  //Set dynamic color state
  if(com_data[0] == 'p' && com_data[1] == 'r' && com_data[2] == 'g'){
    DBGp_COM(0,"program=> set: %c\n", com_data[4]);
    switch(com_data[4]){
    case'R':		//random
      system_stat = STAT_RAND;
      break;
    case'F':		//flash
      system_stat = STAT_FLASH;
      break;
    case'U':		//ufo
      system_stat = STAT_UFO;
      break;
    case'C':		//circle
      system_stat = STAT_CIRCLE;
      break;
    default:
      DBGp_ERR(1,"ERR prg=> char not recognized: %c\n", com_data[4]);
    }
    ReInitDynVars();
  }

  //Set new max_pwm val used by dynamyc color function
  if(com_data[0] == 'p' && com_data[1] == 'w' && com_data[2] == 'm'){
    max_pwm = HEXtoRGB(com_data[4],com_data[5]);
    DBGp_COM(0,"MaxPWMSetting=> set: %u\n", max_pwm);
  }

  //Set new full RGB color
  if(com_data[0] == 'r' && com_data[1] == 'g' && com_data[2] == 'b'){
    system_stat = STAT_STATIC;
    r = HEXtoRGB(com_data[4],com_data[5]);
    g = HEXtoRGB(com_data[6],com_data[7]);
    b = HEXtoRGB(com_data[8],com_data[9]);
    rgb();
    DBGp_COM(0,"rgb-16M=> r:%u g:%u b:%u\n", r, g, b);
  }

  //Set new Static state
  if(com_data[0] == 's' && com_data[1] == 'e' && com_data[2] == 't'){
    DBGp_COM(0,"setting=> system_stat: %c\n", com_data[4]);
    if(com_data[4] == '1') {
      led_on();
      system_stat = STAT_STATIC;
    }
    if(com_data[4] == '0') {
      led_off();
      system_stat = STAT_OFF;
    }
    if(com_data[4] == 'D') {
    dev_Ig = HEXcharTOint(com_data[5]);
    dev_Id = HEXtoRGB(com_data[6],com_data[7]);
    }
    if(com_data[4] == 'T') {
      tickTIMER = HEXcharTOint(com_data[5]);
      if(tickTIMER>0){
        blinkEnable(1);
      }
      else{
        blinkEnable(0);
      }
      DBGp_COM(0,"AutoPOWERoff next ticks: %u\n", tickTIMER);
    }
    if(com_data[4] == 'R') {
      DBGp_COM(0,"Reset Requested...\n", tickTIMER);
      void(* resetFunc) (void) = 0; //declare reset function @ address 0
      resetFunc();  //call reset
    }
  }

  //Set pure color
  if(com_data[0] == 't' && com_data[1] == 'r' && com_data[2] == 'i'){
    system_stat = STAT_STATIC;
    DBGp_COM(0,"tricolor=> set: %c\n", com_data[4]);
    switch(com_data[4]){
    case'r':      
      led_red();  
      break;
    case'g':      
      led_green();  
      break;
    case'b':      
      led_blue();  
      break;
    case'w':      
      led_on();  
      break;
    default:
      DBGp_ERR(1,"ERR tri=> char not recognized: %c\n", com_data[4]);
    }
  }

  //strcpy(com_data,"000000000");
}










