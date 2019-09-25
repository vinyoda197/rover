#include <SoftwareSerial.h>
#include <Servo.h> 
#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is conntec to the Arduino digital pin 4
#define ONE_WIRE_BUS 4

#include "mydht.h"
#include "soil.h"

#define water A1
#define turbidity A2
#define ph A0
#define light A5

#define GPS_LED 5
#define servoPin 11

OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

SoftwareSerial mySer(3, 2); // RX, TX
Servo Servo1;

char g_water[50];
char g_turbidity[50];
char g_ph[50];
char g_light[50];

void setup() {
  pinMode(GPS_LED, OUTPUT);
  digitalWrite(GPS_LED, LOW);
  
  mySer.begin(9600);
  setupDHT();

  Servo1.attach(servoPin);
  Servo1.write(0); // initial

  setupPh();

  sensors.begin();
  
  mySer.println("Sensors online!");
  mySer.println();
}

void loop() {
  fetchCommands();
  
  mySer.println();
  
  loopPh();
  sensors.requestTemperatures();
  runDHT();
  
  delay(500);
}


void servoTap ()
{
  Servo1.write(180); 
   delay(1000); 
   Servo1.write(0);
}

void fetchCommands() {
    String readString = "";
    while(mySer.available()) {
     char c = mySer.read();
     readString += c; 
    }
    
    if (readString.indexOf("dht") >= 0) {
       char temp[100];
       int t = sensors.getTempCByIndex(0);
       snprintf(temp, 100, "{\"Temperature\": %d,\"Humidity\": %s}", t, g_humidity);
       mySer.println(temp);
       mySer.println();
       mySer.flush();
    }
    
    if (readString.indexOf("water") >= 0) {
      char temp2[50];
      snprintf(temp2, 50, "{\"Water\": %d}", analogRead(water)); 
      mySer.println(temp2);
      mySer.println();
      mySer.flush();
    }


    if (readString.indexOf("turbidity") >= 0) {
      char temp2[50];
      float volt, rawVolt;
      float ntu;

      volt = 0;
      for(int i=0; i<800; i++)
      {
          volt += ((float)analogRead(turbidity)/1023)*5;
      }
      volt = rawVolt = volt/800;
      volt = volt*4.2/3.2;
      volt = round_to_dp(volt,1);
      if(volt < 2.5){
        ntu = 3000;
      }else{
        ntu = -1120.4*square(volt)+5742.3*volt-4353.8; 
      }
      //snprintf(temp2, 50, "{\"Voltage\": %.2f,\"Turbidity\": %d}", volt, ntu); 
      //mySer.println(temp2);
      mySer.print("{\"Voltage\": ");
      mySer.println(rawVolt);
      mySer.print(", \"Turbidity\": ");
      mySer.print(ntu);
      mySer.println("}");
      mySer.println();
      mySer.flush();
    }

    if (readString.indexOf("ph") >= 0) {
      char temp2[50]; 
      mySer.println(pH.read_ph());
      mySer.println();
      mySer.flush();
    }

    if (readString.indexOf("light") >= 0) {
      char temp2[50];
         snprintf(temp2, 50, "{\"Light\": %d}", analogRead(light)); 
      mySer.println(temp2);
      mySer.println();
      mySer.flush();
    }


    if (readString.indexOf("servo") >= 0) {
      servoTap();
      mySer.println("ok");
      mySer.println();
      mySer.flush();
    }

    if (readString.indexOf("gpson") >= 0) {
        digitalWrite(GPS_LED, HIGH);
    }

    if (readString.indexOf("gpsoff") >= 0) {
        digitalWrite(GPS_LED, LOW);
    }
  
}

float round_to_dp( float in_value, int decimal_place )
{
  float multiplier = powf( 10.0f, decimal_place );
  in_value = roundf( in_value * multiplier ) / multiplier;
  return in_value;
}
