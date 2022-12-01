//Librerias
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>    //Librería para pantalla LCD
#include "DHT.h"                

//Puertos motores
#define enable1 2
#define enable2 7
#define control1A 4
#define control1B 3
#define control2A 5
#define control2B 6
#define divisor A0

//Puertos sensores
#define outLed 13                 //Led   
#define inVoltVoltimetro A0       //Sensor de voltaje
#define inVoltLuminosidad_L A1      //Sensor de luminosidad
#define inVoltLuminosidad_B A2      //Sensor de luminosidad
#define inVoltLuminosidad_F A3      //Sensor de luminosidad
#define inVoltLuminosidad_R A4      //Sensor de luminosidad
#define DHTPIN 10                 //Sensor de temperatura
#define DHTTYPE DHT11             //Define luminosidad
#define echoPin1 53                 //Puerto de echo, sensor ultrasónico
#define trigPin1 51                //Puerto de trigger, sensor ultrasónico
#define echoPin2 49                 //Puerto de echo, sensor ultrasónico
#define trigPin2 47                //Puerto de trigger, sensor ultrasónico
#define inVoltSharp1 A8            //Sensor Sharp1
#define inVoltSharp2 A9            //Sensor Sharp2
//LCD
LiquidCrystal_I2C lcd(0x27,16,2);  //Set the LCD address to 0x27 for a 16 chars and 2 line display
//Voltaje batería 
int voltaje;
int battery;
//Luminosidad
float voltLuminosidad_L;
float voltLuminosidad_R;
float voltLuminosidad_F;
float voltLuminosidad_B;
float pwmLuminosidad_L;
float pwmLuminosidad_R;
float pwmLuminosidad_F;
float pwmLuminosidad_B;
float L_LDR;
float R_LDR;
float F_LDR;
float B_LDR;
float light_dif;
//Temperatura-Humedad
float tempC;
DHT dht(DHTPIN, DHTTYPE);
//Ultrasónico
long duracionUltrasonico;
int US_Sensor1;
int US_Sensor2;
//Sharp
long voltajeInSharp1;
long L_Sensor;
long voltajeInSharp2;
long R_Sensor;

int estado= 0; 
float L_Diff1; 
float L_Diff2; 
float L, R, F, B; 
int U1, U2, S1, S2, T; 
int i = 0; 
void setup() {
  Serial.begin(9600);
  //setup motores 
  pinMode(enable1, OUTPUT);
  pinMode(enable2, OUTPUT);
  pinMode(control1A, OUTPUT);
  pinMode(control1B, OUTPUT);
  pinMode(control2A, OUTPUT);
  pinMode(control2B, OUTPUT);
  //setup sensores
  pinMode(outLed, OUTPUT);
  pinMode(inVoltLuminosidad_L, INPUT);
  pinMode(inVoltLuminosidad_R, INPUT);
  pinMode(inVoltLuminosidad_F, INPUT);
  pinMode(inVoltLuminosidad_B, INPUT);
  pinMode(inVoltVoltimetro, INPUT);
  pinMode(trigPin1, OUTPUT); 
  pinMode(echoPin1, INPUT); 
  pinMode(trigPin2, OUTPUT); 
  pinMode(echoPin2, INPUT); 
  pinMode(inVoltSharp1, INPUT); 
  pinMode(inVoltSharp2, INPUT); 
  //Inicialización del la pantalla LCD
  lcd.init();    
  lcd.backlight();
  //lcd.setCursor(0,0);
  //lcd.clear();
  Serial.println("lcd");
  //Inicialización de la comunicación con el sensor de humedad
  dht.begin();
}

