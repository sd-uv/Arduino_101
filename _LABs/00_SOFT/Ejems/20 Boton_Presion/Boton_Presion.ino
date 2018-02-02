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

//------------------------------------------------------------------------------
void setup() {
  pinMode(ledPin, OUTPUT);    // Ajuste de tipo (entrada o salida) de...
  pinMode(inputPin, INPUT);   // ... cada terminal empleada
}
//------------------------------------------------------------------------------
void loop() {
  int val = digitalRead(inputPin);  // Lectura del valor de entrada
  if (val == HIGH) {                // ¿La entrada está en "1"?
    digitalWrite(ledPin, HIGH);     // ... SI ...  Enciende el LED
  } else {                          // ... En caso contrario ...
    digitalWrite(ledPin, LOW);      // (está en "0"), Apaga el LED
  }
}
//------------------------------------------------------------------------------
