#define GRID_LINES_WIDTH 2
#define GRID_COLOR GxEPD_BLACK

void drawHorizontalSplit() {
  display.fillRect(
    SPACE_BETWEEN_LINES,
    HORIZONTAL_SPLIT_Y - (GRID_LINES_WIDTH / 2),
    SCREEN_WIDTH - (2 * SPACE_BETWEEN_LINES),
    GRID_LINES_WIDTH,
    GRID_COLOR
  );
}

void drawBottomSplits() {
  int bottomSplitsYStart = HORIZONTAL_SPLIT_Y + (GRID_LINES_WIDTH / 2) + (SPACE_BETWEEN_LINES);
  int bottomSplitsHeight = SCREEN_HEIGHT - HORIZONTAL_SPLIT_Y - (GRID_LINES_WIDTH / 2) - (SPACE_BETWEEN_LINES * 2);

  display.fillRect(
    (SCREEN_WIDTH / 4) - (GRID_LINES_WIDTH / 2),
    bottomSplitsYStart,
    GRID_LINES_WIDTH,
    bottomSplitsHeight,
    GRID_COLOR
  );

  display.fillRect(
    (SCREEN_WIDTH / 2) - (GRID_LINES_WIDTH / 2),
    bottomSplitsYStart,
    GRID_LINES_WIDTH,
    bottomSplitsHeight,
    GRID_COLOR
  );
}

void drawGrid()
{
  drawHorizontalSplit();
  drawBottomSplits();


  display.fillRect(
    0,
    0,
    SCREEN_WIDTH,
    20,
    GxEPD_RED
  );


  display.setTextColor(GxEPD_WHITE);
  display.setCursor(6, 6);
  display.print(WiFi.localIP());

  timeClient.update();
  drawRightAlignedString(timeClient.getFormattedTime(), SCREEN_WIDTH-6, 6);

}

void drawGrid2() {
  display.fillScreen(GxEPD_WHITE);

  // Météo
  display.fillRect(
    0,
    0,
    SCREEN_WIDTH / 4,
    SCREEN_HEIGHT,
    GxEPD_RED
  );

  // courbes
  display.fillRect(
    SCREEN_WIDTH / 4,
    0,
    SCREEN_WIDTH / 2,
    SCREEN_HEIGHT / 2,
    GRID_COLOR
  );

  // citation
  display.fillRect(
    SCREEN_WIDTH / 2,
    SCREEN_HEIGHT / 2,
    SCREEN_WIDTH / 2,
    SCREEN_HEIGHT / 2,
    GRID_COLOR
  );
}
