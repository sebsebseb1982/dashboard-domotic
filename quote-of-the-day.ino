

QuoteOfTheDay getQuoteOfTheDay() {
  HTTPClient http;
  http.begin("https://zenquotes.io/api/random", root_ca);
  int httpCode = http.GET();

  if (httpCode > 0) {
    String response = http.getString();
    DynamicJsonDocument doc(8192);
    DeserializationError error = deserializeJson(doc, response);
    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.c_str());
      return {"", ""};
    }

    return {
      doc[0]["q"],
      doc[0]["a"]
    };

  } else {
    Serial.print("Error on sending GET Request: ");
    Serial.println(httpCode);
    return {"Impossible de recuperer la citation du jour", "La direction"};
  }
  http.end();
}

void drawQuoteOfTheDay() {
  int y = 380;
  QuoteOfTheDay quoteOfTheDay = getQuoteOfTheDay();

  display.setTextColor(GxEPD_BLACK);
  display.setFont(&FreeSans9pt7b);

  display.drawBitmap(450, y - 40, quoteTop, 64, 64, GxEPD_RED);


  int height;
  int margin = 80;
  drawFloatingText(
    quoteOfTheDay.quote,
    (SCREEN_WIDTH / 2) +  margin,
    y,
    (SCREEN_WIDTH / 2) - (2 * margin),
    height
  );

  display.setTextColor(GxEPD_RED);
  display.setFont(&FreeSans9pt7b);
  String author;
  author += F("- ");
  author += quoteOfTheDay.author;

  display.drawBitmap(800, y + height - 20, quoteBottom, 64, 64, GxEPD_RED);
  
  drawRightAlignedString(author,SCREEN_WIDTH - 100,y + height + 20);
}
