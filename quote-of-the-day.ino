

QuoteOfTheDay getQuoteOfTheDay() {
  HTTPClient http;
  String quoteOfTheDayUrl = "https://zenquotes.io/api/random";
  http.begin(quoteOfTheDayUrl, root_ca);

  String message;
  message += F("Récupération de la citation du jour");
  message += F(" (GET ");
  message += quoteOfTheDayUrl;
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
    String response = http.getString();
    http.end();

    Serial.println("OK");
    Serial.println("");

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
    String error;
    error += F("KO -> code erreur = ");
    error += String(httpCode);
    Serial.println(error);
    Serial.println("");
    return {error, "La direction"};
  }
}

void drawQuoteOfTheDay(QuoteOfTheDay quoteOfTheDay) {
  Serial.println("drawQuoteOfTheDay() : START");

  int y = 380;

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

  drawRightAlignedString(author, SCREEN_WIDTH - 100, y + height + 20);
  Serial.println("drawQuoteOfTheDay() : END");
}
