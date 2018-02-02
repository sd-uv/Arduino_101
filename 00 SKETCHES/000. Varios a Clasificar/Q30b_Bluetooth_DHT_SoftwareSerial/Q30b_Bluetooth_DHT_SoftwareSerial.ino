#include <SoftwareSerial.h>
#include "DHT.h"

SoftwareSerial mySer(2,3); //SoftwareSerial for bluetooth
DHT dht(7, DHT22);

void setup() {
  mySer.begin(9600);  // start mySer communication at 9600bps
}

void loop() {

  mySer.print("Humidity: ");
  mySer.print(dht.readHumidity());
  mySer.println("%");
  
  mySer.print ("Temperature: ");
  mySer.print(dht.readTemperature());
  mySer.println("C");
  
  delay(2000);                    // wait 2 sec for next reading
} 
