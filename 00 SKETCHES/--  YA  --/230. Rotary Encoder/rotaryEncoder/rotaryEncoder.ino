//------------------------------------------------------------------------------
// Programa para Ejercitar un Encodificador Rotativo
//------------------------------------------------------------------------------

//Original sketch: https://bigdanzblog.wordpress.com/2014/08/16/using-a-ky040-rotary-encoder-with-arduino/
//Modified by Peter Dalmaris, July 2015

//-----[ Constantes y Variables ]-----
const int PinCLK = 2;                 // Usado para generar interrupciones, señal CLK
const int PinDT = 3;                  // Usado para lectura de la señal DT
const int PinSW = 8;                  // Usado para el interruptor de presión

static long     virtualPosition  = 0; // Sin calificador STATIC no cuenta correctamente
//------------------------------------------------------------------------------
//-----[ Atención a INTERRUPCIÓN ]-----
void isr0 ()  {
  detachInterrupt(0);                 // No se aceptan otras interrupciones
  static unsigned long lastInterruptTime = 0; // Última vez que se interrumpió
  unsigned long interruptTime = millis();     // Temporizado actual
  // Si las interrupciones ocurren más rápido que en 5ms, se asume que es un erbote y se ignora
  if (interruptTime - lastInterruptTime > 5) {
    if (!digitalRead(PinDT))
      virtualPosition++;
    else
      virtualPosition--;
  }
  lastInterruptTime = interruptTime;
  attachInterrupt (0, isr0, RISING);
} // ISR0
//------------------------------------------------------------------------------
//-----[ AJUSTES ]-----
void setup ()  {
  pinMode(PinCLK, INPUT);         // Se programa como entrada
  pinMode(PinDT, INPUT);          // Se programa como entrada
  pinMode(PinSW, INPUT);          // Se programa como entrada
  attachInterrupt (0, isr0, RISING);  // La interrupción 0 siempre está conectada 
                                      // al pin 2 en Arduino UNO
  Serial.begin (9600);
  Serial.println("Inicio");
}
//------------------------------------------------------------------------------
//-----[ Programa PRINCIPAL ]-----
void loop ()  {
  int lastCount = 0;
  while (true) {
    if (!(digitalRead(PinSW))) {      // Verifica si se oprimió el interruptor 
      virtualPosition = 0;            // SI, entonces inicia a cero el contador
      while (!digitalRead(PinSW)) {}  // Espera hasta que se libere el interruptor
      delay(10);                      // Para evitar rebotes 
      Serial.println("Reset");        // Aquí se identificaría un encodificador defectuoso
                                      // 
    }
    if (virtualPosition != lastCount) {
      lastCount = virtualPosition;
      Serial.print("Cuenta: ");
      Serial.println(virtualPosition);
    }
  }
}
//------------------------------------------------------------------------------
