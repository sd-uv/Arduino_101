//------------------------------------------------------------------------------
// Programa para Ejercitar un Motor de CD (Corriente Directa)
//
// Para controlar la velocidad del motor se emplean señales moduladas por el
// del pulso que presentan, conocidas como señales PWM (Pulse Width Modulation)
//------------------------------------------------------------------------------

//-----[ Constantes y Variables ]-----
// Terminales PWM (Arduido) conectadas al módulo L298n para controlar velocidad:
int E1 = 5;   //
int M1 = 4;   //
int E2 = 6;   //
int M2 = 7;   //
//------------------------------------------------------------------------------
void setup() {
  pinMode(M1, OUTPUT);   // Configurada como salida
  pinMode(M2, OUTPUT);   // Configurada como salida
}
//------------------------------------------------------------------------------
void loop() {
  int value;
  for (value = 0 ; value <= 255; value += 1) {
    digitalWrite(M1, HIGH);   // Encendido de un motor
    digitalWrite(M2, HIGH);   // Encendido de otro motor
    analogWrite(E1, value);   // Control de velocidad (PWM)
    analogWrite(E2, value);   // Control de velocidad (PWM)
    delay(30);
  }
}
//------------------------------------------------------------------------------
