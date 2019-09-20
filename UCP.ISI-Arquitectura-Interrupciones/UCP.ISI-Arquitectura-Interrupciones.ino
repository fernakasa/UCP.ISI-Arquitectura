/// 07-09-2019 - CORRIENTES (ARGENTINA).
/// UNIVERSIDAD DE LA CUENCA DEL PLATA.
/// INGENIERIA EN SISTEMAS DE INFORMACION.
/// ARQUITECTURA DE COMPUTADORAS.
/// EJERCICIO 02 - PRIMER AÑO SEGUNDO CUATRIMESTRE.
/// ALUMNOS: 
/// -------- SANCHEZ, FERNANDO GUSTAVO
/// -------- MAROTTOLI, ROMAN FRANCCESCO
/// -------- ARGAÑARAZ, JORGE VICTOR ADAN
///
/// VERSION: 1.0
/// ACTUALIZACION: 07-09-2019
///
/// PROYECTO: INTERRUPCIONES - PROTOTIPO REALIZADO CON ARDUINO.


/// Fase de inicializacion.
const int ledRed01PIN = 7;
const int ledRed02PIN = 8;
const int SensorPin01 = 2;
volatile int state = LOW;

void setup(){
  Serial.begin(9600);
  pinMode(ledRed01PIN , OUTPUT); //Se definen el pin ledRed01PIN = 7 como salida
  pinMode(ledRed02PIN , OUTPUT); //Se definen el pin ledRed01PIN = 8 como salida
  // ACA ESTA LA INTERRUPCION Q AL MOMENTO EN Q EL SENSOR ENVIA UNA SENIAL EJECUTA LA FUNCION puntoMayor
  attachInterrupt(digitalPinToInterrupt(SensorPin01), PuntoMayor, CHANGE); 
}

/// Bucle de ejecucion principal que solo hace titilar al ledRed02PIN = 8.
void loop(){
  digitalWrite(ledRed02PIN, HIGH);
  delay(150);
  digitalWrite(ledRed02PIN, LOW);
  delay(150);
}

/// FUNCION 
void PuntoMayor(){
  state = !state; // se niega el valor de la variable volatile durante la ejecucion de la interrupcion
  digitalWrite(ledRed01PIN , state); // y este nuevo valor se 
}
