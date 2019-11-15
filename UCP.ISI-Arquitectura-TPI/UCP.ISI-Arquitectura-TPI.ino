/// 17-11-2019 - CORRIENTES (ARGENTINA).
/// UNIVERSIDAD DE LA CUENCA DEL PLATA.
/// INGENIERIA EN SISTEMAS DE INFORMACION.
/// PRIMER AÑO SEGUNDO CUATRIMESTRE.
/// ARQUITECTURA DE COMPUTADORAS.
/// TRABAJO PRACTICO INTEGRADOR. 
/// ALUMNOS: 
/// -------- BOATTINI, NICOLAS.
/// -------- SANCHEZ, FERNANDO GUSTAVO.
///
/// VERSION: 1.0
/// ACTUALIZACION: 15-11-2019
///
/// PROYECTO: INTERRUPCIONES + 7 SEGMENTOS + ASSEMBLY - PROTOTIPO REALIZADO CON ARDUINO.
///
/// https://www.arduino.cc/en/uploads/Main/Arduino_Uno_Rev3-schematic.pdf
/// http://numeroscelestes.blogspot.com/2017/03/instrucciones-de-ensamblador-dentro-de.html
/// http://numeroscelestes.blogspot.com/2017/03/usar-asm-esamblador-en-un-sketch-de.html
/// http://www.exa.unicen.edu.ar/catedras/tmicrocon/Material/Primer_ejemplo_en_Assembler.pdf
///
/// ******************************************************************************************************** ///

/// La sentencia asm esta seccionada por :
///     asm volatile(
///                       AssemblerTemplate
///                       : OutputOperands 
///                     [ : InputOperands      \ opcionales
///                     [ : Clobbers ] ]       /
///                   )
///
/// AssemblerTemplate: Texto literal con el codigo ensamblador
/// OutputOperands: variables con datos de salida obtenidos de la ejecucion del codigo ensamblador
/// InputOperands: variables con datos de entrada a utilizarce en la ejecucion del codigo ensamblador
/// Clobbers: son listas que se puede usar desde assembler.
///
/// ******************************************************************************************************** ///
#define FRECUENCIA_RELOJ_CPU 16000000

/// Fase de inicializacion. 
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

uint16_t delay_count;      // la definicion del tipo de dato uint8_t es similar a usar  unsigned char
void asm_delay(uint8_t ms);   // prototipo de la función

void setup(){
  Serial.begin(9600);
  // ACA ESTA LA INTERRUPCION Q AL MOMENTO EN Q EL SENSOR ENVIA UNA SENIAL EJECUTA LA FUNCION puntoMayor
  // attachInterrupt(digitalPinToInterrupt(SensorPin01), PuntoMayor, CHANGE);   
  for (int m=0; m<=7; m++) {
    pinMode(2 + m , OUTPUT);
  }
  
  asm volatile(
  "SBI %0, %1 \n\t"    //pinMode(13, OUTPUT);
  :: "I" (_SFR_IO_ADDR(DDRB)), "I" (DDB5)
  );
  delay_count= FRECUENCIA_RELOJ_CPU;
}


/// Bucle de ejecucion principal que solo hace titilar al ledRed02PIN = 8.
void loop(){
  prender();
  for (int m=0; m<=7; m++){
    digitalWrite(2 + m, HIGH);
  }
  pausas(5000);
  apagar();
  for (int m=0; m<=7; m++){
    digitalWrite(2 + m, LOW);
  }
  pausas(5000);  
}

/// FUNCION 
void prender(){
  /// SBI -> Comando que pone en High el puerto
  /// %0, %1 -> Son dos variables "Formateadas" que referencian a las entradas en la seccion de InputOperands
  /// "\n\t" indica al compilador que ponga una nueva linea (\n) y luego que haga un tabulador (\t) ** Importantisimo! 
  /// :: identificador de fin de linea (end-of-line), equivalente al (;) de C
  /// 

  asm volatile(
  "SBI %0, %1 \n\t"   //digitalWrite(13, HIGH);
  :: "I" (_SFR_IO_ADDR(PORTB)), "I" (PORTB5)
  );
}

void apagar(){
  asm volatile(
  "CBI %0, %1 \n\t"   //digitalWrite(13, LOW);
  :: "I" (_SFR_IO_ADDR(PORTB)), "I" (PORTB5)
  );
}


void pausas(uint8_t ms){
  uint16_t cnt;      // variable cnt,tipo de datos de 2 bytes sin signo
  asm volatile(
    "\n"
    "L_dl1%=:" "\n\t"
    "mov %A0, %A2" "\n\t"
    "mov %B0, %B2" "\n"
    "L_dl2%=:" "\n\t"
    "sbiw %A0, 1" "\n\t"
    "brne L_dl2%=" "\n\t"
    "dec %1" "\n\t"
    "brne L_dl1%=" "\n\t"
    : "=&w" (cnt)
    : "r" (ms), "r" (delay_count)
  );
}
