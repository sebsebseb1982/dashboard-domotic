StatusBarDatas getStatusBarDatas() {
  pinMode(33, INPUT);
  timeClient.update();

  String formattedTime;
  if(timeClient.getHours() < 10) {
    formattedTime += F("0");
  }
  formattedTime += timeClient.getHours();
  formattedTime += F(":");
  if(timeClient.getMinutes() < 10) {
    formattedTime += F("0");
  }
  formattedTime += timeClient.getMinutes();
  
  return {
    WiFi.localIP(),
    ((float)analogRead(33)) * 0.001811,
    formattedTime
  };
}

void drawBatteryLevel(float voltage) {
  String voltageString;
  voltageString += String(voltage);
  voltageString += F("v");
  Serial.println(voltageString);
  drawRightAlignedString(voltageString, SCREEN_WIDTH - 70, 6);

  int batteryX = SCREEN_WIDTH - 60;
  int batteryY = 5;

  display.drawBitmap(batteryX, batteryY, battery, 21, 10, GxEPD_WHITE);

  if (voltage > 4.2) {
    display.fillRect(
      batteryX + 2,
      batteryY + 2,
      3,
      6,
      GxEPD_WHITE
    );
  }
  if (voltage > 4.3) {
    display.fillRect(
      batteryX + 6,
      batteryY + 2,
      3,
      6,
      GxEPD_WHITE
    );
  }
  if (voltage > 4.4) {
    display.fillRect(
      batteryX + 10,
      batteryY + 2,
      3,
      6,
      GxEPD_WHITE
    );
  }
  if (voltage > 4.5) {
    display.fillRect(
      batteryX + 14,
      batteryY + 2,
      3,
      6,
      GxEPD_WHITE
    );
  }
}

void drawStatusBar(StatusBarDatas statusBarDatas) {
  Serial.println("drawStatusBar() : START");
  display.fillRect(
    0,
    0,
    SCREEN_WIDTH,
    20,
    GxEPD_RED
  );

  display.setTextColor(GxEPD_WHITE);
  display.setCursor(6, 6);
  display.print(statusBarDatas.ipAddress);
  
  drawRightAlignedString(statusBarDatas.formattedTime, SCREEN_WIDTH - 6, 6);

  drawBatteryLevel(statusBarDatas.voltage);
  Serial.println("drawStatusBar() : END");
}
