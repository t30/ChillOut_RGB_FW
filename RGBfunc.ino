/*! @file RGBfunc.ino
 @author Ing. M.Lampugnani
 @par Company:
 MyCompany
 @version 0.0.1-RF brach
 @date 21th October 2011 */

#define Winc         r++;g++;b++;
#define Wdec         r--;g--;b--;

//! Init RGB LED
void RGBinit(){
  /*!  - Settaggio dei pin di OUTPUT  
   \arg Settaggio var::RED_PIN  */
  pinMode(RED_PIN, OUTPUT);		
  /*! \arg Settaggio var::GREEN_PIN */
  pinMode(GREEN_PIN, OUTPUT);		
  /*! \arg Settaggio var::BLUE_PIN */
  pinMode(BLUE_PIN, OUTPUT);
}

/*! Funzione che emette tre lampeggi da 200ms dei tre colori principali del led*/
//! Funzione di test LED RGB
void LedInitTest() {
  led_off();
  led_red();
  delay(DELAY_INIT_TEST_ON);
  led_off();
  delay(DELAY_INIT_TEST_OFF);
  led_green();
  delay(DELAY_INIT_TEST_ON);
  led_off();
  delay(DELAY_INIT_TEST_OFF);
  led_blue();
  delay(DELAY_INIT_TEST_ON);
  led_off();
}

/*! Dopo che i valori da scrivere sul led vengono "appoggiati" nelle variabili r, g, b; 
 viene chiamata questa funzione che materialmente scrive i valori sulle uscite PWM indicate nelle var *_pin  */
//! Funzione scrittura colore su I/O
void rgb() {
  /*!  <b> Operazioni eseguite dalla funzione: </b>  */
  /*!  - Scrittura fisica dei valori di PWM da applicare ai pin
   \arg Scrittura var::RED_PIN  */
  analogWrite(RED_PIN,r);
  /*!  \arg Scrittura var::GREEN_PIN  */
  analogWrite(GREEN_PIN,g);
  /*!  \arg Scrittura var::BLUE_PIN  */
  analogWrite(BLUE_PIN,b);

}

//! Passaggio dal colore attuale ad uno RANDOM
/*! Con sfumatura nei colori intermedi  */
void RGBrandom(){
  switch(DYNcolor){
  case DYN_COL_RED:
    if(r < DESTvalue)  r++;
    if(r > DESTvalue)  r--;
    if(r == DESTvalue) DYNcolor = DYN_COL_OFF;
    break;
  case DYN_COL_GREEN:
    if(g < DESTvalue)  g++;
    if(g > DESTvalue)  g--;
    if(g == DESTvalue) DYNcolor = DYN_COL_OFF;
    break;
  case DYN_COL_BLUE:
    if(b < DESTvalue)  b++;
    if(b > DESTvalue)  b--;
    if(b == DESTvalue) DYNcolor = DYN_COL_OFF;
    break;
  case DYN_COL_INIT:
  case DYN_COL_OFF:
    if(r + g + b > 510){ //! @todo non sarebbe meglio mettere come soglia max_pwm*2??
      if(r > g && r > b){
        DYNcolor = DYN_COL_RED;
        DESTvalue = 0;
      }
      else if(g > r && g > b){
        DYNcolor = DYN_COL_GREEN;
        DESTvalue = 0;
      } //! @todo questo else alla fine fa si che il blu capiti molto meno spesso... RIVEDERE
      else{ //(b > r && b > g){
        DYNcolor = DYN_COL_BLUE;
        DESTvalue = 0;
      }
    }
    else{
      randomSeed(analogRead(RANDOM_PIN));
      DYNcolor = random(1, (DYN_COL_MAX+1) );
      DESTvalue = random(0,max_pwm);
    }
    break;
  case DYN_COL_ERR:
    break;
  }
  rgb();
}

