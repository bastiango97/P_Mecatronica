//definimos el pin que vamos a usar con el potenciómetro
#define pot A0 
//ahora definimos el LED y el pin que usaremos
#define led 13

float value = 0; //variable donde guardaremos valor de pot
float voltaje = 0;

void setup() {
  // put your setup code here, to run once:
  //el pot es entrada analógica y lee directamente entonces no tenemos que poner pinmode
  //empezamos com. serial (siempre al usar USB)
  Serial.begin(9600); //la velocidad de transmisión

  //aquí sí pinmode para el LED
  pinMode(led, OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
  value = analogRead(pot); //leemos potenciómetro y guardamos valor en value
  voltaje = value/1023*5;
  //3 volts en bits = 615 
  //LED solo se prende si value > 615 o si voltaje > 3
  if(voltaje > 3) {
    digitalWrite(led, HIGH); //se prende el led si voltaje > 3
    } else {
      digitalWrite(led, LOW);
    }
  //Serial.print("Valor ADC: "); //imprimimos
 Serial.println(voltaje); //imprimimos voltaje potenciómetro con salto de línea
 delay(100); //para imprimir 10 valores en 1seg
}
