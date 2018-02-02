#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include "RTClib.h"

RTC_DS1307 rtc;
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup(){
  lcd.begin(16,2);
  lcd.home();
  
  rtc.begin();
  if (! rtc.isrunning()) lcd.print("RTC is NOT running!");
}

void loop(){
  
  DateTime now = rtc.now();

  char buf[20];

  lcd.home();
  sprintf(buf, "%02d/%02d/%02d  ", now.day(), now.month(), now.year());
  lcd.print(buf);
  lcd.setCursor(0,1);
  sprintf(buf, "%02d:%02d:%02d  ", now.hour(), now.minute(), now.second());
  lcd.print(buf);

  delay(50);
}

