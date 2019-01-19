
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#ifndef DEFS
#include "defs.h"
#endif

#include "config.h"


ESP8266WiFiMulti wifiMulti;
ESP8266WebServer server(80);


// Variable to store the HTTP request
String header;

void setup() {
  wdt_disable();
  setup_shift();
  Serial.begin(115200);
  screen_setup();
  
  wifi_multi_setup(); //wifi_setup();

  server.on("/", handleNotFound);
  server.on("/control", mainPage);
  server.on("/request", processPage);
  server.on("/test.svg", drawGraph);
  //server.on("/icon_swiatlo_parter.svg", []() { server.send(200, "image/svg+xml", icon_swiatlo_parter); }); 
  //server.on("/icon_swiatlo_pietro.svg", []() { server.send(200, "image/svg+xml", icon_swiatlo_pietro); }); 
  server.on("/icons/sbu.svg", drawShieldButtonUp); 
  server.on("/icons/sbst.svg", drawShieldButtonStop); 
  server.on("/icons/sbd.svg", drawShieldButtonDown); 
  
  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");

  wdt_enable(1000);
}

void loop() {
  wifi_test_connection();
  wdt_reset();
  server.handleClient();
  requestExecution();
  timedExecution();
  delay(10);
}
