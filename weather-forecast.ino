TwoDaysWeatherForecasts getWeatherForecasts() {
  WiFiClientSecure client;
  client.setInsecure(); //the magic line, use with caution
  client.connect(API_OPENWEATHERMAP, 443);
  HTTPClient http;

  http.begin(client, API_OPENWEATHERMAP);
  http.addHeader("Content-Type", "application/json");

  int httpResponseCode = http.GET();

  if (httpResponseCode > 0) {

    String response = http.getString();

    Serial.println(httpResponseCode);

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
        doc["daily"][0]["weather"][0]["description"],
        doc["daily"][0]["temp"]["min"],
        doc["daily"][0]["temp"]["max"]
      },
      {
        doc["daily"][1]["dt"],
        doc["daily"][1]["weather"][0]["description"],
        doc["daily"][1]["temp"]["min"],
        doc["daily"][1]["temp"]["max"]
      }
    };
  } else {
    Serial.print("Error on sending GET Request: ");
    Serial.println(httpResponseCode);
    return {{0, "", 0, 0}};
  }

}

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
