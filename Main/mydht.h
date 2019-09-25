
#define DHTPIN 2
#define DHTTYPE    DHT11

DHT_Unified dht(DHTPIN, DHTTYPE);

char * getTemp() {
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  char result[6];
  dtostrf(sensor.max_value, 4, 2, result); 
  return result;
}


char * getHumidity() {
  sensor_t sensor;
  dht.humidity().getSensor(&sensor);
  char result[6];
  dtostrf(sensor.max_value, 4, 2, result); 
  return result;
}
