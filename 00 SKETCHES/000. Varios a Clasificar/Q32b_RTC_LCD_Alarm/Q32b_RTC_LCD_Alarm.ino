#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include "RTClib.h"

#define BUZZ_PIN    3
#define BUZZ_NOTE   262  // C4 (the note, not the explosive)

#define BUTTON_PIN  2
#define POT_PIN     0
#define SWI_PIN     7

RTC_DS1307 rtc;
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

DateTime now;
DateTime alarmTime = 0;
long nowOffset = 0;

void setup(){
  lcd.begin(16,2);
  lcd.home();
  
  pinMode(BUTTON_PIN, INPUT);
  pinMode(SWI_PIN, INPUT);
  
  rtc.begin();
  if (! rtc.isrunning()) lcd.print("RTC is NOT running!");
  rtc.adjust(DateTime(__DATE__, __TIME__));
  alarmTime = DateTime(__DATE__, __TIME__); // initially set alarm to now
  alarmTime = alarmTime.unixtime() - 1; //avoid the alarm going immediately
}

void loop(){
  
  now = rtc.now().unixtime() + nowOffset;
  printTime();
  
  if (digitalRead(BUTTON_PIN) == HIGH) {
    int potVal = analogRead(POT_PIN);
    int modby = map(potVal, 0, 1023, -10, 10);
    
    if (digitalRead(SWI_PIN) == HIGH) {
      alarmTime = alarmTime.unixtime() + modby;
    } else {
      nowOffset = ((nowOffset + modby) % 86400);
    }
  }
  
  if ((now.hour() == alarmTime.hour()) && 
  (now.minute() == alarmTime.minute()) && 
  (now.second() == alarmTime.second())) {
    tone(BUZZ_PIN, BUZZ_NOTE, 10000);
  }
    
  delay(50);
}

void printTime() {
  char buf[20];

  lcd.home();
  sprintf(buf, "%s %02d:%02d:%02d  ", "A", alarmTime.hour(), alarmTime.minute(), alarmTime.second());
  lcd.print(buf);
  lcd.setCursor(0,1);
  sprintf(buf, "%s %02d:%02d:%02d  ", "T", now.hour(), now.minute(), now.second());
  lcd.print(buf);
}
