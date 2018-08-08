//Autor: Justin Rhyner
//Dateiname: Lauflicht
//Datum: 08.08.2018
//Ich habe ein Kleines Lauflicht gemacht, welches zwei Taster besitzt. Jeder der beiden Taster steht f�r eine Richtung, sobald ein Taster ged�ckt wird startet
//das Lauflicht in die entsprechende Richtung. W�hrent dem betrieb kann mit den gleichen Tasten die Richtung gewechselt werden und sobald beide Taster gedr�ckt
//werden, bleibt das Licht stehen. Sobald nun wieder eine Taste gedr�ckt wird, l�uft das Licht in die entsprechende Richtung weiter.


#include <avr/io.h>
#include <stdlib.h>

uint16_t x=0;
uint16_t wert=0;
uint8_t stop=0;
uint8_t taster=0;
uint8_t anzahl=0;


int main (void) 
{

	DDRB=0xFF; //Ganzer Port B als Ausgang 
	PORTB=0x00; //Alle LEDs ausschalten
	
	DDRC=0x00; //Ganzer Port C als Eingang
	PORTC=0x00; //Alle Ausg�nge auf 0 stellen, da ich externe Pullup-Widerst�nde verwende
	
	while(1)
	{
		if(!(PINC&(1<<PC4))) //Taster 1 abfragen
		{
	//		anzahl++;
			taster=1;
			wert=wert; //wert soll seinen Wert bei behalten
		}
		
		if(!(PINC&(1<<PC5))) //Taster 2 abfragen
		{
			taster=2;
			wert=wert; //wert soll seinen Wert bei behalten
		}
		
		if((!(PINC&(1<<PC4)))&&(!(PINC&(1<<PC5)))) // abfragen der Taster 1 und 2
		{
			taster=3;
			stop=1;
		}
		
		
		
		PORTB=wert;	//ausgabe von wert auf Port B
		for(x=0;x<30000;x++); //Zeitverz�gerung
		
		if(taster==1)
		{
			wert=wert*2; //wert wird mit 2 multipliziert
				
			if(wert>128) //weil wir nur 8 LEDs haben, wird nach 128 wieder bei 1 angefangen
			{
				wert=1;
			}
			
			if(wert==0) // f�r den Anfang muss wert auf 1 gesetzt werden, da man 0 nicht durch 2 teilen kann
			{
				wert=1;
			}
		}
		
		
		if(taster==2)
		{
			wert=wert/2; //wert wird durch 2 dividiert
				
			if(wert==0) // wenn die Zahl 0 erscheint, beginnt es wieder bei 128
			{
				wert=128;
			}
		}
		
		
		if(taster==3) //falls beide taster gedr�ckt werden
		{
			stop=1;    
		}
		
		if(stop==1)
		{
			wert=wert; //die LED bleibt am Ort stehen
		}
		
		
		
		/*
		
		if(anzahl==2)
		{
			wert=wert*4;
		}
		
		if(wert>128) //weil wir nur 8 LEDs haben, wird nach 128 wieder bei 1 angefangen
		{
			wert=1;
		}
		
		if(anzahl>2)
		{
			anzahl=0;
		}
		
		
		*/
		
		
		
	}
	
	return 0;
}