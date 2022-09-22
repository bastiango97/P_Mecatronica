//P4A5-SistemaMaestro
#include <LiquidCrystal_I2C.h>
#include <Wire.h> 

#define X A0
#define Y A1
#define Z A2

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

float XG, YG, ZG, roll_angle;
int servo_angle;

float x_min = 267.0;
float x_max = 402.0;
float y_min = 267.0;
float y_max = 403.0;
float z_min = 272.0;
float z_max = 412.0;

void setup() {
  Wire.begin();
  Serial.begin(9600); //comunicación

  lcd.init(); //inicialización
  lcd.backlight(); //luz lcd
}

void loop() {
  XG = map(analogRead(X), x_min, x_max, -100, 100);
  XG = XG/100;
  YG = map(analogRead(Y), y_min, y_max, -100, 100);
  YG = YG/100;
  ZG = map(analogRead(Z), z_min, z_max, -100, 100);
  ZG = ZG/100;

  //Calc ángulo de roll
  roll_angle = -atan(tan(YG/(sqrt(sq(XG)+sq(ZG)))))*180/PI;

  //Ángulo de roll --> ángulo de servo
  servo_angle = map((int)roll_angle, -90, 90, 0, 90);

  //Manda a esclavo
  Wire.beginTransmission(0xAF);
  Wire.write(servo_angle);
  Wire.endTransmission();

  //Imprime resultados en pantalla LCD
  lcd.setCursor(0,0);
  lcd.print("Ang serv:");
  lcd.setCursor(10,0);
  lcd.print(servo_angle);
  lcd.setCursor(0,1);
  lcd.print("IC2: ");
  lcd.setCursor(5,1);
  lcd.print(roll_angle);

  delay(150);
  
  //Imprime resultados en consola
  Serial.print("Angulo Roll: ");
  Serial.print(roll_angle);
  Serial.print("  Angulo Servo: ");
  Serial.println(servo_angle);
}
