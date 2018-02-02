#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

#define DHTPIN 10
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

//LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup(){
  lcd.begin(16,2);  // set up LCD's number of columns and rows
  lcd.clear();
  lcd.home();
  lcd.print("DHT test");
  dht.begin();
}

void loop(){
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  if(isnan(t) || isnan(h)){
    lcd.clear();
    //lcd.setCursor(0,0);
    lcd.print("Can't get");
    lcd.setCursor(0,1);
    lcd.print("reading from DHT");
  }else{
    lcd.clear();
   // lcd.setCursor(0,0);
    lcd.print(" Hum: ");
    lcd.print(h);
    lcd.print(" %");
    
    lcd.setCursor(0,1);
    lcd.print("Temp: ");
    lcd.print(t);
    lcd.print(" C");
  }
  delay(1000);
}

