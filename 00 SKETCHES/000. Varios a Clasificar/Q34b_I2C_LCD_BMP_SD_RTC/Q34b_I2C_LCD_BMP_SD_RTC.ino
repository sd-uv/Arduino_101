#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_BMP085.h>
#include "RTClib.h"
#include <SD.h>

#define SD_CS 10

RTC_DS1307 rtc;
Adafruit_BMP085 bmp;

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup(){
  Serial.begin(115200);
  
  Serial.print("Initialising SD card... ");
  pinMode(SD_CS, OUTPUT);
  if (!SD.begin(SD_CS)) {
    Serial.println("Card failed or not present!");
    return;
  } else {
    Serial.println("card initialised.");
  }
  
  lcd.begin(16,2);  // set up LCD's number of columns and rows
  lcd.clear();
  lcd.home();
  lcd.print("BMP test");
  
  bmp.begin();
  
  rtc.begin();
  //rtc.adjust(DateTime(__DATE__, __TIME__));  
}

void loop(){
  DateTime now = rtc.now();
  float p = bmp.readPressure();
  float t = bmp.readTemperature();
  char buf[25];
  Serial.println("");
  sprintf(buf, "%02d/%02d/%04d %02d:%02d:%02d", 
          now.day(), now.month(), now.year(), now.hour(), now.minute(), now.second());
  Serial.println(buf);
  
  File dataFile = SD.open("bmplog.txt", FILE_WRITE);
  if (!dataFile) {
    Serial.println("error opening bmplog.txt");
  } else {
    dataFile.println(buf);
  }
  
  if(isnan(t) || isnan(p)){
    lcd.clear();
    lcd.print("Can't get");
    lcd.setCursor(0,1);
    lcd.print("reading from BMP");
  }else{
    lcd.clear();
    lcd.print(p);
    lcd.print(" Pa");
    
    Serial.print("Pressure: ");
    Serial.print(p);
    Serial.println("Pa");
    
    if (dataFile) dataFile.print("Pressure: ");
    if (dataFile) dataFile.print(p);
    if (dataFile) dataFile.println("Pa");
    
    lcd.setCursor(0,1);
    lcd.print(t);
    lcd.print(" C");

    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.println(" C");

    if (dataFile) dataFile.print("Temperature: ");
    if (dataFile) dataFile.print(t);
    if (dataFile) dataFile.println("C");
  }
  if (dataFile) dataFile.println("");
  dataFile.close();
  delay(1000);
}

