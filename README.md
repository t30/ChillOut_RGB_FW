ChillOut_RGB ambient lamp project
=================================
Chillout RGB is a complete project to build a full 16.8M Color
by yourserf and control it using a Serial Port with its control 
software or a IR remote

This is the Firmware's repositories

Complete description (it):
http://blog.lampugnani.org/arduino/chillout-rgb-ambient-lamp/

RF branch
=========
This brach will enable, with right hardware, to receive command through
RF board.

Cooking List:
--------------
* Of course, an arduino or a dedicated device (like ChillOut RGB - (it) http://blog.lampugnani.org/project/chillout-rgb-new-pcb/).
* An RGB led (suitable for your driver).
	if you use a 20mA/channel RGB led, you only need a led and 3 limiter resistor
	otherwise you will need a led and suitable power controller.
* Arduino IDE.(you may need to add wirig.c in your tree folder)
* Processing IDE (optional).
	Using a terminal emulator (like HiperTerminal,putty (win) and minicom (linux))
	you are able to send and receive command.
* Metro lib. (you may need to edit some line of code)
* VirtualWire lib.



author: Ing. M.Lampugnani
-------------------------