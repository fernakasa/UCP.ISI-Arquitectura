/// 09-08-2019 - CORRIENTES (ARGENTINA).
/// UNIVERSIDAD DE LA CUENCA DEL PLATA.
/// INGENIERIA EN SISTEMAS DE INFORMACION.
/// ARQUITECTURA DE COMPUTADORAS.
/// EJERCICIO 01 - PRIMER AÑO SEGUNDO CUATRIMESTRE.
/// ALUMNOS: 
/// -------- SANCHEZ, FERNANDO GUSTAVO
/// -------- ALARCON VICCINI, JUAN FRANCISCO
/// -------- MAROTTOLI, ROMAN FRANCCESCO
///
/// VERSION: 1.0
/// ACTUALIZACION: 16-08-2019
///
/// PROYECTO: CALCUINO - PROTOTIPO REALIZADO CON ARDUINO.


/// Variables del programa (no modificar!!!).
int valor1 = 0;
int valor2 = 0;
int operacion = 9;
int estado = 0;
int resultado;
int resultadoBin;
bool inicio = true;

/// Fase de inicializacion.
void setup() {
	Serial.begin(9600);
  for (int m=0; m<=7; m++) {
    pinMode(4 + m , OUTPUT);
  }
}

/// Fase principal (Loop Principal de ejecucion).
void loop() {
  entradas();
  delay(20); // Se realiza un retardo de 1 segundo.
	//debug(); //Funcion para Debug.
}

void entradas(){
	switch(estado){
    case 0:
      Serial.println("Bienvenido a Calrduino");
      estado++;
      break;
    case 1:
      Serial.println("Ingrese el primer valor a calcular: ");
      Serial.flush();
      while(!Serial.available());
      if (Serial.available() > 0) {
        valor1 = Serial.readString().toInt();
      }
      estado++;
      break;
    case 2:
      Serial.println("Ingrese el segundo valor a calcular: ");
      Serial.flush();
      while(!Serial.available());
      if (Serial.available() > 0) {
        valor2 = Serial.readString().toInt();
      }
      estado++;
      break;
    case 3:
      Serial.println("Operaciones a realizar: 1 - Sumar 2 - Restar 3 - Multiplicar 4 - Dividir");
      Serial.println("--> Para Reiniciar presione 5");
      Serial.println("Ingrese el numero de la operacion a realizar: ");
      estado++;
      break;
    case 4:
      Serial.flush();
      while(!Serial.available());
      if (Serial.available() > 0){
        operacion = Serial.readString().toInt();
      }
      if(operacion > 0 and operacion <6){
        if (operacion == 5){
          estado = 0;
        }else{
          calculadora();
          estado = 3;
        }
      }else{
          estado = 3;
      }
      break;
	}
}

void calculadora(){
	switch(operacion){
		case 1:
			resultado = valor1 + valor2;
			break;
		case 2:
			resultado = valor1 - valor2;
			break;
		case 3:
			resultado = valor1 * valor2;
			break;
		case 4:
			resultado = valor1 / valor2;
			break;
	}
  if(resultado > 0 && resultado <= 255) {
    // Hacemos un bucle activando cada led de acuerdo al bit correspondiente
    for (int m=0; m<=7; m++) {
      digitalWrite(4+m, bitRead(resultado, m));
    }
    debug();
  }
}

void debug(){
	Serial.println("--------------------------------------"); //DEBUG salida por pantalla de los datos de sensor
	Serial.print("Primer valor: "); Serial.println(valor1); //DEBUG salida por pantalla de los datos de sensor
	Serial.println("--------------------------------------"); //DEBUG salida por pantalla de los datos de sensor
	Serial.print("Segundo valor: "); Serial.println(valor2); //DEBUG salida por pantalla de los datos de sensor
	Serial.print("Operacion: "); Serial.println(operacion); //DEBUG salida por pantalla de los datos de sensor
	Serial.print("Resultado: "); Serial.println(resultado); //DEBUG salida por pantalla de los datos de sensor
	Serial.print("ResultadoBIN: "); Serial.println(resultado, BIN); //DEBUG salida por pantalla de los datos de sensor
}
