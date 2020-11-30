#define IMAGE_WIDTH 400
#define IMAGE_HEIGHT 250

String getChartImage(String serie) {
  HTTPClient http;
  String url;
  url += F("http://192.168.1.210:8012/charts/series/");
  url += serie;
  http.begin(url);
  int httpCode = http.GET();


  if (httpCode > 0) {
    String response = http.getString();
    return response;

  } else {
    Serial.print("Error on sending GET Request: ");
    Serial.println(httpCode);
    return "Impossible de recuperer la citation du jour";
  }
  http.end();
}

void drawMyImage(int x, int y, String hexString, int w, int h, uint16_t color) {
  int currentX = x;
  int currentY = y;

  //Serial.println( strlen(hexString));

  for (int charIndex = 0; charIndex < hexString.length(); charIndex++) {

    char aChar = hexString[charIndex];
    String merde;
    merde += F("0x");
    merde += aChar;
    int number = strtol(merde.c_str(), NULL, 16);

    for (int tutu = 0; tutu < 4; tutu++) {
      if (bitRead(number, 3-tutu) == 1) {
        display.drawPixel(currentX + tutu, currentY, color);
      }
    }

    if (currentX + 4 >= x + w) {
      currentX = x;
      currentY ++;
    } else {
      currentX += 4;
    }
  }
}

void drawChart() {
  drawMyImage(450, 30, getChartImage("downstairs"), IMAGE_WIDTH, IMAGE_HEIGHT, GxEPD_BLACK);
  drawMyImage(450, 30, getChartImage("upstairs"), IMAGE_WIDTH, IMAGE_HEIGHT, GxEPD_RED);
}
