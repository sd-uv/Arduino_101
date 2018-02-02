//------------------------------------------------------------------------------
// Programa para pruebas de Interruptores de Presión (Pushbuttons)

// Seleccione la terminal (pin) que corresponde al LED
// Seleccione la terminal (pin) de entrada (para el interruptor de presión)
// Declare a la terminal del LED como SALIDA
// Declare a la terminal del interruptor de presión como entrada
//
// ... Por ejemplo...
// Interruptor conectado en terminal 2, LED conectado a terminal 13
//------------------------------------------------------------------------------
// Adaptado por: Sergio Fco. Hernández Machuca
// sfhm_clases@hotmail.com
//------------------------------------------------------------------------------

const int ledPin = 13;    // Asociación de terminales con recursos...
const int inputPin = 2;   //

const int ledPin1 = 12;    // Asociación de terminales con recursos...
const int inputPin1 = 3;   //

const int ledPin2 = 11;    // Asociación de terminales con recursos...
const int inputPin2 = 4;   //
//------------------------------------------------------------------------------
void setup() {
  pinMode(ledPin, OUTPUT);    // Ajuste de tipo (entrada o salida) de...
  pinMode(inputPin, INPUT);   // ... cada terminal empleada
}
//------------------------------------------------------------------------------
void loop() {
  int val = digitalRead(inputPin);  // Lectura del valor de entrada
  if (val == LOW) {                // ¿La entrada está en "1"?
    digitalWrite(ledPin, HIGH);     // ... SI ...  Enciende el LED
  } else {                          // ... En caso contrario ...
    digitalWrite(ledPin, LOW);      // (está en "0"), Apaga el LED
  }

  int val1 = digitalRead(inputPin1);  // Lectura del valor de entrada
  if (val1 == LOW) {                // ¿La entrada está en "1"?
    digitalWrite(ledPin1, HIGH);     // ... SI ...  Enciende el LED
  } else {                          // ... En caso contrario ...
    digitalWrite(ledPin1, LOW);      // (está en "0"), Apaga el LED
  }

  int val2 = digitalRead(inputPin2);  // Lectura del valor de entrada
  if (val2 == LOW) {                // ¿La entrada está en "1"?
    digitalWrite(ledPin2, HIGH);     // ... SI ...  Enciende el LED
  } else {                          // ... En caso contrario ...
    digitalWrite(ledPin2, LOW);      // (está en "0"), Apaga el LED
  }

}
//------------------------------------------------------------------------------
