//------------------------------------------------------------------------------
// Programa para Ejercitar un Motor de CD (Corriente Directa)
//
// Para controlar la velocidad del motor se emplean señales moduladas por el
// del pulso que presentan, conocidas como señales PWM (Pulse Width Modulation)
//
// Se emplea un módulo ultrasónico medidor de distancia para determinar hasta
// cuándo se moverá un motor.
//------------------------------------------------------------------------------

//-----[ Constantes y Variables ]-----
// Terminales PWM (Arduido) conectadas al módulo L298n para controlar velocidad:
int E1 = 5;   //
int M1 = 4;   //
int E2 = 6;   //
int M2 = 7;   //

                  
#define trigPin 13  // Pin (Arduino) para el Disparo del sensor ultrasónico
#define echoPin 12  // Pin (Arduino) para lectura de la señal de Eco.
//------------------------------------------------------------------------------
void setup() 
{ 
    Serial.begin (9600);      // Velocidad de la comunicación
    pinMode(M1, OUTPUT);      // Configurada como salida 
    pinMode(M2, OUTPUT);      // Configurada como salida
    pinMode(trigPin, OUTPUT); // Configurada como salida
    pinMode(echoPin, INPUT);  // Configurada como entrada
} 
//------------------------------------------------------------------------------
void loop() 
{ 
  long duration, distance;      // Variables 
  digitalWrite(trigPin, LOW);   // Preparación para el Disparo ultrasónico
  delayMicroseconds(2);         // Retardo para ajustes
  digitalWrite(trigPin, HIGH);  // Generación de la señal de Disparo
  delayMicroseconds(10);        // Retardo...
  digitalWrite(trigPin, LOW);   // Para no generar un falso disparo
  duration = pulseIn(echoPin, HIGH);  // Lectura del tiempo que tarda
                                      // en "rebotar" la señal
  distance = (duration/2) / 29.1; // Cálculo de la distancia

  move_motors(distance);        // Mover al motor la cantidad correspondiente
                                // a la distancia sensada
}
//------------------------------------------------------------------------------
//-----[ RUTINA para Mover el Motor ]-----
void move_motors(int distance)
{
  if (distance >= 50 ){           // Partir de una distancia mínima
    Serial.print(distance);       // Imprime la distancia a "recorrer"
    Serial.println(" cm - 255");  // Ajuste
    digitalWrite(M1,HIGH);        // Enciende el motor
    digitalWrite(M2, HIGH);       // 
    analogWrite(E1, 0);           // Señal de control de la velocidad (PWM)
    analogWrite(E2, 0);           // 
    delay(30);                    // Retardo
  }
  else {
    int mappedVal = map(distance,0,50,0,255);
    Serial.print(distance);         //
    Serial.print(" cm - ");         //
    Serial.println(mappedVal);      // Valor calculado
    digitalWrite(M1,HIGH);          // Encendido del motor  
    digitalWrite(M2, HIGH);         // 
    analogWrite(E1, 255-mappedVal); // Señal de control de la velocidad (PWM)
    analogWrite(E2, 255-mappedVal); // Señal de control de la velocidad (PWM)
    delay(30);                      // Retardo
  }
}
//------------------------------------------------------------------------------
