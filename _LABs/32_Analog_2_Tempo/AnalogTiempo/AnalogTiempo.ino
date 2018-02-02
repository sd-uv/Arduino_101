/*
  Entrada Analógica
 Demuestra la entrada analógica leyendo un sensor analógico colocado en la 
 entrada A0 y encendiendo y apagando un LED conectado a la terminal 13.
 La cantidad de tiempo que el LED está encendido (o apagado) depende del valor
 leído en la entrada analógica A0, a través de la instrucción analogRead().
 
 El circuito:
 * Un potenciómetro (terminal central) en la entrada analógica A0.
 * Una de las terminales extremas del potenciómetroa + 5 Volts.
 * La otra terminal extrema del potenciómetro a la terminal de GND.
 * La terminal del ánodo del LED (terminal larga) conectada a la salida 
   digital 13, a través de una resistencia de 220 ohms.
 * La terminal del cátodo del LED (termianl corta) conectada a tierra (GND).
 
 * Nota: Es posible que la versión de Arduino (si es UNO, por ejemplo) tenga 
 interconstruido un LED que esté conectado a la terminal 13, por lo que el LED
 puede ser opcional.
 */
//------------------------------------------------------------------------------
// Adaptado por: Sergio Fco. Hernández Machuca
// sfhm_clases@hotmail.com
//------------------------------------------------------------------------------

int sensorPin = 0;    // select the input pin for the potentiometer
int ledPin = 13;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);  
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);    
  // turn the ledPin on
  digitalWrite(ledPin, HIGH);  
  // stop the program for <sensorValue> milliseconds:
  delay(sensorValue);          
  // turn the ledPin off:        
  digitalWrite(ledPin, LOW);   
  // stop the program for <sensorValue> milliseconds:
  delay(sensorValue);                  
}
