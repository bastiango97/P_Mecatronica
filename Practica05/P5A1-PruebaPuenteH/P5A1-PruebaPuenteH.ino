#define MotA 11
#define MotB 10


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //la velocidad de transmisión
  pinMode(MotA, OUTPUT);
  pinMode(MotB, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  //1, 0
  digitalWrite(MotA, HIGH);
  digitalWrite(MotB, LOW);
  Serial.println("Levogiro");
  delay(1000);
  //0, 0
  digitalWrite(MotA, LOW);
  digitalWrite(MotB, LOW);
  Serial.println("Freno pasivo");
  delay(1000);
  //0, 1
  digitalWrite(MotA, LOW);
  digitalWrite(MotB, HIGH);
  Serial.println("Dextrogiro");
  delay(1000);
  //1, 1
  digitalWrite(MotA, HIGH);
  digitalWrite(MotB, HIGH);
  Serial.println("Freno activo");
  delay(1000);
}
