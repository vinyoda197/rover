#define WIFI_LED 2

const char *ssid = "amphibot";
const char *password = "vinyoda197";

ESP8266WebServer server(80);

IPAddress local_IP(192, 168, 1, 183);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 0, 0);

void setupServer() {
  pinMode(WIFI_LED, OUTPUT);
  digitalWrite(WIFI_LED, LOW);

  // Wi-Fi connection
  if (!WiFi.config(local_IP, gateway, subnet)) {
    Serial.println("STA Failed to configure");
  }
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
   
  server.begin();
  Serial.println("HTTP server started");
  digitalWrite(WIFI_LED, HIGH);
}

void respond(String data) {
  server.sendHeader("Access-Control-Allow-Origin","*");
  server.send(200, "text/html", data);
}

void initServerHandlers() {
  
  server.on("/forward", []() {
    forward();
    respond("forward");
  });
  server.on("/stop", []() {
    halt();
    respond("stop");
  });
  server.on("/reverse", []() {
    backing();
    respond("reverse");
  });
  server.on("/left", []() {
    turnLeft();
    respond("left");
  });
  server.on("/right", []() {
    turnRight();
    respond("right");
  });
  
  server.on("/dht", []() {
    respond(sensorGet("dht"));
  });

  server.on("/water", []() {
    respond(sensorGet("water"));
  });

  server.on("/turbidity", []() {
    respond(sensorGet("turb"));
  });

  server.on("/ph", []() {
    respond(sensorGet("ph"));
  });

  server.on("/data", []() {
    respond(sensorGet("d"));
  });

  server.on("/light", []() {
    respond(sensorGet("light"));
  });

  server.on("/servo", []() {
    respond(sensorGet("servo"));
  });

  server.on("/location", []() {
    char lt[20], ln[20];
    
    dtostrf(lati, 8, 12, lt); 
    dtostrf(lngi, 8, 12 , ln);
    
    char temp[150];
    snprintf(temp, 150, "{\"Lat\": %s, \"Lng\": %s}", lt, ln);
    respond(temp);
  });

}
