//------------------------------------------------------------------------------
// Programa para Ejercitar un Motor de CD (Corriente Directa)
//
// Para controlar la velocidad del motor se emplean señales moduladas por el
// del pulso que presentan, conocidas como señales PWM (Pulse Width Modulation)
//
// Se emplea un potenciómetro para determinar cuánto se moverá un motor.
//------------------------------------------------------------------------------

//-----[ Constantes y Variables ]-----
// Terminales PWM (Arduido) conectadas al módulo L298n para controlar velocidad:
int E1 = 5;   //
int M1 = 4;   //
int E2 = 6;   //
int M2 = 7;   //                      
//------------------------------------------------------------------------------
void setup() 
{ 
    Serial.begin (9600);  // Velocidad de la comunicación
    pinMode(M1, OUTPUT);  // Configurada como salida  
    pinMode(M2, OUTPUT);  // Configurada como salida
} 
//------------------------------------------------------------------------------
void loop() 
{ 
  int potentiometerVal = analogRead(A0);  // Lectura de la señal del Pot
  Serial.println(potentiometerVal);       // Impresión del valor
  move_motors(potentiometerVal);          // Movimiento del motor
}
//------------------------------------------------------------------------------
//-----[ RUTINA para Mover el Motor ]-----
void move_motors(int potValue)
{
  if (potValue < 512)                  // Verifica en que dirección está el Pot
   {                                   // a la Izquierda o a la Derecha
     int mappedVal = map(potValue,0,512,0,255); // Calcula el valor ajustado
     // Vamos hacia Adelante
    digitalWrite(M1,HIGH);   
    digitalWrite(M2, HIGH);       
    analogWrite(E1, mappedVal);       // Señal de control de la velocidad (PWM)
    analogWrite(E2, mappedVal);       // Señal de control de la velocidad (PWM)
    delay(30); 
   } else
   {
    // Vamos hacia Atrás
    int mappedVal = map(potValue-512,0,512,0,255); // Calcula el valor ajustado
    digitalWrite(M1,LOW);                  
    digitalWrite(M2, LOW);       
    analogWrite(E1, mappedVal);       // Señal de control de la velocidad (PWM)
    analogWrite(E2, mappedVal);       // Señal de control de la velocidad (PWM)
    delay(30); 
   }
}
//------------------------------------------------------------------------------
