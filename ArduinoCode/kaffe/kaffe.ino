
/*
	FILNAVN: kaffe.ino
	FORMÅL: Hovedlogikk som tracker kaffekanners kvalitet.
	ORIGINALFORFATTER: Torstein Nordgård-Hansen
	PÅBEGYNT: 2018
	REQUIREMENTS: Arduino-mikrokontroller
	NAVNGIVNING:
	 * Skal baseres på suffix etter følgende kriterier:
	 * Dersom en kaffekanne blir knust eller på annet vis må erstattes,
	 * skal den følge samme navngivning som tidligere med tall etter romersk
	 * tallsystem som indikerer generasjonen.
	 * Eksempel: Finn III blir på tragisk vis skutt av en politi-robot i
	 * fremtidens dystopiske samfunn, så da blir nye kannen døpt Finn IV. 
	ENDRINGSLOGG: https://github.com/hackerspace-ntnu/kaffegrut
 */

// Inkluder LCD-bibliotek
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


int finn = 0;
int matias = 0;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  // Print a message to the LCD.
  lcd.print("Finn jr   :");
  lcd.setCursor(0, 1);
  lcd.print("Mathiasito:");


  pinMode(7, INPUT);
  pinMode(8, INPUT);
}

void loop() {
  getUpdate(&finn, &matias);
  
  lcd.setCursor(11, 0);
  lcd.print(hrTime((millis()/1000) , finn));

  lcd.setCursor(11, 1);
	lcd.print(hrTime((millis()/1000) , matias));
}

String hrTime(int seconds, int kanne){
  int h = (seconds - kanne)/3600;
  int m = ((seconds - kanne)/60)%60;
	int s = (seconds - kanne)%60;
  
	return ( (kanne == 0 || (seconds - kanne < 0)) ? " N.A." : ( (h >= 5 ? "  old" :  ( h > 9 ? (String)(h): "0"+(String)(h)) + ":" + ( m > 9 ? (String)(m): "0"+(String)(m)))));
}

void getUpdate(int *finn, int *matias){
  if (digitalRead(7)){ *finn = millis()/1000;}
  if (digitalRead(8)){ *matias = millis()/1000;}
}

