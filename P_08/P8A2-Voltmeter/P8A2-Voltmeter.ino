//leer entrada analogica de valor de resistor y guardarlo como int voltage
//sintonizar fuente a 6.4V y detectar valor de voltage en bits q detecta ADC
//sintonizar fuente a 8.4V y detectar valor en bits
#define LED 13
#define divisor A0
int voltage = 0; //variables que necesitaremos
float valorAnalogo = 0;
float voltajeMax = 860; //8.4 V
float voltajeMin = 680; //6.4 V
float voltajeReal = 0;
int volt = 0;
int mapeo;


void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT); //ponemos LED como output
  pinMode(divisor, INPUT); //divisor voltaje como input
  Serial.begin(9600); //iniciamos valor de transmisión
}


//funcion voltmeter q mapee valor minimo en bits a 0% voltaje y maximo a 100%
//if valor mayor a 0% de bateria --> LightFollower (fn q apaga LED antes encendido e imprime en pantalla "Light Follower")
//if valor menor a 0% de bateria --> LowBattery (fn q enciende LED de placa asociada en puerto 13)

void loop() {
  // put your main code here, to run repeatedly:
  //map(value, fromLow, fromHigh, toLow, toHigh)
    voltage = analogRead(divisor); //leemos voltaje
    Serial.print(voltage);
    Serial.println(" volts");
    delay(150);
    //Serial.println(voltage);
    mapeo = voltmeter(voltage);
    if(voltage>voltajeMin) { //mayor a 680
      LightFollower();
      delay(150);
    }else{
      LowBattery();
      delay(150);
    }
    

}

int voltmeter(int voltage) {
  volt = analogRead(voltage);
  mapeo = (volt, 0, 1023, 0, 5);
  return mapeo;
}

//imprime "Light Follower"
void LightFollower() {
  digitalWrite(LED, LOW);
  Serial.println("Light Follower");
}

void LowBattery() {
  digitalWrite(LED, HIGH);
  Serial.println("Low bat");
}
