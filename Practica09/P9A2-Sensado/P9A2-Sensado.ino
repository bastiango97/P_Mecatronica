/*
 *4 fotorresistencias, 
 *2 sensores ultrasónicos, 
 *2 sensores infrarrojos Sharp, 
 *1 sensor de voltaje, 
 *1 sensor de temperatura,  
 *1 pantalla LCD 16x2 con su módulo I2C 
 */
 //voltageSensor(): sensor voltaje

 #define divisor A0
 int voltaje = 0;
 float voltajeMin = 680; //valor min voltaje. obtenido en practica 8
 int battery = 0;

  
 //lightSensor(): sensor luz


 //distanceSensor(): sensor ultrasonido y 2 sharp
 //sensor ultrasonido 
 const int trigPin = ;
 const int echoPin = ;
 long US_Sensor;
 //sensores (2) infrarrojos sharp
 long L_Sharp;
 long R_Sharp;

 //Temperature_sensor(): sensor de temp
 #include "DHT.h"
 #define DHTPIN 
 #define DHTTYPE DHT11
 DHT dht(DHTPIN, DHTTYPE); 
 float temperatura;

 
void setup() {
  // put your setup code here, to run once:
  pinMode(divisor, INPUT); //divisor de voltaje como input
  Serial.begin(9600); //empezamos transmision
  dht.begin(); //comienza sensor de temp
}

void loop() {
  // put your main code here, to run repeatedly:
  voltageSensor();
  

}

//lee el valor del ADC del divisor de voltaje y lo guarda en variable voltaje
void voltageSensor() {
  voltaje = analogRead(divisor);
  if(voltaje < voltajeMin) {
    battery = 0;
  } else {
    battery = 1;
  }
}

//lee los 3 valores de fotorresistencias y guarda c/u en variable diferente
void lightSensor() {
  //resta diferencia entre valores de fotorresistencias de la derecha y de la izq
  //guarda resta en light_dif
  
}

//lee sensor ultrasonico (trigger pin y echo pin) y 2 infrarrojos Sharp
void distanceSensor() {
  
}

//lee temp de sensor DTH11
void Temperature_sensor() {
  temperatura = dht.readTemperature();
}

//muestra light_dif en primera fila
//muestra si se super{o el umbral en la segunda fila 
void LCD_print() {
  
}
