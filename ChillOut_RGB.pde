/*! @file ChillOut-RGB.pde
 @author Ing. M.Lampugnani
 @par Company:
 MyCompany
 @version 0.0.2
 @date 10th march 2011
 */

#include <IRremote.h> 
//#include <avr/pgmspace.h>
#include "ir_RM8S.h"
#include <util/delay.h>
//! Pin di segnalazione POWER On/Off.
#define LEDPP 13 //!< Sul Pin 13 e' gia' connesso sul Circuito Stampato un LED - OUTPUT

//!< @param MCU pin
//pinout PCB
/*! @name INPUT IR PinOut
 //	Defenizione delle connessioni dell IR Receiver all MCU
 // @param MCU pin
 */
//@{
int gnd_pin = 15; 	//!< Pin di massa - OUTPUT
int vcc_pin = 16; 	//!< Pin di alimentazione (5V; 20mA - 40mA MAX) - OUTPUT
int RECV_PIN = 14; 	//!< Pin di ricezione dati - INPUT
//@}

//pinout IR test
//int gnd_pin = 6;	
//int vcc_pin = 7;	
//int RECV_PIN = 5;

/*! @name OUTPUT RGB PinOut
 //	Definizione delle Connessioni dei tre anodi del led RGB
 // @param MCU pin
 */
//@{
int red_pin = 10; 	//!< Pin dell'MCU al quale e' connesso l'anodo Rosso (R) - OUTPUT 
int green_pin = 9; 	//!< Pin dell'MCU al quale e' connesso l'anodo Verde (G) - OUTPUT
int blue_pin = 5; 	//!< Pin dell'MCU al quale e' connesso l'anodo Blu (B)   - OUTPUT
//@}

//! Array da 3 colonne in cui viene appoggiato il comando proveniente dalla seriale
char cmd[] = {
  0, 0, 0};
//! Array da 7 colonne in cui viene appoggiato l'argomento del comando proveniente dalla seriale
char arg[]= {
  0,0,0,0,0,0,0};
//! Variabile di parcheggio per i dati provenienti dalla porta seriale
int incomingByte = 0;

/*! @name Colore Attuale RGB
 //	Variabili in cui vengono salvati i valori da scrivere sull'uscita per generare un colore \n
 //	Dopo aver cambiato il valore di queste variabili, viene chiamata la funzione rgb() per scriverli fisicamente
 // @param [0-255]
 */
//@{
int max_pwm=255;
/*!< Valore massimo assumibile dai colori (1-255); con 0 non si accenderebbe proprio il led.\n Da tenere presente che anche con valor
bassi il led potrebbe non dare segno di vita */
int r=100; //!< Variabile colore Rosso	(Red) - Questa variabile non puo' mai superare il valore di "max_pwm"
int g=100; //!< Variabile colore Verde	(Green) - Questa variabile non puo' mai superare il valore di "max_pwm"
int b=100; //!< Variabile colore Blu	(Blue) - Questa variabile non puo' mai superare il valore di "max_pwm"
//@}

//!  Numero massimo di stati in cui si puo' trovare il sistema.
/*!      Da tenere presente che sebbene lo stato 0 indichi il LED spento, anche lo 0 e' uno stato a tutti gli effetti
 - 0 = off 
 - 1 = static color
 - 2 = rand_col function
 - 3 = flash function
 */
#define MAX_STATUS 3 
//! Attesa fra un comando e l'altro ricevuto via IR.
#define BTNDELAY 500 //!< Numero di millisecondi da aspettare dopo la pressione di un tasto prima di prendere un nuovo comando via IR
int system_stat = 0; //!< Codice stato attuale in cui si trova il sistema

//! Creo un'istanza per la classe IRrecv
IRrecv irrecv(RECV_PIN); //!< Alla quale devo passare come argomento il pin sul quale arriveranno i dati dal ricevitore (RECV_PIN).

decode_results results;

/*!
 Funzione impiegata nella decodifica dei dati provenienti dal ricevitore IR
 @param[in]  value  Dati provenienti dal Ricevitore IR
 */
