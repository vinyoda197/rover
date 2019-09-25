
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


void setup(void) {
  Serial.begin(9600);

  // Wi-Fi connection
  if (!WiFi.config(local_IP, gateway, subnet)) {
    Serial.println("STA Failed to configure");
  }
  
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
  delay(1);
}
