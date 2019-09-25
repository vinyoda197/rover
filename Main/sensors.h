
SoftwareSerial SensorsSer(5, 16); // Rx, Tx

void setupSensors() {
  SensorsSer.begin(9600);
}

String sensorGet(char * type) {
  SensorsSer.flush();
  SensorsSer.println(type); // send command
  SensorsSer.flush();
  String readString = "";

  while (SensorsSer.available() == 0) { // wait
    if (millis() > 5000) {
      break;
    }
  }
  
  return SensorsSer.readString();
  
}
