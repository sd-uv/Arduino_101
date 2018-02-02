#include <SD.h>

#define CSPIN 10
#define FILENAME "FORTUNE.TXT"

File myFile;

void setup() {
  Serial.begin(9600);
  
  Serial.print("Initialising SD card...");
  
  pinMode(CSPIN, OUTPUT);
  
  if(!SD.begin(CSPIN)){
    Serial.println("initialisation failed!");
    return;
  }
  Serial.println("initialisation done.");
  
  myFile = SD.open(FILENAME);
  if (myFile) {
    Serial.println(FILENAME);
    
    while (myFile.available()){
      Serial.write(myFile.read());
    }
    
    myFile.close();
  } else {
    Serial.println("error opening FILENAME");
  }
}

void loop(){
}
