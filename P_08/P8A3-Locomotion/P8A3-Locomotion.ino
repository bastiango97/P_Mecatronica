#define enable1 2
#define enable2 7
#define control1A 4
#define control1B 3
#define control2A 5
#define control2B 6
#define divisor A0

//definimos los puertos

void setup() {
  pinMode(enable1, OUTPUT);//puertos de control y enable de los dos motores
  pinMode(enable2, OUTPUT);
  pinMode(control1A, OUTPUT);
  pinMode(control1B, OUTPUT);
  pinMode(control2A, OUTPUT);
  pinMode(control2B, OUTPUT);
  pinMode(divisor, INPUT); //divisor voltaje como input
  Serial.begin(9600); //iniciamos valor de transmisión
}

void loop() { //rutina de movimiento usando funcion driverobot
  driveRobot(1,1);//adelante  
  delay(2000);
  driveRobot(-1,-1);//atras
  delay(2000);
  driveRobot(-1,1);//izquierda
  delay(2000);
  driveRobot(1,-1);//derecha
  delay(2000);
  driveRobot(0,0);//stop
  delay(2000);
      
}


void driveRobot(float LSignal, float RSignal){ //función driverobot
  //utiliza ifs para setear los lows, highs y bits para realizar cada movimiento
  //adelante
  
  if(LSignal==1 && RSignal==1){
    analogWrite(enable1, 100); 
    digitalWrite(control1A, HIGH);
    digitalWrite(control1B, LOW); 
    analogWrite(enable2, 100);
    digitalWrite(control2A, HIGH);
    digitalWrite(control2B, LOW); 
    Serial.println("Adelante");
    }
    //atras
    if(LSignal==-1 && RSignal==-1){
    analogWrite(enable1, 100); 
    digitalWrite(control1A, LOW);
    digitalWrite(control1B, HIGH); 
    analogWrite(enable2, 100);
    digitalWrite(control2A, LOW);
    digitalWrite(control2B, HIGH); 
    Serial.println("Atras");
    }
    //derecha
    if(LSignal==1 && RSignal==-1){
    analogWrite(enable1, 100); 
    digitalWrite(control1A, HIGH);
    digitalWrite(control1B, LOW); 
    analogWrite(enable2, 100);
    digitalWrite(control2A, LOW);
    digitalWrite(control2B, HIGH); 
    Serial.println("Der");
    }
    //izq
    if(LSignal==-1 && RSignal==1){
    analogWrite(enable1, 100); 
    digitalWrite(control1A, LOW);
    digitalWrite(control1B, HIGH); 
    analogWrite(enable2, 100);
    digitalWrite(control2A, HIGH);
    digitalWrite(control2B, LOW); 
    Serial.println("Izq");
    }
    //stop
    if(LSignal==0 && RSignal==0){
    analogWrite(enable1, 0); 
    digitalWrite(control1A, LOW);
    digitalWrite(control1B, LOW); 
    analogWrite(enable2, 0);
    digitalWrite(control2A, LOW);
    digitalWrite(control2B, LOW); 
    Serial.println("Stop");
    }
  
}
