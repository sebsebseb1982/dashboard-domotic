const int BATTERY_VOLTAGE_PIN = 33 ;

float getBatteryVoltage() {
  pinMode(BATTERY_VOLTAGE_PIN, INPUT);
  return ((float)analogRead(BATTERY_VOLTAGE_PIN)) * 0.002765;
}

void drawBatteryEmpty() {
  display.drawBitmap(
    SCREEN_WIDTH / 2 - batteryEmptyImageWidth / 2, 
    SCREEN_HEIGHT / 2 - batteryEmptyImageHeight / 2,
    batteryEmptyImage, 
    batteryEmptyImageWidth, 
    batteryEmptyImageHeight, 
    GxEPD_RED
    );
}