//! Decodifica dati provenienti dal ricevitore IR
unsigned long decode(unsigned long value){
  unsigned int b0 = (value&0xff00)>>8;
  unsigned int b1 = (value&0x00ff);
  //  Serial.print("Value b0= ");
  //  Serial.println(b0, HEX);
  //  Serial.print("Value b1= ");
  //  Serial.println(b1, HEX);
  unsigned int ret = -1;
  for (int i=0; i < 7; i++) {
    if(b1 == myBtn[i][0]){
      if (myBtn[i][1] <= 7 && myBtn[i][1] > 0) {
        switch(myBtn[i][1]){

        case 1://!	@arg FUNCTION power button
          {
            if(system_stat == 0){
              rgb();
              system_stat = 1;
              Serial.println("ON");
            } 
            else {
              analogWrite(red_pin,0);
              analogWrite(green_pin,0);
              analogWrite(blue_pin,0);
              system_stat = 0;
              Serial.println("OFF");
            } 
            delay(BTNDELAY);
            break;
          }
        case 2: //!	@arg FUNCTION AV/TV/VCR button
          {
            if(system_stat < MAX_STATUS){
              system_stat++;
            } 
            else {
              system_stat = 1;
            }
            Serial.print("newstatus: ");
            Serial.println(system_stat);
            delay(BTNDELAY);
            break;
          }
        case 3: //!	@arg FUNCTION up button
          {
            Serial.println("up");
            break;
            delay(BTNDELAY);
          }
        case 4: //!	@arg FUNCTION - button
          {
            if(max_pwm > 0){
              max_pwm = max_pwm - 25;
            } 
            Serial.print("pwm-: ");
            Serial.println(max_pwm);
            break;
          }
        case 5: //!	@arg FUNCTION up button
          {
            Serial.println("mute"); 
            delay(BTNDELAY);
            break;
          }
        case 6: //!	@arg FUNCTION + button
          {
            if(max_pwm < 255){
              max_pwm = max_pwm + 25;
            } 
            Serial.print("pwm+: ");
            Serial.println(max_pwm);
            break;
          }
        case 7: //!	@arg FUNCTION up button
          {
            Serial.println("down"); 
            delay(BTNDELAY);
            break;
          }
        }
      }
      ret = myBtn[i][1];
      continue;
      //ret = i;
    }
  }
  return ret;
  //return value;
}

/*!
 Dopo che i valori da scrivere sul led vengono "appoggiati" nelle variabili r, g, b; 
 viene chiamata questa funzione che materialmente scrive i valori sulle uscite PWM indicate nelle var *_pin
 */
//! Funzione scrittura colore su I/O
void rgb() {
  /*!
   <b> Operazioni eseguite dalla funzione: </b>
   */
  /*!
   - Scrittura fisica dei valori di PWM da applicare ai pin
   \arg Scrittura red_pin 
   */
  analogWrite(red_pin,r);
  /*!
   \arg Scrittura green_pin 
   */
  analogWrite(green_pin,g);
  /*!
   \arg Scrittura blue_pin 
   */
  analogWrite(blue_pin,b);
}

/*!
 Con sfumatura nei colori intermedi
 */
//! Passaggio dal colore attuale ad uno RANDOM
void rand_col() {
  randomSeed(analogRead(0));
  // randomSeed((r+0)*(g+0)*(b+0));
  int color,i,value,time=10; // how long does it take each step
  color=random(1,4); // which color to dim now
  value=random(0,max_pwm); // new value of that color
  switch(color) {
  case 1:
    if(r>value) for(i=r;i>value;i--) {
      r = i;
      rgb();
      delay(time);
    }
    else for(i=r;i<value;i++) {
      r = i;
      rgb();
      delay(time);
    }
    r=value;
    break;
  case 2:
    if(g>value) for(i=g;i>value;i--) {
      g = i;
      rgb();
      delay(time);
    }
    else for(i=g;i<value;i++) {
      g = i;
      rgb();
      delay(time);
    }
    g=value;
    break;
  case 3:
    if(b>value) for(i=b;i>value;i--) {
      b = i;
      rgb();
      delay(time);
    }
    else for(i=b;i<value;i++) {
      b = i;
      rgb();
      delay(time);
    }
    b=value;
    break;
  }
  // delay(3000); // some time before next change
}

/*!
 Fa Lampeggiare il LED in modo Random\n
 Prendendo i parametri che gli vengono passati come base per generare i sui impulsi
 @param[in] ledmax		Massima Luminosita' del led [var::max_pwm]
 @param[in] pulselensec 	Durata degli impulsi
 @param[in] freqmin 		Frequenza minima 
 @param[in] freqmax		Frequnza massima
 */
