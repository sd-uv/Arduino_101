#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <Ethernet.h>
#include "DHT.h"
#include <Adafruit_BMP085.h>

const byte B1PIN = 3;

boolean backlighton = true;
boolean buttonActive = false;

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
byte mac[] = { 
  0x90, 0xA2, 0xDA, 0x0F, 0x0F, 0x9D };

EthernetServer server(80);

DHT dht(2, DHT22);
Adafruit_BMP085 bmp;



void setup(){
  pinMode(B1PIN, INPUT);

  lcd.begin(16,2);
  lcd.home();
  lcd.print("My IP address:");

  Ethernet.begin(mac);
  IPAddress ip = Ethernet.localIP();
  server.begin();

  lcd.setCursor(0,1);
  lcd.print(Ethernet.localIP());
  
  dht.begin();
  bmp.begin();
}


void loop(){

  if ((digitalRead(B1PIN) == HIGH) ) {
    if (buttonActive) {
    } 
    else {
      Serial.println("pressed the button!");
      if (backlighton) {
        backlighton = false;
        Serial.println("backlight turned off");
        lcd.noBacklight();
      } 
      else {
        lcd.backlight();
        backlighton = true;
        Serial.println("backlight turned on");
      }
      buttonActive = true;
    }
  }

  if ((digitalRead(B1PIN) == LOW) && (buttonActive)) {
    Serial.println("released the button");
    buttonActive = false;
  }



  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    boolean currentLineIsBlank = true;
    // an http request ends with a blank line
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close"); // the connection will be closed
          //after completion of the response
          client.println("Refresh: 15"); // refresh the page automatically
          // every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
 
          float h = dht.readHumidity();
          float t = dht.readTemperature();
          if (isnan(t) || isnan(h)) {
            Serial.println("Failed to read from DHT");
          }
          else {
            client.println("<h2>DHT data</h2>");
            client.print("Humidity: ");
            client.print(h);
            client.println("% <br />");
            client.print("Temperature: ");
            client.print(t);
            client.print(" *C");
            client.println("<br />");
            client.println("<p>"); 
          }

          client.println("<h2>BMP data</h2>");
          client.print("Temperature: ");
          client.print(bmp.readTemperature());
          client.println(" *C <br />");
          
          client.print("Pressure: ");
          client.print(bmp.readPressure());
          client.println(" Pa <br />");
          
          client.print("Barametric Altitude: ");
          client.print(bmp.readAltitude(102800));
          client.println(" metres<br />");

          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
  }

  // give the web browser time to receive the data
  delay(1);
  // close the connection:
  client.stop();
  Serial.println("client disonnected");




}



