//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();
    lcd.setCursor(15,0);
  lcd.print("Santiago_M");
  lcd.setCursor(19,1);
  lcd.print("Sebastian_G");
  for (int positionCounter = 0; positionCounter < 15; positionCounter++) {
    lcd.scrollDisplayLeft(); 
    delay(150); 
  }
}


void loop()
{
}
