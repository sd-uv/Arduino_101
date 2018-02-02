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

  client.println("<h1> Motor A </h1>");  
  
  client.println("<form action='/' method='GET'>");
  client.println("<h2>Forward</h2>");
  printRadios(1, client);  
  client.println("<input type='hidden' name='direction' value='0'>");
  client.println("</form>");

  client.println("<form action='/' method='GET'>");  
  client.println("<h2>Backward</h2>");
  printRadios(1, client);
  client.println("<input type='hidden' name='direction' value='1'>");
  client.println("</form>");

  client.println("<h1> Motor B </h1>");  
  
  client.println("<form action='/' method='GET'>");
  client.println("<h2>Forward</h2>");
  printRadios(2, client);
  client.println("<input type='hidden' name='direction' value='0'>");
  client.println("</form>"); 

  client.println("<form action='/' method='GET'>");
  client.println("<h2>Backward</h2>");
  printRadios(2, client);
  client.println("<input type='hidden' name='direction' value='1'>");
  client.println("</form>");

  client.println("Action performed: <b>");
  client.println(get_request);
  client.println("</b>");

  client.println("</body>");
  client.println("</html>");
}

void printRadios(byte motor, EthernetClient &client) {
  const int speeds[5] = {0, 63, 127, 184, 254};
  const String speedstring[5] = {"Stop", "1/4", "1/2", "3/4", "Full speed!"};

  for (byte i = 0; i < 5; i++) {
    client.print("<input type='radio' name='speed");
    client.print(motor);
    client.print("' value='");
    client.print(speeds[i]);
    client.print("' onclick='this.form.submit()'>");
    client.print(speedstring[i]);
    client.println("</input>");
  }
  
}


void parseGetRequest(String &str) {
  //We need to parse something like this: "?speed1=50&direction1=0"
  Serial.print(" Parsing this string:");
  Serial.println(str);
  //We need to get the speed and the direction. Speed will have a value made of 1 or 2 digits.
  
  //Notice the value-pair delimiter character: "&"
  int delimiter_index = str.indexOf("&");
  Serial.print("delimiter_index: ");
  Serial.println(str.indexOf("&"));
  
  //Get the speed
  int   speed_index  = str.indexOf("speed");
  Serial.print("motor_number: ");
  Serial.println(str[speed_index + 5]);  
  int   motor_number = str[speed_index + 5] - '0';
  
  //Here's, I am trying to avoid using the substring function because I have been
  //having problems with it and it seems unstable.
  //Instead, I just just an array of chars and copying the speed value from the
  //str variable into the array of chars.
  char speed_value_array[4];
  for(int i = speed_index + 7; i < delimiter_index; i++){
    Serial.print(i-8);
    Serial.print("-");
     speed_value_array[i - 8] = str[i];
     Serial.print(str[i]);
         Serial.print("+");
  }
  Serial.println();
  int   motor_speed_value = atoi(speed_value_array);
  Serial.print("Motor speed value: ");
  Serial.println(motor_speed_value);
  
  //Get the direction
//  int   direction_number    = str[delimiter_index + 9] - '0';
///  Serial.print("direction_number: ");
  //Serial.println(str[delimiter_index + 9]);
  int   direction_value = str[delimiter_index + 11] - '0';
  Serial.print("direction_value: ");
  Serial.println(str[delimiter_index + 11]);
 
  executeInstruction(motor_number, motor_speed_value, direction_value);
}

void executeInstruction(int motor_number, int motor_speed_value, int direction_value) {   

  if (motor_number == 1) {
    pinMode(M1, OUTPUT);
    digitalWrite(M1, HIGH);
    Serial.print("Motor 1 ");
    if (direction_value == 0) { //forward
      analogWrite(R1, 0);
      Serial.print("forward at ");
      analogWrite(F1, motor_speed_value);
      Serial.println(motor_speed_value);
    } else { //reverse
      analogWrite(F1, 0);
      Serial.print("reverse at ");
      analogWrite(R1, motor_speed_value);
      Serial.println(motor_speed_value);
    }
  } else if (motor_number == 2) {
    pinMode(M2, OUTPUT);
    digitalWrite(M2, HIGH);
    Serial.print("Motor 2 ");
    if (direction_value == 0) { //forward
      analogWrite(R2, 0);
      Serial.print("forward at ");
      analogWrite(F2, motor_speed_value);
      Serial.println(motor_speed_value);
    } else { //reverse
      analogWrite(F2, 0);
      Serial.print("reverse at ");
      analogWrite(R2, motor_speed_value);
      Serial.println(motor_speed_value);
    }
  }
  delay(30); 
}

