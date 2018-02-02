// Esta rutina de ajuste se ejecuta una sola vez cuando se oprime "Reset":
void setup() {
  // Inicializa la comunicación serial a 9600 baudios:
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

