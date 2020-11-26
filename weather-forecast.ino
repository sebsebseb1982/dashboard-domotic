moonPhase moonPhase;

TwoDaysWeatherForecasts getWeatherForecasts() {
  HTTPClient http;
  http.begin(API_OPENWEATHERMAP, root_ca);
  int httpCode = http.GET();

  if (httpCode > 0) {
    String response = http.getString();
    DynamicJsonDocument doc(8192);
    DeserializationError error = deserializeJson(doc, response);
    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.c_str());
      return {{0, "", 0, 0}};
    }

    return {
      {
        doc["daily"][0]["dt"],
        doc["daily"][0]["weather"][0]["icon"],
        doc["daily"][0]["temp"]["min"],
        doc["daily"][0]["temp"]["max"]
      },
      {
        doc["daily"][1]["dt"],
        doc["daily"][1]["weather"][0]["icon"],
        doc["daily"][1]["temp"]["min"],
        doc["daily"][1]["temp"]["max"]
      }
    };

  } else {
    Serial.print("Error on sending GET Request: ");
    Serial.println(httpCode);
    return {{0, "", 0, 0}};
  }
  http.end();
}

/*
  void displayWeatherForecast(WeatherForecast weatherForecast) {
  display.print(day(weatherForecast.date));
  display.print("/");
  display.print(month(weatherForecast.date));
  display.print(" ");
  display.println(weatherForecast.weather);
  int minTemperature = round(weatherForecast.min);
  display.println(minTemperature);
  display.println(round(weatherForecast.max));
  }
*/

void drawTemperature(float temperature, int x, int y) {
  display.setFont(&FreeSans12pt7b);
  display.setTextColor(GxEPD_BLACK);

  String temperatureBuffer;
  temperatureBuffer += String(temperature, 1);
  temperatureBuffer += F(" C");
  drawRightAlignedString(temperatureBuffer, x, y);

  // Pour remplacer le putain de caractère °
  display.drawCircle(x - 16, y - 16, 1, GxEPD_BLACK);
  display.drawCircle(x - 16, y - 16, 2, GxEPD_BLACK);
}

void drawDate(int date, int x, int y) {
  display.setFont(&FreeSans9pt7b);
  display.setTextColor(GxEPD_RED);

  String dateBuffer;

  dateBuffer += String(day(date));
  dateBuffer += F("/");
  dateBuffer += String(month(date));
  drawCentreString(
    dateBuffer,
    x,
    y
  );
}

void drawIcon(int x, int y, String icon) {
  timeClient.update();
  Serial.println(timeClient.getFormattedTime());
  moonData_t moon;

  moon = moonPhase.getPhase(timeClient.getEpochTime());

  Serial.println(moon.angle);
  Serial.println(moon.percentLit * 100);
  Serial.print(hour());
  Serial.print("h");
  Serial.print(minute());
  Serial.print("m");
  Serial.print(second());
  Serial.println("s");

  if (icon.startsWith("01")) {
    display.drawBitmap(x, y, clear_sky_01d, 100, 100, GxEPD_RED);
  }  else if (icon.startsWith("02")) {
    display.drawBitmap(x, y, few_clouds_02d, 100, 100, GxEPD_RED);
  }  else if (icon.startsWith("03")) {
    display.drawBitmap(x, y, scattered_clouds_03d, 100, 100, GxEPD_RED);
  }
}

void drawWeatherForecast(WeatherForecast weatherForecast, String dayDescription, int x, int y) {
  int center = x + (SCREEN_WIDTH / 8);

  display.setTextColor(GxEPD_BLACK);
  display.setFont(&FreeSans12pt7b);
  drawCentreString(
    dayDescription,
    center,
    y + 30
  );

  drawDate(
    weatherForecast.date,
    center,
    y + 60
  );

  drawTemperature(
    weatherForecast.max,
    center - 20,
    y + 120
  );

  drawTemperature(
    weatherForecast.min,
    center - 20,
    y + 150
  );

  drawIcon(
    center - 10,
    y + 75,
    weatherForecast.icon
  );


}

void drawTwoDaysWeatherForecasts() {
  TwoDaysWeatherForecasts twoDaysWeatherForecasts = getWeatherForecasts();

  int y = HORIZONTAL_SPLIT_Y + SPACE_BETWEEN_LINES;
  drawWeatherForecast(
    twoDaysWeatherForecasts.today,
    "Aujourd'hui",
    0,
    y
  );
  drawWeatherForecast(
    twoDaysWeatherForecasts.tomorrow,
    "Demain",
    SCREEN_WIDTH / 4,
    y
  );
}
