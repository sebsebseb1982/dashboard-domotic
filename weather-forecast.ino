moonPhase moonPhase;

TwoDaysWeatherForecasts getWeatherForecasts() {
  HTTPClient http;
  http.begin(API_OPENWEATHERMAP, root_ca);

  String message;
  message += F("Récupération de la météo");
  message += F(" (GET ");
  message += API_OPENWEATHERMAP;
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
    http.end();
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
    String error;
    error += F("KO -> code erreur = ");
    error += String(httpCode);
    Serial.println(error);
    Serial.println("");
    return {{0, "", 0, 0}};
  }

}

void drawTemperature(float temperature, int x, int y, uint16_t color) {
  display.setFont(&FreeSans12pt7b);
  display.setTextColor(color);

  String temperatureBuffer;
  temperatureBuffer += String(temperature, 1);
  temperatureBuffer += F(" C");
  drawRightAlignedString(temperatureBuffer, x, y);

  // Pour remplacer le putain de caractère °
  display.drawCircle(x - 16, y - 15, 1, color);
  display.drawCircle(x - 16, y - 15, 2, color);
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

void drawIcon(int x, int y, String icon, boolean replaceByMoonPhaseAtNight) {

  boolean isNight = timeClient.getHours() >= 21 || timeClient.getHours() <= 4;

  if (replaceByMoonPhaseAtNight && isNight) {
    moonData_t moon = moonPhase.getPhase(timeClient.getEpochTime());

    if (moon.angle >= 349 || moon.angle < 11) {
      display.drawBitmap(x + 10, y + 10, moon000, MOON_PHASE_IMAGE_WIDTH, MOON_PHASE_IMAGE_HEIGHT, GxEPD_RED);
    } else if (moon.angle >= 11 && moon.angle < 34) {
      display.drawBitmap(x + 10, y + 10, moon022, MOON_PHASE_IMAGE_WIDTH, MOON_PHASE_IMAGE_HEIGHT, GxEPD_RED);
    } else if (moon.angle >= 34 && moon.angle < 56) {
      display.drawBitmap(x + 10, y + 10, moon045, MOON_PHASE_IMAGE_WIDTH, MOON_PHASE_IMAGE_HEIGHT, GxEPD_RED);
    } else if (moon.angle >= 56 && moon.angle < 79) {
      display.drawBitmap(x + 10, y + 10, moon067, MOON_PHASE_IMAGE_WIDTH, MOON_PHASE_IMAGE_HEIGHT, GxEPD_RED);
    } else if (moon.angle >= 79 && moon.angle < 101) {
      display.drawBitmap(x + 10, y + 10, moon090, MOON_PHASE_IMAGE_WIDTH, MOON_PHASE_IMAGE_HEIGHT, GxEPD_RED);
    } else if (moon.angle >= 101 && moon.angle < 124) {
      display.drawBitmap(x + 10, y + 10, moon112, MOON_PHASE_IMAGE_WIDTH, MOON_PHASE_IMAGE_HEIGHT, GxEPD_RED);
    } else if (moon.angle >= 124 && moon.angle < 146) {
      display.drawBitmap(x + 10, y + 10, moon135, MOON_PHASE_IMAGE_WIDTH, MOON_PHASE_IMAGE_HEIGHT, GxEPD_RED);
    } else if (moon.angle >= 146 && moon.angle < 169) {
      display.drawBitmap(x + 10, y + 10, moon157, MOON_PHASE_IMAGE_WIDTH, MOON_PHASE_IMAGE_HEIGHT, GxEPD_RED);
    } else if (moon.angle >= 169 && moon.angle < 191) {
      display.drawBitmap(x + 10, y + 10, moon180, MOON_PHASE_IMAGE_WIDTH, MOON_PHASE_IMAGE_HEIGHT, GxEPD_RED);
    } else if (moon.angle >= 191 && moon.angle < 214) {
      display.drawBitmap(x + 10, y + 10, moon202, MOON_PHASE_IMAGE_WIDTH, MOON_PHASE_IMAGE_HEIGHT, GxEPD_RED);
    } else if (moon.angle >= 214 && moon.angle < 236) {
      display.drawBitmap(x + 10, y + 10, moon225, MOON_PHASE_IMAGE_WIDTH, MOON_PHASE_IMAGE_HEIGHT, GxEPD_RED);
    } else if (moon.angle >= 236 && moon.angle < 259) {
      display.drawBitmap(x + 10, y + 10, moon247, MOON_PHASE_IMAGE_WIDTH, MOON_PHASE_IMAGE_HEIGHT, GxEPD_RED);
    } else if (moon.angle >= 259 && moon.angle < 281) {
      display.drawBitmap(x + 10, y + 10, moon270, MOON_PHASE_IMAGE_WIDTH, MOON_PHASE_IMAGE_HEIGHT, GxEPD_RED);
    } else if (moon.angle >= 281 && moon.angle < 304) {
      display.drawBitmap(x + 10, y + 10, moon292, MOON_PHASE_IMAGE_WIDTH, MOON_PHASE_IMAGE_HEIGHT, GxEPD_RED);
    } else if (moon.angle >= 304 && moon.angle < 326) {
      display.drawBitmap(x + 10, y + 10, moon315, MOON_PHASE_IMAGE_WIDTH, MOON_PHASE_IMAGE_HEIGHT, GxEPD_RED);
    } else if (moon.angle >= 326 && moon.angle < 349) {
      display.drawBitmap(x + 10, y + 10, moon337, MOON_PHASE_IMAGE_WIDTH, MOON_PHASE_IMAGE_HEIGHT, GxEPD_RED);
    }
  } else {
    if (icon.startsWith("01")) {
      display.drawBitmap(x, y, clear_sky_01, 100, 100, GxEPD_RED);
    }  else if (icon.startsWith("02")) {
      display.drawBitmap(x, y, few_clouds_02, 100, 100, GxEPD_RED);
    }  else if (icon.startsWith("03")) {
      display.drawBitmap(x, y, scattered_clouds_03, 100, 100, GxEPD_RED);
    }  else if (icon.startsWith("04")) {
      display.drawBitmap(x, y, broken_clouds_04, 100, 100, GxEPD_RED);
    }  else if (icon.startsWith("09")) {
      display.drawBitmap(x, y, shower_rain_09, 100, 100, GxEPD_RED);
    }  else if (icon.startsWith("10")) {
      display.drawBitmap(x, y, rain_10, 100, 100, GxEPD_RED);
    }  else if (icon.startsWith("11")) {
      display.drawBitmap(x, y, thunderstorm_11, 100, 100, GxEPD_RED);
    }  else if (icon.startsWith("13")) {
      display.drawBitmap(x, y, snow_13, 100, 100, GxEPD_RED);
    }  else if (icon.startsWith("50")) {
      display.drawBitmap(x, y, mist_50, 100, 100, GxEPD_RED);
    }
  }
}

void drawWeatherForecast(WeatherForecast weatherForecast, String dayDescription, int x, int y, boolean replaceByMoonPhaseAtNight) {
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
    y + 120,
    GxEPD_BLACK
  );

  drawTemperature(
    weatherForecast.min,
    center - 20,
    y + 150,
    GxEPD_BLACK
  );

  drawIcon(
    center - 10,
    y + 75,
    weatherForecast.icon,
    replaceByMoonPhaseAtNight
  );
}

void drawTwoDaysWeatherForecasts(TwoDaysWeatherForecasts twoDaysWeatherForecasts) {
  Serial.println("drawTwoDaysWeatherForecasts() : START");

  int y = HORIZONTAL_SPLIT_Y + SPACE_BETWEEN_LINES;
  drawWeatherForecast(
    twoDaysWeatherForecasts.today,
    "Aujourd'hui",
    0,
    y,
    true
  );
  drawWeatherForecast(
    twoDaysWeatherForecasts.tomorrow,
    "Demain",
    SCREEN_WIDTH / 4,
    y,
    false
  );
  Serial.println("drawTwoDaysWeatherForecasts() : END");
}
