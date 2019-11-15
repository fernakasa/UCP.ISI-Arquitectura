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

int contador = 5;
// lo de arriba borrar
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
  
  delay_count = FRECUENCIA_RELOJ_CPU / 400;
}

/// Bucle de ejecucion principal que solo hace titilar al ledRed02PIN = 8.
void loop(){
  asmLedHigh();
  asmLedPrint(contador); //render de los numeros
  asmDelay(20);
  asmLedLow();
  asmLedAllLow;
  asmDelay(20);  
  // if (contador == 9){
  //   contador = 0;
  //   for (int i = 0; i < 3; i++){
  //     asmLedAllHigh();
  //     asmDelay(20);
  //     asmLedAllLow();
  //     asmDelay(20); 
  //   }
  // }else{
  //   contador++;
  // }
}

/// FUNCION 
void asmLedHigh(){
  /// SBI -> Comando que pone en High el puerto
  /// %0, %1 -> Son dos variables "Formateadas" que referencian a las entradas en la seccion de InputOperands.
  /// "\n\t" indicador de fin de linea (end-of-line), equivalente al (;) de C, pone una nueva linea (\n) y luego que hace un tabulador (\t) ** Importantisimo! 
  /// :: Estos indicadores dividen las secciones de la sentencia asm.
  /// "I" (_SFR_IO_ADDR(PORTB)), "I" (PORTB5) son 2 variables de entrada declaradas en el InputOperands que tomarian el lugar de %0, %1 respectivamente.

  asm volatile(
  "SBI %0, %1 \n\t"   //digitalWrite(13, HIGH);
  :: "I" (_SFR_IO_ADDR(PORTB)), "I" (PORTB5)
  );
}

void asmLedLow(){
  /// CBI -> Comando que pone en LOW el puerto
  /// El resto del codigo se mantiene igual al de PinUp
  asm volatile(
  "CBI %0, %1 \n\t"   //digitalWrite(13, LOW);
  :: "I" (_SFR_IO_ADDR(PORTB)), "I" (PORTB5)
  );
}

void asmDelay(uint8_t ms){
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

void asmLed(int pin, int state){
  switch (pin){
  case 0: // Pin 2
    if (state == 0){
      asm volatile("CBI %0, %1 \n\t" :: "I" (_SFR_IO_ADDR(PORTD)), "I" (PORTD2));
    }else{
      asm volatile("SBI %0, %1 \n\t" :: "I" (_SFR_IO_ADDR(PORTD)), "I" (PORTD2));
    }      
  break;
  case 1: // Pin 3
    if (state == 0){
      asm volatile("CBI %0, %1 \n\t" :: "I" (_SFR_IO_ADDR(PORTD)), "I" (PORTD3));
    }else{
      asm volatile("SBI %0, %1 \n\t" :: "I" (_SFR_IO_ADDR(PORTD)), "I" (PORTD3));
    }      
  break;
  case 2: // Pin 4
    if (state == 0){
      asm volatile("CBI %0, %1 \n\t" :: "I" (_SFR_IO_ADDR(PORTD)), "I" (PORTD4));
    }else{
      asm volatile("SBI %0, %1 \n\t" :: "I" (_SFR_IO_ADDR(PORTD)), "I" (PORTD4));
    }      
  break;
  case 3: // Pin 5
    if (state == 0){
      asm volatile("CBI %0, %1 \n\t" :: "I" (_SFR_IO_ADDR(PORTD)), "I" (PORTD5));
    }else{
      asm volatile("SBI %0, %1 \n\t" :: "I" (_SFR_IO_ADDR(PORTD)), "I" (PORTD5));
    }      
  break;
  case 4: // Pin 6
    if (state == 0){
      asm volatile("CBI %0, %1 \n\t" :: "I" (_SFR_IO_ADDR(PORTD)), "I" (PORTD6));
    }else{
      asm volatile("SBI %0, %1 \n\t" :: "I" (_SFR_IO_ADDR(PORTD)), "I" (PORTD6));
    }      
  break;
  case 5: // Pin 7
    if (state == 0){
      asm volatile("CBI %0, %1 \n\t" :: "I" (_SFR_IO_ADDR(PORTD)), "I" (PORTD7));
    }else{
      asm volatile("SBI %0, %1 \n\t" :: "I" (_SFR_IO_ADDR(PORTD)), "I" (PORTD7));
    }      
  break;
  case 6: // Pin 8
    if (state == 0){
      asm volatile("CBI %0, %1 \n\t" :: "I" (_SFR_IO_ADDR(PORTB)), "I" (PORTB0));
    }else{
      asm volatile("SBI %0, %1 \n\t" :: "I" (_SFR_IO_ADDR(PORTB)), "I" (PORTB0));
    }      
  break;
  }
}

void asmLedAllLow(){
  for (int i=0; i<=6; i++) {
    asmLed(i,0);
  }
}

void asmLedAllHigh(){
  for (int i=0; i<=6; i++) {
    asmLed(i,1);
  }
}

void asmLedPrint(int count){
  switch (count){
    case 0: // Dibuja 0
      asmLedAllHigh();
      asmLed(6,LOW);
    break;
    case 1: // Dibuja 1
      asmLedAllLow();
      asmLed(1,HIGH);
      asmLed(2,HIGH);
    break;
    case 2: // Dibuja 2
      asmLedAllHigh();
      asmLed(2,LOW);
      asmLed(5,LOW);
    break;
    case 3: // Dibuja 3
      asmLedAllHigh();
      asmLed(4,LOW);
      asmLed(5,LOW);
    break;
    case 4: // Dibuja 4
      asmLedAllHigh();
      asmLed(0,LOW);
      asmLed(3,LOW);
      asmLed(4,LOW);
    break;
    case 5: // Dibuja 5
      asmLedAllHigh();
      asmLed(1,LOW);
      asmLed(4,LOW);
    break;
    case 6: // Dibuja 6
      asmLedAllHigh();
      asmLed(1,LOW);
    break;
    case 7:
      asmLedAllLow();
      asmLed(0,HIGH);
      asmLed(1,HIGH);
      asmLed(2,HIGH);
    break;
    case 8:
      asmLedAllHigh();
    break;
    case 9:
      asmLedAllHigh();
      asmLed(4,LOW);
    break;
  }
}

// Ejemplos	
// byte x = 33; // crea e inicializa x con el valor 33 (00100001 en binario)
// byte a = bitRead(x, 5);	// crea e inicializa a con el valor 1, ya que bitRead retorna el valor del 5o bit de la variable x
