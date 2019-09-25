static const int RXPin = 12, TXPin = 14; // GPS Module’s Tx to D6 & Rx to D5
static const uint32_t GPSBaud = 9600;
float lati = 0.0, lngi = 0.0;

TinyGPSPlus gps;

SoftwareSerial gpss(RXPin, TXPin);

void setupGPS() {
  SensorsSer.println("gpsoff");
  gpss.begin(GPSBaud);
}

void displayInfo()
{
  if (gps.location.isValid())
  {
    Serial.print(F("Location: "));
    lati = gps.location.lat();
    lngi = gps.location.lng();
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
    SensorsSer.println("gpson");
  }
  else
  {
    Serial.print(F("."));
    SensorsSer.println("gpsoff");
  }

  if (gps.date.isValid())
  {
    Serial.print(F("  Date/Time: "));
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  }
  else
  {
    Serial.print(F("."));
  }

  Serial.println();
}

bool checkInfo() {
  if (gps.location.isValid())
  {
    lati = gps.location.lat();
    lngi = gps.location.lng();
    return true;
  }
  return false;
}


void runGPS() {
  while (gpss.available() > 0) {
    if (gps.encode(gpss.read())) {
      if (checkInfo()) {
        SensorsSer.println("gpson");
        return;
      } else {
        Serial.println();
      }
      // displayInfo();
    }
  }
      
  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS Module Found! Check Hardware!!"));
    // while(true);
  }
}
