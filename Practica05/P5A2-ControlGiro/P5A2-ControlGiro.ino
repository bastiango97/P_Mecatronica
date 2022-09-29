#define MotA 11
#define MotB 10
#define pot A0 
float value = 0; //variable donde guardaremos valor de pot


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //la velocidad de transmisión
  pinMode(MotA, OUTPUT);
  pinMode(MotB, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  value = analogRead(pot); 
  if(value<=409.2) { //0V < V_leido < 2V
    levogiro();
  }
  if(value<613.8 && value>409.2){
    detenido();
  }
  if(value>=613.8){
    dextrogiro();
  }
}

void levogiro() {
    //1, 0
  digitalWrite(MotA, HIGH);
  digitalWrite(MotB, LOW);
  Serial.println("Levogiro");
  Serial.println(value);
  delay(1000);  
}

void dextrogiro() {
  //0, 1
  digitalWrite(MotA, LOW);
  digitalWrite(MotB, HIGH);
  Serial.println("Dextrogiro");
  Serial.println(value);
  delay(1000);
}

void detenido() {
    //1, 1
  digitalWrite(MotA, HIGH);
  digitalWrite(MotB, HIGH);
  Serial.println("Freno activo");
  Serial.println(value);
  delay(1000);


}
