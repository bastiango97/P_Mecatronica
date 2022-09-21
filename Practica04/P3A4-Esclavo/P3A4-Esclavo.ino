#include <Wire.h>

int dato;
#define led 13;

void setup() {
  Wire.begin(0xAF); //tienes que tener la direccion del esclavo desde que inicia
  Wire.onReceive(lectura); //cuando reciba algo, habilito función
  pinMode(led, OUTPUT);
  Serial.begin(9600); //comunicacion
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(dato);
  delay(100);
  
}

void lectura() {
  dato = Wire.read();
  if (dato==1) {
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW);
  }
}
