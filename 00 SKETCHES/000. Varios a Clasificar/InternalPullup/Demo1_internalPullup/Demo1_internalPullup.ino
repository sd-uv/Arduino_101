
// Las constantes no cambiarán, será usadas para ajustar el número de los pines:
const int buttonPin = 2;     // Número del pin para el interruptor de presión.
const int ledPin =  13;      // Número de pin para el LED.

// Las variables cambiarán:
int buttonState = 0;         // Variable de lectura del estado del
                             // interruptor de presión.

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);      
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin,INPUT_PULLUP);   // turn on pullup resistors
}

void loop(){
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == LOW) {     
    // turn LED on:    
    digitalWrite(ledPin, HIGH);  
  } 
  else {
    // turn LED off:
    digitalWrite(ledPin, LOW); 
  }
}