//! Passaggio rapido dei colori in modalita' RANDOM
/*! Flash random nei colori primari (R-G-B)  */
void RGBflash(){
  switch(DYNcolor){
  case DYN_COL_RED:
    r = max_pwm;
    DYNcolor = DYN_COL_OFF;
    break;
  case DYN_COL_GREEN:
    g = max_pwm;
    DYNcolor = DYN_COL_OFF;
    break;
  case DYN_COL_BLUE:
    b = max_pwm;
    DYNcolor = DYN_COL_OFF;
    break;
  case DYN_COL_INIT:
  case DYN_COL_OFF:
    r = 0;
    g = 0;
    b = 0;
    randomSeed(analogRead(RANDOM_PIN));
    DYNcolor = random(1, (DYN_COL_MAX+1) );
    break;
  case DYN_COL_ERR:
    break;
  }
  rgb();
}

//! Passaggio random graduale fra diverse tonalita' del colore attualmente piu' forte
/*! Effetto fading su singolo colore (R-G-B-W) */
void RGBufo(){
  switch(DYNcolor){
  case DYN_COL_WHITE:
    if(r < DESTvalue)  {
      r++;
      g++;
      b++;
    }
    if(r > DESTvalue)  {
      r--;
      g--;
      b--;
    }
    if(r == DESTvalue) DYNcolor = DYN_COL_OFF;
    break;
  case DYN_COL_RED:
    if(r < DESTvalue)    r++;
    if(r > DESTvalue)    r--;
    if(g > 0)            g--;
    if(b > 0)            b--;
    if(r == DESTvalue) DYNcolor = DYN_COL_OFF;
    break;
  case DYN_COL_GREEN:
    if(g < DESTvalue)    g++;
    if(g > DESTvalue)    g--;
    if(r > 0)            r--;
    if(b > 0)            b--;
    if(g == DESTvalue) DYNcolor = DYN_COL_OFF;
    break;
  case DYN_COL_BLUE:
    if(b < DESTvalue)    b++;
    if(b > DESTvalue)    b--;
    if(r > 0)            r--;
    if(g > 0)            g--;
    if(b == DESTvalue) DYNcolor = DYN_COL_OFF;
    break;
  case DYN_COL_INIT:
  case DYN_COL_OFF:
    if(r>g && r>b)    DYNcolor=DYN_COL_RED;
    if(g>r && g>b)    DYNcolor=DYN_COL_GREEN;
    if(b>g && b>r)    DYNcolor=DYN_COL_BLUE;
    if(r==g && r==b)  DYNcolor=DYN_COL_WHITE;
    randomSeed(analogRead(RANDOM_PIN));
    DESTvalue = random(1,max_pwm);
    break;
  case DYN_COL_ERR:
    break;
  }
  rgb();
}

//! Passaggio graduale fra diverse tonalita' del colore attuale
/*! Effetto fading su giro colori (R-G-B) */
void RGBcircle(){
  switch(DYNcolor){
  case DYN_COL_RED:
    if(r < DESTvalue)    r++;
    if(r > DESTvalue)    r--;
    if(g > 0)            g--;
    if(b > 0)            b--;
    if(r == DESTvalue) DYNcolor = DYN_COL_OFF;
    break;
  case DYN_COL_GREEN:
    if(g < DESTvalue)    g++;
    if(g > DESTvalue)    g--;
    if(r > 0)            r--;
    if(b > 0)            b--;
    if(g == DESTvalue) DYNcolor = DYN_COL_OFF;
    break;
  case DYN_COL_BLUE:
    if(b < DESTvalue)    b++;
    if(b > DESTvalue)    b--;
    if(r > 0)            r--;
    if(g > 0)            g--;
    if(b == DESTvalue) DYNcolor = DYN_COL_OFF;
    break;
  case DYN_COL_INIT:
    DYNcolor=DYN_COL_RED;
    break;
  case DYN_COL_OFF:
    if(r>g && r>b)    DYNcolor=DYN_COL_GREEN;
    if(g>r && g>b)    DYNcolor=DYN_COL_BLUE;
    if(b>g && b>r)    DYNcolor=DYN_COL_RED;
    if(r==g && r==b)  DYNcolor=DYN_COL_RED;  // exception
    DESTvalue = 255;
    //DESTvalue = random(1,max_pwm);
    break;
  case DYN_COL_ERR:
    break;
  }
  rgb();
}







