
SoftwareSerial SensorsSer(5, 16); // Rx, Tx

void setupSensors() {
  SensorsSer.begin(9600);
}

String sensorGet(char * type) {
  SensorsSer.println(type); // send command
  SensorsSer.flush();
  String readString = "";

  while (SensorsSer.available() == 0) { // wait
    if (millis() > 3000) {
      break;
    }
  }
  
  return SensorsSer.readString();
  
}
