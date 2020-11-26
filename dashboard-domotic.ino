#include <WiFi.h>
#include <HTTPClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <ArduinoJson.h>
#include <TimeLib.h>
#include <moonPhase.h>

#include "secret.h"
#include "common.h"
#include "quote-of-the-day.h"
#include "quote-img.h"
#include "weather-forecast.h"

// base class GxEPD2_GFX can be used to pass references or pointers to the display instance as parameter, uses ~1.2k more code
// enable or disable GxEPD2_GFX base class
#define ENABLE_GxEPD2_GFX 0

#define REFRESH_EVERY_N_MINUTES 30

#include <GxEPD2_BW.h>
#include <GxEPD2_3C.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSans12pt7b.h>

GxEPD2_3C < GxEPD2_750c_Z90, GxEPD2_750c_Z90::HEIGHT / 2 > display(GxEPD2_750c_Z90(/*CS=*/ 15, /*DC=*/ 27, /*RST=*/ 26, /*BUSY=*/ 25)); // GDEH075Z90 880x528

WiFiClient espClient;
WiFiUDP ntpUDP;

NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 3600, 60000);

void setup()
{
  Serial.begin(115200);

  Serial.println();
  Serial.println("setup");
  display.init(115200); // uses standard SPI pins, e.g. SCK(18), MISO(19), MOSI(23), SS(5)
  // *** special handling for Waveshare ESP32 Driver board *** //
  // ********************************************************* //
  SPI.end(); // release standard SPI pins, e.g. SCK(18), MISO(19), MOSI(23), SS(5)
  //SPI: void begin(int8_t sck=-1, int8_t miso=-1, int8_t mosi=-1, int8_t ss=-1);
  SPI.begin(13, 12, 14, 15); // map and init SPI pins SCK(13), MISO(12), MOSI(14), SS(15)
  // *** end of special handling for Waveshare ESP32 Driver board *** //
  // **************************************************************** //

  setupWifi();
  delay(3000);
  timeClient.begin();

  //display.setFullWindow();
  display.firstPage();
  do
  {
    //display.fillScreen(GxEPD_WHITE);


    drawGrid();
    //drawGrid2();
    drawQuoteOfTheDay();
    drawTwoDaysWeatherForecasts();
  }
  while (display.nextPage());
  display.powerOff();
  Serial.println("setup done");
  esp_sleep_enable_timer_wakeup(REFRESH_EVERY_N_MINUTES * 60 * 1000000);
  esp_deep_sleep_start();
}

void loop()
{
}
