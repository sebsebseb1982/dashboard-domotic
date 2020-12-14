#define HOUSE_X 30
#define HOUSE_Y 50
#define HOUSE_WIDTH 309
#define HOUSE_HEIGHT 200

void drawLabels(int x, int y, uint16_t color) {
  display.fillRoundRect(
    x - 75,
    y - 28,
    83,
    40,
    3,
    GxEPD_WHITE
  );
  display.drawRoundRect(
    x - 75,
    y - 28,
    83,
    40,
    3,
    color
  );

}

Temperatures getTemperatures() {
  return {
    getJeedomVirtualValue(315),
    getJeedomVirtualValue(314),
    getJeedomVirtualValue(320),
    getJeedomVirtualValue(291)
  };
}

void drawThermostat(String setPoint) {
  int thermostatX = SPACE_BETWEEN_LINES;
  int thermostatY = 230;
  int thermostatWidth = 110;
  int thermostatHeight = 50;

  display.drawRoundRect(
    thermostatX,
    thermostatY,
    thermostatWidth,
    thermostatHeight,
    6,
    GxEPD_BLACK
  );

  display.drawLine(
    thermostatX + thermostatWidth - 30,
    thermostatY,
    thermostatX + thermostatWidth - 30,
    thermostatY + thermostatHeight - 1,
    GxEPD_BLACK
  );

  display.drawCircle(
    thermostatX + thermostatWidth - 16,
    thermostatY + (thermostatHeight / 2) - 1,
    4,
    GxEPD_BLACK
  );

  display.drawBitmap(
    thermostatX + thermostatWidth - 20,
    thermostatY + 10,
    arrowUp,
    9,
    5,
    GxEPD_BLACK
  );

  display.drawBitmap(
    thermostatX + thermostatWidth - 20,
    thermostatY + thermostatHeight - 15,
    arrowDown,
    9,
    5,
    GxEPD_BLACK
  );

  display.setFont(&FreeSans12pt7b);
  display.setTextColor(GxEPD_BLACK);

  drawRightAlignedString(
    String(atof(setPoint.c_str()), 1),
    thermostatX + thermostatWidth - 45,
    thermostatY + (thermostatHeight / 2) + 7
  );
}

void drawHouse(Temperatures temperatures) {
  Serial.println("drawHouse() : START");

  display.drawBitmap(
    HOUSE_X,
    HOUSE_Y,
    house,
    HOUSE_WIDTH,
    HOUSE_HEIGHT,
    GxEPD_BLACK
  );

  display.drawBitmap(
    HOUSE_X,
    HOUSE_Y,
    roof,
    HOUSE_WIDTH,
    HOUSE_HEIGHT,
    GxEPD_RED
  );

  int upstairsX = HOUSE_X + 170;
  int upstairsY = HOUSE_Y + 80;
  drawLabels(upstairsX, upstairsY, GxEPD_RED);
  drawTemperature(
    atof(temperatures.upstairs.c_str()),
    upstairsX,
    upstairsY,
    GxEPD_RED
  );

  int downstairsX = HOUSE_X + 170;
  int downstairsY = HOUSE_Y + 150;
  drawLabels(downstairsX, downstairsY, GxEPD_BLACK);
  drawTemperature(
    atof(temperatures.downstairs.c_str()),
    downstairsX,
    downstairsY,
    GxEPD_BLACK
  );

  int outsideX = HOUSE_X + 320;
  int outsideY = HOUSE_Y + 205;
  drawLabels(outsideX, outsideY, GxEPD_BLACK);
  drawTemperature(
    atof(temperatures.outside.c_str()),
    outsideX,
    outsideY,
    GxEPD_BLACK
  );

  drawThermostat(temperatures.setPoint);

  Serial.println("drawHouse() : END");
}
