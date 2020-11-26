
void setupWifi() {

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");

/*
  display.setTextColor(GxEPD_BLACK);

  display.setCursor(0, 0); // set the postition to start printing text
  display.print(WiFi.localIP()); // print some text
  */



}
