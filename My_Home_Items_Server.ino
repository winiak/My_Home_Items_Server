
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#include "config.h"

ESP8266WebServer server(80);

// Variable to store the HTTP request
String header;

String output5State = "off";
String output4State = "off";
const int output5 = 8;
const int output4 = 7;


void setup() {
  setup_shift();
  Serial.begin(115200);
  wifi_setup();

  server.on("/", mainPage);
  server.on("/test.svg", drawGraph);
  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
