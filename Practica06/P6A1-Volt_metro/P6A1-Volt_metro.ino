/*P6A1-Volt_metro:
 *Lee una entrada analógica asociada a la lectura del divisor de voltaje.
 Detecte el valor máximo y mínimo en bits.
 Si varía el valor de voltaje que suministra de la fuente entre 8.4V y 6.4 V, se permitirá que el programa principal funcione.
 El programa principal será el parpadeo del LED que tiene su tarjeta con una frecuencia de 4 Hz.
 Si el voltaje suministrado por la fuente es menor a 6.4 V el programa principal dejará de funcionar y se quedará encendido el LED mostrado en la figura 1.
 */
 
#define LED 7 //definimos LED en pin 7
#define divisor A0 //definimos divisor voltaje en pin A0
float voltaje = 0; //variables que necesitaremos
float valorAnalogo = 0;
float voltajeMax = 970; //8.4 V
float voltajeMin = 765; //6.4 V
float voltajeReal = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT); //ponemos LED como output
  pinMode(divisor, INPUT); //divisor voltaje como input
  Serial.begin(9600); //iniciamos valor de transmisión

}

void loop() {
  valorAnalogo = analogRead(divisor); //leemos voltaje
  voltajeReal = valorAnalogo;
  Serial.println(voltajeReal);
  if(voltajeReal<voltajeMax && voltajeReal>voltajeMin) {
    digitalWrite(LED, HIGH);
    delay(250); //porque es 1/F, o sea 1/4
    digitalWrite(LED, LOW);
    delay(250);
  } else if(voltajeReal<voltajeMin) {
    digitalWrite(LED, HIGH);
  }
  // put your main code here, to run repeatedly:

}
