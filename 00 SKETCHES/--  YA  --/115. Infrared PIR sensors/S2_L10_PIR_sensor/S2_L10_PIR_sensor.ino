//------------------------------------------------------------------------------
// Programa para pruebas simples del sensor de presencia PIR
//------------------------------------------------------------------------------

//-----[ DEFINICIONES de CONSTANTES y VARIABLES ]-----
int ledPin = 13;      // Terminal del LED (el LED que está en la tarjeta)      
int inputPin = 2;     // Terminal para conectar la salida del sensor PIR 
int pirState = true;  // Se inicia asumiendo que no hay movimiento
int val = 0;          // Variable que manetiene la lectura del Pin de Estado

//------------------------------------------------------------------------------
//-----[ Sección de AJUSTES ]-----
void setup() {
  pinMode(ledPin, OUTPUT);      // Declaración de la Salida para el LED
  pinMode(inputPin, INPUT);     // Declaración de la Entrada para el Sensor
  Serial.begin(9600);           // Velocidad de la comunicación serial
}

 //------------------------------------------------------------------------------
//-----[ Programa PRINCIPAL ]-----
void loop(){
  val = digitalRead(inputPin);    // Lectura del valor de entrada
  if (val == HIGH) {              // Verifica si la entrada está en HIGH
    digitalWrite(ledPin, HIGH);   // Enciende el LED
    if (pirState == LOW) {
      // Se acaba de encender el sistema
      Serial.println("-- Movimiento Detectado --");
      // Sólo queremos imprimir el cambio de salida, no el estado
      pirState = HIGH;
    }
  } else {
    digitalWrite(ledPin, LOW);    //Apagar el LED
    if (pirState == HIGH){
      // Se acaba de apagar
      Serial.println("## Sin Movimiento ##");
      // Sólo queremos imprimir el cambio de salida, no el estado
      pirState = LOW;
    }
  }
}

