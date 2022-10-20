#define in A0

void setup() {
  pinMode(in, INPUT); 
  Serial.begin(9600);
}

long voltajeEntrada;
long distancia;

void loop() {
  voltajeEntrada = analogRead(in);

  distancia = pow( (916.53) / (voltajeEntrada) , 0.623);

  Serial.print("Distancia: ");
  Serial.print(voltajeEntrada);
  Serial.print(" bV -->");
  Serial.print( distancia);
  Serial.println("  cm");
  
}
