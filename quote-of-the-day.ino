QuoteOfTheDay getQuoteOfTheDay() {
  //
  const char* host = "https://zenquotes.io/api/random";
  //const char* host = "https://favqs.com/api/qotd";

  WiFiClientSecure client;
  client.setInsecure(); //the magic line, use with caution
  client.connect(host, 443);
  HTTPClient http;

  http.begin(client, host);
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
      return {"", ""};
    }

    return {
      doc[0]["q"],
      doc[0]["a"]
    };
  } else {
    Serial.print("Error on sending GET Request: ");
    Serial.println(httpResponseCode);
    return {"", ""};
  }
}
