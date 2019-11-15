/// 07-09-2019 - CORRIENTES (ARGENTINA).
/// UNIVERSIDAD DE LA CUENCA DEL PLATA.
/// INGENIERIA EN SISTEMAS DE INFORMACION.
/// PRIMER AÑO SEGUNDO CUATRIMESTRE.
/// ARQUITECTURA DE COMPUTADORAS.
/// TRABAJO PRACTICO INTEGRADOR. 
/// ALUMNOS: 
/// -------- MAROTTOLI, ROMAN FRANCCESCO
/// -------- SANCHEZ, FERNANDO GUSTAVO
///
/// VERSION: 1.0
///
/// PROYECTO: INTERRUPCIONES + 7 SEGMENTOS + ASSEMBLY - PROTOTIPO REALIZADO CON ARDUINO.

/// https://www.arduino.cc/en/uploads/Main/Arduino_Uno_Rev3-schematic.pdf
/// http://numeroscelestes.blogspot.com/2017/03/instrucciones-de-ensamblador-dentro-de.html
/// http://numeroscelestes.blogspot.com/2017/03/usar-asm-esamblador-en-un-sketch-de.html
/// http://www.exa.unicen.edu.ar/catedras/tmicrocon/Material/Primer_ejemplo_en_Assembler.pdf


/// Fase de inicializacion.
// int A = 7;   //Defines all pins on the Arduino Uno board in order of connection.
// int B = 6;
// int C = 4;  // DOT is pin 5, not used in this example.
// int D = 3;
// int E = 2;
// int F = 8;
// int G = 9;
 
byte num0 = 0x3F;  //Hexadecimal format based upon the A-G, 0-9 Chart in excel and the wiring      // of the segment (refer to the on/off table image below).
byte num1 = 0x6;
byte num2 = 0x5B;
byte num3 = 0x4F;
byte num4 = 0x66;
byte num5 = 0x6D;
byte num6 = 0x7C;
byte num7 = 0x7;
byte num8 = 0x7F;
byte num9 = 0x6F;

//------->>> DEPRECATED

// const int ledRed01PIN = 7;
// const int ledRed02PIN = 8;
// const int SensorPin01 = 2;
// volatile int state = LOW;

//<<<------- 



void setup(){
  Serial.begin(9600);
  // pinMode(ledRed01PIN , OUTPUT); //Se definen el pin ledRed01PIN = 7 como salida
  // pinMode(ledRed02PIN , OUTPUT); //Se definen el pin ledRed01PIN = 8 como salida
  // ACA ESTA LA INTERRUPCION Q AL MOMENTO EN Q EL SENSOR ENVIA UNA SENIAL EJECUTA LA FUNCION puntoMayor
  // attachInterrupt(digitalPinToInterrupt(SensorPin01), PuntoMayor, CHANGE); 
  
  for (int m=0; m<=7; m++) {
    pinMode(2 + m , OUTPUT);
  }
  
  
}

/// Bucle de ejecucion principal que solo hace titilar al ledRed02PIN = 8.
void loop(){
	// digitalWrite(ledRed02PIN, HIGH);
	// delay(150);
	// digitalWrite(ledRed02PIN, LOW);
	delay(250);
	for (int m=0; m<=7; m++) {
		digitalWrite(2 + m, LOW);
	}

	delay(250);
	for (int m=0; m<=7; m++) {
		digitalWrite(2 + m, HIGH);
	}

}

/// FUNCION 
// void PuntoMayor(){
  // state = !state; // se niega el valor de la variable volatile durante la ejecucion de la interrupcion
  // digitalWrite(ledRed01PIN , state); // y este nuevo valor se 
// }


  

//void setup() {       // Our setup routine         
  // pinMode(A, OUTPUT); // Making all pins outputs
  // pinMode(B, OUTPUT);
  // pinMode(C, OUTPUT);
  // pinMode(D, OUTPUT);
  // pinMode(E, OUTPUT);
  // pinMode(F, OUTPUT);
  // pinMode(G, OUTPUT);
  // pinMode(10,OUTPUT);
  
  
//}

// void loop() {   // Loops forever
	// on(num0);   // Passing "num0" to the function  "on()" defined above to display "0"
	// delay(1000);   // Delay for 1 second to see the "0"
	// on(num1);  // Change to "1"
	// delay(1000); 
	// on(num2);  
	// delay(1000);
	// on(num3);  
	// delay(1000);
	// on(num4);  
	// delay(1000);
	// on(num5);  
	// delay(1000);
	// on(num6);  
	// delay(1000);
	// on(num7);
	// delay(1000);
	// on(num8);  
	// delay(1000);  
	// on(num9);  
	// delay(1000);
// }

// This function turns on the correct pins to display numbers passed to it         // through the variable "num".
// void on(byte num){
	// int result = bitRead(num, 0);  // Read the first binary entry in num and stores it in result.
 
	// Check to see if this segment should be on.
	// if (result == 1){digitalWrite(A, HIGH);}   // Turns on the segment.
    // else   // Otherwise, it turns it off.
    // {digitalWrite(A, LOW);}  // Turns segment off.
 
      // result = bitRead( num, 1);  // Same thing for the 6 remaining segments.
 
      // if (result == 1)
 
    // {digitalWrite(B, HIGH);}
    // else
    // {digitalWrite(B, LOW);}     
    // result = bitRead( num, 2);
 
      // if (result == 1)
 
    // {digitalWrite(C, HIGH);}
    // else
    // {digitalWrite(C, LOW);}    
   // result = bitRead( num, 3);
 
      // if (result == 1)
 
    // {digitalWrite(D, HIGH);}
    // else
    // {digitalWrite(D, LOW);}    
   // result = bitRead( num, 4);
 
      // if (result == 1)
    // {digitalWrite(E, HIGH);}
    // else
    // {digitalWrite(E, LOW);}
    
   // result = bitRead( num, 5);  
      // if (result == 1)
    // {digitalWrite(F, HIGH);}
    // else
    // {digitalWrite(F, LOW);}    
    
   // result = bitRead( num, 6);
      // if (result == 1)
    // {digitalWrite(G, HIGH);}
    // else
    // {digitalWrite(G, LOW);}
  // }