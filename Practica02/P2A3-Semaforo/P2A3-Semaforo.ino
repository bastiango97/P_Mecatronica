// definimos todos nuestros LEDs
// semáforo 1: rojo 6s, verde 5s, amarillo 1s
// semáforo 2: verde 5s, amarillo 1s, rojo 6s
#define rojoSem1 13
#define amarilloSem1 12
#define verdeSem1 11

#define rojoSem2 10
#define amarilloSem2 9
#define verdeSem2 8

int change=0; //bandera para señalar que acabó un ciclo


//el modo de los LEDs será output
void setup() {
  // put your setup code here, to run once:
  pinMode (rojoSem1, OUTPUT);
  pinMode (verdeSem1, OUTPUT);
  pinMode (amarilloSem1, OUTPUT);
  
  pinMode (rojoSem2, OUTPUT);
  pinMode (verdeSem2, OUTPUT);
  pinMode (amarilloSem2, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
    digitalWrite(rojoSem1, HIGH);
    digitalWrite(verdeSem2, HIGH); 
    //mientras el primer rojo está encendido, 
    //el segundo verde igual
    delay(5000);
    digitalWrite(verdeSem2, LOW);
    digitalWrite(amarilloSem2, HIGH);
    delay(1000);
    //apagamos el rojo1 despues de 6segundos
    digitalWrite(rojoSem1, LOW);
    //ahora se apaga el amarillo2
    digitalWrite(amarilloSem2, LOW);
    //se prende el verde1
    digitalWrite(verdeSem1, HIGH);
    //se prende el rojo2
    digitalWrite(rojoSem2, HIGH);
    delay(5000);
    //se apaga el verde1 desp de 5s
    digitalWrite(verdeSem1, LOW);
    //se prende el amarillo1
    digitalWrite(amarilloSem1, HIGH);
    delay(1000);
    //se apagan amarillo1 y rojo2
    digitalWrite(amarilloSem1, LOW);
    digitalWrite(rojoSem2, LOW);
   


}
