/*
  Parpadeo para más de un LED
 
*/
//------------------------------------------------------------------------------
// Adaptado por: Sergio Fco. Hernández Machuca
// sfhm_clases@hotmail.com
//------------------------------------------------------------------------------
 
// Se utilizan tres Pines o Terminales DIGITALES para controlar LEDs.
int LedRojo = 13;
int LedVerde = 12;
int LedAzul = 11;

// Esta rutina de ajuste se ejecuta una sola vez cuando se oprime "Reset":
void setup() {                  
  pinMode(LedRojo, OUTPUT);   // Inicializa el Pin Digital como "salida".
  pinMode(LedVerde, OUTPUT);  // Inicializa el Pin Digital como "salida".
  pinMode(LedAzul, OUTPUT);   // Inicializa el Pin Digital como "salida".
}

// Esta rutina en lazo se ejecuta una y otra vez, por siempre:
void loop() {
  digitalWrite(LedRojo, HIGH);  // 
  digitalWrite(LedVerde, LOW);  // 
  delay(1000);                  // Espera por un segundo.
  digitalWrite(LedRojo, LOW);   // 
  digitalWrite(LedVerde, HIGH); // 
  delay(1000);                  // Espera por un segundo.
}
