
String temp_string;

void wifi_test_connection() {
  static long last_check;
  const long check_every = 30000;
  static int last_state = -10;
  int current_state = wifiMulti.run();
  if (last_check+check_every < millis()) {
    writeLine("IP address: " + WiFi.localIP().toString()); 
    last_check = millis();
  }
  if (current_state == last_state)
    return;
  if (current_state != WL_CONNECTED) {
    Serial.println("WiFi not connected!");
    writeLine("WiFi not connected!");
  }
  if (current_state == WL_CONNECTED) {
    Serial.println("WiFi connected:");
    Serial.println(WiFi.SSID());
    writeLine("AP: " + WiFi.SSID()); 
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
    writeLine("IP address: " + WiFi.localIP().toString());    
  }
  last_state = current_state;
}

void wifi_multi_setup() {
  String con_ssid;
  Serial.println("Connecting...");
  delay(10);
  WiFi.mode(WIFI_STA);
  for (byte n=0; n < NUMBER_OF_AP; n++)
    wifiMulti.addAP(ap_login[n].ssid, ap_login[n].password);
  if (wifiMulti.run() == WL_CONNECTED) {
    Serial.println("WiFi connected");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
    writeLine("IP address: " + WiFi.localIP().toString());
  }
}

void wifi_setup() {
  // Connect to Wi-Fi network with SSID and password
  String con_ssid;
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.print("Connected to ");
  temp_string = ssid;
  writeLine("Connected to " + temp_string);
  Serial.println(ssid);
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  //temp_string = sprint();
  writeLine("IP address: " + WiFi.localIP().toString());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }

  server.send(404, "text/plain", message);
}

void drawGraph() {
  String out = "";
  char temp[100];
  out += "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"400\" height=\"150\">\n";
  out += "<rect width=\"400\" height=\"150\" fill=\"rgb(250, 230, 210)\" stroke-width=\"1\" stroke=\"rgb(0, 0, 0)\" />\n";
  out += "<g stroke=\"black\">\n";
  int y = rand() % 130;
  for (int x = 10; x < 390; x += 10) {
    int y2 = rand() % 130;
    sprintf(temp, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke-width=\"1\" />\n", x, 140 - y, x + 10, 140 - y2);
    out += temp;
    y = y2;
  }
  out += "</g>\n</svg>\n";

  server.send(200, "image/svg+xml", out);
}

String getArgument(String argumentName) {
  if (server.args() == 0)
    return "";
  if (argumentName == "")
    return "";
  for (uint8_t i = 0; i < MAX_ARGUMENTS; i++)
    if (argumentName == recArguments[i].arg_name) {
      //Serial.print("Found: ");
      //Serial.print(recArguments[i].arg_name);
      //Serial.print("\t with value: ");
      //Serial.println(recArguments[i].arg_value);
      return recArguments[i].arg_value;
    }
  return "";
}

void getArguments() {
  String message = "URI: ";
  message += server.uri();
  message += "";
  message += (server.method() == HTTP_GET) ? " (GET)" : " (POST)";
  // print it
  Serial.println(message);
  //writeLine(message);
  
  message = "Arg:";
  for (uint8_t i = 0; i < MAX_ARGUMENTS; i++) {
    recArguments[i].arg_name = "";
    recArguments[i].arg_value = "";
  }
  //Serial.print("Number of arguments: ");
  //Serial.println(server.args());
  
  for (uint8_t i = 0; i < server.args(); i++) {
    recArguments[i].arg_name = server.argName(i);
    recArguments[i].arg_value = server.arg(i);
    message += " " + server.argName(i) + "=" + server.arg(i) + ";";
  }
  //message += "";

  // print it
  //Serial.println(message);
  //writeLine(message);
}