//!  Flash colori RANDOM
void bedazzle(int ledmax, int pulselensec, int freqmin, int freqmax) {
  long pulses;
  /*!
   <b> Operazioni eseguite dalla funzione: </b>
   
   */
  /*!
   - Init - Spegne il LED 
   */
  r=0;
  g=0;
  b=0;
  rgb();
  // analogWrite(redpin1, 0);
  // analogWrite(redpin2, 0);
  // analogWrite(greenpin1, 0);
  // analogWrite(greenpin2, 0);
  // analogWrite(bluepin1, 0);
  // analogWrite(bluepin2, 0);
  //
  // note we dont use red LEDs in this
  /*!
   - Setup - Calcola i parametri necessari al suo funzionamento:
   \arg Sceglie Random la frequenza di funzionamento
   */
  int freq = random(freqmin, freqmax+1);
  int pulsedelay = 1000/freq;
  /*!
   \arg Si calcola di conseguenza la durata di ogni stato (ON-OFF visto che lampeggia)
   */
  pulsedelay /= 2;
  /*!
   \arg Si calcola di conseguenza la durata di ogni impulso
   */
  pulses = pulselensec;
  pulses *= 100;
  pulses /= 2*pulsedelay;
  // Serial.print("pulsing at ");
  // Serial.print(freq, DEC);
  // Serial.print(" Hz (");
  // Serial.print(pulsedelay, DEC);
  // Serial.println(" ms on/off)");
  // Serial.print(pulses);
  // Serial.println(" pulses");
  while (pulses--) {
    /*!
     - Loop - Cambia ciclicamente il colore del LED:
     \arg Sceglie Random e successivamente scrive i valori di var::r, var::g, var::b in un range compreso fra 0 e ledmax
     */
    r=random(0,ledmax);
    g=random(0,ledmax);
    b=random(0,ledmax);
    rgb();
    /*!
     \arg Resta in attesa per un tempo pari alla durata di ogni stato
     */
    _delay_ms(pulsedelay);
    /*!
     \arg Spegne il LED 
     */
    r=0;
    g=0;
    b=0;
    rgb();
    //_delay_ms(pulsedelay);
    /*!
     \arg Se lo stato del sistema e' cambiato esce dal loop (contenuto nella variabile var::system_stat )
     */
    if (system_stat != 2) return;
  }
}

//! Funzione di Setup del dipositivo (init)
void setup()
{
  /*!
   <b> Operazioni eseguite dalla funzione: </b>
   */
  /*!
   - Settaggio dei pin di OUTPUT
   \arg Settaggio red_pin 
   */
  pinMode(red_pin, OUTPUT);		
  /*! \arg Settaggio green_pin */
  pinMode(green_pin, OUTPUT);		
  /*! \arg Settaggio blue_pin */
  pinMode(blue_pin, OUTPUT);		
  /*! \arg Settaggio gnd_pin */
  pinMode(gnd_pin, OUTPUT);		
  /*! \arg Settaggio vcc_pin */
  pinMode(vcc_pin, OUTPUT);		
  /*! \arg Settaggio LEDPP */
  pinMode(LEDPP, OUTPUT);		
  //!\n
  /*!
   - Settaggio dello stato dei PIN di alimentazione del ricevitore IR
   \arg Settaggio stato LOW al gnd_pin
   */
  digitalWrite(gnd_pin, LOW);		
  /*!   \arg Settaggio stato HIGH al pin vcc_gnd */
  digitalWrite(vcc_pin, HIGH);  	
  //!\n
  /*!
   - Start-up porta seriale e ricevitore IR
   	\arg Avvio della porta seriale
   */
  Serial.begin(9600); 
  /*!	\arg Invio sulla porta del messaggio "enabling IR"*/
  Serial.println("enabling IR ");	
  /*!	\arg Avvio fisico della ricezione via IR*/
  irrecv.enableIRIn(); 			
  /*!	\arg Accensione del LED di stato LEDPP*/
  digitalWrite(LEDPP,HIGH);		
  // rgb(0,0,255);
  //delay(3000);
  // Serial.begin(9600);
}

