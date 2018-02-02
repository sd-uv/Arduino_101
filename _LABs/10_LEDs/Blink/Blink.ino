/*
  Parpadeo
  Enciende un LED por un segundo, lo apaga otro segundo, repetidamente.
*/
//------------------------------------------------------------------------------
// Adaptado por: Sergio Fco. Hernández Machuca
// sfhm_clases@hotmail.com
//------------------------------------------------------------------------------

// En la mayoría de las tarjetas Arduino el Pin 13 tiene conectado un LED.
// Se le asigna un nombre al Pin (Terminal) 13:
int led = 13;

// Esta rutina de ajuste se ejecuta una sola vez cuando se oprime "Reset":
void setup() {                  
	pinMode(led, OUTPUT); // Inicializa el Pin Digital como "salida".
}

// Esta rutina en lazo se ejecuta una y otra vez, por siempre:
void loop() {
	digitalWrite(led, HIGH);   // Enciende el LED (HIGH es un nivel de voltaje)
	delay(400);               // Espera por un segundo.
	digitalWrite(led, LOW);    // Apaga el LED, haciendo el voltaje LOW.
	delay(250);               // Espera por un segundo.
}
