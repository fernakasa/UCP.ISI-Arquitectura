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
/// PROYECTO: 7 SEGMENTOS + ASSEMBLY - PROTOTIPO REALIZADO CON ARDUINO.
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
int contador = 0;
int modo = 0;
int ValorA = 0;
int ValorB = 0;
int resultado = 0;
int operacion = 0;
int estadoBoton = 0;
uint16_t delay_count;      // la definicion del tipo de dato uint8_t es similar a usar  unsigned char
void asm_delay(uint8_t ms);   // prototipo de la función

void setup(){
  Serial.begin(9600);
  delay_count = FRECUENCIA_RELOJ_CPU / 400;
  asmPinUp();
  asmLed(12,1);
}

/// Bucle de ejecucion principal que solo hace titilar al ledRed02PIN = 8.
void loop(){
  estadoBoton = digitalRead(13);
  if (estadoBoton == HIGH){ 
    modo = 1;
  }
  if(modo == 1){
      modoB();
  }else{
      modoA();
  }
}

void modoA(){   // MODO 7 Segmentos
  asmLedPrint(contador);
  asmBinCount(contador); 
  asmDelay(50);
  asmLedAllLow;
  asmDelay(50);
  if (contador == 9){
    contador = 0;
    for (int i = 0; i < 3; i++){
      asmLedAllHigh();
      asmDelay(20);
      asmLedAllLow();
      asmDelay(20); 
    }
  }else{
    contador++;
  }
}

void modoB(){   // MODO COMPUERTAS
  asmBinCount(0);
  asmLedPrint(1); 
  Serial.println("Compuertas: ");
  Serial.println("Ingrese valor de A (0/1): ");
  Serial.flush();
  while(!Serial.available());
  if (Serial.available() > 0) {
    ValorA = Serial.readString().toInt();
  }
  Serial.println("Ingrese valor de B (0/1): ");
  Serial.flush();
  while(!Serial.available());
  if (Serial.available() > 0) {
    ValorB = Serial.readString().toInt();
  }
  Serial.println("Operaciones a realizar: 1 - AND 2 - OR 3 - XOR");
  Serial.println("--> Para Reiniciar presione 4");
  Serial.println("Numero de la operacion a realizar: ");
  Serial.flush();
  while(!Serial.available());
  if (Serial.available() > 0){
    operacion = Serial.readString().toInt();
  }
  if(operacion > 0 and operacion <5){
    if (operacion == 4){
      modo = 0;
    }else{
      compuertas();
    }
  }
}

void compuertas(){
  if(ValorA < 0 or ValorA > 1){
    ValorA = 0;
  }
  if(ValorB < 0 or ValorB > 1){
    ValorB = 0;
  }
  asmLed(7, ValorA);
  asmLed(8, ValorB);
  if(operacion == 1){  // AND
    if(ValorA == 1 and ValorB == 1){
      asmLed(10, 1);
      resultado = 1;
    }
    else{
      asmLed(10, 0);
      resultado = 0;
    }
  }
  if(operacion == 2){ // OR
    if(ValorA == 0 and ValorB == 0){
      asmLed(10, 0);
      resultado = 0;
    }
    else{
      asmLed(10, 1);
      resultado = 1;
    }
  }
  if(operacion == 3){  // XOR
    if(ValorA == ValorB){
      asmLed(10, 0);
      resultado = 0;
    }
    else{
      asmLed(10, 1);
      resultado = 1;
    }
  }
  resPantalla();
  delay(3000);
  modo = 0;
}

void resPantalla(){
	Serial.println("--------------------------------------"); //DEBUG salida por pantalla de los datos de sensor
	Serial.print("Primer valor: "); Serial.println(ValorA); //DEBUG salida por pantalla de los datos de sensor
	Serial.print("Segundo valor: "); Serial.println(ValorB); //DEBUG salida por pantalla de los datos de sensor
	Serial.print("Operacion: "); Serial.println(operacion); //DEBUG salida por pantalla de los datos de sensor
  Serial.println("--------------------------------------"); //DEBUG salida por pantalla de los datos de sensor
	Serial.print("Resultado: "); Serial.println(resultado); //DEBUG salida por pantalla de los datos de sensor
}

/// ************************************************************************************************************************************************************************* ///
/// FUNCION DEMOSTRATIVAS (NO SE USAN)
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

