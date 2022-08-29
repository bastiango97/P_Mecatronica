//definimos el pin que vamos a usar con el potenciómetro
#define pot A0 
//ahora definimos el LED y el pin que usaremos
#define led 13

float value = 0; //variable donde guardaremos valor de pot
float brillo = 0;
int pwm = 0;
void setup() {

  Serial.begin(9600); //la velocidad de transmisión

  //aquí sí pinmode para el LED
  pinMode(led, OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
  value = analogRead(pot); //leemos potenciómetro y guardamos valor en value
  brillo = value/1023*100; //de 0 a 100% de brillo; de 0 a 1023
  //máximo del led es 256 entonces si le mandamos 1023 directo (value) hace 3 "ciclos" con 
  //256 y múltiplos como ceros
  analogWrite(led, value/4);
  //Serial.print("Valor ADC: "); //imprimimos
  Serial.println(brillo); //imprimimos voltaje potenciómetro con salto de línea
  delay(100); //para imprimir 10 valores en 1seg
}
