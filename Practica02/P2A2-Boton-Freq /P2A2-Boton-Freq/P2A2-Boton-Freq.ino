#define LED 13
#define BTN 12

int button_state;
void setup() {
  pinMode (LED, OUTPUT);
  pinMode (BTN, INPUT);

}

void loop() {

  button_state = digitalRead(BTN); 
  if(button_state ==1) {
    digitalWrite(LED, HIGH);
    delay(250);
    digitalWrite(LED, LOW); 
    delay(250);
  }else {
    digitalWrite(LED, HIGH);
    delay(1000);
    digitalWrite(LED, LOW); 
    delay(1000);
  }


}
