/*
  Lectura de un valor analógico.
  Lee el valor de un voltaje analógico presente en la terminal "0".
  
  Se emplea un fotoresistor en serie con una resistencia (de 220 ohms)
  
  Una de las terminales del fotoresistor se conecta a la terminal de tierra 
  (cero volts) y la otra terminal a la toma de + 5 volts a través de la 
  resistencia.
  
  La terminal entre la resistencia y el fotoresistor se conecta a la terminal 
  "A0" de Arduino.
  
  En lugar del fotoresistor también se puede emplear un potenciómetro. En caso 
  de emplear un potenciómetro la terminal central se conecta a "A0", uno de los
  extremos a la terminal de tierra (0 volts) y la otra terminal a la terminal
  positiva.
 */

// Esta rutina de ajuste se ejecuta una sola vez cuando se oprime "Reset":
void setup() {
  // Inicializa la comunicación serial a 9600 bits por segundo:
  Serial.begin(9600);
}

// Esta rutina en lazo se ejecuta una y otra vez, por siempre:
void loop() {
  // Lectura en la entrada del pin analógico "0":
  int sensorValue = analogRead(A0);
  // Impresión del valor leído en la terminal serial:
  Serial.println(sensorValue);
  delay(10);
}
