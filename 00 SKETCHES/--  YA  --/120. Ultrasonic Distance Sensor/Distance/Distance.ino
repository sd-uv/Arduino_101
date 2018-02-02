//------------------------------------------------------------------------------
// Programa para pruebas simples del Detector de Distancias HC - SR04 Ping 
//------------------------------------------------------------------------------

/*
Ejercicio del sensor de distancia ultrasónico HC-SR04

Las terminales que se usarán son:

--> VCC   -- Terminal + 5 Volts de la tarjeta Arduino 
--> GND   -- Terminal Gnd de la tarjeta Arduino 
--> Echo  -- A pin 12 
--> Trig  -- A pin 13
*/

#define trigPin 13    // Terminal para el disparo
#define echoPin 12    // Terminal para el Eco

//------------------------------------------------------------------------------
void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);   // Ajuste de Salida
  pinMode(echoPin, INPUT);    // Ajuste de Entrada
}

//------------------------------------------------------------------------------
void loop() {
  long duration, distance;      // Variables para las operaciones
  digitalWrite(trigPin, LOW);   // LÍNEA AGREGADA al sistema básico
  delayMicroseconds(2);         // LÍNEA AGREGADA al sistema básico
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000);    // LÍNEA REMOVIDA
  delayMicroseconds(10);        // LÍNEA AGREGADA al sistema básico
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1; // Cálculo en relación a la velocidad a la cual
                                  // viaja el sonido en el aire.
  if (distance >= 200 || distance <= 0){
    Serial.println("Fuera de Rango");
  }
  else {
    Serial.print(distance);
    Serial.println(" cms");
  }
  delay(250);
}
//------------------------------------------------------------------------------
