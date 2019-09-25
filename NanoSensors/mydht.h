#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN A3
#define DHTTYPE    DHT11

DHT_Unified dht(DHTPIN, DHTTYPE);

char g_temp[6];
char g_humidity[6];

void setupDHT() {
  dht.begin();
}

void runDHT() {
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    dtostrf(event.temperature, 4, 2, g_temp); 
  }
  
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    dtostrf(event.relative_humidity, 4, 2, g_humidity);
  }
}
