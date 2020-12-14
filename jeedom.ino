String getJeedomVirtualValue(int virtualId) {
  HTTPClient http;
  String jeedomUrl;
  jeedomUrl += F("http://");
  jeedomUrl += JEEDOM_HOST;
  jeedomUrl += F("/core/api/jeeApi.php?apikey=");
  jeedomUrl += JEEDOM_API_KEY;
  jeedomUrl += F("&type=cmd&id=");
  jeedomUrl += String(virtualId);
  http.begin(jeedomUrl);

  String message;
  message += F("Récupération du virtual ");
  message += String(virtualId);
  message += F(" (GET ");
  message += jeedomUrl;
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
    String virtualValue = http.getString();
    http.end();
    String message;
    message += F("OK -> valeur = ");
    message += virtualValue;
    Serial.println(message);
    Serial.println("");
    return virtualValue;
  } else {
    String error;
    error += F("KO -> code erreur = ");
    error += String(httpCode);
    Serial.println(error);
    Serial.println("");
    return "Erreur";
  }

}

void updateJeedomVirtualValue(int virtualId, String value) {
  HTTPClient http;

  String jeedomUrl;
  jeedomUrl += F("http://");
  jeedomUrl += JEEDOM_HOST;
  jeedomUrl += F("/core/api/jeeApi.php?plugin=virtual&apikey=");
  jeedomUrl += JEEDOM_VIRTUAL_API_KEY;
  jeedomUrl += F("&type=virtual&id=");
  jeedomUrl += String(virtualId);
  jeedomUrl += F("&value=");
  jeedomUrl += value;
  http.begin(jeedomUrl);

  String message;
  message += F("Mise a jour du virtual ");
  message += String(virtualId);
  message += F(" (GET ");
  message += jeedomUrl;
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
  } else {
    String error;
    error += F("KO -> code erreur = ");
    error += String(httpCode);
    Serial.println(error);
    Serial.println("");
  }
  http.end();

}
