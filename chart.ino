#define IMAGE_WIDTH 400
#define IMAGE_HEIGHT 250

String getChartImage(String serie) {
  HTTPClient http;
  String url;
  url += F("http://");
  url += DOMOTIC3_USER;
  url += F(":");
  url += DOMOTIC3_TOKEN;
  url += F("@");
  url += JEEDOM_HOST;
  url += F(":");
  url += DOMOTIC3_PORT;
  url += F("/home/series/");
  url += serie;
  http.begin(url);

  String message;
  message += F("Récupération du graphique ");
  message += serie;
  message += F(" (GET ");
  message += url;
  message += F(")");
  Serial.println(message);



  int httpCode;
  int retry = 0;

  do {
    httpCode = http.GET();
    retry ++;
    Serial.println("...");
  } while (httpCode <= 0 && retry < HTTP_RETRY);

  if (httpCode > 0) {
    Serial.println("OK");
    Serial.println("");
    String response = http.getString();
    return response;
  } else {
    Serial.print("Error on sending GET Request: ");
    Serial.println(httpCode);
    return "Impossible de recuperer la citation du jour";
  }
  http.end();
}

ChartDatas getChartDatas() {
  return {
    getChartImage("outside"),
    getChartImage("upstairs"),
    getChartImage("downstairs")
  };
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

void drawChart(ChartDatas chartDatas) {
  Serial.println("drawChart() : START");
  int chartX = 430;
  int chartY = 40;
  drawMyImage(chartX, chartY, chartDatas.downstairs, IMAGE_WIDTH, IMAGE_HEIGHT, GxEPD_BLACK);
  drawMyImage(chartX, chartY, chartDatas.upstairs, IMAGE_WIDTH, IMAGE_HEIGHT, GxEPD_RED);
  drawMyImage(chartX, chartY, chartDatas.outside, IMAGE_WIDTH, IMAGE_HEIGHT, GxEPD_BLACK);
  Serial.println("drawChart() : END");
}
