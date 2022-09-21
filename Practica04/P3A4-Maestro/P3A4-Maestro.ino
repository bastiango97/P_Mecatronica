#include <Wire.h> 
void setup() {
  Wire.begin();
  Serial.begin(9600); //comunicacion
  
  //programa manda un num 0 por 0.5 seg, luego un 1 por 0.5 y on and on
  

}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0; i<2; i++) {
    Wire.beginTransmission(0xAF); //num de 1 byte es la direccion de la otra persona
    //es el num q tendra que tener el esclavo 
    Wire.write(i);
    Wire.endTransmission();
    Serial.println(i);
    delay(500);
    
  }


}
