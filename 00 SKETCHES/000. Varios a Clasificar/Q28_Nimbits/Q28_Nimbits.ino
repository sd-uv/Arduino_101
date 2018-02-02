#include <SPI.h>
#include <Ethernet.h>
#include <PString.h>
#include "config.h"            // private config items
#include "DHT.h"
#include <Wire.h>
#include <Adafruit_BMP085.h>

#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

Adafruit_BMP085 bmp;

char buffer[400];            // larger than required for this example, resize to suit your application
char content[200];           // larger than required for this example, resize to suit your application
PString str(buffer, sizeof(buffer));
PString cont(content, sizeof(content));

int dht_t ;    // variables to store analog samples
int dht_h ;
int light;
float bmp_p = 0;
float bmp_t = 0;

/************ ETHERNET STUFF ************/
byte mac[] = { 0x90, 0xA2, 0xDA, 0x0F, 0x0F, 0x9D };


EthernetClient nimbitsServiceClient;
//***************************************

unsigned long lastConnectionTime = 0;          // last time you connected to the server, in milliseconds
const unsigned long postingInterval = 120000;  // 120-sec delay between updates to logging service, 720 per 24hrs to keep within the 1000 quota
                                               // and leave room for other types of API access 

// these are for your nimbits account
char mailaddr [] = CFG_MAILADDR;    // your email address for the logging account
char key [] = CFG_KEY;                     // your KEY you created for the account. Not the UUID.


void setup() {
  Serial.begin(9600);    // serial debug
  
  Ethernet.begin(mac);
  Serial.println("up and running....");
  
  IPAddress ip = Ethernet.localIP();
  Serial.print("My IP: ");
  Serial.println(Ethernet.localIP());
  
  dht.begin();
  bmp.begin();
  
  Serial.print("POST interval is ");
  Serial.print(postingInterval/1000);
  Serial.println(" seconds");
}

// =========================================================================
// very simple main loop. Just constantly reads two ADC channels and then if its time to log again, do_weblog() sends in the latest values
// of A8 and A9
void loop()
{
  dht_t = dht.readTemperature();
  dht_h = dht.readHumidity();   
  
  bmp_p = bmp.readPressure();
  bmp_t = bmp.readTemperature();
   
  light = analogRead(0);
  
  do_weblog();
  delay(5000); //delay 5 seconds to avoid cooking the DHT
} 

// =========================================================================
/*
This is where it all happens.
If the posting interval is reached then a new POST is done with the latest data
If not time yet, we simply exit
 */
void do_weblog() {
    // if you're not connected, and 'postinginterval' secs have passed since
    // your last connection, then connect again and send data:
    if(!nimbitsServiceClient.connected() && (millis() - lastConnectionTime > postingInterval)) {
        str.begin();    // reset the into-string pointer. This is the 'final' composite string being assembled.
        cont.begin();   // and for the actual content ie payload string
        sendData();    // the POST gets created and sent here
        delay(1);
        nimbitsServiceClient.stop();    // stop the client
        nimbitsServiceClient.flush();   // and tidy up
    }
}

void sendData() {
  // Create the 'content' string to send. Its assembled from the user details, then the sensor data
  // 1st part of content is access-details
  cont.print("email=");
  cont.print(mailaddr);
  cont.print("&key=");
  cont.print(key);
  
  cont.print("&p1=dht_tmp&v1=");
  cont.print(dht_t,DEC);
  cont.print("&p2=dht_hum&v2=");
  cont.print(dht_h,DEC);
  cont.print("&p3=bmp_tmp&v3=");
  cont.print(bmp_t,DEC);
  cont.print("&p4=bmp_pr&v4=");
  cont.print(bmp_p,DEC);
  cont.print("&p5=light&v5=");
  cont.print(light,DEC);
  
  int contlen = (cont.length());

    // now try and connect to the web-site
    Serial.println("connecting...");
    if (nimbitsServiceClient.connect("cloud.nimbits.com", 80))     // make the attempt...
    { 
        // the format of the POST section below seems to be fairly critical. 
        str.print("POST /service/batch HTTP/1.1\r\n");
        str.print("Host: cloud.nimbits.com\r\n");
        str.print("Connection: close\r\n");
        str.print("Cache-Control: max-age=0\r\n");
        str.print("Content-Length: ");
        str.print(contlen,DEC);
        str.print("\r\n");
        str.print("Content-Type: application/x-www-form-urlencoded\r\n");
        str.print("\r\n");  // this empty line is REQUIRED
        str.print(cont);    // the actual content string 'cont' (access details, data points)
        str.print("\r\n");  // and a terminating newline
// this completes the assembly of the string to send (contained in 'str')

// the total string (post headers and content) is now sent to the ethernet connection in one hit
        nimbitsServiceClient.print(str);  // ethernet send to Nimbits

        Serial.println();        // for debug
        
        Serial.print(str);       // this is a copy of whats sent to the ethernet (the same string)
                                 // you can comment-out the line: nameofclient.print(str) above to just see the debug output
                                 // while testing. This lets you see if your POST looks sensible.
        
        Serial.println();        // for debug
        Serial.println();        // for debug

// shows the response from the server. Comment below if not required.
        delay(1500);        // wait 1.5 sec for a response
        while (nimbitsServiceClient.available()) {
          char c = nimbitsServiceClient.read();
          Serial.print(c);
        }
    }

    else {
        // if you couldn't make a connection:
        Serial.println();
        Serial.println("Connection failed");
        Serial.println("disconnecting.");
        Serial.println();
    }
    // note the time that the connection was made
    lastConnectionTime = millis();
}
