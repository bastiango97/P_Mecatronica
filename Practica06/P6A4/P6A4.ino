const int trigPin = 6;
const int echoPin = 7;
#define LED 8
long duracion;
int distancia;
void setup() {
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  pinMode(LED, OUTPUT);
  Serial.begin(9600); 
}
void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duracion = pulseIn(echoPin, HIGH);
  distancia = duracion * 0.0343 / 2;
  if(distancia<15) { //si la distancia es menor a quince se prende el led
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW); //si la distancia es mayor a quince se apaga el led
  }
  Serial.print("D: ");
  Serial.print(distancia);
  Serial.print(" cm");
  Serial.print("\n");
  delay(100);
  

}
