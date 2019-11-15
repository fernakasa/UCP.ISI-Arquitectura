/// 07-09-2019 - CORRIENTES (ARGENTINA).
/// UNIVERSIDAD DE LA CUENCA DEL PLATA.
/// INGENIERIA EN SISTEMAS DE INFORMACION.
/// ARQUITECTURA DE COMPUTADORAS.
/// EJERCICIO 02 - PRIMER AÑO SEGUNDO CUATRIMESTRE.
/// ALUMNOS: 
/// -------- BOATTINI, NICOLAS.
/// -------- SANCHEZ, FERNANDO GUSTAVO.
///
/// VERSION: 1.0
/// ACTUALIZACION: 15-11-2019
///
/// PROYECTO: INTERRUPCIONES - PROTOTIPO REALIZADO CON ARDUINO.

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

#define FRECUENCIA_RELOJ_CPU 16000000

uint16_t delay_count;      // la definicion del tipo de dato uint8_t es similar a usar  unsigned char
void asm_delay(uint8_t ms);   // prototipo de la función


void setup(){
  asm volatile(
  "SBI %0, %1 \n\t"    //pinMode(13, OUTPUT);
  :: "I" (_SFR_IO_ADDR(DDRB)), "I" (DDB5)
  );
  delay_count= FRECUENCIA_RELOJ_CPU;
}


/// Bucle de ejecucion principal que solo hace titilar al ledRed02PIN = 8.
void loop(){
  prender();
  pausas(1000);
  apagar();
  pausas(1000);
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
