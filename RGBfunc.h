/*! @file Debug.h
 The definition are used to call the main funcion limited to its contest.\n
 Commenting definition you should disable debug.\n
 @author Ing. M.Lampugnani
 @par Company:
 MyCompany
 @version 0.0.1-RF brach
 @date 21th October 2011 */
 
#ifndef	RGB_FUNC_H
#define	RGB_FUNC_H


#define led_on()     r=255;g=255;b=255;rgb();    //rgb(255,255,255)
#define led_off()    r=0;g=0;b=0;rgb();          //rgb(0,0,0)
#define led_red()    r=255;g=0;b=0;rgb();        //rgb(255,0,0)
#define led_green()  r=0;g=255;b=0;rgb();        //rgb(0,255,0)
#define led_blue()   r=0;g=0;b=255;rgb();        //rgb(0,0,255)




#endif