/// ************************************************************************************************************************************************************************* ///
///  Funciones
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
  case 7: // Pin 9
    if (state == 0){
      asm volatile("CBI %0, %1 \n\t" :: "I" (_SFR_IO_ADDR(PORTB)), "I" (PORTB1));
    }else{
      asm volatile("SBI %0, %1 \n\t" :: "I" (_SFR_IO_ADDR(PORTB)), "I" (PORTB1));
    }      
  break;
  case 8: // Pin 10
    if (state == 0){
      asm volatile("CBI %0, %1 \n\t" :: "I" (_SFR_IO_ADDR(PORTB)), "I" (PORTB2));
    }else{
      asm volatile("SBI %0, %1 \n\t" :: "I" (_SFR_IO_ADDR(PORTB)), "I" (PORTB2));
    }      
  break;
  case 9: // Pin 11
    if (state == 0){
      asm volatile("CBI %0, %1 \n\t" :: "I" (_SFR_IO_ADDR(PORTB)), "I" (PORTB3));
    }else{
      asm volatile("SBI %0, %1 \n\t" :: "I" (_SFR_IO_ADDR(PORTB)), "I" (PORTB3));
    }      
  break;
  case 10: // Pin 12
    if (state == 0){
      asm volatile("CBI %0, %1 \n\t" :: "I" (_SFR_IO_ADDR(PORTB)), "I" (PORTB4));
    }else{
      asm volatile("SBI %0, %1 \n\t" :: "I" (_SFR_IO_ADDR(PORTB)), "I" (PORTB4));
    }      
  break;
  case 11: // Pin 13
    if (state == 0){
      asm volatile("CBI %0, %1 \n\t" :: "I" (_SFR_IO_ADDR(PORTB)), "I" (PORTB5));
    }else{
      asm volatile("SBI %0, %1 \n\t" :: "I" (_SFR_IO_ADDR(PORTB)), "I" (PORTB5));
    }      
  break;
  case 12: // Pin A0
    if (state == 0){
      asm volatile("CBI %0, %1 \n\t" :: "I" (_SFR_IO_ADDR(PORTC)), "I" (PORTC0));
    }else{
      asm volatile("SBI %0, %1 \n\t" :: "I" (_SFR_IO_ADDR(PORTC)), "I" (PORTC0));
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

void asmPinUp(){
      asm volatile("SBI %0, %1 \n\t" :: "I" (_SFR_IO_ADDR(DDRD)), "I" (DDD2));
      asm volatile("SBI %0, %1 \n\t" :: "I" (_SFR_IO_ADDR(DDRD)), "I" (DDD3));
      asm volatile("SBI %0, %1 \n\t" :: "I" (_SFR_IO_ADDR(DDRD)), "I" (DDD4));
      asm volatile("SBI %0, %1 \n\t" :: "I" (_SFR_IO_ADDR(DDRD)), "I" (DDD5));
      asm volatile("SBI %0, %1 \n\t" :: "I" (_SFR_IO_ADDR(DDRD)), "I" (DDD6));
      asm volatile("SBI %0, %1 \n\t" :: "I" (_SFR_IO_ADDR(DDRD)), "I" (DDD7));
      asm volatile("SBI %0, %1 \n\t" :: "I" (_SFR_IO_ADDR(DDRB)), "I" (DDB0));
      asm volatile("SBI %0, %1 \n\t" :: "I" (_SFR_IO_ADDR(DDRB)), "I" (DDB1));
      asm volatile("SBI %0, %1 \n\t" :: "I" (_SFR_IO_ADDR(DDRB)), "I" (DDB2));
      asm volatile("SBI %0, %1 \n\t" :: "I" (_SFR_IO_ADDR(DDRB)), "I" (DDB3));
      asm volatile("SBI %0, %1 \n\t" :: "I" (_SFR_IO_ADDR(DDRB)), "I" (DDB4));
      //asm volatile("SBI %0, %1 \n\t" :: "I" (_SFR_IO_ADDR(DDRB)), "I" (DDB5));
      asm volatile("SBI %0, %1 \n\t" :: "I" (_SFR_IO_ADDR(DDRC)), "I" (DDC0));
      pinMode(13, INPUT);
}


void asmBinCount(int count){
  for (int i=0; i<=3; i++) {
    asmLed(i + 7, bitRead(count, i));
  }
}



// Ejemplos	
// byte x = 33; // crea e inicializa x con el valor 33 (00100001 en binario)
// byte a = bitRead(x, 5);	// crea e inicializa a con el valor 1, ya que bitRead retorna el valor del 5o bit de la variable x
