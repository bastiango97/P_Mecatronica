/*
  ADXL3xx

  Reads an Analog Devices ADXL3xx accelerometer and communicates the
  acceleration to the computer. The pins used are designed to be easily
  compatible with the breakout boards from SparkFun, available from:
  https://www.sparkfun.com/categories/80

  The circuit:
  - analog 0: accelerometer self test
  - analog 1: z-axis
  - analog 2: y-axis
  - analog 3: x-axis
  - analog 4: ground
  - analog 5: vcc

  created 2 Jul 2008
  by David A. Mellis
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/ADXL3xx
*/

// these constants describe the pins. They won't change:
const int groundpin = 18;             // analog input pin 4 -- ground
const int powerpin = 19;              // analog input pin 5 -- voltage
const int xpin = A0;                  // x-axis of the accelerometer
const int ypin = A1;                  // y-axis
const int zpin = A2;                  // z-axis (only on 3-axis models)
const float pi = 3.14; 

float Xg, Yg, Zg; 
float Xval, Yval, Zval; 
float Z_min = 272.0; 
float Z_max = 403.0;
float X_min = 272.0; 
float X_max = 403.0;
float Y_min = 272.0; 
float Y_max = 403.0;
float alfa;
float beta;


void setup() {
  // initialize the serial communications:
  Serial.begin(9600);

  // Provide ground and power by using the analog inputs as normal digital pins.
  // This makes it possible to directly connect the breakout board to the
  // Arduino. If you use the normal 5V and GND pins on the Arduino,
  // you can remove these lines.
  pinMode(groundpin, OUTPUT);
  pinMode(powerpin, OUTPUT);
  digitalWrite(groundpin, LOW);
  digitalWrite(powerpin, HIGH);
}

void loop() {
  Xval = analogRead(xpin);
  Yval = analogRead(ypin);
  Zval = analogRead(zpin); 


  Zg = map(Zval, Z_min, Z_max, -100, 100);
  Zg = Zg/100; 
  Yg = map(Yval, Y_min, Y_max, -100, 100);
  Yg = -Yg/100;
  Xg = map(Xval, X_min, Z_max, -100, 100);
  Xg = Xg/100;

  //vamos a calcular alfa, el ángulo de inc respecto al eje x (roll)
  alfa = atan(Yg/(sqrt(sq(Xg)+sq(Zg))));
  //la pasamos a grados
  alfa = (alfa*180)/pi;
  
  //beta, ángulo de inc respecto al eje y (pitch)
  beta = atan(Xg/(sqrt(sq(Yg)+sq(Zg))));
  //la pasamos a grados
  beta = (beta*180)/pi;
//  Serial.print(" X: ");
//  Serial.print(Xg);
// 
//  Serial.print("\t");
//  
//  Serial.print(" Y: ");
//  Serial.print(Yg);
//  
//  Serial.print("\t");
//  
//  Serial.print(" Z: ");
//  Serial.println(Zg);
//  
//  Serial.print("\t");
  Serial.print(" alfa: ");
  Serial.print(alfa);
  //Serial.print("º");
  
  Serial.print("\t");
  
  Serial.print(" b: ");
  Serial.println(beta);
 // Serial.println("º");
  delay(100);
}
