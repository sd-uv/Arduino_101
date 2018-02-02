#include <SPI.h>
#include <Ethernet.h>
#include "DHT.h"
//#include <LiquidCrystal.h>

#include <Adafruit_CharacterOLED.h>

// initialize the library with the OLED hardware 
// version OLED_Vx and numbers of the interface pins. 
// OLED_V1 = older, OLED_V2 = newer. If 2 doesn't work try 1 ;)
Adafruit_CharacterOLED lcd(OLED_V2, 3, 4, 2, 9, 8, 7, 6);


//#define LEDPIN 4

//LiquidCrystal lcd(3,4,2,9,8,7,6);
DHT dht(5, DHT22);

byte mac[] = { 0x90, 0xA2, 0xDA, 0x0F, 0x0F, 0x9D };
EthernetServer server(23); // telnet defaults to port 23

boolean gotAMessage = false; // whether or not you got a message from the client yet
String commandString;
boolean alreadyConnected = false;

void setup() {
  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("My IP address: ");


  // start the Ethernet connection:
  Ethernet.begin(mac);
  IPAddress ip = Ethernet.localIP();
  server.begin();

  // print your local IP address:
  lcd.setCursor(0,1);
  lcd.print(Ethernet.localIP());
}

void loop() {
  EthernetClient client = server.available(); // wait for a new client
  commandString = "";
  if (client) {
    // when the client sends the first byte, say hello
    if (!alreadyConnected) {
      client.flush(); // clear out the input buffer
      commandString = ""; //clear the commandString variable
      server.println("--> Please type your command and hit Return...");
      alreadyConnected = true;
    }
    while (client.available()) {
      char newChar = client.read();
      // read the bytes incoming from the client
      if (newChar == 0x0D) // If a 0x0D is received, a Carriage Return,
        // then evaluate the command
      {
        processCommand(commandString);
      } 
      else
      {
        Serial.println(newChar);
        commandString += newChar;
      }
    }
  }
}

void processCommand(String command) {
  server.print("Processing command ");
  server.println(command);
  if (command.indexOf("photo") > -1){
    lcdEcho("Photo reading");
    server.print("Reading from photoresistor: " );
    server.println(analogRead(0)); //Print the integer returned by analogRead
  }
  else if (command.indexOf("ledon") > -1){
    lcdEcho("LED On");
   // digitalWrite(LEDPIN, HIGH);
    // sets the LED on
    server.println("LED was turned on");
  }
  else if (command.indexOf("ledoff") > -1){
    lcdEcho("LED Off");
    //digitalWrite(LEDPIN, LOW);
    // sets the LED off
    server.println("LED was turned off");
  }
  else if (command.indexOf("temp") > -1){
    lcdEcho("Get temperature");
    server.print("Temperature: ");
    server.print(dht.readTemperature());
    server.println("C");
  } 
  else if (command.indexOf("hum") > -1){
    lcdEcho("Get humidity");
    server.print("Humidity: ");
    server.print(dht.readHumidity());
    server.println("%");
  } 
  else {
    lcdEcho("Send instruction");
    instructions();
  }
  server.println("");
  commandString = "";
}

void instructions() {
  server.println("I don't understand");
  server.println("Please use one of these commands:");
  server.println("* photo, to get a reading from the photoresistor");
  server.println("* ledon, to turn on the LED");
  server.println("* ledoff, to turn off the LED");
  server.println("* temp, to get a temperature reading");
  server.println("* hum, to get a humidity reading");
}

void lcdEcho(String input) {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(input);
}

