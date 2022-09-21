// Codigo para el esclavo
#include <Wire.h>
#include <Servo.h>

Servo servo; 

int angulo;

void setup() {
  servo.attach(3);
  
  Wire.begin(0xAF);
  
  Serial.begin(9600);
}

void loop() {
  // Imprimimos llegadas de datos
  Wire.onReceive(lectura);
  Serial.print("  Ángulo Servo: ");
  Serial.println(angulo);
}

void lectura() {
  angulo = Wire.read();
  servo.write(angulo);
}
