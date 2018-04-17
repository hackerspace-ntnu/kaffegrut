// include the library code:
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
  lcd.print("Finn jr:");
  lcd.setCursor(0, 1);
  lcd.print("Mathias:");

  pinMode(7, INPUT);
  pinMode(8, INPUT);

}

void loop() {
  getUpdate(&finn, &matias);
  
  lcd.setCursor(9, 0);
  lcd.print(hrTime((millis()/1000) , finn));

  lcd.setCursor(9, 1);
	// lcd.print(hrTime((millis()/1000) , matias));
	lcd.print("Knust");
}

String hrTime(int seconds, int kanne){
  int h = (seconds - kanne)/3600;
  int m = ((seconds - kanne)/60)%60;
	int s = (seconds - kanne)%60;
  
return ( (kanne == 0 || (seconds - kanne < 0)) ? "no time" : ( (h >= 5 ? " to old" : "  " + ( h > 9 ? (String)(h): "0"+(String)(h)) + ":" + ( m > 9 ? (String)(m): "0"+(String)(m)))));
}

void getUpdate(int *finn, int *matias){
  if (digitalRead(7)){ *finn = millis()/1000;}
  if (digitalRead(8)){ *matias = millis()/1000;}
}

