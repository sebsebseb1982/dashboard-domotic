void drawLabels(int x, int y) {
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
    GxEPD_BLACK
  );

}

void drawHouse() {
  display.drawBitmap(60 , 60, house, 309  , 200, GxEPD_BLACK);
  display.drawBitmap(60 , 60, toit, 309  , 200, GxEPD_RED);

  drawLabels(220, 140);
  drawTemperature(20.9, 220, 140);
  drawLabels(220, 210);
  drawTemperature(20.2, 220, 210);
  drawLabels(380, 250);
  drawTemperature(8.6, 380, 250);
}
