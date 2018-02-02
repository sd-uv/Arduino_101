#include <SoftwareSerial.h>

#define REDLED 8
#define GREENLED 9
#define YELLOWLED 10

SoftwareSerial mySer(2,3); //SoftwareSerial for bluetooth

char val;
boolean redon = false;
boolean greenon = false;
boolean yellowon = false;

void setup() {
  mySer.begin(9600);  // start mySer communication at 9600bps
  pinMode(REDLED, OUTPUT);
  pinMode(GREENLED, OUTPUT);
  pinMode(YELLOWLED, OUTPUT);
}

boolean toggle(boolean inbool) {
  if (inbool) {
    return false;
  } else {
    return true;
  }
}

void loop() {

  if (mySer.available()) {
    val = mySer.read();
  }
  
  
  if (val == 'R') {
    redon = toggle(redon);
  } else if (val == 'G') {
    greenon = toggle(greenon);
  } else if (val == 'Y') {
    yellowon = toggle(yellowon);
  }
  
  if (redon) {
    digitalWrite(REDLED, HIGH);
  } else {
    digitalWrite(REDLED, LOW);
  }
  
  if (greenon) {
    digitalWrite(GREENLED, HIGH);
  } else {
    digitalWrite(GREENLED, LOW);
  }
  
  if (yellowon) {
    digitalWrite(YELLOWLED, HIGH);
  } else {
    digitalWrite(YELLOWLED, LOW);
  }
  
  val = ' '; //reset val
  
  
  delay(100);                    // wait 100ms for next reading
} 
