/*P6A3-TemperaturaHumedad

*/
#include "DHT.h"
#include <string.h>
#define DHTPIN 21  
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println(("DHTxx test!"));

  dht.begin();
}

void loop() {
  float humedad = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float tempC = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float tempF = dht.readTemperature(true);
  char dato;
  if(Serial.available()>0) {
    strcpy(dato, Serial.read());
  
    if(strcmp(dato,"snsr_tempC")) {
        Serial.print(("Temperature: "));
        Serial.print(tempC);
        Serial.print(("°C "));
      
    }
    if(strcmp(dato,"snsr_tempF")) {
        Serial.print(("Temperature: "));
        Serial.print(tempF);
        Serial.print(("°F"));
      
    }
    if(strcmp(dato,"opcion3")) {
      
      Serial.print(("Humidity: "));
      Serial.print(humedad);
      Serial.print("%");
      
    }
  }

  // Check if any reads failed and exit early (to try again).
  if (isnan(humedad) || isnan(tempC) || isnan(tempF)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }


}
