#include <SPI.h>
#include "config.h"
#include <Twitter.h>
#include <Ethernet.h>
#include <PString.h>

byte mac[] = { 0x90, 0xA2, 0xDA, 0x0F, 0x0F, 0x9D };

Twitter twitter(CFG_TOKEN);

unsigned long lastConnectionTime = 0;
const unsigned long postingInterval = 120000;  // 2 minutes (short time for testing only)

char tweet[200];
PString tweet_pstring(tweet, sizeof(tweet));


int light;
int temp;

void setup() {
  Serial.begin(9600);  
  
  Ethernet.begin(mac);
  
}

void loop() {
  light = analogRead(0);
  temp = analogRead(1);
  
     if((millis() - lastConnectionTime > postingInterval)) {
        tweet_pstring.begin();
        int ana_A = analogRead(0);
        Serial.println("connecting ...");
        tweet_pstring.print("Light intensity:");
        tweet_pstring.print(light);
        tweet_pstring.print(". Thermo reading:");
        tweet_pstring.print(temp);
        
        if (twitter.post(tweet_pstring)) {
            // Specify &Serial to output received response to Serial.
            // If no output is required, you can just omit the argument, e.g.
            //int status = twitter.wait();
            int status = twitter.wait(&Serial);
            if (status == 200) {
               Serial.println("OK.");
            } else {
               Serial.print("failed : code ");
               Serial.println(status);
            }
          } else {
            Serial.println("connection failed.");
         }
         // note the time that the connection was made
         lastConnectionTime = millis();
      }
  
  delay(1000);
}
