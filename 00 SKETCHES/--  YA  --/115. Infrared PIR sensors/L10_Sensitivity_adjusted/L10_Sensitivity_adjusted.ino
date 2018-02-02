//------------------------------------------------------------------------------
// Programa para pruebas del sensor de presencia PIR
//------------------------------------------------------------------------------

//-----[ DEFINICIONES de CONSTANTES y VARIABLES ]-----
int ledPin = 13;      // Terminal del LED (el LED que está en la tarjeta)      
int inputPin = 3;     // Terminal para conectar la salida del sensor PIR 
int pirState = true;  // Se inicia asumiendo que no hay movimiento.
int val = 0;          // Variable que manetiene la lectura del Pin de Estado.
// Si el sensor envía una señal de "bajo" por más tiempo que el especificado 
// abajo, se supondrá que no existe actividad:
int minimummSecsLowForInactive = 5000;
long unsigned int timeLow;  //                   
boolean takeLowTime;        //
// Este es el tiempo que se le da al sensor para calibrares. De acuerdo a la
// hoja de datos es un tiempo entre 10 y 60 segundos.
int calibrationTime = 30;  

//------------------------------------------------------------------------------
//-----[ Sección de AJUSTES ]-----
void setup() {
  pinMode(ledPin, OUTPUT);      // Declaración de la Salida para el LED
  pinMode(inputPin, INPUT);     // Declaración de la Entrada para el Sensor
  Serial.begin(9600);           // Velocidad de la comunicación serial
  
  // Tiempo otorgado a la calibración del sensor
  Serial.print(" Calibrando Sensor ");
  for(int i = 0; i < calibrationTime; i++){
    Serial.print(".");
    delay(500);
    }
  Serial.println(" Listo ");
  Serial.println("SENSOR ACTIVO");
  delay(50);
}

//------------------------------------------------------------------------------
//-----[ Programa PRINCIPAL ]-----
void loop(){
  val = digitalRead(inputPin);    // Lectura del valor de entrada
  if (val == HIGH) {              // Verifica si la entrada está en HIGH
    digitalWrite(ledPin, HIGH);   // Enciende el LED
    if (pirState) {
      // Se acaba de encender el sistema
      pirState = false;
      Serial.println("- Movimiento Detectado -");
      // Sólo queremos imprimir el cambio de salida, no el estado
      delay(50);
    }
   takeLowTime = true;
  } else {
    digitalWrite(ledPin, LOW);    // Apagar el LED
    
    if (takeLowTime){
      timeLow = millis();
      takeLowTime = false;
    }
    
    if(!pirState && millis() - timeLow > minimummSecsLowForInactive){
     pirState = true; 
     Serial.println(" ## No Hay Movimiento Detectado ##");     
     delay(50);
    }
  }
}

