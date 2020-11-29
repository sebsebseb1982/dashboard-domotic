//https://forum.arduino.cc/index.php?topic=642749.0
void drawCentreString(const String &buf, int x, int y) {
  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds(buf, x, y, &x1, &y1, &w, &h);
  display.setCursor(x - w / 2, y);
  display.print(buf);
}

void drawRightAlignedString(const String buf, int x, int y) {
  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds(buf, 0, 0, &x1, &y1, &w, &h);

  display.setCursor(x - w, y);
  display.print(buf);
}

String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }

  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

#define LINE_HEIGHT 18

void drawFloatingText(const String &buf, int x, int y, int maxWidth, int &height) {
  int wordIndex = 0;
  int lineIndex = 0;
  String nextWord = getValue(buf, ' ', wordIndex);

  String previousLine;
  String currentLine;

  int16_t x1, y1;
  uint16_t w, h;

  while (nextWord != "") {
    if (currentLine != " ") {
      currentLine += F(" ");
    }
    currentLine += nextWord;

    display.getTextBounds(currentLine, 0, 0, &x1, &y1, &w, &h);

    if (w > maxWidth) {
      display.setCursor(x, y + (lineIndex * LINE_HEIGHT));
      display.print(previousLine);
      currentLine = "";
      previousLine = "";
      lineIndex++;
    } else {
      previousLine = currentLine;
      wordIndex++;
      nextWord = getValue(buf, ' ', wordIndex);
    }
  }

  display.setCursor(x, y + (lineIndex * LINE_HEIGHT));
  display.print(previousLine);

  height = (lineIndex + 1) * LINE_HEIGHT;
}
