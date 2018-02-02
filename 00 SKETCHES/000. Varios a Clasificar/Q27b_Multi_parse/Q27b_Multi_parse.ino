#include <SPI.h>
#include <Ethernet.h>

#define F1 5
#define R1 6
#define M1 2

#define F2 9
#define R2 3
#define M2 8

byte mac[] = { 0x90, 0xA2, 0xDA, 0x0F, 0x0F, 0x9D };


String         message      = "";     //Will hold the confirmation message that will be shown to the user
EthernetServer server(80);
String         get_request  = "";     //Holds the GET request
boolean        reading      = false;  //TRUE while the GET request is being received

void setup() {

  
 // pinMode(B1PIN, INPUT);
  Serial.begin(9600);
  //Serial.print("Free RAM: "); Serial.println(getFreeRam(), DEC);

  Serial.print("Ethernet beginning... ");
  Ethernet.begin(mac);
  Serial.println("done!");
  IPAddress ip = Ethernet.localIP();

  Serial.print("Server beginning... ");
  server.begin();
  Serial.println("done!");

  Serial.print("My IP: ");
  Serial.println(Ethernet.localIP());
}

void loop(){
 // listen for incoming clients
  EthernetClient   client = server.available();
  char           return_message[30]; 
  if (client) {
    Serial.println("new client");
    boolean sentContent    = false;
    get_request           = "";

    boolean        currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char       c = client.read();
        if(reading && c == ' ') 
        { reading = false;  
          parseGetRequest(get_request);
          
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
       construct_page(client);//, return_message);         
       sentContent = true;        
     }
    
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}


void construct_page(EthernetClient &client)
{
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println();
  client.println("<html><head><title>");   
  client.println("GET motor control example");
  client.println("</title><body>");

  client.println("<h1>Don't care</h1>");

  client.println("</body>");
  client.println("</html>");
}



void parseGetRequest(String &str) {
  //We need to parse something like this: "?speed1=50&direction1=0"
  Serial.print(" Parsing this string:");
  Serial.println(str);

  int strLen = str.length();
  String tmpStr = "";
  
  for (int p = 1; p < strLen; p++) {
    char tmpChar = str.charAt(p);
    if (tmpChar == '&') {
      // deal with each pair individually here
      Serial.print("Pair is - ");
      Serial.println(tmpStr);
      tmpStr = "";
    } else {
      tmpStr += tmpChar;
    }
  }
  // deal with final pair here
  Serial.print("Pair is - ");
  Serial.println(tmpStr);
      
}


