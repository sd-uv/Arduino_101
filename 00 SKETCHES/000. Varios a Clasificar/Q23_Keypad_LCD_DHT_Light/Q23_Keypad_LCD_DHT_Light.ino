#include <LiquidCrystal.h>
#include "DHT.h"

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
DHT dht(8, DHT22);

int keyboardPin = 0;
int keyboardValue = 0;

// Analog input pin that the keypad is attached to
// value read from the keypad
void setup(){
  lcd.begin(16,2);
  lcd.clear();
  dht.begin();
}

void loop(){
  keyboardValue = analogRead(keyboardPin); // read the keyboard value (0 - 1023)
  lcd.clear();
  lcd.home();
  
  while (keyboardValue < 5){
    //do nothing until a key is pressed
    keyboardValue = analogRead(keyboardPin);
    delay(50);
  }
  
  float t, h;
  
  switch (getKey(keyboardValue)) {
    case 1:
      t = dht.readTemperature();
      if (isnan(t)) {
        lcd.clear(); // clear the screen
        lcd.setCursor(0, 0);
        lcd.print("Can't get reading");
        lcd.setCursor(0, 1);
        lcd.print("from DHT");
      } else {
        lcd.print("Temp: ");
        lcd.print(t);
        lcd.print(" C");
      }
      break; 
    case 2:
      h = dht.readHumidity();
      if (isnan(h)) {
        lcd.clear(); // clear the screen
        lcd.setCursor(0, 0);
        lcd.print("Can't get reading");
        lcd.setCursor(0, 1);
        lcd.print("from DHT");
      } else {
        lcd.print("Hum: ");
        lcd.print(h);
        lcd.print("%");
      }
      break;
    case 3:
      lcd.print("Light: ");
      lcd.print(analogRead(A1));
      break;
    case 4:
      lcd.print("Hello");
      break;
  }

  
  while (keyboardValue > 25) {
    delay (100);
    keyboardValue = analogRead((keyboardPin)); // read the value (0-1023)
  } //wait until key no longer being pressed before continuing
  
}


byte getKey(int keyVal){
  byte keypressed = 0;

  if ((keyVal >870) && (keyVal < 885)){
    keypressed = 1;
  }
  else if ((keyVal >765) && (keyVal < 775)){
    keypressed = 2;
  }
  else if ((keyVal >665) && (keyVal < 675)){
    keypressed = 3;
  }
  else if ((keyVal >605) && (keyVal < 615)){
    keypressed = 4;
  }


  return keypressed;
}

