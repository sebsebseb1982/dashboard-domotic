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
#include "moon.h"
#include "house.h"
#include "battery.h"
#include "status-bar.h"

// base class GxEPD2_GFX can be used to pass references or pointers to the display instance as parameter, uses ~1.2k more code
// enable or disable GxEPD2_GFX base class
#define ENABLE_GxEPD2_GFX 0

#include <GxEPD2_BW.h>
#include <GxEPD2_3C.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSans12pt7b.h>

GxEPD2_3C < GxEPD2_750c_Z90, GxEPD2_750c_Z90::HEIGHT / 2 > display(GxEPD2_750c_Z90(/*CS=*/ 15, /*DC=*/ 27, /*RST=*/ 26, /*BUSY=*/ 25)); // GDEH075Z90 880x528

WiFiClient espClient;
WiFiUDP ntpUDP;

NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 3600, 60000);

void print_wakeup_reason() {
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch (wakeup_reason) {
    case ESP_SLEEP_WAKEUP_EXT0 : Serial.println("Wakeup caused by external signal using RTC_IO"); break;
    case ESP_SLEEP_WAKEUP_EXT1 : Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
    case ESP_SLEEP_WAKEUP_TIMER : Serial.println("Wakeup caused by timer"); break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD : Serial.println("Wakeup caused by touchpad"); break;
    case ESP_SLEEP_WAKEUP_ULP : Serial.println("Wakeup caused by ULP program"); break;
    default : Serial.printf("Wakeup was not caused by deep sleep: %d\n", wakeup_reason); break;
  }
}

void setup()
{
  delay(500);
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

  //print_wakeup_reason();

  setupWifi();
  delay(5000);

  timeClient.begin();

  display.setFullWindow();
  display.firstPage();

  float batteryVoltage = getBatteryVoltage();
  updateJeedomVirtualValue(330, String(batteryVoltage));

  timeClient.update();

  if (batteryVoltage > 7.5) {
    StatusBarDatas statusBarDatas = getStatusBarDatas();
    QuoteOfTheDay quoteOfTheDay = getQuoteOfTheDay();
    Temperatures temperatures = getTemperatures();
    TwoDaysWeatherForecasts twoDaysWeatherForecasts = getWeatherForecasts();

    do {
      display.fillScreen(GxEPD_WHITE);
      drawGrid();
      drawStatusBar(statusBarDatas, batteryVoltage);
      drawChart();
      drawHouse(temperatures);
      //drawGrid2();
      drawQuoteOfTheDay(quoteOfTheDay);
      drawTwoDaysWeatherForecasts(twoDaysWeatherForecasts);
    } while (display.nextPage());
  } else {
    do {
      display.fillScreen(GxEPD_WHITE);
      drawBatteryEmpty();
    } while (display.nextPage());
  }


  display.powerOff();

  Serial.print("It is ");
  Serial.print(getFormattedTime());
  Serial.println(".");


  int refreshRateInMinutes = getRefreshRateInMinutes(batteryVoltage);

  esp_sleep_enable_timer_wakeup(refreshRateInMinutes * 60e6);
  Serial.print("Going back to sleep for ");
  Serial.print(refreshRateInMinutes);
  Serial.println(" minutes.");
  Serial.flush();
  esp_deep_sleep_start();
}

uint64_t getRefreshRateInMinutes(float batteryVoltage) {
  int refreshRate = 59;
  if (batteryVoltage < 7.8) {
    refreshRate += 60;
  }

  if (timeClient.getHours() > 0 && timeClient.getHours() < 5) {
    refreshRate += 60;
  }

  return refreshRate;
}

void loop()
{
}
