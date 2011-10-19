/*! @file RGBfunc.h
 @author Ing. M.Lampugnani
 @par Company:
 MyCompany
 @version 0.0.1-RF brach
 @date 9th august 2011 */
#ifndef	RGBFUNC_H
#define	RGBFUNC_H

#define led_on()     r=255;g=255;b=255;rgb();    //rgb(255,255,255)
#define led_off()    r=0;g=0;b=0;rgb();          //rgb(0,0,0)
#define led_red()    r=255;g=0;b=0;rgb();        //rgb(255,0,0)
#define led_green()  r=0;g=255;b=0;rgb();        //rgb(0,255,0)
#define led_blue()   r=0;g=0;b=255;rgb();        //rgb(0,0,255)

#define Winc         r++;g++;b++;
#define Wdec         r--;g--;b--;

/*! Dopo che i valori da scrivere sul led vengono "appoggiati" nelle variabili r, g, b; 
 viene chiamata questa funzione che materialmente scrive i valori sulle uscite PWM indicate nelle var *_pin  */
//! Funzione scrittura colore su I/O
void rgb() {
  /*!  <b> Operazioni eseguite dalla funzione: </b>  */
  /*!  - Scrittura fisica dei valori di PWM da applicare ai pin
   \arg Scrittura RED_PIN  */
  analogWrite(RED_PIN,r);
  /*!  \arg Scrittura GREEN_PIN  */
  analogWrite(GREEN_PIN,g);
  /*!  \arg Scrittura BLUE_PIN  */
  analogWrite(BLUE_PIN,b);

}

/*!  Con sfumatura nei colori intermedi  */
//! Passaggio dal colore attuale ad uno RANDOM
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
  case DYN_COL_OFF:
    randomSeed(analogRead(0));
    DYNcolor = random(1, (DYN_COL_MAX+1) );
    DESTvalue = random(0,max_pwm);
    break;
  case DYN_COL_ERR:
    break;
  }
  rgb();
}

/*!  Effetto fading su singolo colore (R-G-B-W) */
//! Passaggio graduale fra diverse tonalita' del colore attualmente piu' forte
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
  case DYN_COL_OFF:
    if(r>g && r>b)    DYNcolor=DYN_COL_RED;
    if(g>r && g>b)    DYNcolor=DYN_COL_GREEN;
    if(b>g && b>r)    DYNcolor=DYN_COL_BLUE;
    if(r==g && r==b)  DYNcolor=DYN_COL_WHITE;
    DESTvalue = random(1,max_pwm);
    break;
  case DYN_COL_ERR:
    break;
  }
  rgb();
}

/*!  Effetto fading su giro colori (R-G-B) */
//! Passaggio graduale fra diverse tonalita' del colore attuale
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

#endif