void loop() {
  L = L_L(); 
  R = R_L(); 
  F = F_L(); 
  B = B_L(); 
  L_Diff1 = R-L;
  L_Diff2 = F-B;  
  T = temperatureSensor(); 
  U1 = US1(); 
  U2 = US2(); 
  S1 = sharp1(); 
  S2 = sharp2(); 
  switch(estado){
    case 0://stop o inicio 
      estado = 1; 
      //LCD_print("Stop");
      driveRobot(0,0);
      delay(100);  
      break; 
    case 1://mover adelante si no hay obstaculos y si luz está adelante
      if(U1<7){
        estado =4; //Objeto detectado por el sensor ultrasónico izquierdo, gurar a la derecha
        LCD_print("Esquiva der.", L_Diff1);    
        }
      else if(U2<7){
        estado = 5; //Objeto detectado por el sensor ultrasónico derecho, gurar a la izquierda
        LCD_print("Esquiva izq.", L_Diff1);
        }
      else if(S1>200){
        estado =6; //Objeto detectado por el sensor sharp derecho, gurar a la izquierda
        LCD_print("Esquiva der.", L_Diff1);
        }
      else if(S2>200){
        estado =7; //Objeto detectado por el sensor sharp izquierdo, gurar a la derecha
        LCD_print("Esquiva izq.", L_Diff1);
        }
      else if(L_Diff1>15 || L_Diff1<0 ){ //Robot hace un giro
        estado = 2;
      }else if (L_Diff2<25){ //Robot tiene que rotar
        estado = 3;
      }else{ //Luz está enfrente, robot va hacia adelante
        estado = 0; 
        driveRobot(-1, -1); 
        LCD_print("Adelante", L_Diff1);
      }
      break; 
    case 2: 
      if(L_Diff1>15){
        estado = 0; 
        driveRobot(-1, 1); 
        LCD_print("Derecha", L_Diff1); 
      }else if(L_Diff1<0){
        estado = 0; 
        driveRobot(1, -1); 
        LCD_print("Izquierda", L_Diff1); 
      } 
      break;  
    case 3: 
      estado = 0; 
      driveRobot(-1, 1); 
      LCD_print("Rotando", L_Diff1); 
      break;
    case 4: 
    //Sensor ultrasónico izquierdo detecta allgo, esquiva por la derecha.
      if(U1<7){
        driveRobot(-1, 1); 
        LCD_print("Esquiva der.", L_Diff1); 
        estado = 4; 
        } else {
          estado = 8;
          }
      break; 
    case 5:
    //Sensor ultrasónico derecho detecta algo, esquiva por la izquierda.
    if(U2<7){
        driveRobot(1, -1); 
        LCD_print("Esquiva izq.", L_Diff1); 
        estado = 5; 
        }else {
      estado = 9;
      } 
      break; 
    case 6: 
    //Sensor sharp izquierdo detecta algo, esquiva por la derecha.
    if(S1>200){
        driveRobot(-1, 1); 
        LCD_print("Esquiva der.", L_Diff1);  
        estado = 6; 
        } else {
         estado = 8;
        }
      break;
    case 7: 
    //Sensor sharp derecho detecta algo, esquiva por la izquierda.
    if(S2>200){
        driveRobot(1, -1); 
        LCD_print("Esquiva i<q.", L_Diff1);  
        estado = 7; 
        } else {
      estado = 9;
        } 
      break;
    case 8: //forzar adelante despues de esquivar derecha 
        if(U1>7 && U2 >7 && S1<200 && S2<200){
          driveRobot(-1, -1); 
          LCD_print("Forzar adelante", L_Diff1); 
          delay(400); 
          estado = 0; 
         } else {
          driveRobot(1, -1); 
          LCD_print("Rotando", L_Diff1);
          delay(400);
          estado = 8; 
          }
          break; 
       case 9: //forzar adelante despues de esquivar izq
        if(U1>7 && U2 >7 && S1<200 && S2<200){
          driveRobot(-1, -1); 
          LCD_print("Forzar adelante", L_Diff1); 
          delay(400); 
          estado = 0; 
         } else {
          driveRobot(-1, 1); 
          LCD_print("Rotando", L_Diff1);
          delay(400);
          estado = 9; 
          }
          break;     
  }
}


