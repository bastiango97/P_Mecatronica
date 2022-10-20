#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
#include <Wire.h>
#include "DHT.h"
#include <string.h>
int DHTPIN = 19;
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

int pinSharp = A0;
int LED = 8; 
int pinVolt = A1;
int pinUltra = A2; 
int pinLumi = A3;
int trigPin = 6;
int echoPin = 7;
#define DHTPIN 21  

int valorSharp  = 0;
int valorLumi = 0;
int valorTemp = 0;
int valorUltra = 0;

int valorVolt = 0;
float voltajeMax = 970; //8.4 V
float voltajeMin = 765; //6.4 V

long duracion;
int distancia;

float disSharp; 

String error1=""; 
String error2="";
int errorCounter = 0; 
void setup() {
  lcd.init(); 
  lcd.backlight();
  lcd.setCursor(0,0);
  pinMode(LED, OUTPUT);
  pinMode(pinVolt, INPUT);
  pinMode(pinSharp, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  dht.begin();
}

void loop() {
    //Voltaje, Luminosidad, temperatura
    valorVolt= analogRead(pinVolt);
    valorLumi = analogRead(pinLumi);
    float tempC = dht.readTemperature();

    //Ultrasonido
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duracion = pulseIn(echoPin, HIGH);
    distancia = duracion * 0.0343 / 2;

    //sharp
    valorSharp = analogRead(pinSharp);
    disSharp =  pow(valorSharp/758.73, -1/.486);
  
    //impresion serial
    Serial.print("V: "); Serial.print(valorVolt); Serial.print("bits -- L: "); Serial.print(valorLumi); Serial.print("bits -- T: "); 
    Serial.print(tempC); Serial.print(("°C -- DU: "));Serial.print(distancia);Serial.print(" cm -- DS: "); Serial.print(disSharp); Serial.print(" cm"); 

    //Errores
    lcd.setCursor(0,0);
    String msg = "Li: "; 
    msg = msg + valorLumi; 
    msg = msg + " bits";
    lcd.print(msg);
    errorCounter = 0; 
    if(valorVolt < 765){
      error1 = "Low Battery"; 
      error2 = error2 + "Bt";
      errorCounter = errorCounter++;
      }
    if(tempC>30){
      error1 = "Overheating"; 
      error2 = error2 + "-Tmp";
      errorCounter = errorCounter++;
      }
     if(distancia<=15){
      error1 = "U_Obstacle"; 
      error2 = error2 + "-UObs";
      errorCounter = errorCounter++;
      }
     if(disSharp<=15){
     error1 = "S_Obstacle"; 
     error2 = error2 + "-SObs";
     errorCounter = errorCounter++;
     }
     if(errorCounter==1){
        lcd.setCursor(0,1);
        lcd.print(error1);
        analogWrite(LED, HIGH);
      } else if(errorCounter>1){
        lcd.setCursor(0,1);
        lcd.print(error2);
        analogWrite(LED, HIGH);
      } else {
        lcd.setCursor(0,1);
        lcd.print("");
        analogWrite(LED, LOW);
        }
      
     
    delay(1000); 
    Serial.println("");
}
