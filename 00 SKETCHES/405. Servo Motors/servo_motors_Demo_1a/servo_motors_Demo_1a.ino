//------------------------------------------------------------------------------
// Programa para Ejercitar un Servo Motor
//
// Para controlar la velocidad del motor se emplean señales moduladas por el
// del pulso que presentan, conocidas como señales PWM (Pulse Width Modulation)
//------------------------------------------------------------------------------
//-----[ BIBLIOTECA requerida ]-----
#include <Servo.h>

// Creación de un objeto
Servo myservo;  // Crea un objeto (instancia) para controlar un servo
                // Se pueden crear hasta 8 objetos representando servos
//-----[ Constantes y Variables ]-----
int pos = 0;    // Variable para almacenar la posición del servo
//------------------------------------------------------------------------------
void setup() {
  myservo.attach(9);  // Conecta la señal del servo al pin 9 (Arduino)
}
//------------------------------------------------------------------------------
void loop() {
  for (pos = 0; pos < 180; pos += 1) {  // Barrido de 0 a 180 grados
                                        // en etapas de 1 grado
    myservo.write(pos);     // Indícale al servo que se posicione como lo marca
    delay(15);              // la variable 'pos', espera a que llegue. 
  }
  for (pos = 180; pos >= 1; pos -= 1) { // Ahora se recorre de 180 a 0 grados

    myservo.write(pos);     // Indícale al servo que se posicione como lo marca
    delay(15);              // la variable 'pos', espera a que llegue. 
  }
}
//------------------------------------------------------------------------------
