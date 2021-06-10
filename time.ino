String getFormattedTime() {
  String formattedTime;
  if(timeClient.getHours() < 10) {
    formattedTime += F("0");
  }
  formattedTime += timeClient.getHours();
  formattedTime += F(":");
  if(timeClient.getMinutes() < 10) {
    formattedTime += F("0");
  }
  formattedTime += timeClient.getMinutes();

  return formattedTime;
}
