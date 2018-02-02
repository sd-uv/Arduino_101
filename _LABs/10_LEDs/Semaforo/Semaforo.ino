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

  // Primero apagamos todos los LEDs
  digitalWrite(LedRojo, LOW);     //
  digitalWrite(LedVerde, LOW);    //
  digitalWrite(LedAzul, LOW);     //
}
//---------------------------------------------------------------------
// Esta rutina en lazo se ejecuta una y otra vez, por siempre:
void loop() {
  digitalWrite(LedAzul, LOW);   //
  digitalWrite(LedRojo, LOW);   //
  digitalWrite(LedVerde, HIGH); // VERDE
  delay(5000);
  digitalWrite(LedRojo, LOW);   //
  digitalWrite(LedVerde, LOW);  //
  digitalWrite(LedAzul, HIGH);  // AMARILLO (bueno, Azul)
  delay(2000);
  digitalWrite(LedAzul, LOW);   //
  digitalWrite(LedVerde, LOW);  //
  digitalWrite(LedRojo, HIGH);  // ROJO
  delay(5000);
}
