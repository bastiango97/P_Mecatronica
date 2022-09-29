#define MotA 11
#define MotB 10
#define pot A0 
float value = 0; //variable donde guardaremos valor de pot
#define SalidA 9
float pmw = 0;
float voltaje = 0;
float voltajePorcentaje = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //la velocidad de transmisión
  pinMode(MotA, OUTPUT);
  pinMode(MotB, OUTPUT);
  pinMode(SalidA, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  value = analogRead(pot); 
  voltaje = map(pot, 0, 1023, 0, 5);
  pmw = pot/4;
  voltajePorcentaje = map(value, 0, 1023, 0, 500);

  if(value<=409.2 && value>=0) { //0V < V_leido < 2V
    levogiro();
    pmw = map(voltajePorcentaje, 0, 200, 0, 255);
    analogWrite(SalidA, 255-pmw);
  }
  if(value<613.8 && value>409.2){ //2V < v < 3V
    detenido();
    analogWrite(SalidA, 0);
  }
  if(value>=613.8 && value<=1024){ //3v <= v <= 5v
    dextrogiro();
    pmw = map(voltajePorcentaje, 300, 500, 0, 255);
    analogWrite(SalidA, pmw);
  }

}

void levogiro() {
  //1, 0
  digitalWrite(MotA, HIGH);
  digitalWrite(MotB, LOW);
  Serial.println("Levogiro");
  Serial.println(value);
  
}

void dextrogiro() {
  //0, 1
  digitalWrite(MotA, LOW);
  digitalWrite(MotB, HIGH);
  Serial.println("Dextrogiro");
  Serial.println(value);
 
}

void detenido() {
    //1, 1
  digitalWrite(MotA, HIGH);
  digitalWrite(MotB, HIGH);
  Serial.println("Freno activo");
  Serial.println(value);



}