//! Funzione Principale del dipositivo (main)
void loop()
{
  if (irrecv.decode(&results)) {

    //Serial.println(results.value, HEX);
    int result = decode(results.value);
    //    if (result != -1 && result != 11 && result != 15 && result != 19 && result != 23){
    //      system_stat = 0;
    //    }
    Serial.print("Pressed button: ");
    Serial.println(result);
    //    Serial.print("resume receiver: ");
    irrecv.resume(); // Receive the next value
    //    Serial.println("OK");
  }
  if (system_stat == 2) {
    rand_col();
  }

  if (system_stat == 3) {
    bedazzle(max_pwm, 10, 7, 11);
  }

  if (Serial.available() > 0) {
    system_stat = 1;
    incomingByte = Serial.read();
    for (int i=0; i < 3; i++){
      cmd[i] = cmd[i+1];
      cmd[3] = '\0';
    }
    cmd[2] = incomingByte;
    //Serial.println(cmd);
    if(cmd[0] == 's' && cmd[1] == 'e' && cmd[2] == 't'){
      system_stat = 0;
      Serial.println("setting");
      if (Serial.available() > 0) {
        for(int i=0; i<2;i++){
          arg[i]=Serial.read();
        }
      }
      if(arg[1] == '1') {
        r=255;
        g=255;
        b=255;
        rgb();
      }
      if(arg[1] == '0') {
        r=0;
        g=0;
        b=0;
        rgb();
      }
    }
    if(cmd[0] == 'p' && cmd[1] == 'r' && cmd[2] == 'g'){
      Serial.println("program");
      if (Serial.available() > 0) {
        for(int i=0; i<2;i++){
          arg[i]=Serial.read();
        }
      }
      if(arg[1] == 'R') {
        system_stat = 2;
      }
      if(arg[1] == 'F') {
        system_stat = 3;
      }
    }
    if(cmd[0] == 't' && cmd[1] == 'r' && cmd[2] == 'i'){
      system_stat = 0;
      Serial.println("tricolor");
      if (Serial.available() > 0) {
        for(int i=0; i<2;i++){
          arg[i]=Serial.read();
        }
      }
      if(arg[1] == 'r') {
        r=255;
        g=0;
        b=0;
        rgb();
      }
      if(arg[1] == 'g') {
        r=0;
        g=255;
        b=0;
        rgb();
      }
      if(arg[1] == 'b') {
        r=0;
        g=0;
        b=255;
        rgb();
      }
      if(arg[1] == 'w') {
        r=255;
        g=255;
        b=255;
        rgb();
      }
    }
    if(cmd[0] == 'r' && cmd[1] == 'g' && cmd[2] == 'b'){
      system_stat = 0;
      Serial.println("rgb-16M");
      if (Serial.available() > 0) {
        for(int i=0; i<7;i++){
          arg[i]=Serial.read();
        }
      }

      //RED stuff
      if(arg[1]>=48 && arg[1]<=57){
        r = int(arg[1])-48;
        r = r << 4;
      }
      else if(arg[1]>=65 && arg[1]<=70){
        r = int(arg[1])-55;
        r = r << 4;
      }
      if(arg[2]>=48 && arg[2]<=57){
        r = r + int(arg[2])-48;
      }
      else if(arg[2]>=65 && arg[2]<=70){
        r = r + int(arg[2])-55;
      }

      //GREEN stuff
      if(arg[3]>=48 && arg[3]<=57){
        g = int(arg[3])-48;
        g = g << 4;
      }
      else if(arg[3]>=65 && arg[3]<=70){
        g = int(arg[3])-55;
        g = g << 4;
      }
      if(arg[4]>=48 && arg[4]<=57){
        g = g + int(arg[4])-48;
      }
      else if(arg[4]>=65 && arg[4]<=70){
        g = g + int(arg[4])-55;
      }

      //BLUE stuff
      if(arg[5]>=48 && arg[5]<=57){
        b = int(arg[5])-48;
        b = b << 4;
      }
      else if(arg[5]>=65 && arg[5]<=70){
        b = int(arg[5])-55;
        b = b << 4;
      }
      if(arg[6]>=48 && arg[6]<=57){
        b = b + int(arg[6])-48;
      }
      else if(arg[6]>=65 && arg[6]<=70){
        b = b + int(arg[6])-55;
      }

      //print to serial and apply the color
      Serial.print("#");
      Serial.print(r,HEX);
      Serial.print(g,HEX);
      Serial.print(b,HEX);
      rgb();
    }
  }
}

