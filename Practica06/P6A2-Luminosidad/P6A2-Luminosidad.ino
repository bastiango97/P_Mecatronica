/*P6A2-Luminosidad
Usamos sensor de luminosidad para controlar el brillo de un LED
Mientras mayor la luminosidad del sensor, menor el brillo del LED
*/
 
#define LED 7 //definimos pin led
#define sensor A0 //definimos pin sensor
float pmw = 0;
float luminosidad = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT); //led como output
  pinMode(sensor, INPUT); //ponemos al sensor como input
  Serial.begin(9600); //iniciamos transmisión
}

void loop() {
  luminosidad = analogRead(sensor); //leemos luminosidad del sensor   
  Serial.println(luminosidad);
  pmw = map(luminosidad, 854, 514, 0, 255); //hacemos mapping usando los valores max y min de luminosidad
  //obtuvimos esos valores imprimiendo la luminosidad y viendo su rango
  //primero estabamos haciendo map de 0 a 1023 y al ver que el mínimo era 514 y el máximo 854 los cambiamos
  Serial.println(pmw);
  analogWrite(LED, pmw);

}