void driveRobot(float LSignal, float RSignal){ //función driverobot
  //utiliza ifs para setear los lows, highs y bits para realizar cada movimiento
  //atras
  if(LSignal==1 && RSignal==1){
    analogWrite(enable1, 220); 
    digitalWrite(control1A, HIGH);
    digitalWrite(control1B, LOW); 
    analogWrite(enable2, 255);
    digitalWrite(control2A, HIGH);
    digitalWrite(control2B, LOW); 
    }
    //adelante
    if(LSignal==-1 && RSignal==-1){
    analogWrite(enable1, 200); 
    digitalWrite(control1A, LOW);
    digitalWrite(control1B, HIGH); 
    analogWrite(enable2, 255);
    digitalWrite(control2A, LOW);
    digitalWrite(control2B, HIGH); 
    }
    //izquierda
    if(LSignal==1 && RSignal==-1){
    analogWrite(enable1, 220); 
    digitalWrite(control1A, HIGH);
    digitalWrite(control1B, LOW); 
    analogWrite(enable2, 255);
    digitalWrite(control2A, LOW);
    digitalWrite(control2B, HIGH); 
    }
    //derecha
    if(LSignal==-1 && RSignal==1){
    analogWrite(enable1, 220); 
    digitalWrite(control1A, LOW);
    digitalWrite(control1B, HIGH); 
    analogWrite(enable2, 255);
    digitalWrite(control2A, HIGH);
    digitalWrite(control2B, LOW); 
    }
    //stop
    if(LSignal==0 && RSignal==0){
    analogWrite(enable1, 0); 
    digitalWrite(control1A, LOW);
    digitalWrite(control1B, LOW); 
    analogWrite(enable2, 0);
    digitalWrite(control2A, LOW);
    digitalWrite(control2B, LOW); 
    }
}


void voltageSensor(){
  voltaje = analogRead(inVoltVoltimetro); //*5/1023;
  Serial.print("V: ");
  Serial.print(voltaje*5/1023);
  Serial.print(" v -- ");
  if(voltaje < 687)  //687 bits ==> 6.4 V
    battery = 0;
  else
    battery = 1;
}

float L_L(){
  voltLuminosidad_L = analogRead(inVoltLuminosidad_L);  
  L_LDR = map(voltLuminosidad_L, 0, 1023, 0, 255);
  return L_LDR; 
  }
float R_L(){
  voltLuminosidad_R = analogRead(inVoltLuminosidad_R);  
  R_LDR = map(voltLuminosidad_R, 0, 1023, 0, 255);
  return R_LDR; 
  }
float F_L(){
  voltLuminosidad_F = analogRead(inVoltLuminosidad_F);  
  F_LDR = map(voltLuminosidad_F, 0, 1023, 0, 255);
  return F_LDR; 
  }
float B_L(){
  voltLuminosidad_B = analogRead(inVoltLuminosidad_B);  
  B_LDR = map(voltLuminosidad_B, 0, 1023, 0, 255);
  return B_LDR; 
  }

int temperatureSensor(){
    tempC = dht.readTemperature();
    if ( isnan(tempC)  ) {
      Serial.println(F("Failed to read from DHT sensor!"));
      return 1;
    } else {
     return tempC;
     }  
}

int US1(){//izquierdo
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duracionUltrasonico = pulseIn(echoPin1, HIGH);
  US_Sensor1 = duracionUltrasonico * 0.0343 / 2;
  return US_Sensor1; 
  }
int US2(){//derecho
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duracionUltrasonico = pulseIn(echoPin2, HIGH);
  US_Sensor2 = duracionUltrasonico * 0.0343 / 2;
  return US_Sensor2; 
  }
long sharp1(){//izquierda
   voltajeInSharp1 = analogRead(inVoltSharp1);
   //L_Sensor = pow(voltajeInSharp1/758.73,-1/.486);
   return voltajeInSharp1; 
  }
long sharp2(){//derecha
  voltajeInSharp2 = analogRead(inVoltSharp2);
  //R_Sensor = pow(voltajeInSharp2/758.73,-1/.486);
  }
void LCD_print(String mensaje, int L_Diff){
  lcd.setCursor(0,0);
  lcd.print("                  ");
  lcd.setCursor(0,1);
  lcd.print("                  ");
  lcd.setCursor(0,0);
  lcd.print(mensaje);
  lcd.setCursor(0,1);
  lcd.print(String(L_Diff));
  }
