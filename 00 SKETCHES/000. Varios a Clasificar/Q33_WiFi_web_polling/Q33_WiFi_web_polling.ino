/**
* Uses Adafruit CC3000 library (and module) to connect to wifi network
* pulls /cc3000.txt from a webserver and acts on instructions in that
* file to turn LEDs on or off.
*
* contents of file are of the form
*
* led8=1
* led7=0
*
* to turn the LED on pin 8 on and the LED on pin 7 off
*
**/
#include <Adafruit_CC3000.h>
#include <ccspi.h>
#include <SPI.h>
#include <string.h>
#include "utility/debug.h"
#include <avr/wdt.h>

// comment out to reduce serial monitor verbosity and program size
#define DEBUG

#define ADAFRUIT_CC3000_IRQ   3
#define ADAFRUIT_CC3000_VBAT  5
#define ADAFRUIT_CC3000_CS    10
Adafruit_CC3000 cc3000 = Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT, SPI_CLOCK_DIVIDER);

#define WLAN_SSID      "test-net"
#define WLAN_PASS      "qazxsw12"
#define WLAN_SECURITY  WLAN_SEC_WPA2

#define IDLE_TIMEOUT_MS 3000
#define WEBSITE  "lilt.twpsyn.com"
#define WEBPAGE  "/cc3000.txt"

Adafruit_CC3000_Client www;

unsigned long ip; 
unsigned long t; 
byte port = 80;
word connectTimeout = 5000;
word repeat_counter = 0;
boolean reading = false;
String get_request = "";

void setup(){
  Serial.begin(115200);

  Serial.print(F("\nInitializing... "));
  if (!cc3000.begin()) {
    Serial.println(F("\nCouldn't begin()! Check your wiring?"));
    while(1);
  } 
  else {
    Serial.println("done");
  }

  Serial.print("Connecting to SSID: ");
  Serial.print(WLAN_SSID); 
  Serial.print(" ... ");

  if (!cc3000.connectToAP(WLAN_SSID, WLAN_PASS, WLAN_SECURITY)) {
    Serial.println(F("Failed!"));
    while(1); 
  }
  Serial.println("connected");

  Serial.print("Requesting DHCP... ");
  while (!cc3000.checkDHCP()) {
    delay(100); 
  }
  Serial.println("ok\n");

  //unsigned long ip = 0;
  Serial.print(WEBSITE); 
  Serial.print(F(" -> "));
  while (ip == 0) {
    if (! cc3000.getHostByName(WEBSITE, &ip)) {
      Serial.println(F("Couldn't resolve!"));
    }
    delay(500);
  }
  cc3000.printIPdotsRev(ip);

  Serial.println("\n");

  //  cc3000.disconnect();

}

void loop(){

  repeat_counter++;
  reading = false;

#ifdef DEBUG  
  Serial.print(F("Free RAM: ")); 
  Serial.println(getFreeRam(), DEC);
  Serial.print(F("Repeat counter: ")); 
  Serial.println(repeat_counter);

  Serial.print(F("Starting connection to "));
  Serial.println(ip);
#endif  

  wdt_enable(WDTO_8S);
  t = millis();
  do {
    www = cc3000.connectTCP(ip, port); 
  }
  while((!www.connected()) && ((millis() - t) < connectTimeout));

  wdt_disable();

  if (www.connected()) {
    Serial.println(F("Connected"));
    www.fastrprint(F("GET "));
    www.fastrprint(WEBPAGE);
    www.fastrprint(F(" HTTP/1.1\r\n"));
    www.fastrprint(F("Host: ")); 
    www.fastrprint(WEBSITE); 
    www.fastrprint(F("\r\n"));
    www.fastrprint(F("\r\n"));
    www.println();
    Serial.println(F("Request sent"));
  } 
  else {
    Serial.println(F("Connection failed"));
    return;
  }

#ifdef DEBUG
  Serial.println(F("---------------------"));
#endif
  unsigned long lastRead = millis();
  while (www.connected() && (millis() - lastRead < IDLE_TIMEOUT_MS)){
    boolean currentLineIsBlank = true;
    get_request = "";
    boolean sentContent = false;
    while (www.available()){
      char c = www.read();
#ifdef DEBUG
      Serial.print(c);
#endif
      if(reading && c == '\n' && !currentLineIsBlank) {
        parseGetRequest(get_request);
        break;
      }
      if (reading) {
        get_request += c;
      }
      if (reading && c == '\n') {
        break;
      }
      if (c == '\n' && currentLineIsBlank) {
        reading = true;
      }
      if (c == '\n') {
        currentLineIsBlank = true;
      } 
      else if (c != '\r') {
        currentLineIsBlank = false;
      }
    }
  }
  www.close();
  Serial.println(F("------------------"));
  delay(10000);

}


void parseGetRequest(String &str) {
#ifdef DEBUG
  Serial.print(F("Parsing this string:"));
  Serial.println(str);
#endif
  int led_index = str.indexOf("led");
  int led_pin = str[led_index + 3] - '0';
  int led_val = str[led_index + 5] - '0';
#ifdef DEBUG
  Serial.print(F("Executing instruction: pin "));
  Serial.print(led_pin);
  Serial.print(" to ");
  Serial.println(led_val);
#endif
  pinMode(led_pin, OUTPUT);
  digitalWrite(led_pin, led_val);
#ifdef DEBUG
  Serial.println(F("Done!"));
#endif	
}

