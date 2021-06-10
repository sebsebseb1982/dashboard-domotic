StatusBarDatas getStatusBarDatas() {
  pinMode(BATTERY_VOLTAGE_PIN, INPUT);
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

  display.drawBitmap(batteryX, batteryY, batteryIcon, 21, 10, GxEPD_WHITE);

  if (voltage > 7.48) {
    display.fillRect(
      batteryX + 2,
      batteryY + 2,
      3,
      6,
      GxEPD_WHITE
    );
  }
  if (voltage > 7.66) {
    display.fillRect(
      batteryX + 6,
      batteryY + 2,
      3,
      6,
      GxEPD_WHITE
    );
  }
  if (voltage > 7.84) {
    display.fillRect(
      batteryX + 10,
      batteryY + 2,
      3,
      6,
      GxEPD_WHITE
    );
  }
  if (voltage > 8.02) {
    display.fillRect(
      batteryX + 14,
      batteryY + 2,
      3,
      6,
      GxEPD_WHITE
    );
  }
}

void drawStatusBar(StatusBarDatas statusBarDatas, float batteryVoltage) {
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

  drawBatteryLevel(batteryVoltage);
  Serial.println("drawStatusBar() : END");
}
