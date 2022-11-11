

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
void setup() {
  lcd.begin(16,2);
}

void loop() {
  lcd.setCursor(15,0);
  lcd.print("Santiago_M");
  lcd.setCursor(19,1);
  lcd.print("Sebastian_G");
  for (int positionCounter = 0; positionCounter < 15; positionCounter++) {
    lcd.scrollDisplayLeft(); 
    delay(150); 
  } 
  exit(0);
}
