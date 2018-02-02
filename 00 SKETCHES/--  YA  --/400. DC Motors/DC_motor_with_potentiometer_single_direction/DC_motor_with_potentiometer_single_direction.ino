//------------------------------------------------------------------------------
// Programa para Ejercitar un Motor de CD (Corriente Directa)
//
// Para controlar la velocidad del motor se emplean señales moduladas por el
// del pulso que presentan, conocidas como señales PWM (Pulse Width Modulation)
//
// Se usa un potenciómetro para avanzar el movimiento.
//------------------------------------------------------------------------------

//-----[ Constantes y Variables ]-----
// Terminales PWM (Arduido) conectadas al módulo L298n para controlar velocidad:
int E1 = 5;   //
int M1 = 4;   //
int E2 = 6;   //
int M2 = 7;   //
//------------------------------------------------------------------------------
void setup() {
  Serial.begin (9600);  // Velocidad de la comunicación
  pinMode(M1, OUTPUT);  // Configurada como salida
  pinMode(M2, OUTPUT);  // Configurada como salida
}
//------------------------------------------------------------------------------
void loop() {
  int potentiometerVal = analogRead(A0);  // Lectura del potenciómetro
  Serial.println(potentiometerVal);       // Impresión del valor
  move_motors(potentiometerVal);          // Movimiento del motor
}
//------------------------------------------------------------------------------
//-----[ RUTINA del Movimiento del Motor ]-----
void move_motors(int potValue) {
  int mappedVal = map(potValue, 0, 1023, 0, 255); // Cálculo del valor
  digitalWrite(M1, HIGH);       // Tipo de movimiento ...
  digitalWrite(M2, HIGH);       // ... del motor
  analogWrite(E1, mappedVal);   // Señal de control de la velocidad (PWM)
  analogWrite(E2, mappedVal);   // Señal de control de la velocidad (PWM)
  delay(30);
}
//------------------------------------------------------------------------------
