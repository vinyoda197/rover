
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
// #include <ESP8266mDNS.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include "index.h"
#include "sensors.h"
#include "mobility.h"
#include "mygps.h"
#include "server.h"

#define COLLEFT 12
#define COLRIGHT 14

int colL = HIGH;
int colR = HIGH;


void setup(void) {
  Serial.begin(9600);

  // Wi-Fi connection
  if (!WiFi.config(local_IP, gateway, subnet)) {
    Serial.println("STA Failed to configure");
  }

  pinMode(1, FUNCTION_3);
  pinMode(3, FUNCTION_3);
  
  pinMode(COLLEFT, INPUT);
  pinMode(COLRIGHT, INPUT);
  
  setupMobility();
  setupGPS();
  setupSensors();
  setupServer();
  initServerHandlers();
}

void loop(void) {
  server.handleClient();
  // MDNS.update();
  runGPS();


  colL = digitalRead(COLLEFT);
  colR = digitalRead(COLRIGHT);

  if (colL == LOW) {
    digitalWrite(m1, 1);  // reverse right motor
    digitalWrite(m2, 0);
  } else {
    if (!onReverse) {
      digitalWrite(m1, 0);
    }
  }

  if (colR == LOW) {
    digitalWrite(m3, 0);
    digitalWrite(m4, 1);  // reverse left motor
  } else {
    if (!onReverse) {
      digitalWrite(m4, 0);
    }
  }

 
  delay(1);
}
