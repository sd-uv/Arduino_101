/*
 * A simple web server with a GET request parser.
 *
 */
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <Ethernet.h>

const byte B1PIN = 3;

boolean backlighton = true;
boolean buttonActive = false;

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
byte mac[] = { 0x90, 0xA2, 0xDA, 0x0F, 0x0F, 0x9D };


String         message      = "";     //Will hold the confirmation message that will be shown to the user
EthernetServer server(80);
String         get_request  = "";     //Holds the GET request
boolean        reading      = false;  //TRUE while the GET request is being received

void setup()
{

  pinMode(B1PIN, INPUT);

  lcd.begin(16,2);
  lcd.home();
  lcd.print("My IP address:");

  Ethernet.begin(mac);
  IPAddress ip = Ethernet.localIP();
  server.begin();

  lcd.setCursor(0,1);
  lcd.print(Ethernet.localIP());


  Serial.begin(9600);
  /*  Ethernet.begin(mac, ip);
   server.begin();
   */  Serial.println("ready");
}

void loop() {
  checkLCDBackLight();

  // listen for incoming clients
  EthernetClient   client = server.available();
  String return_message; 

  if (client) {
    Serial.println("new client");
    boolean sentContent    = false;
    get_request           = "";
    // an http request ends with a blank line
    boolean        currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char       c = client.read();
        if(reading && c == ' ') 
        { 
          reading = false;  
          return_message = parseGetRequest(get_request);
          break;
        }

        if(c == '?'){
          reading = true; //found the ?, begin reading the info
        }

        if(reading){ 
          get_request += c;
        }


        if (reading && c=='\n')
        {
          break; 
        }

        if (c == '\n' && currentLineIsBlank)  {
          break;
        }
        if (c == '\n') {
          currentLineIsBlank = true;
        } 
        else if (c != '\r') {
          currentLineIsBlank = false;
        }
      }
    }

    if (!sentContent){
      construct_page(client, return_message);         
      sentContent = true;        
    }

    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }
}

void construct_page(EthernetClient &client, String &rmessage)
{
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println();
  client.print("<html><head><title>");   
  client.print("GET request example");
  client.println("</title><body>");
  client.println("<h2>Click buttons to turn red led on or off</h2>");
  client.print("<form action='/' method='GET'><p><input type='hidden' name='led8'");
  client.println(" value='0'><input type='submit' value='Off'/></form>");
  client.print("<form action='/' method='GET'><p><input type='hidden' name='led8'");
  client.print(" value='1'><input type='submit' value='On'/></form>");
  client.println("<h2>Click buttons to turn yellow led on or off</h2>");
  client.print("<form action='/' method='GET'><p><input type='hidden' name='led7'");
  client.println(" value='0'><input type='submit' value='Off'/></form>");
  client.print("<form action='/' method='GET'><p><input type='hidden' name='led7'");
  client.print(" value='1'><input type='submit' value='On'/></form>");
  client.print("Action(s) performed: <b>");
  client.print(rmessage);
  client.print("</b>");
  client.print("</body>");
  client.print("</html>");
}

String parseGetRequest(String &str) {
  Serial.print(" Parsing this string:");
  Serial.println(str);
  int   led_index  = str.indexOf("led");
  int   led_pin    = str[led_index + 3]  - '0';
  int   led_val    = str[led_index + 5]  - '0';
 
  String return_message = "";
  return_message = "Setting LED ";
  return_message += led_pin;
  return_message += " to ";
  return_message += led_val;
  executeInstruction(led_pin, led_val);
  return return_message;
}

void executeInstruction(int pin, int val)
{ 
  pinMode(pin, OUTPUT);
  digitalWrite(pin, val);  
}


void checkLCDBackLight() {

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
}

