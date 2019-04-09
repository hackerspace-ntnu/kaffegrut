/*
	FILNAVN: kaffe.ino
	FORMÅL: Hovedlogikk som tracker kaffekanners kvalitet.
	ORIGINALFORFATTER: Torstein Nordgård-Hansen
	PÅBEGYNT: 2018
	REQUIREMENTS: Arduino-mikrokontroller
	ENDRINGSLOGG: https://github.com/hackerspace-ntnu/kaffegrut
 */

// Inkluder LCD-bibliotek
#include <LiquidCrystal.h>


// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


int lastTime = 0;


int finnjr = 0;
int matiasito = 0;

bool finnjrValid = false;
bool matiasitoValid = false;


void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  // Print a message to the LCD.
  lcd.print("Finnjr jr   :");
  lcd.setCursor(0, 1);
  lcd.print("Mathiasito:");


  pinMode(7, INPUT);
  pinMode(8, INPUT);
}


void loop() {
  if (digitalRead(7)){ getUpdate(&finnjr, &finnjrValid); }
  if (digitalRead(8)){ getUpdate(&matiasito, &matiasitoValid); }

  if (isTime()){
    if (finnjrValid){
      finnjr += 1;
    }
    if (matiasitoValid){
      matiasito += 1;
    }
  }

  lcd.setCursor(11, 0);
  lcd.print(hrTime(finnjr, &finnjrValid));

  lcd.setCursor(11, 1);
  lcd.print(hrTime(matiasito, &matiasitoValid));
}

String hrTime(int kanne, bool *valid){
  int h = kanne/3600;
  int m = (kanne/60)%60;
  int s = kanne%60;

  if ( h >= 8 ){
    *valid = false;
  }
  
  if ( *valid ){
    return (( h > 9 ? (String)(h): "0"+(String)(h)) + ":" + ( m > 9 ? (String)(m): "0"+(String)(m)));
  }
  else if ( kanne == 0 ){
    return ( "N.A.");
  }
  else {
    return ("8+h ");
  }
}

void getUpdate(int* kannetid, bool* kanneValid){
  *kannetid = millis()/1000;
  *kanneValid = true;
}

bool isTime(){
  if (millis() > 1000 + lastTime && millis() < 100000 + lastTime){
    lastTime = millis();
    return true;
  }
  else if (millis() < lastTime){
    lastTime = 0;
    return true;
  }
  else {
    return false;
  }
}
